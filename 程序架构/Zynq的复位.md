# Zynq的软件复位与运行



|            |                               |      |
| ---------- | ----------------------------- | ---- |
| APU        | application processing unit   |      |
| FPD_SWDT   | FPD system watchdog timer     |      |
| FPD_SRST   | FPD system reset              |      |
| APU MPCore | Cortex™-A53 MPCore processors |      |

The APU MPCore reset can be triggered by the FPD system watchdog timer (FPD_SWDT) or a software register write.   

APU MPCore重置可由FPD系统监视定时器(FPD_SWDT)或软件寄存器写入触发。但是，APU重置时不会优雅地终止对APU的请求。FPD系统重置(FPD_SRST)用于FPD系统发生灾难性故障的情况。APU重置主要用于软件调试。

#### **Programming steps for a software-generated reset:**

1. **Enable the reset request interrupt in the PMU. Write a 1 to one or more bits [APUx] in the PMU_GLOBAL.REQ_SWRST_INT_EN register.**

2. **Trigger the interrupt request. Write a 1 to one or more bits [APU{0:3}] in theREQ_SWRST_TRIG register.**

| Register Name    | Type | Description                                                  |
| ---------------- | ---- | ------------------------------------------------------------ |
| REQ_SWRST_INT_EN | WO   | Reset request interrupt enable register. A write of 1 to this location will unmask the interrupt. |
| REQ_SWRST_TRIG   | WO   | Reset request trigger register. A write of 1 to this location will set the reset status register related to this interrupt. |





# 特征

• Power on reset and system reset.  

• Independent PS reset capability while PL is still operating.

• Independent debug reset signals.

• Software identification of cause of reset from reset reason register.

