# Zynq 的镜像启动

# 术语

|      |                             |      |
| ---- | --------------------------- | ---- |
| LPD  | 低功率域                    |      |
| FPD  | 高功率域                    |      |
| PLPD | PL power domain             |      |
| BPD  | Battery power domain        |      |
| PMU  | platform management unit    |      |
| CSU  | configuration security unit |      |
| FSBL | first-stage boot loader     |      |
|      |                             |      |
|      |                             |      |

# Functional Units and Peripherals  

| Name              | Description                                                  |      |
| ----------------- | ------------------------------------------------------------ | ---- |
| APU MPCore        | Application processing units: two or four 64-bit Cortex-A53 processors, supports four exception levels, NEON instructions, and single/double precision floating-point calculations, includes accelerator port (ACP) and AXI coherency extension (ACE), snoop-control unit (SCU), and L2 cache controller (CG devices are dual core, all others are quad). |      |
| RPU MPCore        | Real-time processing units: dual 32-bit Cortex-R5F processor, Arm instruction set, dynamic branch prediction, redundant CPU logic for fault detection, 32/64/128-bit AXI interface to the PL for low-latency applications. |      |
| GPU               | Graphics processing units: one geometry processor, two pixel processors, OpenGL ES 1.1 and 2.0, OpenVG 1.1, advanced anti-aliasing support (available in the EG and EV product families). |      |
| VCU               | The video codec unit (VCU) provides multi-standard video encoding and decoding, including support for the high-efficiency video coding (HEVC) H.265 and advanced video coding (AVC) H.264 standards. The unit contains both encode (compress) and decode (decompress) functions, and is capable of simultaneous encode and decode. The VCU is included in the EV product family of the MPSoC devices. |      |
| RF                | The RF-ADC, RF-DAC, and soft-decision FEC functions are located in the PL. These RF circuits enable software-defined radios using the direct RF sampling data converters to enable CPRI™ and gigabit Ethernet-to-RF functionality. The RF unit is included in the DR product family exclusively part of the RFSoC devices. |      |
| AMBA interconnect | AXI cache-coherent interconnect, interconnects belonging to two power domains, (central switch and low-power switch), processing system to programmable logic interface.APB buses for register access, AHB for some IOP masters. |      |
| CSU               | Configuration security unit: triple redundant processor for controlling; supports secure and non-secure boot flows. |      |
| System interrupts | Processor, controller, and other system element interrupts. Inter-processor interrupts (IPI). Software generated interrupts. RPU and APU interrupts and system interrupts. Inter-processor interrupt, support for software generated interrupt and shared peripheral interrupt. |      |
| TTC               | 4x Triple Timer Counters: programmable 32-bit and 64-bit timers, programmable event counters. |      |

# 平台管理和启动

PMU: platform management unit, 平台管理单元

CSU: configuration security unit, 配置安全性单元

## MPSoc的启动过程

**1.1 三个启动阶段**

启动过程包括三个功能阶段。Pre-configuration，Configuration和Post-configuration。需要说明的是，据我的理解，这三个阶段的划分是根据CSU的行为来界定的。

**•预配置阶段(Pre-configuration)**

预配置阶段CSU尚未启动，由PMU完全控制，但是执行的是PUM ROM里面代码，ROM里面的代码是固化的，用户无法修改，所以我们无法干预这一阶段的任何行为。

PMU处理所有复位和唤醒过程。上电复位用于复位CSU和PMU，因为它们负责调试，系统和软件复位。还有其他复位方法，例如SRST和SLCR。

初次启动期间将执行下列步骤：

• 通过上电复位 (POR) 将 PMU 从复位状态唤醒。

• PMU 执行来自 PMU ROM 的代码。

• PMU 初始化 SYSMON 和启动所需的 PLL、清空低功耗域和全功耗域， 并释放 CSU 复位。

这阶段结束的标志是CSU复位的释放。

**•配置阶段(Configuration)**

在配置阶段CSU开始工作，BootROM（CSU ROM代码的一部分）解释boot header以配置系统，并将PS的FSBL(first-stage boot loader)

代码加载到片内RAM（on-chip RAM, OCM）中(无论是在安全还是非安全启动模式)。系统根据BOOT Header的内容选择在CPU(Cortex-A53)还是RPU(Cortex-R5)上执行。负责初始化必要的时钟、内存和外设，加载Bit文件和用户代码等。

在boot过程中，CSU还将PMU用户固件（PMU Firmware）加载到PMU RAM中，以与PMU ROM一起提供平台管理服务。PMU的Firmware不是必须的，但是大多数基于Xilinx的FSBL和系统软件的系统都存在PMU Firmware。

这个阶段FBSL可以通过PCAP接口从PS配置PL，但是这只是一个可选的操作。因为其实我们也可以在PS端的操作系统启动之后再动态配置PL端。有时，可能只需要 FSBL 在启动过程中加载部分 PL。随后，有必要在系统生命周期里继续对 PL 进行部分重配置。

在 PMU 释放 CSU 后， CSU 将执行以下操作：

• 检查并判定 FSBL 或用户应用是否需要进行身份验证。

• 执行身份验证检查， 并且只有在身份验证检查通过以后才继续执行。然后， 检查镜像是否包含任何已加密的分区。

• 如果 CSU 检测到分区已加密， 那么 CSU 会执行解密并初始化 OCM、判定启动模式设置、执行 FSBL 加载和可选PMU 固件加载操作。

• 执行 CSU ROM 代码后， 它会将控制权交给 FSBL。 FSBL 使用 PCAP 接口来对含比特流的 PL 进行编程。

随后，在后配置阶段 FSBL 会负责对系统进行操作。

**•后配置阶段(Post-configuration)**

开始执行FSBL之后，CSU ROM代码进入后配置阶段，该阶段负责系统干预响应。 CSU硬件提供持续的硬件支持，以验证文件，通过PCAP配置PL，存储和管理安全密钥以及解密文件。

这个阶段会启动SSBL，就是Linux的bootloader，开始引导启动Linux系统。

讲完配置的三个阶段，我们来单独讲一下PL的配置

**1.2 PL的配置**

处理器配置访问端口processor configuration access port（PCAP）用于从PS配置PL。 PCAP是在正常操作条件下用于配置PL的唯一接口。在调试过程中，可以使用JTAG接口来配置PL。 PS通过secure-stream switch连接到PCAP。可以使用CSU DMA或AES路径将比特流数据发送到PL。

> 说明：这个secure-stream switch具体是什么我没有去研究，有兴趣的朋友可以去了解一下，猜测应该是为了代码的安全传输防止加载过程中被窃。

执行CSU ROM代码后，CSU将控制权移交给FSBL。FSBL使用PCAP接口为PL配置比特流，步骤如下：

1.初始化PCAP接口。

2.通过PCAP写入比特流(Bitstream)。

3.等待PL完成状态。





















# 参考文档

ug1085

xapp1257

xapp1296







# 未完待续

[ZYNQ UltraScale+ MPSoc FPGA自学笔记-启动加载配置 - 知乎](https://zhuanlan.zhihu.com/p/260163123)











