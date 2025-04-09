# zynq相关

# 术语

|  术语  |  含义  |  备注  |
| --- | --- | --- |
|  VTC  |  Video Timing Controller  |   |
|   |   |   |
|   |   |   |

# 关于CACHE

在Zynq SoC中，PS包含一个多级缓存体系结构，包括指令缓存（ICache）、数据缓存（DCache）和二级缓存（L2 Cache）。这些缓存用于存储最近使用的数据和指令，以便快速访问。然而，在某些情况下，例如当PL通过DMA控制器直接访问PS内存时，就需要解决缓存一致性问题。

DMA操作：DMA可以在没有CPU干预的情况下直接在内存之间移动数据。如果DMA读取或写入的数据位于缓存中，则可能导致缓存中的数据与物理内存中的数据不一致。

共享内存：如果PS和PL共享相同的内存空间，并且两者都在同时访问这段内存，则必须确保它们看到的数据是一致的。\[1\]([https://blog.csdn.net/qq\_45355365/article/details/141125433](https://blog.csdn.net/qq_45355365/article/details/141125433))

如果使能了cache写入的DDR的数据可能没有办法第一时间被PS感知，可以通过

```c
 Xil_DCacheDisable();
```

或者mem\_2\_cache的方式，待补充

把缓存刷新到DDR

void Xil\_DCacheFlushRange(volatile u32 \*Addr, u32 Size);

Addr: 指向要刷新的数据缓存区域的起始地址。

Size: 要刷新的数据缓存区域的大小（以字节为单位）。

这个函数将确保从Addr开始、长度为Size的内存区域中的所有修改都被写回到主内存，并且任何未决的读取操作也被完成。

# 关于中断

在FreeRtos下开发中断需要注意如下事项：

1.  **需要通过创建的任务中执行配置中断；**
    
2.  **中断控制器不能自己初始化**
    
3.  **中断处理函数实现时的逻辑如下，先关闭中断，然后读取中断相关标记完毕后，清除标记，进行处理，然后使能中断；因为我在某次测试的时候**
    

```c
VOID WX_Camera_ProcAxiGpioInterrupt(VOID *CallbackRef) 
{
     // 关闭中断
      XGpio_InterruptDisable(axiGpioPtr, AXIGPIO_CHANNEL_1);
      // 读中断标记
      UINT32 isr = XCAMERA_ReadReg(WX_CAMERA_INTR_STATUS_REG_OFFSET);
      // 清理中断
       XGpio_InterruptClear(axiGpioPtr, AXIGPIO_CHANNEL_1);

      // TODO 中断处理函数
  
      // 使能中断
      XGpio_InterruptEnable(axiGpioPtr, AXIGPIO_CHANNEL_1);
}
```

```c
vPortInstallFreeRTOSVectorTable:

	/* Set VBAR to the vector table that contains the FreeRTOS handlers. */
	ldr	r0, =_freertos_vector_table
	mcr	p15, 0, r0, c12, c0, 0
	dsb
	isb
	bx lr
```

这段汇编代码定义了一个名为 `vPortInstallFreeRTOSVectorTable` 的函数，其作用是将 FreeRTOS 的中断向量表安装到 ARM Cortex-M 处理器的向量表基址寄存器（VBAR）中。以下是对每一行代码的详细解释：

`.type vPortInstallFreeRTOSVectorTable, %function`:

这一行声明了 `vPortInstallFreeRTOSVectorTable` 是一个函数类型。`.type` 是汇编器指令，用于指定符号的类型。

`vPortInstallFreeRTOSVectorTable:`:

这是函数的入口标签，表示函数的开始。

`ldr r0, =_freertos_vector_table`:

这条指令将 `_freertos_vector_table` 的地址加载到寄存器 `r0` 中。`_freertos_vector_table` 是 FreeRTOS 的中断向量表的起始地址。

`mcr p15, 0, r0, c12, c0, 0`:

这是一条协处理器指令，用于将 `r0` 寄存器中的值写入到 VBAR（向量表基址寄存器）中。VBAR 是 ARM Cortex-M 处理器中用于指定中断向量表基址的寄存器。

`p15` 是协处理器编号，`c12` 是 VBAR 的寄存器编号，`c0` 是操作码，`0` 是选项。

**关于1**，是因为创建任务会执行`vPortInstallFreeRTOSVectorTable`函数，该函数会安装freeRTOS的中断向量表，如果不创建任务则会使用默认的中断向量表，导致死循环；

关于2，是因为任务创建的会创建一个中断控制器，我们不用重复创建中断控制器，一旦重复创建中断控制器，则会导致之前的中断不好用；在代码中extern全局的中断控制器, 使用这个中断控制器对中断进行配置

```c
extern XScuGic xInterruptController;
```

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/v9kqDANPw8zaOVxe/img/6ae3678d-80f7-492b-8568-0d9475121605.png)

# 中断

## 软件中断

```c
/* Initialize the soft interrupt for core inter communication */
UINT32 WX_CoreInterCom_InitSoftIntr(WxCoreInterCom *this, WxCoreInterComCfg *cfg)
{
    this->intcInst = WX_GetScuGicInstance();
    if (this->intcInst == NULL) {
        wx_excp_cnt(WX_EXCP_CORE_INTER_COM_NO_INTC);
        return WX_RET_ERR_NO_INTC;
    }
    UINT16 intrId = this->softIntrId2CoreIdx[this->coreIdx];
    INT32 ret = XScuGic_Connect(this->intcInst, intrId,
                                (Xil_InterruptHandler)WX_CoreInterCom_SoftIntrHandler, this);
    if (ret != XST_SUCCESS) {
        wx_excp_cnt(WX_EXCP_CORE_INTER_COM_INTC_CONNECT_FAIL);
        return WX_RET_ERR_INTC_CONNECT_FAIL;
    }
    /* 7:3 is the priority, 0:2 is the trigger type */
    XScuGic_SetPriorityTriggerType(this->intcInst, intrId, 0x90, 0x03);
    XScuGic_Enable(this->intcInst, intrId);
    /* Initialize the soft interrupt */
    return WX_SUCCESS;
}


```

# 汇编指令

[asm volatile](https://www.baidu.com/s?rsv_dl=re_dqa_generate&sa=re_dqa_generate&wd=%3Cstrong%3Easm%3C%2Fstrong%3E%20%3Cstrong%3Evolatile%3C%2Fstrong%3E&rsv_pq=9c98a51b000ace39&oq=__asm__%20__volatile__&rsv_t=022d4Fy2N+x3fSSIMLuUU8OAihn3QKCHboUgxz3qWV5gMbjo7fJqhPjoLWyr8QtFEmZZZZp+klGm&tn=49055317_59_hao_pg&ie=utf-8)是GCC编译器中用于在C或C++代码中嵌入汇编指令的一种方式。它允许开发者直接在高级语言代码中插入汇编代码，以实现更高效的代码执行或直接操作硬件。

### 基本用法

`__asm__ __volatile__`的基本语法如下：

```c
__asm__ __volatile__("汇编指令" : 输出操作数 : 输入操作数 : 破坏描述);

```

*   汇编指令‌：这是要执行的汇编代码。
    
*   输出操作数‌：定义了汇编指令的输出结果，格式为“限定符 变量名”。例如，“=r”表示输出到通用寄存器。
    
*   输入操作数‌：定义了传递给汇编代码的C变量，格式为“限定符 变量名”。例如，“m”表示直接操作内存中的变量。
    
*   破坏描述‌：描述汇编代码可能破坏的寄存器或内存，格式为“破坏的寄存器或内存”。例如，“memory”表示汇编代码可能会修改内存。
    

### 示例代码

以下是一个简单的示例，展示了如何在C代码中使用`__asm__ __volatile__`：

```c
main() {
    int a = 10;
    __asm__ __volatile__("movl %0, %1" : "=r"(a) : "r"(a+1));
    return 0;
}

```

这段代码将变量`a`的值增加1。这里，`"%0"`和`"%1"`是占位符，分别代表输出操作数和输入操作数。`"=r"(a)`表示`a`是一个输出操作数，将被放入通用寄存器中；`"r"(a+1)`表示`a+1`是一个输入操作数，也将被放入通用寄存器中。

关于%0和%1的是输入占位符号，具体代表哪一个，需要看有几个参数，由于上文中同时存在输入和输出，所以%0表示输出，%1表示输如；

|  指令  |  含义  |  解释  |
| --- | --- | --- |
|  msr  |  Move to Special register from Register”  |  将一个通用寄存器的值传送到特殊寄存器中  |
|   |   |   |

寄存器R0-R3

## 符号表解读

```c
00000000011ef5f0 g     O .data	0000000000000008 XGpioPs_ConfigTable
0000000000055df8 g     F .text	0000000000000134 XQspiPsu_CfgInitialize
000000000033c6c0 g     .rodata1	0000000000000000 __rodata1_end
000000000005a9a0 g     F .text	00000000000000cc XUartPs_GetOptions
0000000000048238 g     F .text	0000000000000084 i2c_reg16_write
```

每行的信息解释如下

```plaintext
地址  符号类型  所在节区  符号大小  符号名
```

#### 1. 地址（Address）

这是符号在内存中的虚拟地址。例如 `0000000008c70f80` 就是 `_end` 符号的地址。在程序加载到内存运行时，这个地址指示了符号在内存中的具体位置。

#### 2. 符号类型（Symbol Type）

*   `g`：表示全局符号（Global Symbol），意味着该符号在整个程序中是可见的，可以被其他目标文件引用。
    
*   常见的其他符号类型还有：
    
    *   `l`：本地符号（Local Symbol），只在定义它的文件内可见。
        
    *   `u`：未定义符号（Undefined Symbol），表示该符号在当前文件中被引用，但定义在其他文件中。
        
    *   `T`：代码段（`.text`）中的全局符号，通常是函数。
        
    *   `D`：数据段（`.data`）中的全局符号，通常是已初始化的全局变量。
        
    *   `B`：未初始化数据段（`.bss`）中的全局符号，通常是未初始化的全局变量。
        

#### 3. 所在节区（Section）

节区是 ELF 文件中具有特定用途的一段数据区域。

*   `.stack`：栈相关的节区，栈用于存储函数调用的局部变量、返回地址等信息。`_end` 符号通常标记着某个段的结束，这里可能是栈区域的结束。
    
*   `.text`：代码段，存放程序的可执行指令。像 `WX_Camere_ResetSensorByGpio`、`WX_XUartNs550_SendDataHandler` 等符号都在 `.text` 节区，说明它们是函数。
    
*   `.data`：数据段，存放已初始化的全局变量和静态变量。例如 `g_wxCanMasterCfg` 就在 `.data` 节区，它是一个已初始化的全局变量。
    
*   `.rodata1`：只读数据段，用于存放只读数据，如常量字符串等。`__rodata1_end` 标记了这个只读数据段的结束。
    

#### 4. 符号大小（Size）

表示符号占用的字节数。例如 `WX_Camere_ResetSensorByGpio` 的大小是 `0000000000000050` 字节，即 80 字节，这意味着该函数的代码占用 80 字节的内存空间。

#### 5. 符号名（Symbol Name）

符号的具体名称，用于标识程序中的函数、变量等。如 `_end`、`WX_Camere_ResetSensorByGpio`、`g_wxCanMasterCfg` 等。

## 内存屏障

```plaintext
DMB         ; 数据内存屏障
DSB         ; 数据同步屏障
ISB         ; 指令同步屏障

/* Instruction Synchronization Barrier */
#define isb() __asm__ __volatile__ ("isb sy")   

/* Data Synchronization Barrier */
#define dsb() __asm__ __volatile__("dsb sy")  

/* Data Memory Barrier */
#define dmb() __asm__ __volatile__("dmb sy")  ---  防止指令乱序

```

# 寄存器

## 当前程序状态寄存器（CPSR）

ARM 的程序状态寄存器（Program Status Register）是 ARM 处理器中非常重要的寄存器，用于存储与处理器当前状态相关的各种信息。主要包括当前程序状态寄存器（CPSR，Current Program Status Register）和备份程序状态寄存器（SPSR，Saved Program Status Register），下面为你详细介绍：

### 当前程序状态寄存器（CPSR）

CPSR 是一个 32 位的寄存器，在所有 ARM 处理器模式下都可以访问。它包含了条件码标志、中断使能位、处理器模式等重要信息，控制着处理器的当前操作和行为。CPSR 的具体位分配如下：

#### 条件码标志位（31 - 28 位）

N（Negative）：符号标志位。当运算结果的最高位（符号位）为 1 时，N 被置为 1，表示结果为负数；否则为 0，表示结果为正数或零。

Z（Zero）：零标志位。若运算结果为 0，则 Z 被置为 1；否则为 0。

C（Carry）：进位标志位。在加法运算中，当产生进位时 C 置为 1；在减法运算中，当产生借位时 C 清 0。此外，在移位操作中，C 保存最后移出的位。

V（Overflow）：溢出标志位。当算术运算结果发生溢出时，V 被置为 1；否则为 0。

这些条件码标志位通常用于条件分支指令，根据不同的标志位组合来决定程序的执行流程。例如，`BEQ`（Branch if Equal）指令会检查 Z 标志位，如果 Z = 1，则执行分支操作。

#### 控制位（7 - 0 位）

**BIT7**      **0x80**

I（IRQ disable）：中断禁止位。当 I = 1 时，禁止外部中断（IRQ）；当 I = 0 时，允许外部中断。

**BIT6     0x40**

F（FIQ disable）：快速中断禁止位。当 F = 1 时，禁止快速中断（FIQ）；当 F = 0 时，允许快速中断。

**BIT5     0x20**

T（Thumb state）：状态位。在 ARMv4 及以上版本中，T 位用于区分 ARM 状态和 Thumb 状态。当 T = 0 时，处理器处于 ARM 状态，执行 32 位的 ARM 指令；当 T = 1 时，处理器处于 Thumb 状态，执行 16 位的 Thumb 指令。

**BIT4:0**

 M\[4:0\]（Mode bits）：模式位。用于定义处理器的工作模式，不同的模式对应不同的权限和寄存器组。具体模式如下：

|  M\[4:0\]  |  模式名称  |  描述  |
| --- | --- | --- |
|  10000  |  User (USR)  |  正常用户模式，程序正常执行的模式  |
|  10001  |  FIQ  |  快速中断模式，用于处理快速中断请求  |
|  10010  |  IRQ  |  外部中断模式，用于处理普通中断请求  |
|  10011  |  Supervisor (SVC)  |  管理模式，操作系统使用的特权模式  |
|  10111  |  Abort (ABT)  |  数据或指令预取中止模式，用于处理存储器访问异常  |
|  11011  |  Undefined (UND)  |  未定义指令模式，用于处理未定义的指令  |
|  11111  |  System (SYS)  |  系统模式，运行特权级的操作系统任务  |

读cpsr的C定义

```c
#if defined (versal) && !defined(ARMR5) && EL3
/*
 * Cortexa72 processor in versal is coupled with GIC-500, and GIC-500 supports
 * only FIQ at EL3. Hence, tweaking this macro to always disable FIQ
 * ignoring argument passed by user.
 */

#define read_cpsr mfcpsr
#elif defined (__GNUC__) || defined (__ICCARM__)
#define read_cpsr mfcpsr
#else
#define read_cpsr mfcpsr
#endif
```

### 备份程序状态寄存器（SPSR）

SPSR 也是一个 32 位的寄存器，它的作用是在异常发生时保存 CPSR 的当前值，以便在异常处理结束后恢复处理器的状态。每个异常模式（除了用户模式和系统模式）都有一个对应的 SPSR，当进入异常模式时，硬件会自动将 CPSR 的值复制到相应的 SPSR 中；当异常处理结束，从异常模式返回时，再将 SPSR 的值恢复到 CPSR 中。

### 操作程序状态寄存器的指令

在 ARM 汇编中，可以使用以下指令来操作程序状态寄存器：

MRS（Move from Special register to Register）：用于将 CPSR 或 SPSR 的值传送到通用寄存器中。例如：

```asm
MRS R0, CPSR  ; 将 CPSR 的值传送到 R0 寄存器

```

MSR（Move to Special register from Register）：用于将通用寄存器的值传送到 CPSR 或 SPSR 中。例如：

```asm
MSR CPSR, R0  ; 将 R0 寄存器的值传送到 CPSR 中

```

通过这些指令，程序员可以方便地读取和修改程序状态寄存器的值，从而控制处理器的行为和状态。

### C读取当前程序状态寄存器

```c

register u32 Reg __asm("cpsr");  // 读
mtcpsr((Reg) & (~((Mask) & XIL_EXCEPTION_ALL))); // 写
```

# 相机读处理流程

1.  开始
    
2.  配置相机
    
3.  配置中断
    
4.  循环等待中断产生
    

初始配置

使能A地址；

中断服务函数：

1.  读清状态寄存器，如果状态不为0则发送消息到任务，否则记录异常；
    

任务处理

任务在收到消息后进行如下处理：

如果状态A有效，则

使能B地址，处理A图片；

如果状态B有效，则

使能A地址，处理B图片

# 关于断言

提供的断言函数，如果不满足条件，则会调用设置的断言不满足处理函数：

```c
Xil_AssertSetCallback
```

```c
typedef void (*Xil_AssertCallback) (const char8 *File, s32 Line);
```

```c
/* Trigger FW Error0 */
	XPfw_RMW32(PMU_LOCAL_PMU_SERV_ERR, PMU_LOCAL_PMU_SERV_ERR_FWERR0_MASK,
			PMU_LOCAL_PMU_SERV_ERR_FWERR0_MASK);
```

# 打印程序运行轨迹

```c
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

void print_task_runtime_stats(void) {
    TaskStatus_t *pxTaskStatusArray;
    UBaseType_t uxArraySize, x;
    unsigned long ulTotalRunTime;

    // 获取当前任务数量
    uxArraySize = uxTaskGetNumberOfTasks();

    // 分配内存以存储任务状态
    pxTaskStatusArray = pvPortMalloc(uxArraySize * sizeof(TaskStatus_t));

    if (pxTaskStatusArray != NULL) {
        // 获取任务状态信息
        uxArraySize = uxTaskGetSystemState(pxTaskStatusArray, uxArraySize, &ulTotalRunTime);

        // 打印表头
        printf("Task Name\t\tState\t\tRuntime\t\tStack High Watermark\n");
        printf("------------------------------------------------------------\n");

        // 打印每个任务的信息
        for (x = 0; x < uxArraySize; x++) {
            printf("%-16s\t", pxTaskStatusArray[x].pcTaskName);  // 任务名称
            switch (pxTaskStatusArray[x].eCurrentState) {       // 任务状态
                case eRunning:   printf("Running\t\t"); break;
                case eReady:    printf("Ready\t\t"); break;
                case eBlocked:  printf("Blocked\t\t"); break;
                case eSuspended:printf("Suspended\t"); break;
                case eDeleted: printf("Deleted\t\t"); break;
                default:         printf("Unknown\t\t"); break;
            }
            printf("%lu\t\t", pxTaskStatusArray[x].ulRunTimeCounter); // 运行时间
            printf("%u\n", pxTaskStatusArray[x].usStackHighWaterMark); // 堆栈高水位线
        }

        // 释放内存
        vPortFree(pxTaskStatusArray);
    }
}
```

vTaskList(pcWriteBuffer);

下面的函数是打印程序栈信息

```c
void print_call_stack() {
  // 获取当前任务的栈指针
  TaskHandle_t mymy = xTaskGetCurrentTaskHandle();
  volatile StackType_t	*pStack = mymy;

  // 打印调用栈
  printf("Call stack:\n");
  for (int i = 0; i < 10; i++) { // 假设最多打印 10 层调用栈
    uint32_t return_address = pStack[i];
    printf("  [%d] 0x%08lx\n", i, return_address);
  }
}

```

软件复位

NVIC\_SystemReset(); // 需要包含相应的头文件 #include "stm32f4xx.h"

# 关于HDMI视频输出相关的编程

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/v9kqDANPw8zaOVxe/img/4d2d77f8-6718-4ac8-aadc-90d95c248db9.png)

ZYNQ视频输出涉及三个重要的IP核

1.  Video Timing Controller(VTC)
    
2.  AXI4-Stream to Video out
    
3.  Video DMA
    

## VTC

VTC核本质上是一个时许发生其，用于产生显示器输出所需要的时许信号

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/v9kqDANPw8zaOVxe/img/9478dc75-c459-4330-acdf-cdaa5c09e16d.png)

