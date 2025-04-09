# SONY\_IMX990

# 特性

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/eYVOLXa7LrZwOpz2/img/ccb88ef3-fcd7-46c0-9389-99f330b06f66.png)

# 设备结构

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/eYVOLXa7LrZwOpz2/img/9b5460c4-bd10-48a9-8dbf-a09efc125ea2.png)

# 像素排列

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/eYVOLXa7LrZwOpz2/img/adc7fbfb-fc7f-49e9-821b-d0be098690b3.png)

#  相机的主从模式（MASTER=1/0）

    相机的数字输入输出接口

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/eYVOLXa7LrZwOpz2/img/bd61aac0-af81-4b92-a7b5-254222f4b87a.png)

外部输入**XMASTER 信号的作用**

*   **XMASTER** 是控制设备主从模式的信号。
    
*   当 **XMASTER = High** 时，设备处于从属模式，依赖外部 XVS 和 XHS 信号。
    
*   当 **XMASTER = Low** 时，设备可能处于主模式，主动生成 XVS 和 XHS 信号。
    

### Master Mode（主模式）

*   在主模式下，设备会主动生成 XVS 和 XHS 信号，并将这些信号提供给其他从属设备（Slave Devices）。
    
*   这意味着设备作为主设备，控制整个系统的同步时序。
    

# 相机通信接口（I2C）

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/eYVOLXa7LrZwOpz2/img/a784fbec-76d0-43bb-a0fa-e68534a66e5e.png)

The serial data input order is MSB-first transfer. The table below shows the various data types and descriptions. 

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/eYVOLXa7LrZwOpz2/img/06426e44-ed7d-4bd9-ad46-50b895cc4481.png)

The sensor can use two kinds of slave addresses by switching the polarity of SLAMODE Pin for one I2C bus, and can use a common slave address in both polarities of SLAMODE Pin for one I2C bus. 

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/eYVOLXa7LrZwOpz2/img/f71b5584-3ca9-4612-9d0b-4b06497f02e5.png)

#### SLAVE Address 

相机使用 **SLAMODE = 1** 模式，即相机地址 **0x37**

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/eYVOLXa7LrZwOpz2/img/2063f7db-de8c-4ee3-94d0-6e9e50c0bc21.png)

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/eYVOLXa7LrZwOpz2/img/8df9d7c2-d1b2-4c40-9987-f20722f07b46.png)

如果是配置反射类型是"V"的寄存器需要使用REGHOLD进行配置

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/eYVOLXa7LrZwOpz2/img/db8c461d-e180-4beb-b0d3-a56af93c63d2.png)

#### Register Hold Setting 

For the registers marked "V" in the item of Reflection timing, register setting can be transmitted with divided to several frames and it can be reflected globally at a certain frame by the register REGHOLD. By setting REGHOLD = 1, the registers that are set thereafter aren’t reflected at “frame reflection register reflection timing”. The registers that are set during REGHOLD = 1 are reflected globally by setting REGHOLD = 0 by the “frame reflection register reflection timing” before the frame which you want to reflect the registers. 

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/eYVOLXa7LrZwOpz2/img/28437ece-4a46-43aa-b746-1e37d165844d.png)

# 相机系统（XCLR）复位

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/eYVOLXa7LrZwOpz2/img/99f608a9-9d3e-47a4-805c-1dffd96bcd8e.png)

# 上电和下电时序

### 上电时序

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/eYVOLXa7LrZwOpz2/img/5dcf3faa-689c-4a78-ba7e-5693dcf17e05.png)

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/eYVOLXa7LrZwOpz2/img/41637bc5-46f7-4fa8-b7c9-05d8b3295eae.png)

#### 下电时序

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/eYVOLXa7LrZwOpz2/img/23ec263c-39ef-46f0-b5cd-4da8633027c1.png)

# 传感器主模式设置流程

The figure below shows operating flow in sensor master mode.

