# AXI4-Lite源代码分析

## Verilog +: -:语法

AXI4-Lite源代码中使用

```
slv_reg0[(byte_index8) +: 8] <= S_AXI_WDATA[(byte_index8) +: 8]；

变量[起始地址 +: 数据位宽] <–等价于–> 变量[(起始地址+数据位宽-1)：起始地址]
data[0 +: 8]  <--等价于--> data[7:0]
data[15 +: 2] <--等价于--> data[16:15]

变量[结束地址 -: 数据位宽] <–等价于–> 变量[结束地址：(结束地址-数据位宽+1)]
data[7 -: 8]  <--等价于--> data[7:0]
data[15 -: 2] <--等价于--> data[15:14]
```



## 1.AXI-Lite源代码关键信号分析

重点关注代码的写入逻辑和输出逻辑

### 1.1AXI-Lite-Slave 源码分析

```verilog
parameter integer C_S_AXI_DATA_WIDTH	= 32,
parameter integer C_S_AXI_ADDR_WIDTH	= 5
```

源码中首先定义了数据位宽和地址位宽，我在生成该源码时设定DATA_WIDTH= 32,ADDR_WIDTH= 5

问题来了：ADDR_WIDTH 在这里为什么只有5？看一下代码：

```verilog
case ( axi_awaddr[ADDR_LSB+OPT_MEM_ADDR_BITS:ADDR_LSB] )

localparam integer ADDR_LSB = (C_S_AXI_DATA_WIDTH/32) + 1;
localparam integer OPT_MEM_ADDR_BITS = 2;
```

以上三行代码要一起看：

这段的意思是对寄存器寻址

计算机中1word = 32bit = 4Bytes, CPU按照字节寻址，

所以寻字节的过程地址+1，寻字就是地址+4；

这里是寻找一个word（一个寄存器存一个word），就应该地址增4；故 ADDR_LSB=2
本代码设定该接口有八个寄存器，故OPT_MEM_ADDR_BITS = 2代表寻址范围是【4：2】也就是8个



ADDR_LSB在32bits datawith 下是2，OPT_MEM_ADDR_BITS在定义8个寄存器情况下为2，地址总线的0、1位从00变换到01、10、11其实就是地址信号axi_awaddr在不停加4。也就验证了不同寄存器的地址偏移4。即地址总线的第2、3、4bit位决定了数据总线访问哪一个寄存器。



```verilog
case ( axi_awaddr[ADDR_LSB+OPT_MEM_ADDR_BITS:ADDR_LSB] )
      2'h0:
        for ( byte_index = 0; byte_index <= (C_S_AXI_DATA_WIDTH/8)-1; byte_index = byte_index+1 )
          if ( S_AXI_WSTRB[byte_index] == 1 ) begin
            slv_reg0[(byte_index*8) +: 8] <= S_AXI_WDATA[(byte_index*8) +: 8];
end
```

这里展示了对字节寻址的逻辑：数据发来每次以字节写入，分四次写完一个寄存器。整个always块的解释为： 在一个时钟周期内，对寄存器写操作时，地址以4递增寻址，如果寻址到slv_reg0【31：0】就分四次，每次一字节对slv_reg0进行赋值（32bits位宽）。如果寻址到slv_reg1就分四次，每次1字节对slv_reg0进行赋值，依此类推



------

其中(byte_index*8) +: 8解释：

如果byte_index = 0，

那么以上可计算为0 *8+：8 = 0+：8 ,

 A+:B的意思是A向上增加B位，

0+：8代表[7:0] 数据段

---

一定要注意，这里展示的是`写数据`逻辑，AXI源码**写和读是分开的**















```verilog
always @(*)
begin
	  // Address decoding for reading registers
	  case ( axi_araddr[ADDR_LSB+OPT_MEM_ADDR_BITS:ADDR_LSB] )
	        3'h0   : reg_data_out <= slv_reg0;
	        3'h1   : reg_data_out <= slv_reg1;
	        3'h2   : reg_data_out <= slv_reg2;
	        3'h3   : reg_data_out <= slv_reg3;
	        3'h4   : reg_data_out <= slv_reg4;
	        3'h5   : reg_data_out <= slv_reg5;
	        3'h6   : reg_data_out <= slv_reg6;
	        3'h7   : reg_data_out <= slv_reg7;
	        default : reg_data_out <= 0;
	  endcase
end
```

这里展示的是AXI4读逻辑，只不过采用的是组合逻辑，axi_araddr信号寻址然后对应地址数据(寄存器中的数据)输出。
**这里需要注意的是**：
四个寄存器从一个固定端口reg_data_out输出，我们以后在修改逻辑时可能需要注意这个端口。

```verilog
if (slv_reg_rden)
    begin
      axi_rdata <= reg_data_out;     // register read data
end 
```

```verilog
assign S_AXI_RDATA	= axi_rdata;
```

这里可以看到，读出的信号从S_AXI_RDATA 端口送出，也符合S_AXI_RDATA是读地址端口









































```mermaid
sdadad
```















































