其中

Optional AXI4-Lite Control Interface : 用于通过AXI总线实时动态更换VTC核的参数

Detector Interface : 图中的Video Timing (input) Interface，探测器接口，用于捕捉视频时序然后处理

Generator Interface : 图中Video Timing (input) Interface，用于生成的视频时序

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/v9kqDANPw8zaOVxe/img/e6fb8c9e-c280-4347-b9c7-c6e0fccf69f0.png)

## vDMA的配置

1.  实例化VDMA， 需要提前准备好VDMA的设备ID(XPAR\_AXIVDMA\_0\_DEVICE\_ID)， 从配置中我们可以获取支持缓存的帧个数（Config\->MaxFrameStoreNum)
    

```c
XAxiVdma_Config *XAxiVdma_LookupConfig(u16 DeviceId);
int XAxiVdma_CfgInitialize(XAxiVdma *InstancePtr, XAxiVdma_Config *CfgPtr,
				UINTPTR EffectiveAddr);
```

2.  配置读通道，调用下述函数对通道支持的帧个数进行配置
    

```c
int XAxiVdma_SetFrmStore(XAxiVdma *InstancePtr, u8 FrmStoreNum, u16 Direction)
```

3.  设置帧计数器，仅用于测试观察(可选)
    

```c
    XAxiVdma_FrameCounter FrameCfg;
    FrameCfg.ReadFrameCount = ReadCount;
    FrameCfg.WriteFrameCount = WriteCount;
    FrameCfg.ReadDelayTimerCount = DELAY_TIMER_COUNTER;
    FrameCfg.WriteDelayTimerCount = DELAY_TIMER_COUNTER;

    Status = XAxiVdma_SetFrameCounter(&AxiVdma, &FrameCfg);
    if (Status != XST_SUCCESS) {
        xil_printf("Set frame counter failed %d\r\n", Status);

        if (Status == XST_VDMA_MISMATCH_ERROR)
            xil_printf("DMA Mismatch Error\r\n");

        return XST_FAILURE;
    }

```

