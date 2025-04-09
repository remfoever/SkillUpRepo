# FPGA相关

# 术语

|  术语  |  解释  |
| --- | --- |
|  VTC  |  视频时钟控制器，一个IP核用于HDMI图像输出  |
|   |   |
|   |   |
|   |   |
|   |   |

# 芯片信号

xczu4ev-sfvc784-1-i

# Vivado开发相关

## 芯片兼容性分析

|  芯片信号  |   |   |
| --- | --- | --- |
|  XCZU4EV-1SFVC784I  |   |   |
|  XCZU5EV-1SFVC784I  |   |   |

## 管脚分配

要综合以后才能看管脚分配

对于输出引脚一般需要指定如下信息

1.  电压
    
2.  绑定的芯片引脚
    
3.  上下拉（可选）
    

```tcl
set_property PULLUP true [get_ports xxx]
```

## 关于约束

时序检查的概念

1.  源时钟指发送数据的时钟
    
2.  目的时钟是捕获数据的时钟
    
3.  **建立要求**
    

# 编程技巧

## 差分信号处理

```verilog
IBUFDS IBUFDS_inst(.O(sys_clk),.I(sys_clk_p),.IB(sys_clk_n));
```

## verilog参数的应用

申明模块的时候可以指定参数，以便模块更好的适应不同的场景

```verilog
module module_name
#(
    parameter N = 16
)
(
    input clk;
    input rst_n;
);
    reg [N-1: 1] data;
    always @(posedge clk) begin
        if (rst_n) 
            data <= { N{1'b0} };
        else begin
        // ....
        end
```

## Verilog +: -:语法

AXI4-Lite源代码中使用

```verilog
slv_reg0[(byte_index8) +: 8] <= S_AXI_WDATA[(byte_index8) +: 8]；

变量[起始地址 +: 数据位宽] <–等价于–> 变量[(起始地址+数据位宽-1)：起始地址]
data[0 +: 8]  <--等价于--> data[7:0]
data[15 +: 2] <--等价于--> data[16:15]

变量[结束地址 -: 数据位宽] <–等价于–> 变量[结束地址：(结束地址-数据位宽+1)]
data[7 -: 8]  <--等价于--> data[7:0]
data[15 -: 2] <--等价于--> data[15:14]



```

## 跨时钟域处理

### 单bit信号跨时钟域

#### 从慢到快

两级电平同步

注意事项：

1.  如果慢时钟是clk\_slow，快时钟是clk\_fast，那么从clk\_slow打出的单bit信号宽度至少是clk\_fast周期的**1.5倍**，否则认为是从快到慢；
    
2.  从clk\_slow同步到clk\_fast，从clk\_slow打出的信号必须**经过clk\_slow打过，否则组合逻辑输出会有毛刺**，被clk\_fast采到，会增大clk\_fast时钟域第一级触发器出现亚稳态的概率，从而增大同步器出现亚稳态的概率；
    

如下图所示：

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/YdgOkpNA5LQ8l4BX/img/ca882cb8-aed3-4844-8787-39a025c4c129.png)

#### 从快到慢

单bit从clk\_fast跨时钟域到clk\_slow

**方法1：开环控制**

展宽clk\_fast时钟域的信号宽度到大于等于1.5倍clk\_slow时钟域周期，这样可以保证信号被clk\_fast采集到，但是这样的话，对clk\_fast和clk\_slow的频率有一个约束关系，当设计改动clk\_fast和clk\_slow频率变化时，可能需要重新修改代码，这种设计不具有健壮性，如下图所示：

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/YdgOkpNA5LQ8l4BX/img/26100e84-c425-4ef7-9804-0cbd395f10eb.png)

**方法2：闭环控制**

使用反馈信号自动延长快时钟域的信号；

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/YdgOkpNA5LQ8l4BX/img/22df5be1-7a4a-41a5-9677-df7246bceb80.png)

