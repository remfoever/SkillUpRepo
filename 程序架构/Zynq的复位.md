# Zynq的复位

## 简介

`PS复位子系统`负责处理设备外部输入并满足内部所有功能单元的重置要求。

处理系统（PS）重置序列分为三个功能区域。

1. 上电复位顺序

2. 管理系统中的其他信号以触发系统重置

3. （在软件中）重置单个功能单元的能力



## 特色

1. 上电复位和系统复位
2. PL仍在运行时，具有独立的PS复位功能
3. 独立的调试复位信号
4. 软件可以从重置原因寄存器中识别重置原因

|    术语    |             含义              | 备注 |
| :--------: | :---------------------------: | :--: |
|    APU     |  application processing unit  |      |
|  FPD_SWDT  |   FPD system watchdog timer   |      |
|  FPD_SRST  |       FPD system reset        |      |
| APU MPCore | Cortex™-A53 MPCore processors |      |



## 系统复位条件

**复位表**

| Reset Name     | Source         | Control                                                      | System Effects                                               | Subject to the PROG_GATE effect for PL? | Reset Reason       |
| -------------- | -------------- | ------------------------------------------------------------ | ------------------------------------------------------------ | --------------------------------------- | ------------------ |
| External POR   | PS_POR_B pin   | Deasserted after power up. Assert at any time with immediate affect. | Resets all logic, RAMs, and registers.Prepares device for possible secure boot.<br />• Mode pins sampled. | No                                      | [external_por]     |
| Internal POR   | System error   | PMU_Global.ERROR_POR_{1,2}.                                  | Same as External POR except:<br />• ERROR_STATUS_{1, 2}registers unaffected. | No                                      | [internal_por]     |
| External SRST  | PS_SRST_B pin  | Device pin that is usually connected to the debugging tool.Disable RESET_CTRL [srst_dis] | Same as External POR except:Modes pins not sampled. Several registers unaffected (i.e., require a POR to reset):<br />• System error enable.<br />• PMU global persistent.<br />• CSU_status, ENC_status<br />• LOC_PWR_STATE (powerstate).<br />• RAMs not cleared. | Yes                                     | [srst]             |
| Internal SRST  | Register write | CRL_APB.RESET_CTRL [soft_reset].                             | Same as external SRST.                                       | Yes                                     | [soft]             |
| Internal SRST  | System error   | PMU_GLOBAL.ERROR_SRST_{1,2}.                                 | Same as external SRST.                                       | Yes                                     | [pmu_sys_reset]    |
| Internal SRST  | Register write | CRL_APB.RST_LPD_TOP [fpd_reset].                             | Same as external SRST except:<br />• PL and LPD unaffected.  | N/A                                     |                    |
| Internal SRST  | Register write | PMU_GLOBAL.GLOBAL_RESET [PS_ONLY_RST].                       | Same as external SRST except:<br />• PL and LPD unaffected   | Yes                                     | [psonly_reset_req] |
| Debug SRST     | DAP controller | Arm DAP.                                                     | Same as external SRST except the debug logic state is preserved.( | Yes                                     | [debug_sys]        |
| Reset Debugger | DAP controller | BLOCKONLY_RST [debug_only].                                  | Resets the CoreSight debug logic only.                       | N/A                                     | No change.         |

1. 所有重置都立即生效。 效果由重置边沿和效果驱动。

2. PS_SRST_B 引脚可以通过写 CRL_APB.RESET_CTRL [srst_dis] 位使能和失能。

3. RPU 调试逻辑未被保留。 

**复位原因寄存器（Reset Reason Register  ）**

| Bit Field        | Bit  | Description                                                  |
| ---------------- | ---- | ------------------------------------------------------------ |
| external_por     | 0    | External POR; the PS_POR_B reset signal pin was asserted.    |
| internal_por     | 1    | Internal POR. A system error triggered a POR reset.          |
| pmu_sys_reset    | 2    | Internal system reset. A system error triggered a system reset. |
| psonly_reset_req | 3    | PS-only reset. Write to PMU_GLOBAL.GLOBAL_RESET [PS_ONLY_RST]. |
| srst             | 4    | External system reset; the PS_SRST_B reset signal pin was asserted. |
| soft             | 5    | Software system reset. Write to RESET_CTRL [soft_reset].     |
| debug_sys        | 6    | Software debugger reset. Write to BLOCKONLY_RST [debug_only]. |

这里软件复位只需要关注`[soft]`和`[psonly_reset_req]`两种方式。这两种方式都是属于`Internal SRST`，通过`Register write`进行复位

| 寄存器名称                             | 复位原因           | 备注 |
| -------------------------------------- | ------------------ | ---- |
| CRL_APB.RESET_CTRL [soft_reset].       | [soft]             |      |
| PMU_GLOBAL.GLOBAL_RESET [PS_ONLY_RST]. | [psonly_reset_req] |      |
|                                        |                    |      |



## PS Only Reset  

当需要仅复位 PS（Processing System）而不复位 PL（Programmable Logic）时，必须由 **PMU（Power Management Unit）** 来管理此复位序列。通过 PMU 的错误处理机制，所有错误均可配置为仅触发 PS 复位。PMU 会向 PL 电源域发送一个信号，阻止 CSU（Configuration Security Unit）拉低 `PS_PROG_B`。此控制位由 PMU 管理，可在系统初始化时或中断服务例程中设置。一旦该位被置位，对于 LPD（Low Power Domain）中的复位模块来说，**仅复位 PS** 和 **系统全局复位** 的唯一区别在于：当 PL 未被复位时，LPD 的复位模块会在复位原因寄存器中标记不同的状态位。

#### **实现机制**

- **PMU 的核心作用**：
  - 作为复位仲裁者，控制复位信号的传播范围。
  - 通过配置寄存器（如 `PMU_GLOBAL_PS_CNTRL`）关闭 `Prog_Gate`，阻止复位信号传递到 PL。
- **关键信号 `PS_PROG_B`**：
  - 通常由 CSU 控制，用于触发 PL 的重新配置（拉低时 PL 会复位）。
  - PMU 通过硬件信号强制保持 `PS_PROG_B` 为高电平，避免 PL 被意外复位。



## System-level Software Reset  

PS（Processing System）中的每个模块都有一个或多个由软件控制的复位信号，这些信号由复位模块发出，作用于位于低功耗域（LPD）或全功耗域（FPD）的 PS 模块。复位信号由与目标模块处于同一电源域的复位模块生成。例如：

- APU 的复位信号来自 FPD 中的复位模块，
- Cortex®-R5F 的复位信号来自 LPD 中的复位模块。
  当发生系统级复位时，LPD 中的复位模块会被复位；而对 FPD 复位模块的复位会重置 FPD 中的所有模块。

软件可通过写入寄存器 `APB_CRL.RST_LPD_TOP [FPD_RESET]` 来复位 FPD 逻辑。PMU 也具备复位 FPD 的能力。
来自 APU 的 `WARMRSTREQ` 信号会路由至 PMU，可用于触发 APU 系统的局部复位。

#### **1. PS 复位的层级结构**

PS 的复位分为 **电源域（Power Domain）** 和 **模块级复位**：

- **低功耗域（LPD）**：
  - 包含 Cortex-R5F（RPU）、低功耗外设等。
  - 复位源来自 LPD 内部的复位模块。
- **全功耗域（FPD）**：
  - 包含 APU（Cortex-A）、DDR 控制器、高性能外设等。
  - 复位源来自 FPD 内部的复位模块。

#### **2. 复位信号的控制方式**

| **复位类型**     | **控制方式**                                      | **影响范围**              |
| :--------------- | :------------------------------------------------ | :------------------------ |
| **系统级复位**   | 硬件全局复位（如 PS_SRST_B 引脚）或 PMU 全局复位  | PS + PL + 所有电源域      |
| **FPD 复位**     | 写 `APB_CRL.RST_LPD_TOP[FPD_RESET]` 或 PMU 触发   | APU、DDR、AXI 等 FPD 模块 |
| **APU 局部复位** | 通过 `WARMRSTREQ` 信号触发 PMU 生成 APU 复位      | 仅 APU（Cortex-A 核）     |
| **RPU 复位**     | 通过 LPD 复位模块控制（如 `RPU_LS_RST` 寄存器位） | 仅 Cortex-R5F（RPU）      |

#### **3. 关键信号与寄存器**

- **`WARMRSTREQ`**：
  - 由 APU 发出，请求 PMU 触发局部复位（如 CPU 核挂起时）。
  - 用途：调试恢复、安全隔离、动态重配置。
- **`APB_CRL.RST_LPD_TOP[FPD_RESET]`**：
  - 软件直接写入该寄存器位可复位整个 FPD（需谨慎使用）。



## PS-only Reset Sequence  

**仅PS复位的需求** 是在保持PL（可编程逻辑）运行的同时复位PS（处理系统）。这种复位可以通过 **硬件错误信号** 或 **软件寄存器写入** 触发。如果复位是由硬件错误信号引起的，则该错误信号必须同时通知PL。

仅PS复位可以作为 **系统复位的子集** 实现，但在触发复位前，需要 **优雅终止PS与PL之间的AXI事务**。以下是实现仅PS复位的步骤流程。

1. 设置 `pmu_global.PS_CNTRL[prog_gate]` 为 `1`，以阻止 PL 在 PS 复位时被复位。
2. 错误中断触发，且该错误要求仅复位 PS。此请求以中断形式发送至 PMU。
3. 为通知 PL，设置 PMU 错误标志（表示 PS-only 复位）。
4. 通过 **AMBA 隔离模块（AIB）** 阻断 FPD → PL 和 LPD → PL 的接口。
5. 如果未收到 AIB 的确认信号，PMU 应超时并继续流程。
6. 通过 AIB（在 PL 设计中）阻断 PL → FPD 和 PL → LPD 的接口。
7. 如果未收到 AIB 的确认信号，PMU 应超时并继续流程。
8. 通过写入 **PMU 全局复位请求寄存器** 发起仅 PS 复位。
9. 通过写入 `pmu_global.GLOBAL_RESET[ps_only_rst]` 位触发仅 PS 复位。此位会自动清除，并导致仅 PS 复位。
10. 释放 PS 与 PL 之间所有被隔离的信号。

**1. 仅PS复位的核心目标**

- **保持PL运行**：PL逻辑（如实时信号处理、自定义硬件加速器）不受影响。
- **复位PS**：重启ARM CPU（APU/RPU）、内存控制器、系统总线等，以恢复软件状态。

**2. 触发条件**

| **触发源**       | **行为**                                                     |
| :--------------- | :----------------------------------------------------------- |
| **硬件错误信号** | 例如APU内存访问错误、总线超时，需通过信号通知PL（如中断或状态寄存器）。 |
| **软件主动触发** | 写入PMU或复位控制寄存器（如`PMU_GLOBAL_RST_CTRL[PS_ONLY_RST]`）。 |

**3. 关键挑战：AXI事务的优雅终止**

PS与PL通过AXI总线通信，突然复位PS可能导致：

- **PL侧挂起**：未完成的AXI事务阻塞PL逻辑。
- **数据丢失**：传输中的数据损坏。

**解决方案**：

1. **暂停PS新请求**：关闭CPU到PL的AXI主端口。
2. **等待未完成事务完成**：检查AXI桥状态寄存器，确认所有事务结束。
3. **复位PS**：确保无遗留总线冲突后再触发复位。



### **软件需主动设置的步骤**

以下步骤需要 **软件配置寄存器或触发动作**（其余由硬件或 PMU 自动完成）：

| **步骤** | **操作**                                             | **软件需参与？** | **说明**                                                     |
| :------- | :--------------------------------------------------- | :--------------- | :----------------------------------------------------------- |
| 1        | 设置 `pmu_global.PS_CNTRL[prog_gate] = 1`            | **是**           | 关闭复位传播到 PL 的路径。                                   |
| 2        | 错误中断触发 PS-only 复位请求                        | 否               | 硬件自动触发（如 APU 内存错误）。                            |
| 3        | 设置 PMU 错误标志通知 PL                             | **是**           | 写入 PMU 错误状态寄存器（如 `PMU_ERROR_STATUS`）。           |
| 4-7      | 通过 AIB 隔离 PS-PL 接口（双向）                     | **部分**         | 软件需启动隔离流程，但超时处理由 PMU 硬件完成。              |
| 8        | 写入 PMU 全局复位请求寄存器                          | **是**           | 写入复位请求寄存器（如 `PMU_GLOBAL_RESET_REQ`）。            |
| 9        | 写入 `pmu_global.GLOBAL_RESET[ps_only_rst]` 触发复位 | **是**           | 此位写入后自动清除，复位由硬件执行。                         |
| 10       | 释放 PS-PL 隔离信号                                  | **是**           | 复位完成后，软件需重新使能 AXI 通信（如清除 AIB 隔离标志）。 |

------

### **关键点说明**

1. **软件必须主动配置的寄存器**：
   - `PS_CNTRL[prog_gate]`（步骤 1）
   - PMU 错误标志（步骤 3）
   - PMU 复位请求寄存器（步骤 8-9）
   - 隔离信号释放（步骤 10）
2. **硬件自动完成的部分**：
   - 错误中断触发（步骤 2）
   - AIB 隔离超时处理（步骤 5、7）
   - `ps_only_rst` 位自动清除（步骤 9）
3. **PL 侧的配合**：
   - PL 需集成 AIB 模块以响应隔离请求（步骤 4-7）。
   - 若 PL 未正确响应，PMU 超时机制可保证流程继续（但可能残留总线冲突风险）。







## FPD Reset Sequence  

待补充





## RPU Reset Sequence  

待补充



