4.  **对vDMA实例进行配置**
    
    1.  配置vDMA图像的分辨率，和步长
        

```c
int XAxiVdma_DmaConfig(XAxiVdma *InstancePtr, u16 Direction,
                       XAxiVdma_DmaSetup *DmaConfigPtr);
```

其中配置的结构体定义如下

```c
/**
 * The XAxiVdma_DmaSetup structure contains all the necessary information to
 * start a frame write or read.
 *
 */
typedef struct {
    int VertSizeInput;      /**< Vertical size input */
    int HoriSizeInput;      /**< Horizontal size input */
    int Stride;             /**< Stride */
    int FrameDelay;         /**< Frame Delay */

    int EnableCircularBuf;  /**< Circular Buffer Mode? */
    int EnableSync;         /**< Gen-Lock Mode? */
    int PointNum;           /**< Master we synchronize with */
    int EnableFrameCounter; /**< Frame Counter Enable */
    UINTPTR FrameStoreStartAddr[XAXIVDMA_MAX_FRAMESTORE];
                            /**< Start Addresses of Frame Store Buffers. 帧缓冲区的地址 */
    int FixedFrameStoreAddr;/**< Fixed Frame Store Address index， 存储索引 */
    int GenLockRepeat;      /**< Gen-Lock Repeat? */
    u8 EnableVFlip;	    /**< Vertical Flip state */
} XAxiVdma_DmaSetup;
```