其中一种做法是使用脉冲同步器(genpart\_pulse\_sync)：

这种脉冲同步器可以接受单周期脉冲，也可以接受多周期脉冲，设计理念是如果Input没有拉低，那么就不会让ack\_from\_dst拉低src\_sig\_d；

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/YdgOkpNA5LQ8l4BX/img/96437c95-f9a6-42f1-a81e-f109824111d0.png)

src\_sig为高电平则输出固定位为1，此时ack\_from\_dst为1，不会影响高电平输出

src\_sig拉低后

ack\_from\_dst为高则说明高电平已经被感知，则输出0，符合预期；

ack\_from\_dst为低，则其上一时刻的高电平会作为输入保持高电平，直到ack\_frome\_dst被成功置位；

感觉很妙啊

简单说，就是目的没有拉高那就保持高输入，直到拉高为止，后如果输入为0才能输出0；

额外增加一个寄存器，检测上升沿脉冲

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/YdgOkpNA5LQ8l4BX/img/44709b0f-9ac5-4f83-b50f-917104567a2c.png)

最新的为1，旧的为0则产生高脉冲

参考实现

```verilog
`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2025/02/14 13:50:21
// Design Name: 
// Module Name: gen_pulse_sync
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 把时钟域A的信号src_sig同步到时钟域产生一个脉冲
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module gen_pulse_sync(
	input wire src_clk,
	input wire src_rst_n,
	input wire dst_clk,
	input wire dst_rst_n,
	input wire src_sig,
	output wire dst_sig // 输出的脉冲
);