![image-20250327171023878](https://picture-1344593885.cos.ap-beijing.myqcloud.com/image-20250327171023878.png)

The system reset is deasserted once the reset logic hands off control to the PMU and is asserted back when an event, such as a debug system reset, occurs that needs to assert system reset.  

![image-20250327172225212](https://picture-1344593885.cos.ap-beijing.myqcloud.com/image-20250327172225212.png)



Note: If PS_REF_CLK is to be active after POR_B pin de-assertion, then PS_REF_CLK must be stable before it is active.  



# PS_SRST_B Reset Pin During Hardware Boot  

PS_SRST_B  的输入引脚在PS_POR_B释放后被禁用，并在CSU ROM执行的第一部分保持禁用状态。

• For non-secure boot, the PS_SRST_B input is enabled before loading the FSBL into OCM memory.

• For secure boot, the PS_SRST_B input remains disabled (not enabled by CSU ROM). Secure code can enable the PS_SRST_B reset input using the CRL_APB.RESET_CTRL register.  

##### example

In this example, the PS_SRST_B reset input is held Low (asserted) while PS_POR_B is deasserted and the CSU executes its ROM code. The CSU continues to execute the ROM code (regardless of the PS_SRST_B state) until the CSU can verify if the boot is secure or non-secure by reading the boot header. For non-secure boot and PS_SRTS_B asserted, the CSU execution halts when it enables the PS_SRST_B input. For secure boot and PS_SRST_B asserted, the CSU continues to execute and the FSBL is loaded into memory because the PS_SRST_B pin remains disabled.  

| Reset Name     | Source         | Control                                                      | System Effects                                               | Subject to the PROG_GATE effect for PL? | Reset Reason       |
| -------------- | -------------- | ------------------------------------------------------------ | ------------------------------------------------------------ | --------------------------------------- | ------------------ |
| External POR   | PS_POR_B pin   | Deasserted after power up. Assert at any time with immediate affect. | Resets all logic, RAMs, and registers.Prepares device for possible secure boot.• Mode pins sampled. | No                                      | [external_por]     |
| Internal POR   | System error   | PMU_Global.ERROR_POR_{1,2}.                                  | Same as External POR except:<br />• ERROR_STATUS_{1, 2}registers unaffected. | No                                      | [internal_por]     |
| External SRST  | PS_SRST_B pin  | Device pin that is usually connected to the debugging tool.Disable RESET_CTRL [srst_dis] | Same as External POR except:Modes pins not sampled. Several registers unaffected (i.e., require a POR to reset):<br />• System error enable.<br />• PMU global persistent.<br />• CSU_status, ENC_status<br />• LOC_PWR_STATE (powerstate).<br />• RAMs not cleared. | Yes                                     | [srst]             |
| Internal SRST  | Register write | CRL_APB.RESET_CTRL [soft_reset].                             | Same as external SRST.                                       | Yes                                     | [soft]             |
| Internal SRST  | System error   | PMU_GLOBAL.ERROR_SRST_{1,2}.                                 | Same as external SRST.                                       | Yes                                     | [pmu_sys_reset]    |
| Internal SRST  | Register write | CRL_APB.RST_LPD_TOP [fpd_reset].                             | Same as external SRST except:<br />• PL and LPD unaffected.  | N/A                                     |                    |
| Internal SRST  | Register write | PMU_GLOBAL.GLOBAL_RESET [PS_ONLY_RST].                       | Same as external SRST except:<br />• PL and LPD unaffected   | Yes                                     | [psonly_reset_req] |
| Debug SRST     | DAP controller | Arm DAP.                                                     | Same as external SRST except the debug logic state is preserved.( | Yes                                     | [debug_sys]        |
| Reset Debugger | DAP controller | BLOCKONLY_RST [debug_only].                                  | Resets the CoreSight debug logic only.                       | N/A                                     | No change.         |



Notes:

1. All resets have an immediate effect. Effects are driven by reset edges and levels.

2. The PS_SRST_B pin can be enabled and disabled by writing to the CRL_APB.RESET_CTRL [srst_dis] bit.

3. RPU debug logic is not preserved.





# Reset Reason Register  

| Bit Field        | Bit  | Description                                                  |
| ---------------- | ---- | ------------------------------------------------------------ |
| external_por     | 0    | External POR; the PS_POR_B reset signal pin was asserted.    |
| internal_por     | 1    | Internal POR. A system error triggered a POR reset.          |
| pmu_sys_reset    | 2    | Internal system reset. A system error triggered a system reset. |
| psonly_reset_req | 3    | PS-only reset. Write to PMU_GLOBAL.GLOBAL_RESET [PS_ONLY_RST]. |
| srst             | 4    | External system reset; the PS_SRST_B reset signal pin was asserted. |
| soft             | 5    | Software system reset. Write to RESET_CTRL [soft_reset].     |
| debug_sys        | 6    | Software debugger reset. Write to BLOCKONLY_RST [debug_only]. |



# PS Only Reset  

When the PS must be reset without resetting the PL, the PMU (only the PMU) must manage this reset sequence. Through the error mechanism in the PMU, all of the errors can be set to cause a PS only reset. The PMU asserts a signal to the PL power domain that blocks PS_PROG_B from assertion by the CSU. This bit is controlled by the PMU and can be set at the beginning of time or during an interrupt routine. Once this bit is set in the PMU, the only difference to the reset block in the LPD between a PS-only reset and a system-reset request is that the reset block in the LPD marks a different bit in the reset reason register when the PL is not reset.  



# System-level Software Reset  

Each module in the PS has one or more software controlled resets that are asserted from the reset module to the PS block residing in the low-power or full-power domain. The resets are generated by the reset module that is in the same power domain as the consuming module. For instance, the APU resets come from the reset block in the FPD, while the Cortex®-R5F resets come from the reset block in the LPD. The reset block in the LPD is reset when there is a system-level reset. A reset applied to the reset block in the FPD resets all the blocks in the FPD.

Software can write to the FPD reset pin in register **APB_CRL.RST_LPD_TOP [FPD_RESET]** to reset the FPD logic. The PMU also has the ability to reset the FPD.

The WARMRSTREQ signal from the APU is routed to the PMU. It can be used to trigger a block reset to the APU system.



# Register Overview  

| Register Type | Register Name | Description                                                  |
| ------------- | ------------- | ------------------------------------------------------------ |
| LPD reset     | RESET_CTRL    | Reset control register. Controls miscellaneous functions with regards to triggers. |
| LPD reset     | BLOCKONLY_RST | Records the reason for the block-only reset.                 |
| LPD reset     | RESET_REASON  | Records the reason for the reset in the RESET_REASON register |
| LPD reset     | RST_LPD_TOP   | Software control register for the LPD block.                 |
| LPD reset     | RST_LPD_DBG   | Debug register for both the LPD and FPD. Only the POR can cause hardware to clear this register. During a debug_reset, the PMU resets this register. |
| LPD reset     | RST_LPD_IOU0  | Software controlled reset for the GEM.                       |
| LPD reset     | RST_LPD_IOU1  | Power-on reset type register.                                |
| LPD reset     | RST_LPD_IOU2  | Software control register for the IOU block. Each bit causes a single peripheral or part of the peripheral to be reset. |
| FPD reset     | RST_FPD_TOP   | FPD block-level software controlled reset.                   |
| FPD reset     | RST_FPD_TOP   | APU block-level software controlled resets.                  |