XAxiVdma\_DmaSetup配置参数详解

|  参数  |  **解释**  |  **备注**  |
| --- | --- | --- |
|  VertSizeInput  |  表示输入视频帧的垂直尺寸，也就是视频帧的高度，单位是行。例如，对于一个 1080p（1920×1080）的视频，`VertSizeInput`的值就应该设置为 1080。  |  填写图像的像素高度  |
|  HoriSizeInput  |  代表输入视频帧的水平尺寸，也就是视频帧在水平方向上所包含的数据尺寸, 单位字节  |  计算HoriSizeInput值： 对于RGB888格式：HoriSizeInput = 水平像素数 × 3 对于YUV422格式：HoriSizeInput = 水平像素数 × 2 对于灰度图像：HoriSizeInput = 水平像素数 × 1  |
|  Stride  |  行缓存的大小，需要大于图像一行的数据个数  |   |
|  FrameDelay  |   |   |
|  EnableCircularBuf  |  用于配置帧缓冲区之间的步幅（stride），即一行像素的字节数。  |  **1-表示为循环读写模式；0-表示固定地址模式，固定读某个索引对应的地址中的图片；**  |
|  EnableSync  |   |   |
|  PointNum  |   |   |
|  EnableFrameCounter  |   |   |
|  FrameStoreStartAddr\[\]  |   |   |
|  FixedFrameStoreAddr  |   |   |
|  GenLockRepeat  |   |   |
|  EnableVFlip  |   |   |