reg src_sig_d;
reg [1:0] ack_from_dst;
reg [2:0] dst_sig_sync;
always @(posedge src_clk or negedge src_rst_n)
begin
	if (src_rst_n == 1'b0) begin
		src_sig_d <= 1'b0;
		ack_from_dst <= 2'b0;
	end
	else begin
		ack_from_dst <= {ack_from_dst[0], dst_sig_sync[1]};
		if (src_sig == 1'b1)
			src_sig_d <= 1'b1; // 如果信号为高电平则是时钟保持高电平，直到目的端置后，清0
		else if (ack_from_dst[1] == 1'b1) 
			src_sig_d <= 1'b0;
		else
			src_sig_d <= src_sig_d;
	end
end

always @(posedge dst_clk or negedge dst_rst_n)
begin
	if (dst_rst_n == 1'b0)
		dst_sig_sync <= 0;
	else
		dst_sig_sync <= {dst_sig_sync[1:0],  src_sig_d};
end


assign dst_sig = (!dst_sig_sync[2]) && dst_sig_sync[1]; // 上升沿脉冲

endmodule
```

### 多bit信号跨时钟域

fifo吧比较靠谱

# 外设

## DDR4

双倍数据速率第四代

双倍数据速率，上升沿和下降沿都能传输数据，因此速率是传统内存的两倍；

预取：每次从存储单元中预取16bit数据

**读写操作**

**读操作：控制发出地址和读命令，内存找到对应数据并通过数据总线传输**

**写操作：控制器发出地址，写命令和数据，内存将数据存入指定位置**

**支持突发传输：**

DDR内存的存储单元可以想象成一个巨大的表格，这个表格由行和列。每个格子里面存放着数据。为了找到某个数据，DDR需要通过行地址和列地址来定位

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/YdgOkpNA5LQ8l4BX/img/677873b2-aacc-48df-b4b5-35eb8ff32a59.png)

DDR的读写操作分为几个关键步骤，每个步骤都有对应的延迟时间。以下是通俗的解释：

1.  预充电（Precharge），在开始读写之前，内存需要清理一下，把之前用过的行关闭，准备迎接新的操作。这个过程叫预充电。（Active to Precharge Delay， tRP），看书的时候先把数和尚，准备翻到新的新的一页；
    

#### 2. 行激活（Row Activation）

*   **通俗解释**：内存需要先找到你要访问的“行”。这个过程叫**行激活**，也就是打开某一行。
    
*   **术语**：RAS（Row Address Strobe），行地址选通。
    
*   **延迟时间**：tRAS（行激活到预充电的时间）。
    
*   **类比**：就像你在书架上找到某一本书（行），然后打开它。
    

#### 3. 列选通（Column Activation）

*   **通俗解释**：找到行之后，还需要找到具体的“列”，也就是你要读写的具体数据位置。
    
*   **术语**：CAS（Column Address Strobe），列地址选通。
    
*   **延迟时间**：
    
    *   **tRCD**：从行激活到列选通的延迟（RAS to CAS Delay）。
        
    *   **tCL**：从列选通到数据真正开始传输的延迟（CAS Latency）。
        
*   **类比**：就像你打开书后，翻到具体的某一页（列），然后开始阅读。
    

#### 4. 数据传输（Data Transfer）

*   **通俗解释**：找到具体的列之后，数据就可以开始传输了。
    
*   **术语**：Burst Transfer（突发传输），DDR会一次性传输多个数据单元。
    
*   **类比**：就像你找到书中的内容后，开始连续阅读几行。
    

### DDR的实际工作流程

结合上面的步骤，DDR的实际工作流程如下：

1.  **发出BANK地址和行地址**：
    
    *   内存中有多个BANK（可以理解为多个独立的表格），首先选择要操作的BANK，然后激活对应的行。
        
    *   **类比**：选择某个书架（BANK），然后打开某本书（行）。
        
2.  **等待tRCD延迟**：
    
    *   从行激活到列选通之间需要一段时间（tRCD），这段时间内存在进行内部准备工作。
        
    *   **类比**：你打开书后，需要花点时间找到具体的页码。
        
3.  **发出列地址和读写命令**：
    
    *   找到列地址后，内存开始准备传输数据。
        
    *   **类比**：翻到具体的页码后，准备开始阅读。
        
4.  **等待tCL延迟**：
    
    *   从列选通到数据真正开始传输之间还有一段延迟（tCL），这是内存找到数据的最后一步。
        
    *   **类比**：你找到页码后，还需要花点时间定位到具体的文字。
        
5.  **数据传输**：
    
    *   数据开始传输，DDR会一次性传输多个数据单元（突发传输）。
        
    *   **类比**：你开始连续阅读几行内容。
        

DDR内存的读写过程可以简单概括为：

1.  **预充电**：清理之前的操作，准备新的读写。
    
2.  **行激活**：找到要操作的行。
    
3.  **列选通**：找到要操作的列。
    
4.  **数据传输**：开始读写数据。
    

每个步骤都有对应的延迟时间（tRP、tRAS、tRCD、tCL），这些延迟决定了内存的性能。DDR通过优化这些步骤和延迟，实现了高效的数据传输。

工作频率

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/YdgOkpNA5LQ8l4BX/img/6ab220d3-99b8-4818-a70e-22ce9533c732.png)

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/YdgOkpNA5LQ8l4BX/img/977d42dd-5715-479f-bc0d-83c86f01485f.png)

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/YdgOkpNA5LQ8l4BX/img/dc873fa5-29da-4623-adbb-3368556fc530.png)

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/YdgOkpNA5LQ8l4BX/img/b083b826-39a4-4d15-84eb-8810c2b238e6.png)

个人理解，Effective DRAM Bus Width，是总线的宽度，需要根据实际使用的总线位宽确定，这里是64bit，单个内存颗粒是16bit，其型号如下

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/YdgOkpNA5LQ8l4BX/img/bd984d35-98a3-414a-af67-d9a55eee9371.png)

512M16BIT， 也就是可以提供8192Mbits的的存储容量， 4个内存颗粒组成64bit的总线通道，其内存总量为4GB，这里的B是byte；

### ECC

**Error Correction Code，错误纠正码**

### 什么是ECC？

*   **ECC** 是一种内存技术，用于检测和纠正内存中的数据错误。
    
*   它通过在数据中添加额外的校验位（冗余信息），来确保数据的准确性。
    
*   如果内存中的数据出现错误（比如由于电磁干扰、硬件故障等原因），ECC可以自动检测并修复这些错误。
    

### ECC的工作原理

1.  **数据存储**：
    
    *   当数据写入内存时，ECC会生成一组校验位，并与数据一起存储。
        
    *   比如，64位数据可能会附带8位校验位，总共72位。
        
2.  **数据读取**：
    
    *   当数据从内存中读取时，ECC会重新计算校验位，并与存储的校验位进行比较。
        
    *   如果发现不一致，ECC可以检测到错误，并尝试纠正错误。
        
3.  **错误纠正**：
    
    *   ECC可以纠正**单比特错误**（1 bit错误），并检测**双比特错误**（2 bit错误）。
        
    *   如果错误超过ECC的纠正能力（比如多比特错误），系统会报告错误，但无法修复。
        

使能ECC内存是否需要增多？eg：原来的64bit增加ECC

*   Error correction code (ECC) support in 32-bit and 64-bit mode, 2-bit error detection  and 1-bit error correction.
    
*   Ability to poison the write data by adding uncorrectable errors, for use in testing ECC  error handling (ECC poison).
    

16bit总线宽度不支持ECC

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/YdgOkpNA5LQ8l4BX/img/e8dacd42-a208-4a2e-a6d8-2c2d5ce99180.png)

The DDR I/O pins are located on **bank 504** and can have a 32-bit or 64-bit data path to the  DRAMs depending on the device type. Bytes 0 to 3 correspond to 32-bit data and bytes 0  to 7 correspond to 64-bit data. Byte 8 refers to the ECC bits. The pins are summarized in  Table 17-3. **See AXI DMA v7.1 LogiCORE IP Product Guide: Vivado Design Suite (PG201)  \[Ref 18\] for pin assignments.**

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/YdgOkpNA5LQ8l4BX/img/d4caec45-95bd-47bb-96b6-81935ed0c1ef.png)

Several events in the DDR memory controller can assert IRQ 144. The interrupts from the  following sources are managed by the DDR\_QOS\_CTRL.QOS\_IRQ\_{STATUS, MASK} registers.  • Correctable ECC error \[DDR\_ECC\_CORERR\].  • Uncorrectable ECC error

## 主控板相机

主控板相机的整体框图如下所示

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/YdgOkpNA5LQ8l4BX/img/20d03458-e62f-405d-8d11-4e6ba29f5ba9.png)

其中：

*   解串模块，把相机的串行数据转换为并行数据
    
*   axi-write 负责把相机数据通过axi-master发送给PS的DDR
    
*   axi-master为axi-master写模块
    
*   camera-cfg为相机配置模块，负责接收PS的配置数据和控制信号
    
*   I2C用于配置相机
    

### 相机搬数

相机采用的AB桶的方式进行搬数，在PS在处理A桶的数据时候，B桶可以用于写新数据，以此类推，以提升读写效率；相机某桶的数据写好后会触发中断通知PS，PS在中断寄存器的中，读取中断状态寄存器，可知是哪一个桶的数据有效；数据处理完毕后，PS重新使能该桶；其交互流程如下所示

sequenceDiagram participant PS participant PL PS->>+PL: Enable addr1 Note over PL: 地址1写图像 PL-->>-PS: Interrupt signal Note over PS: 读中断确定数据源 PS->>+PL: Enable addr2 Note over PS: 处理地址1图象 Note over PL: 地址2写图像 PL-->>-PS: ...   

图像AB地址在共享内存区域规划，取值如下

|  地址  |  说明  |  备注  |
| --- | --- | --- |
|  0x6400\_0000  |  可以写图像的地址A  |  实际测试时图像的最大尺寸为2,931,560Byte  |
|  0x6430\_0000  |  可以写图像的地址B  |   |

图像数据一个64bit由4个数据组成，数据的位宽最大为12，高4bit，用于标志数据信息，定义如下

最高位的4'BXYZP含义

*   X - 置1表示为图像的第一个数据   -  8
    
*   Y - 置1表示为图像的有效数据       - 4 
    
*   Z - 预留固定位0
    
*   P - 置1表示为图像的结束**假数据**，假数据之前均应该有效数据 1
    

内存中存放如下所示：

![1739349660094_579AD842-BA7F-43ca-967E-6CC1E69533E4.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/YdgOkpNA5LQ8l4BX/img/d99f9511-916d-4a00-a69c-b221d8c1c3d8.png)

图片的大小最大为：2CBBC0 = 2931684

目前规划的8个寄存器用于配置和控制相机模块

|  NO  |  OFFSET  |  寄存器  |  备注  |
| --- | --- | --- | --- |
|  0  |  0  |  控制寄存器  |  暂未实现  |
|  1  |  4  |  中断使能寄存器  |  暂未实现，中断默认使能  |
|  2  |  8  |  中断状态寄存器  |  读请，不支持写  |
|  3  |  A  |  图像位宽寄存器  |  暂不支持  |
|  4  |  10  |  地址1使能寄存器  |  写1则会使能地址1  |
|  5  |  14  |  地址2使能寄存器  |  写1会使能地址2  |
|  6  |  18  |  预留  |   |
|  7  |  1A  |  预留  |   |

寄存器的基值：XPAR\_AX\_CAMERA\_0\_S00\_AXI\_BASEADDR include "xparameters.h"

```c
#define WX_CAMERA_INTR_STATUS_REG_OFFSET (2 * 4)
#define WX_CAMERA_ADDR1_ENABLE_REG_OFFSET (4 * 4)
#define WX_CAMERA_ADDR2_ENABLE_REG_OFFSET (5 * 4)

#define XCAMERA_WriteReg(RegOffset, RegisterValue)                             \
  Xil_Out32((XPAR_AX_CAMERA_0_S00_AXI_BASEADDR) + (RegOffset), (RegisterValue))
#define XCAMERA_ReadReg(RegOffset)                                             \
  (Xil_In32((XPAR_AX_CAMERA_0_S00_AXI_BASEADDR) + (RegOffset)))
```

### 测试结果

测试步骤：

1.  使能地址1
    
2.  等待一段时间，查看地址1的状态并检查数据
    
3.  设置地址1的数据为无效值
    
4.  是能地址2
    
5.  等待一段时间，查看地址2的状态并检查数据
    
6.  设置地址2的数据为无效值
    
7.  重复步骤1
    

测试预期：

步骤2，5中能够检测中断状态被正确置位，读取的数据符合预期

测试结果：

如下所示，符合预期

![1739349498857_8B565F03-8A63-4894-A914-DAB7386DA9CF.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/YdgOkpNA5LQ8l4BX/img/94408d08-8e56-4278-a6ef-d07b5479343a.png)

图像到达时候PL能够正常触发AXI突发写，如下所示：

![1739349892701_AED99AD6-F0A6-4816-B1DB-41E382C2EDD5.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/YdgOkpNA5LQ8l4BX/img/f1638210-e86c-4ead-9146-e4249212d4d3.png)

图像结束的时候PL能够正常通知图像写完成，如下所示

![1739350015729_4970FB19-BCE4-4b64-806D-79645EC4D5C2.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/YdgOkpNA5LQ8l4BX/img/99770270-d5d5-4931-bf94-98a7db03ab0f.png)

## AXI-GPIO

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/YdgOkpNA5LQ8l4BX/img/77e5d560-1f45-48fe-9ec4-c932a3c7df47.png)

每通道有自己的三态，每个bit有自己三态，也就意味着每个通道 的每个bit的方向都是可以配置的；

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/YdgOkpNA5LQ8l4BX/img/a0c06bcd-fb52-406d-86dd-7a1610615e6c.png)

AXI是PS与PL的交互接口，AXI\_GPIO有两个通道

外设架构完毕后，可以再sdk的xparameters.h中找到中断的ID

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/YdgOkpNA5LQ8l4BX/img/2e5985f7-80d6-431e-a882-d91c5a13e050.png)

从xparameters.h中找到如下的ID

*   设备ID
    
*   中断ID
    
*   中断控制器的设备ID（XPAR\_SCUGIC\_SINGLE\_DEVICE\_ID）
    

代码实现步骤如下：

1.  初始化GPIO， XGpio\_Initialize（XGpio \*，设备ID）
    
2.  配置方向，XGpio\_SetDataDirection（XGpio \*， channel 1/2，key\_bit(0x1-1bit, 其他类推)）
    
3.  建立GPIO中断系统
    

```c
{
    XScuGic_Config *IntcConfig; // 入参

	/*
	 * Initialize the interrupt controller driver so that it is ready to
	 * use.
	 */
	IntcConfig = XScuGic_LookupConfig(INTC_DEVICE_ID);
	if (NULL == IntcConfig) {
		return XST_FAILURE;
	}

	Result = XScuGic_CfgInitialize(IntcInstancePtr, IntcConfig,
					IntcConfig->CpuBaseAddress);
	if (Result != XST_SUCCESS) {
		return XST_FAILURE;
	}

// 设置中断触发方式和优先级优先级
    XScuGic_SetPriorityTriggerType(IntcInstancePtr, IntrId,
					0xA0, 0x3);

/*
	 * Connect the interrupt handler that will be called when an
	 * interrupt occurs for the device.
	 */
	Result = XScuGic_Connect(IntcInstancePtr, IntrId,
				 (Xil_ExceptionHandler)自定义的Gpio中断服务函数, InstancePtr);
	if (Result != XST_SUCCESS) {
		return Result;
	}

    XScuGic_Enable(IntcInstancePtr, IntrId);
/*
	 * Enable the GPIO channel interrupts so that push button can be
	 * detected and enable interrupts for the GPIO device
	 */
    XGpio_InterruptEnable(InstancePtr, IntrMask);
    XGpio_InterruptGlobalEnable(InstancePtr);


/*
	 * Initialize the exception table and register the interrupt
	 * controller handler with the exception table
	 */
    Xil_ExceptionInit();

	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
			 (Xil_ExceptionHandler)INTC_HANDLER, IntcInstancePtr);

	/* Enable non-critical exceptions */
    Xil_ExceptionEnable();
}


```

### GPIO相关的API介绍

|  函数  |  说明  |  备注  |
| --- | --- | --- |
|  XGpio\_DiscreteWrite  |  对GPIO指定通道的某些bit置位  |  bits每一bit标识某个引脚  |
|  XGpio\_DiscreteClear  |  对GPIO指定通道的某些bit清0  |   |
|  XGpio\_SetDataDirection ( XGpio \*InstancePtr,  unsigned Channel, u32 DirectionMask )  |  设置GPIO指定某通道的方向  |  1-标识输入； 0-标识输出 其根本原理再与设置该通道的三态寄存器  |
|  XGpio\_Initialize  |  GPIO初始化，使用前需要初始化  |  需要提供设备ID  |
|  XGpio\_InterruptEnable  |  使能某通道的中断，0x3双通道；0x1-第一个通道；0x2-第二个通道  |   |
|  XGpio\_InterruptClear  |  清除某通道的中断  |   |
|  XGpio\_InterruptGlobalEnable  |  使能GPIO的全局中断  |   |
|  XGpio\_InterruptDisable  |  去使能某通道的中断  |   |
|  XGpio\_GetDataDirection  |  获取某通道当前的方向  |   |

## 地址编译器

一些外设在设计好后，需要进行地址分配，地址分配在

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/YdgOkpNA5LQ8l4BX/img/cc611d3e-90d7-4fa3-877b-8e7af93384ae.png)

界面上看，可以看到哪些分配了，那些没有分配；

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/YdgOkpNA5LQ8l4BX/img/d3efb1bc-7f05-4b92-9cf2-585848612239.png)

## HDMI相关

### 图像的输出

使用哪些IP组装了图像输出系统，每个什么含义？

|  组件  |  功能  |  备注  |
| --- | --- | --- |
|  I2C  |  用于配置HDMI芯片  |  使用AXI-I2C实现  |
|  时钟  |  150Mhz  |   |
|  中断  |   |   |
|  AXI Video Direct Memory Access   |  VDMA 图像搬数  |   |
|  Video Timing Controller  |  视频时序控制器（VTC）  |   |
|  AXI4-stream to video out  |   AXI 流转视频输出控制器  |   |
|  Dynamic Clock Generator  |  动态时钟IP  |  根据不同的分偏绿配置出不同的时钟输出  |
|   |   |   |

图像的相关概念

图像有行和列的概念，在VDMA的寄存器中，即

*   HSIZE
    
*   VSIZE
    
*   STRIDE寄存器可以理解为一行存储的最大字节数，大于等于HSize
    

举例说明：假设显示器分辨率为1920\*1080 像素为24位深度（3个字节），那么

HSIZE = 1920 \* 3字节

VSIZE = 1080 \* 3字节

STRIDE - 一行存储的最大字节数，大于等于HSIZE即可

PS产生图像，HDMI显示数据；

*   I2C，由于EMIO的I2C被用于控制相机；
    
*   Memory Map接口，采用AXI4接口，与ZYNQ HP寇进行数据交互；
    
*   HP 配置64位，
    
*   AXI stream流接口，用于传输图像数据到HDMI接口，位宽；， Frame Buffers为帧缓存数，可以存储多帧图像；Line Buffer Depth类似于FIFO缓存，以Stream Data width为单位；设置大写，可以缓存的数据越多
    

输出引脚有哪些？

关于分辨率

由于视频有很多分辨率，各种分辨率的时钟频率不相同，需要使用一个动态时钟控制器，这个IP来自开源软件，找到里程里的repo目录，赋值到自己的目录下；

动态时钟的IP，根据不同的分辨率配置出不同的时钟输出，本之上是调用了锁相环，但要注意的是，此模块的的参考时钟必须设置100Mhz

### I2C

用于配置HDMI，由于I2C0被人使用了这里使用I2C1, 如下所示：

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/YdgOkpNA5LQ8l4BX/img/1ac12cff-7968-4cea-a9c7-6311679f5525.png)

### AXI Video Direct Memory Access

专门用于视频搬数的一个IP，DDR作为一个显存；VDMA需要连载到PS的HP接口，需要在PS上进行配置；

由于我们只进行读DDR操作，所以写入操作可以关闭；

带宽选择64bit

图片像素为24bit

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/YdgOkpNA5LQ8l4BX/img/fa1f3626-19c3-4ded-9984-73519ecd6286.png)

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/YdgOkpNA5LQ8l4BX/img/01edce3e-1cce-4f72-91a0-1c8a7ab958f0.png)

参数说明

*   Frame Buffers: VDMA缓存图像的帧数，默认协同到和都通道都设置相同的缓存帧数，具体设置多少帧合适一般根据应用来顶，比如读写贷款相同，相同DDR做一个兵乓buffer，那就可以设置成2帧，写一个地址，读第二个地址，写第二个地址，读第一个地址。这里设置杜少，就在VDMA寄存器配置的时候，设置对应的起始地址。
    
*   包含两个通道，一个是写通道，一个读通道，如果仅用于视频输出，则写通道不需要；
    
*   Memory Map Data width：代表AXI4总线上的数据位宽；
    
*   Burst Size： AXI总写上突发传输的长度，一般设置为16
    
*   Stream Data width： VDMA需要通过stream流协议和PL的HDMI通信，这里就是流数据的问款
    
*   Line Buffer Depth： VDMA内部会有一个行缓存FIFO, stream数据会先写入FIFO，然后AXI总线裸机会读出到总线上，这个深度就代表FIFO的深度。需要根据AXI总线和Stream的带宽设置，防止数据溢出丢失；
    

### 视频时序控制器（ATC）

### AXI-Stream to Video out

# 中断相关

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/YdgOkpNA5LQ8l4BX/img/3bcfb4cc-c85f-4ceb-842a-42143c11dc02.png)

ISR表示各个中断源中断发生后，中断服务函数的实例。通过中断号作为HandlerTable的索引值跳转到具体的中断服务函数。

中断服务函数中根据外设的MASK 和状态来判断具体是哪个部分发生了中断。

GIC的输入是各个中断源的中断线，通过中断号来记录是哪个中断源发生了中断，这里是记录。

中断发生后，GIC根据配置把中断信号，给到对应的CPU，CPU接收到了中断后，由硬件进行中断跳转，跳转到VectorTable对应的中断服务函数。以GPIO为例，GIC会触发CPU 的IRQ中断，CPU就会通过VextorTABLE中IRQ中断的入口跳转到XScuGic\_InterruptHandler.

所有的IRQ中断都会进入到XScuGic\_InterruptHandler函数，XScuGic\_InterruptHandler函数根据GIC中记录的中断号来判断，是哪个中断源发生了中断，进行软件跳转到ISR #n。这里和MCU (ARM cortex M3,M4)内核的中断有非常大的区别。

理清楚上面的关系后，就不难理解代码。代码中有多个函数的配置和关联，本质上就是上图信息流的配置。

原文链接：[https://blog.csdn.net/denghuajing/article/details/128508465](https://blog.csdn.net/denghuajing/article/details/128508465)

XExc\_VectorTable

#define XIL\_EXCEPTION\_ID\_RESET    0U

#define XIL\_EXCEPTION\_ID\_UNDEFINED\_INT    1U

#define XIL\_EXCEPTION\_ID\_SWI\_INT    2U

#define XIL\_EXCEPTION\_ID\_PREFETCH\_ABORT\_INT    3U

#define XIL\_EXCEPTION\_ID\_DATA\_ABORT\_INT    4U

#define XIL\_EXCEPTION\_ID\_IRQ\_INT    5U

#define XIL\_EXCEPTION\_ID\_FIQ\_INT    6U

#define XIL\_EXCEPTION\_ID\_LAST    6U

# 参考文档

\[1\]. [FreeRtos任务状态打印](https://www.cnblogs.com/seekwhale13/p/17507475.html)

\[2\]. VDMA 的手册 PG020， pg044；

\[3\]. [https://xilinx-wiki.atlassian.net/wiki/spaces/A/pages/18841897/Zynq+UltraScale+MPSoC+-+64-bit+DDR+access+with+ECC](https://xilinx-wiki.atlassian.net/wiki/spaces/A/pages/18841897/Zynq+UltraScale+MPSoC+-+64-bit+DDR+access+with+ECC)

# vivado FDCP问题

出现这个问题可能就是跨时钟域产生的问题。

由于rst\_n是个异步信号，而在异步信号的驱动下去采样另一个寄存器是有可能导致时序不满足的，就是可能发生亚稳态。这个很好理解，只要对异步信号多打几拍就可以解决这个问题。现在把rst\_n信号触发的执行语句改为赋值一个固定初始值，再次综合问题就解决啦。

参考：

[http://xilinx.eetrend.com/d6-xilinx/article/2018-02/12599.html](http://xilinx.eetrend.com/d6-xilinx/article/2018-02/12599.html)