For details of "Power on" to "System clear", see the item of "Power on sequence" in this section. For details of "Standby cancel" to "Wait for image stabilization", see the item of "Standby mode". In master mode, “Master mode start” by setting the master mode start register XMSTA to “0” after “Wait for internal regulator stabilization”. “**Standby setting (power save mode) can be made by setting the STANDBY register to “1” during “Operation”. This time, set "master mode stop" by setting XMSTA to "1".**

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/eYVOLXa7LrZwOpz2/img/9f3dc723-a4d2-4768-b8ca-b6c5d5d357ce.png)

# 模式转换（ROI模式和All-pixel模式转换只需一个时钟周期）

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/eYVOLXa7LrZwOpz2/img/68cff064-948d-4244-bf49-bec00ce09b8d.png)

# ROI Mode

ROI mode 即 Region of Interest，感兴趣区域。

This Sensor has ROI function that signals are cut out and read out in multi arbitrary positions.

Cropping position can set maximum 64 areas that specified by horizontal 8 points and vertical 8 points, regarding effective pixel start position as origin (0, 0) in all pixel scan mode. Cropping is available from All - pixel scan mode and horizontal period are fixed to the value for this mode.

These cropped areas by horizontal cropping setting (ROI (1, y) to ROI (8, y)) are output with left justified and that extends the horizontal blanking period. In vertical cropping area (ROI (x, 1) to ROI (x, 8)), the number of image data is also output from cropping start line and the frame rate can be adjusted by changing the number of input XVS lines in slave mode or changing register VMAX in master mode.

One invalid frame is generated when the ROI area changing size or cropping address.

ROI image is shown in the figure below.

In case of Vertical / Horizontal 1/2 subsampling mode, this sensor doesn't support ROI mode.

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/eYVOLXa7LrZwOpz2/img/4e0bd911-773d-49d0-906d-cd121caac358.png)

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/eYVOLXa7LrZwOpz2/img/24d260b2-ca37-4787-93f2-247057ff4ca1.png)

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/eYVOLXa7LrZwOpz2/img/a7d7984f-65e8-4bfb-89ef-f011c3e6ed26.png)

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/eYVOLXa7LrZwOpz2/img/2f470ac3-9d6f-436a-883d-048ca5c3f3e9.png)

#### Restrictions on ROI mode 

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/eYVOLXa7LrZwOpz2/img/de79606b-7439-4ffa-8126-2a0eb035a9aa.png)

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/eYVOLXa7LrZwOpz2/img/7c9a6dda-6cb1-4115-872d-e4122a2f8163.png)

当前 **GTWAIT(6h) + GSDLY(0h) + 26  =  32**

**分辨率VMAX**

|  **分辨率**  |  **VMAX**  |  **Vtr**  |  **VMAX\_HEX**  |
| --- | --- | --- | --- |
|  最大  |  1068  |  1100  |  42Ch  |
|  1024\*1280  |  1024  |  1056  |  400h  |
|  512\*512  |  512  |  544  |  200h  |
|  256\*256  |  256  |  288  |  100h  |
|  128\*128  |  128  |  160  |  80h  |
|   |   |   |   |

**分辨率HMAX**

|  **位宽**  |  **HMAX(FREQ = 0h SLVS 4 ch )**  |  **HMAX\_HEX**  |
| --- | --- | --- |
|  8 bit  |  516  |  204h  |
|  10 bit  |  555  |  22Bh  |
|  12 bit  |  972  |  3CCh  |

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/eYVOLXa7LrZwOpz2/img/c5cc4998-db60-4c94-9c8d-ff5de23ea6ea.png)

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/eYVOLXa7LrZwOpz2/img/644f4040-8f02-4bbb-9b00-bd3877acb125.png)

# 各种功能说明

#### Standby mode 

This sensor stops its operation and goes into standby mode which reduces the power consumption **by writing “1” to the standby control register** _**STANDBY**_. Standby mode is also established after power-on or other system reset operation.  