### 寄存器

|   |   |   |
| --- | --- | --- |
|  Park Pointer Register  |  XAXIVDMA\_PARKPTR\_OFFSET  |  指定  |
|   |   |   |

### API介绍

|  **函数**  |  **说明**  |  **备注**  |
| --- | --- | --- |
|  XAxiVdma\_StartParking  |  启动 VDMA（Video Direct Memory Access，视频直接内存访问）的停车模式（Parking Mode），在停车模式下，VDMA 会持续从指定的帧缓冲区（由 `FrameIndex` 指定）读取或写入数据，而不会在不同的帧缓冲区之间切换，这在一些需要持续显示或采集同一帧数据的应用场景中非常有用。 `int FrameIndex`： 指定要停车的帧缓冲区的索引。帧缓冲区通常是一段连续的内存区域，用于存储视频帧数据。这个索引值用于指定 VDMA 要持续访问的是哪个帧缓冲区。 `**u16 Direction**`：指定数据传输的方向，有两种可能的值： *   `XAXIVDMA_READ`：表示从内存（帧缓冲区）读取数据到视频外设，通常用于视频显示。      *   `XAXIVDMA_WRITE`：表示从视频外设写入数据到内存（帧缓冲区），通常用于视频采集。       |  **调用该函数前需要配置**  |
|  XAxiVdma\_DmaStop  |  **停止搬数**  |   |
|  XAxiVdma\_DmaStart  |  配置好DMA后，启动搬数caozuo  |   |
|  XAxiVdma\_IntrEnable  |  使能读/写通道的中断  |  数据传输完毕会触发中断  |
|  XAxiVdma\_SetCallBack  |  设置不同中断的处理函数  |  XAXIVDMA\_HANDLER\_GENERAL - 读写完成 XAXIVDMA\_HANDLER\_ERROR - 出现错误  |
|  XAxiVdma\_DmaSetBufferAddr  |  设置缓存的数据的地址  |  需要和channel的个数保持一致  |
|  XAxiVdma\_DmaConfig  |  配置VDMA  |  配置参数详见上节介绍  |