**Register List of Standby setting**  

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/eYVOLXa7LrZwOpz2/img/8b78970c-de47-42c7-9359-c91835f4946a.png)

The serial communication registers hold the previous values. However, the address registers transmitted in standby mode are overwritten. The serial communication block operates even in standby mode, so **standby mode can be canceled by setting the STANDBY register to “0”**. Some time is required for sensor internal circuit stabilization after standby mode is canceled. For details on the sequence of setting and cancel of standby mode, see the sensor setting flow after power on. **After standby mode is canceled, a normal image is output from the 9 frames after internal regulator stabilization (29 ms or more)**.  

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/eYVOLXa7LrZwOpz2/img/98e2e65c-9f0b-45e1-9348-26a7413d578c.png)

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/eYVOLXa7LrZwOpz2/img/4cdfa8e7-965b-42ac-80a8-212be0b2f72c.png)

配置寄存器的时候设置成Standby 模式

#### Readout Drive Modes 

The table below lists the operating modes available with this sensor. (Each value is the Max. frame rate of each number of ch.) 

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/eYVOLXa7LrZwOpz2/img/076d10ed-9581-401a-aa1d-85da487e4428.png)

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/eYVOLXa7LrZwOpz2/img/74d01984-970f-4965-9e0d-0400740a13e9.png)

这个FREQ决定了每个通道的数据速率

# 相机寄存器说明

#### Register Map (There is a possible to change the registers on this document.) 

This sensor has a total of 5376 bytes of registers, composed of registers with address 00h to FFh that correspond to Chip ID = 02h to 0Ch, 10h to 19h. Use the initial values for empty address. Some registers must be change from the initial values, so the sensor control side should be capable of setting 5376 bytes.

**There are three different register reflection timings.**

About the Reflection timing column of the Register Map, **registers noted as "I" are reflected immediately after writing to register, registers noted as "S" are set during standby mode and reflected after standby canceled, registers noted as "V" are reflected at “Fame reflection register reflection timing” on the figure described in the section of “Setting Registers with Serial Communication”**.

Do not perform communication to addresses and setting not listed in the Register Map. Doing so may result in operation errors.

# Register Map 

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/eYVOLXa7LrZwOpz2/img/cbc6fc40-e4ea-4aec-81ef-9185195876eb.png)

Address and setting value is described in HEXA. For empty part, use it by an Default value

地址和设置的值是16进制描述。

![image](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/eYVOLXa7LrZwOpz2/img/3705f429-a53a-41a3-8984-9c4bf538c263.png): It is neccessary to set in each drive mode. Set suitable values of drive mode with reference to the data sheet.

![image](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/eYVOLXa7LrZwOpz2/img/59923fea-35f8-4e3e-8ada-ccae9708644c.png): It is necessary to change from an initial value at standby period. 

Symbols: Def(Default value), R.T.(Reflection timing), I(Reflected Immediately), V(Reflected after XVS), S(Please set the register at standby period. Reflected affter the standby mode.)

|  **Symbols**  |  **Description**  |
| --- | --- |
|  Def  |  Default value  |
|  R.T.  |  Reflection timing  |
|  I  |  Reflected Immediately  |
|  V  |  Reflected after XVS  |
|  S  |  Reflected affter the standby mode  |

# 相机测试图模式（Patton Generator）

The output area of the PG pattern is the effective area of each mode. (The area shown in the blue of the following figure is output area.) In a pattern (0, 4, 5, 6) that specifies the location, the origin of horizontal is the next pixel of SAV 4th and the origin of vertical is the next line of frame information line. By the register PGTHRU, the background can be selected to "Fixed 0h (pattern 0, 6)" and "Setting PGDATA2 (pattern 4, 5)" and "Through" (imaging data). The figure below shows the details. 

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/eYVOLXa7LrZwOpz2/img/8ad0149e-de54-4227-b6ef-2dc2c0e8c998.png)

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/eYVOLXa7LrZwOpz2/img/c884d622-ce5a-45d9-a162-62fec10e3443.png)

##### 1. 输出区域（Output Area）

*   **定义**：PG模式的输出区域是每种模式的有效区域。在提供的图示中，蓝色区域表示输出区域。
    
*   **例子**：假设你有一个图像传感器，它生成的图像分辨率为1920x1080。输出区域可能是其中的一部分，比如中间的1280x720像素区域。这个区域是实际生成图像的有效区域。
    

##### 2. 模式定位（Pattern Location）

*   **定义**：在指定位置的模式（0, 4, 5, 6）中：
    
    *   **水平起点**：是SAV（Start of Active Video）第4个像素的下一个像素。
        
    *   **垂直起点**：是帧信息行的下一行。
        
*   **例子**：假设SAV的第4个像素位于水平位置100，那么水平起点就是第101个像素。如果帧信息行位于垂直位置10，那么垂直起点就是第11行。这意味着输出区域的左上角将从第101列和第11行开始。
    

##### 3. 背景选择（Background Selection）

*   **定义**：通过寄存器PGTHRU，可以选择背景模式：
    
    *   **固定0h（模式0, 6）**：背景设置为固定的0h值（通常是黑色）。
        
    *   **设置PGDATA2（模式4, 5）**：背景由PGDATA2寄存器设置（可以自定义背景颜色或模式）。
        
    *   **Through（成像数据）**：背景直接通过成像数据（即使用实际捕捉的图像数据作为背景）。
        
*   **例子**：如果你选择“固定0h”，那么输出区域之外的背景将是黑色。如果你选择“设置PGDATA2”，你可以将背景设置为特定的颜色或图案。如果你选择“Through”，那么背景将是实际捕捉的图像数据。
    

##### 4. 图示细节

*   **定义**：提供的图示展示了这些设置的详细信息，包括输出区域、模式定位和背景选择的配置。
    
*   **例子**：假设图示中蓝色区域表示1280x720的输出区域，水平起点为101，垂直起点为11。如果你选择“固定0h”，那么除了这个蓝色区域外，其他区域将是黑色。如果你选择“设置PGDATA2”，你可以将背景设置为红色或其他颜色。如果你选择“Through”，那么背景将是实际捕捉的图像数据。
    

##### 综合例子

假设你有一个1920x1080的图像传感器，你希望生成一个1280x720的图像，并且你希望：

*   输出区域从第101列和第11行开始。
    
*   背景设置为红色。
    

你可以通过以下步骤实现：

1.  设置输出区域为1280x720，起点为101列和11行。
    
2.  选择“设置PGDATA2”模式，并将PGDATA2寄存器设置为红色。
    
3.  生成图像时，输出区域内的图像数据将是你捕捉的图像，而输出区域外的背景将是红色。
    

---

#### 图案清单

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/eYVOLXa7LrZwOpz2/img/0ac1437b-e5a5-45be-9efe-f3089020561e.png)

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/eYVOLXa7LrZwOpz2/img/edadc274-d6f8-4b91-8198-ae04fd0c9098.png)

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/eYVOLXa7LrZwOpz2/img/0b5db01d-180f-42e5-abbf-ef753991e540.png)

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/eYVOLXa7LrZwOpz2/img/457c1368-5e4f-4e73-be16-8aab0bcff1ac.png)

# 位宽设置需要更改的寄存器

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/eYVOLXa7LrZwOpz2/img/6f78fefa-d617-43f0-8fca-66ffc9e3ed17.png)

# 曝光设置寄存器

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/eYVOLXa7LrZwOpz2/img/e04a21ed-891f-4182-b919-c303b8a8402a.png)

![image.png](https://alidocs.oss-cn-zhangjiakou.aliyuncs.com/res/eYVOLXa7LrZwOpz2/img/10ce54ac-31bf-4656-b38b-c37118184106.png)

# VMAX参数设置