**什么时候会触发中断呢？每一组地址读完就会触发中断；**

**相机的图像是B, G, R**

# 定时器

软件定时器

|   |   |   |
| --- | --- | --- |
|  xTimerIsTimerActive  |   |   |
|   |   |   |

## TTC

|   |   |   |
| --- | --- | --- |
|  XTtcPs\_CalcIntervalFromFreq  |  给定一个频率，计算频率所需要的分频系数和计数间隔，用于定时器配置  |   |
|  XTtcPs\_IsStarted  |  是否启动  |   |

# ECC

Error Correcting Code关于ECC的一些资料整理

The controller supports **single-bit single-error correction**, double-error detection-error 

correction code (SEC/DED ECC). An **ECC lane** is defined as a word of data, of width equal to 

the SDRAM width, where the ECC calculations are performed. **One ECC byte** is added per 

ECC lane. The DFI interface transfers four ECC lanes of data in each clock cycle. The **DDRC** 

performs the following functions.（通过lane计算了ECC byte）

• On writes, the ECC is calculated across each ECC lane, and the resulting ECC code is 

written as an additional byte along with the data in the ECC lane . This additional ECC byte is always written to the uppermost byte (or bits \[71:64\]). （附加的8字节和数据一起写入)。

• On reads, the ECC lane including the ECC byte is read from the SDRAM and is then 

decoded. A check is performed to verify that the ECC byte is as expected, based on the 

data in the ECC lane. If it is correct, the data is sent to the processing system as normal. 

If it is not correct it executes steps as described in the section on **page 445**. （读的时候进行校验）

• On read-modify-write operations, first a read is performed. The read data is then 

combined with the write data, making use of the write mask received to over-write 

certain bytes of the data that are read. The ECC is then calculated on the resulting word 

(per ECC lane), and the write is performed.

The ECC that is calculated and decoded by the **ECC engine** is transferred on a single edge of 

the DQ bus. When the input data to the ECC engine is less than 64 bits, padded zeros are 

applied to the data to make it into a 64-bit bus, before the data is sent for encoding or 

decoding. Table 17-4 shows the number of ECC and pad bits that are applicable in the 

various bus width scenarios.（数据不够64bit会补充够64bit进行计算）

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/v9kqDANPw8zaOVxe/img/10a1f94a-e6a8-45de-9fdf-3ea5a9b16e0c.png)

In the half bus-width case, during the ECC encoding phase, data is first split into multiple 

cycles, padding is added as required, and it is then sent through the ECC engine. On the 

decoder side, the incoming data from PHY is sent through the ECC decoder, with padding 

added as required. The data gathering for half bus width mode is done after the data has 

passed through the ECC decoder.

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/v9kqDANPw8zaOVxe/img/f63437b9-67e3-4ced-b82d-4b586f8715cc.png)

对于x16的内存条，需要5个芯片颗粒，组成72bit的宽度，最后一个是8bit？

## DDR DRAM Pins

The DDR I/O pins are located on **bank 504** and can have a 32-bit or 64-bit data path to the 

DRAMs depending on the device type. Bytes 0 to 3 correspond to 32-bit data and bytes 0 

to 7 correspond to 64-bit data. **Byte 8 refers to the ECC bits.** The pins are summarized in 

Table 17-3. See AXI DMA v7.1 LogiCORE IP Product Guide: Vivado Design Suite (PG201) 

\[Ref 18\] for pin assignments.

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/v9kqDANPw8zaOVxe/img/3b4e684b-4a37-451b-b9d5-6b12bc8c298f.png)

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/v9kqDANPw8zaOVxe/img/47390fbb-1e4a-4512-9e66-fc350b24fe21.png)

## 中断源

Several events in the DDR memory controller can assert **IRQ 144.** The interrupts from the 

following sources are managed by the DDR\_QOS\_CTRL.QOS\_IRQ\_{STATUS, MASK} registers.

*   Correctable ECC error \[DDR\_ECC\_CORERR\].
    
*   Uncorrectable ECC error.
    

All interrupts from the list, except for DFI initialization complete, must be clear in both the 

QoS controller and DDR controller by writing to their respective clear registers. The steps 

that are required for clearing interrupts are listed.

1. Clear the interrupt in the DDR controller by writing to the respective clear register.

2. Clear the interrupt in the QoS controller by writing to the 

DDR\_QOS\_CTRL.qos\_irq\_status register.

# 常见问题定位分析

## 运行时提示 Task initTask overflowed its stack

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/v9kqDANPw8zaOVxe/img/21fa2932-8409-450a-8d19-8137f85f8000.png)

提示该问题的代码对应代码：

```c
/* This default stack overflow hook will stop the application for executing.  It
is declared as a weak symbol to allow the application writer to override this
default by providing their own implementation in the application code. */
void vApplicationStackOverflowHook( TaskHandle_t xTask, char *pcTaskName )
{
/* Attempt to prevent the handle and name of the task that overflowed its stack
from being optimised away because they are not used. */
volatile TaskHandle_t xOverflowingTaskHandle = xTask;
volatile char *pcOverflowingTaskName = pcTaskName;

	( void ) xOverflowingTaskHandle;
	( void ) pcOverflowingTaskName;

	xil_printf( "HALT: Task %s overflowed its stack.", pcOverflowingTaskName );
	portDISABLE_INTERRUPTS();
	for( ;; );
}
```

# 杂记待整理：

**显示器分辨率：**VMODE\_1920x1080

**修改环回对代码的影响，无**

**修改模式对代码的影响**

**以较大的分辨率显示图片，图片会处于左上角，比例显示，如下所示：**

VMODE\_800x600 **按照**VMODE\_1280x1024;去显示

![lQDPKHXUhN1Zi4nNBaDNB4CwyGPGCu1GbmAHl6al3ldQAA_1920_1440.jpeg](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/v9kqDANPw8zaOVxe/img/545993c1-3d41-4e26-9597-a4ceaacb1e77.jpeg)

```c
dispPtr->vMode = VMODE_1280x1024;
```

VTC的时序如何计算？

两个中断；

VDMA什么时候触发呢？

VTC的中断什么时候触发呢？

# SPI (PS-EMIO)

SPI Interface