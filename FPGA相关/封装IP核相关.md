# temp封装IP核相关

#### **1.更改IP复位引脚电平设置**

![img](https://picture-1344593885.cos.ap-beijing.myqcloud.com/5eecdaf48460cde52bc55d42b53da73d39576dfe9d17afb0ac1d964c3b7cbdddf7141c81ae695a8065a117e969287064514f877028eecd5a6eae00f771b9e57774e2b99d6a3745002eb2fb11e24cce032024a8324bda95a42c7cc62e6d91332a)

#### **2.更改Ip核默认时钟大小**

![img](https://picture-1344593885.cos.ap-beijing.myqcloud.com/5eecdaf48460cde52bc55d42b53da73d39576dfe9d17afb0ac1d964c3b7cbdddf7141c81ae695a8065a117e9692870647e14adc2258511f1e891955f3dccc35a4b04f5c9d6bbb58c931df4aff6d4a79b19a9f09914138da9149565b860957ab4)

#### **3.在总体工程中封装其中一个用verilog模块ip的方法（以mem_test为例）**

![img](https://picture-1344593885.cos.ap-beijing.myqcloud.com/5eecdaf48460cde52bc55d42b53da73d39576dfe9d17afb0ac1d964c3b7cbdddf7141c81ae695a8065a117e969287064bff39aec776d5fac9bc809271eb06466ea26d874580d911932f88e79f06b6d52a3d7a5f62347ed5cdb36240b59277002)

![img](https://picture-1344593885.cos.ap-beijing.myqcloud.com/5eecdaf48460cde52bc55d42b53da73d39576dfe9d17afb0ac1d964c3b7cbdddf7141c81ae695a8065a117e969287064d89ddecd1a92d656d2f1a037432081a62ee18946f9f3557b8103ef67066264ab050777c34e142a969508fd59fedd0e8f)

![img](https://alidocs.dingtalk.com/core/api/resources/img/5eecdaf48460cde52bc55d42b53da73d39576dfe9d17afb0ac1d964c3b7cbdddf7141c81ae695a8065a117e969287064a99c3cae3fcc3cf6696fff60506241e48f5f65e9bcff56cebdfa7f5b064af24c06d5ad1542cab12f606601fe23b54967?tmpCode=5ffc922d-49dc-4826-ab7d-d3176f3eef33)

![img](https://picture-1344593885.cos.ap-beijing.myqcloud.com/5eecdaf48460cde52bc55d42b53da73d39576dfe9d17afb0ac1d964c3b7cbdddf7141c81ae695a8065a117e96928706494252a0f5e2b67a41848977e3f8a699fc95a46acf40e63709a11cb9ca7b643cda1b05d6c68116f2ea8af4430009de0b1)



![img](https://picture-1344593885.cos.ap-beijing.myqcloud.com/5eecdaf48460cde52bc55d42b53da73d39576dfe9d17afb0ac1d964c3b7cbdddf7141c81ae695a8065a117e96928706412f922dab89f112af007ce4e6a48edc94de71ff70f37490b4744ea3f7b61b3e06063f2e0f3a43764f39f100446eb8627)

这里封装出来的不只有mem_test.v文件，会有ps_block等ip也被封装进来，不需要可以去掉

![img](https://picture-1344593885.cos.ap-beijing.myqcloud.com/5eecdaf48460cde52bc55d42b53da73d39576dfe9d17afb0ac1d964c3b7cbdddf7141c81ae695a8065a117e969287064b8423c5040a7af457556b9edd3210ed7d25eb4adf65f81249f44daf875c7304ca2238d60cc7ac2a9bbb8e147348d6c36)

![img](https://picture-1344593885.cos.ap-beijing.myqcloud.com/5eecdaf48460cde52bc55d42b53da73d39576dfe9d17afb0ac1d964c3b7cbdddf7141c81ae695a8065a117e969287064b2ef886461f183aaab29332e2590017d6eb88643c39fefd8385ce3cc519860519132f4ff57be15e2606601fe23b54967)



#### **4.如果出现ip核加进去无法更改引脚绑定的情况，在封装ip前，将总工程的xdc删除，这里没有.xdc再生成ip核应该就不会和其他工程的约束文件冲突**![img](https://picture-1344593885.cos.ap-beijing.myqcloud.com/5eecdaf48460cde52bc55d42b53da73d39576dfe9d17afb0ac1d964c3b7cbdddf7141c81ae695a8065a117e9692870641f63273d312b2ada8664d92a15c141ef1d08c8961547d0433059dcb25778d119c938904ab82a43972c7cc62e6d91332a)





# **如何****自定义含AXI4接口IP核-ps与pl的交互**

### **目的：****封装带有AXI4接口的IP的方式，实现PS和PL的数据交换**

#### **步骤一：打开**[**Vivado**](https://so.csdn.net/so/search?q=Vivado&spm=1001.2101.3001.7020)**后，点击下图位置的Manage IP,并在选项中选择New IP Location。**

![img](https://picture-1344593885.cos.ap-beijing.myqcloud.com/5eecdaf48460cde52bc55d42b53da73d39576dfe9d17afb0ac1d964c3b7cbdddf7141c81ae695a8065a117e969287064426606e01b13ecfbb10dc20088a3b1bc0e1adf426ca5ce3f77f9d124e54f7bd3428cf0aa07d4cba6985ea16e2deb3474)

然后再设置界面自行选择一个保存IP的地址，其他保持默认即可。点击Finish，完成创建。

![img](https://picture-1344593885.cos.ap-beijing.myqcloud.com/5eecdaf48460cde52bc55d42b53da73d39576dfe9d17afb0ac1d964c3b7cbdddf7141c81ae695a8065a117e969287064aedadb5703eb452a6a52a8b32ad4175024031e7315f76326a1bcf10b97ed768d58c58330ca0b7da7a900dfd662445084)

进入设计后在工具栏点击下图位置

![img](https://picture-1344593885.cos.ap-beijing.myqcloud.com/5eecdaf48460cde52bc55d42b53da73d39576dfe9d17afb0ac1d964c3b7cbdddf7141c81ae695a8065a117e969287064f26a4afe3ba671867c41a26e3f6a283d0c4019d4196926efed4a181b71a94d8737ca97defd744cc8bbb8e147348d6c36)

在创建过程中，参数配置过程如下图所示，其他配置则默认即可

![img](https://picture-1344593885.cos.ap-beijing.myqcloud.com/5eecdaf48460cde52bc55d42b53da73d39576dfe9d17afb0ac1d964c3b7cbdddf7141c81ae695a8065a117e9692870645fb17b69bc7beda0411cc54efe2e2d98ddfe34e0322f60b3262ceed3e603502390d37640ee5c022d9508fd59fedd0e8f)

![img](https://picture-1344593885.cos.ap-beijing.myqcloud.com/5eecdaf48460cde52bc55d42b53da73d39576dfe9d17afb0ac1d964c3b7cbdddf7141c81ae695a8065a117e9692870646ded009ae1329a3b9b4eff97e748c4c4c5e671c4d78f262b41bfb3d6fe595d462b18ec8dc2033b87f39f100446eb8627)

![img](https://picture-1344593885.cos.ap-beijing.myqcloud.com/5eecdaf48460cde52bc55d42b53da73d39576dfe9d17afb0ac1d964c3b7cbdddf7141c81ae695a8065a117e96928706413cde8cdcc7b0c556545c4982f5471582f4ede3b00afc8df0b1c73cd35efb20ea7bdcfcb224c13e71051f7e0fe55f913)

上图参数在本实验中可保持默认，但此配置比较重要，则此处做个介绍：

###### **Interface Tpye（接口类型）：**

共三种接口类型可选，分别是 Lite、 Full 和 Stream。 AXI4-Lite 接口是简化版的 AXI4 接口， 用于较少数据量的存储映射通信； AXI4-Full 接口是高性能存储映射接口，用于较多数据量的存储映射通信； AXI4-Stream 用于高速数据流传输，非存储映射接口。本次实验只需少量数据的通信，因此接口类型选择默认的 Lite 接口。

###### **Interface Mode（接口模式）：**

接口模式有 Slave（从机）和 Master（主机）两种模式可选， AXI 协议是主机和从机通过“握手”的方式建立连接，这里选择默认的 Slave 接口模式。

###### **Data Width（数据宽度）：**

数据位宽保持默认，即 32 位位宽。

###### **Memory Size（存储器大小）：** 

在 AXI4-Lite 接口模式下，该选项不可设置。

###### **Number of Registers（寄存器数量）：**

用于配置寄存器的数量，这里保持默认。

点击“ Next”按钮。



#### **步骤二：添加完成后，在IP Catalog界面可以看见我们新添加的IP。接下来我们需要对这个IP进行编辑。选中这个IP，右键—Edit in IP Packager。弹出窗口默认点OK即可。**

![img](https://alidocs.dingtalk.com/core/api/resources/img/5eecdaf48460cde52bc55d42b53da73d39576dfe9d17afb0ac1d964c3b7cbdddf7141c81ae695a8065a117e969287064a467468496d5ba448a5506f66e8478dfd9fa6ddd6de8209712fe7279a33636198db07a8c93f550202c7cc62e6d91332a?tmpCode=5ffc922d-49dc-4826-ab7d-d3176f3eef33)

此时会新打开一个工程。打开这两个文件的Verilog源代码。

![img](https://alidocs.dingtalk.com/core/api/resources/img/5eecdaf48460cde52bc55d42b53da73d39576dfe9d17afb0ac1d964c3b7cbdddf7141c81ae695a8065a117e9692870648922c2e3866820305414ba3dc5a5b89b553f309d0c4de5d0126deaec833f057d951387bfbb3e6736a8af4430009de0b1?tmpCode=5ffc922d-49dc-4826-ab7d-d3176f3eef33)

此处我们需要简单介绍下面这个文件实现AXI4协议下的读写寄存器的功能。如下图所示，下面定义的四个寄存器则为我们前面配置时候设置的四个寄存器，对这四个寄存器的读写即可实现PS与PL端的数据交互，且这八个寄存器均为32位宽。

![img](https://alidocs.dingtalk.com/core/api/resources/img/5eecdaf48460cde52bc55d42b53da73d39576dfe9d17afb0ac1d964c3b7cbdddf7141c81ae695a8065a117e9692870647736bc43b0cb8259b4e59c15b3bef70be9be7fb68088afc9194330987525be617113de4262deb72ea5f44275aa76f220?tmpCode=5ffc922d-49dc-4826-ab7d-d3176f3eef33)

![img](https://alidocs.dingtalk.com/core/api/resources/img/5eecdaf48460cde52bc55d42b53da73d39576dfe9d17afb0ac1d964c3b7cbdddf7141c81ae695a8065a117e969287064333622aca071e4bf8bbbbbbab8c7abfcb5c36b58192a6266c90be4c1ac5b129efe719ff1202e5ca3e2835520bce621d8?tmpCode=5ffc922d-49dc-4826-ab7d-d3176f3eef33)

添加端口。

![img](https://alidocs.dingtalk.com/core/api/resources/img/5eecdaf48460cde52bc55d42b53da73d39576dfe9d17afb0ac1d964c3b7cbdddf7141c81ae695a8065a117e969287064d76193bd8ce096938c6ff915a77041e9356013f8dc00a9b7af7b6e3aea8548ec834a47d305a4d64ce2835520bce621d8?tmpCode=5ffc922d-49dc-4826-ab7d-d3176f3eef33)



## **关于AXI-Lite协议**

![img](https://alidocs.dingtalk.com/core/api/resources/img/5eecdaf48460cde52bc55d42b53da73d39576dfe9d17afb0ac1d964c3b7cbdddf7141c81ae695a8065a117e9692870645ca28642852c2ac1a1509d7d5edc1d8eef21e193c8aabf9b2a5869a95ac11ed0cec64baf279b49cef2ac17fb040400bd?tmpCode=5ffc922d-49dc-4826-ab7d-d3176f3eef33)

每个通道都包含了一组信号，尤其需要注意的是 VALID 和 READY 信号。VALID 信号由源端（source）产生，表示当前地址或者数据线上的信息是有效的；而 READY 信号由目的端（destination）产生，则表示已经准备好接收地址、数据以及控制信息。

举个例子，对于读数据通道，Slave需要将数据发送给Master，所以Slave是源端，也就是Slave负责产生 VALID 信号，Master负责产生READY信号

对于写数据通道，Master需要将数据发送给Slave，所以Master是源端，也就是Master负责产生 VALID 信号，Slave负责产生READY信号。

在由通道传输信息的时候，需要通过 VALID 和 READY 信号进行握手，如下图所示，图片中的 `INFORMATION` 是指通过通道传输的某种信息，可以是地址、数据、控制信号等等。

![img](https://alidocs.dingtalk.com/core/api/resources/img/5eecdaf48460cde52bc55d42b53da73d39576dfe9d17afb0ac1d964c3b7cbdddf7141c81ae695a8065a117e96928706459a8b8d5f921e3f4e961207bb1881b2875990afe51b995a720ac2c0eaac5e38e3862e53e1757bdc7a5f44275aa76f220?tmpCode=5ffc922d-49dc-4826-ab7d-d3176f3eef33)

为了防止死锁，VALID信号和READY必须遵守以下的约定：

VALID信号的拉高不能依赖于 READY 信号，也就是说源端不允许等目的端的 READY 信号拉高之后，才将 VALID 信号拉高。而且， 一旦 VALID 拉高，源端必须保持其处于拉高状态，直至成功握手（在时钟上升沿检测到 VALID 和 READY 均为高电平）后才能拉低 VALID

目的端可以等检测到 VALID 信号拉高后，才将READY信号拉高；也可以不等

到这里，已经简单介绍了 AXI4-Lite 接口的读写过程，以及握手协议。

![img](https://picture-1344593885.cos.ap-beijing.myqcloud.com/5eecdaf48460cde52bc55d42b53da73d39576dfe9d17afb0ac1d964c3b7cbdddf7141c81ae695a8065a117e96928706474d41693702333a741fe2cf6a6aa62999bec292c272805baf963944a42a1a9a03cda7f3387d112191051f7e0fe55f913)

![img](https://alidocs.dingtalk.com/core/api/resources/img/5eecdaf48460cde52bc55d42b53da73d39576dfe9d17afb0ac1d964c3b7cbdddf7141c81ae695a8065a117e969287064fbc2e1dc2c1007c3f30012ed243efb9541d15476634678795fe928a96f5b2f9f73685f6c45d15a9cbbb8e147348d6c36?tmpCode=5ffc922d-49dc-4826-ab7d-d3176f3eef33)

![img](https://alidocs.dingtalk.com/core/api/resources/img/5eecdaf48460cde52bc55d42b53da73d39576dfe9d17afb0ac1d964c3b7cbdddf7141c81ae695a8065a117e969287064b7e6f42c43e03e1b198589666109ac998be5b3cb10e1993a5844eb7151c67f6c029f507adeba14a4e2835520bce621d8?tmpCode=5ffc922d-49dc-4826-ab7d-d3176f3eef33)

![img](https://alidocs.dingtalk.com/core/api/resources/img/5eecdaf48460cde52bc55d42b53da73d39576dfe9d17afb0ac1d964c3b7cbdddf7141c81ae695a8065a117e9692870643b2a8e9e3d4ea593b7fea140a62166de8a82a5f65c1173293385b46876655feffabc7132d89e213bf2ac17fb040400bd?tmpCode=5ffc922d-49dc-4826-ab7d-d3176f3eef33)

![img](https://alidocs.dingtalk.com/core/api/resources/img/5eecdaf48460cde52bc55d42b53da73d39576dfe9d17afb0ac1d964c3b7cbdddf7141c81ae695a8065a117e9692870645a74353dfddbe334de5e9c55ad0bf4e3fed36ad6863ada733b1182ee8c13382719155f05faefa9842c7cc62e6d91332a?tmpCode=5ffc922d-49dc-4826-ab7d-d3176f3eef33)

![img](https://alidocs.dingtalk.com/core/api/resources/img/5eecdaf48460cde52bc55d42b53da73d39576dfe9d17afb0ac1d964c3b7cbdddf7141c81ae695a8065a117e96928706470768f5dee6fc6db4df66e1269d37d79635e78dbc7ba40f3e7bc03bb9fd2e6e0b9a3354a0c388798149565b860957ab4?tmpCode=5ffc922d-49dc-4826-ab7d-d3176f3eef33)

![img](https://picture-1344593885.cos.ap-beijing.myqcloud.com/5eecdaf48460cde52bc55d42b53da73d39576dfe9d17afb0ac1d964c3b7cbdddf7141c81ae695a8065a117e9692870643c3fa79570c9b8c7f39b24d98f35eb808971e38ee06097d6b9c5271d6a3ed13bb2de773e2fe790072c7cc62e6d91332a)

![img](https://picture-1344593885.cos.ap-beijing.myqcloud.com/5eecdaf48460cde52bc55d42b53da73d39576dfe9d17afb0ac1d964c3b7cbdddf7141c81ae695a8065a117e969287064c715331995c5c9b1fe0613cd3a2fc20f5d0663e161aa5973fe9019d8d08098ef03e8425870805cdce2835520bce621d8)

![img](https://picture-1344593885.cos.ap-beijing.myqcloud.com/5eecdaf48460cde52bc55d42b53da73d39576dfe9d17afb0ac1d964c3b7cbdddf7141c81ae695a8065a117e969287064d260dbc70a89377c91b55fd29f7060ee315bab396b65d30e012dc3f1be2f764488bda8310d9d53fda900dfd662445084)





```
if (slv_reg_wren)
begin
    case (axi_awaddr[ADDR_LSB+OPT_MEM_ADDR_BITS:ADDR_LSB])
        3'h0:
            for (byte_index = 0; byte_index <= (C_S_AXI_DATA_WIDTH/8)-1; byte_index = byte_index+1)
                if (S_AXI_WSTRB[byte_index] == 1) begin
                    slv_reg0[(byte_index*8) +: 8] <= S_AXI_WDATA[(byte_index*8) +: 8];
                end
    endcase
end
```

这段代码是Verilog HDL的语法，用于实现基于AXI4-Lite总线的写操作。它的功能是根据写地址（`axi_awaddr`）和写选通信号（`S_AXI_WSTRB`），将数据写入对应的寄存器（`slv_reg0`到`slv_reg7`）。以下是对这段代码的详细解析：

### 1. **整体结构**

```
if (slv_reg_wren)
begin
    case (axi_awaddr[ADDR_LSB+OPT_MEM_ADDR_BITS:ADDR_LSB])
        3'h0:
            for (byte_index = 0; byte_index <= (C_S_AXI_DATA_WIDTH/8)-1; byte_index = byte_index+1)
                if (S_AXI_WSTRB[byte_index] == 1) begin
                    slv_reg0[(byte_index*8) +: 8] <= S_AXI_WDATA[(byte_index*8) +: 8];
                end
    endcase
end
```

- `slv_reg_wren`：写使能信号，表示当前是一个有效的写操作。
- `case`**语句**：根据写地址（`axi_awaddr`）选择对应的寄存器。
- `for`**循环**：遍历数据总线的每个字节（byte）。
- `if (S_AXI_WSTRB[byte_index] == 1)`：检查写选通信号，决定是否更新当前字节。

------

### 2. **关键语法解析**

#### (1) `case`**语句**

```
case (axi_awaddr[ADDR_LSB+OPT_MEM_ADDR_BITS:ADDR_LSB])
    3'h0: // 对应 slv_reg0
    3'h1: // 对应 slv_reg1
    ...
endcase
```

- **功能**：根据写地址（`axi_awaddr`）选择对应的寄存器。
- `ADDR_LSB`：地址的最低有效位（Least Significant Bit），用于对齐地址。
- `OPT_MEM_ADDR_BITS`：地址的位数，用于选择寄存器。

#### (2) `for`**循环**

```
for (byte_index = 0; byte_index <= (C_S_AXI_DATA_WIDTH/8)-1; byte_index = byte_index+1)
```

- **功能**：遍历数据总线的每个字节。
- `C_S_AXI_DATA_WIDTH`：数据总线的宽度（默认为32位）。
- `C_S_AXI_DATA_WIDTH/8`：计算字节数（例如，32位总线对应4个字节）。

#### (3) `if (S_AXI_WSTRB[byte_index] == 1)`

```
if (S_AXI_WSTRB[byte_index] == 1)
```

- **功能**：检查写选通信号（`S_AXI_WSTRB`）的当前字节是否有效。
- `S_AXI_WSTRB`：写选通信号，每一位对应一个字节。例如，`S_AXI_WSTRB = 4'b1100`表示高2字节有效。

#### (4) `slv_reg0[(byte_index*8) +: 8]`

```
slv_reg0[(byte_index*8) +: 8] <= S_AXI_WDATA[(byte_index*8) +: 8];
```

- **功能**：将`S_AXI_WDATA`的当前字节写入`slv_reg0`的对应字节。
- `+: 8`：Verilog中的位选择语法，表示从起始位开始选择8位。
  - 例如，`byte_index = 1`时：
    - `byte_index*8 = 8`。
    - `[(byte_index*8) +: 8]`表示选择第8位到第15位（即第2个字节）。

------

### 3. **代码功能**

这段代码的功能是：

1. 根据写地址（`axi_awaddr`）选择对应的寄存器（`slv_reg0`到`slv_reg7`）。
2. 遍历数据总线的每个字节，检查写选通信号（`S_AXI_WSTRB`）是否有效。
3. 如果有效，则将`S_AXI_WDATA`的对应字节写入寄存器的对应字节。

------

### 4. **示例**

假设：

- `C_S_AXI_DATA_WIDTH = 32`（4字节）。
- `S_AXI_WSTRB = 4'b1100`（高2字节有效）。
- `S_AXI_WDATA = 32'hAABBCCDD`。
- `axi_awaddr`选择`slv_reg0`。

执行过程：

1. `byte_index = 0`：
   - `S_AXI_WSTRB[0] = 0`，不更新。
2. `byte_index = 1`：
   - `S_AXI_WSTRB[1] = 0`，不更新。
3. `byte_index = 2`：
   - `S_AXI_WSTRB[2] = 1`，更新`slv_reg0[23:16]`为`S_AXI_WDATA[23:16] = 0xAA`。
4. `byte_index = 3`：
   - `S_AXI_WSTRB[3] = 1`，更新`slv_reg0[31:24]`为`S_AXI_WDATA[31:24] = 0xBB`。

最终，`slv_reg0`的值更新为`32'hAABBxxxx`（`x`表示未更新的字节）。

### 5. **总结**

这段代码的核心是通过`case`、`for`和`if`语句，实现基于AXI4-Lite总线的字节级写操作。它的语法是Verilog中常见的组合逻辑和时序逻辑的混合使用，适用于处理总线协议中的细粒度数据更新。



在硬件设计中，`ADDR_LSB`（Least Significant Bit，最低有效位）用于确定地址的最低有效位的位置，以便正确访问寄存器或存储器。它的值取决于数据总线的宽度（`C_S_AXI_DATA_WIDTH`），即每个地址可以访问的数据位数。

### 为什么 `ADDR_LSB` 的值与数据宽度相关？

1. **32位数据宽度（**`C_S_AXI_DATA_WIDTH = 32`**）**：
   - 每个地址对应 4 字节（32 位）的数据。
   - 地址的最低 2 位（`ADDR_LSB = 2`）用于选择 4 字节中的具体字节（例如，`00` 表示第 0 字节，`01` 表示第 1 字节，依此类推）。
   - 因此，地址的高位（`n downto 2`）用于选择 4 字节的块。
2. **64位数据宽度（**`C_S_AXI_DATA_WIDTH = 64`**）**：
   - 每个地址对应 8 字节（64 位）的数据。
   - 地址的最低 3 位（`ADDR_LSB = 3`）用于选择 8 字节中的具体字节。
   - 因此，地址的高位（`n downto 3`）用于选择 8 字节的块。

### 公式推导

`ADDR_LSB` 的值可以通过以下公式计算：ADDR_LSB=log⁡2(C_S_AXI_DATA_WIDTH/8)ADDR_LSB=log2(C_S_AXI_DATA_WIDTH/8)

- 对于 32 位数据宽度：ADDR_LSB=log⁡2(32/8)=log⁡2(4)=2ADDR_LSB=log2(32/8)=log2(4)=2
- 对于 64 位数据宽度：ADDR_LSB=log⁡2(64/8)=log⁡2(8)=3ADDR_LSB=log2(64/8)=log2(8)=3

### 总结

`ADDR_LSB` 的值取决于数据总线的宽度，因为它决定了每个地址可以访问的数据量。通过调整 `ADDR_LSB`，可以确保地址的高位正确映射到存储器或寄存器的块，而低位用于选择块内的具体字节。





















双击“component.xml”文件

![img](https://alidocs.dingtalk.com/core/api/resources/img/5eecdaf48460cde52bc55d42b53da73d39576dfe9d17afb0ac1d964c3b7cbdddf7141c81ae695a8065a117e969287064e69091c3fcbdcabd50d96b548a91109b44719337dbf4d998757fef4654e7b221b575c7e31763a97c149565b860957ab4?tmpCode=5ffc922d-49dc-4826-ab7d-d3176f3eef33)

在“File Groups”选项中点击“Merge changers from File Groups Wizard”

在“Customization Parameters”选项中点击“Merge changes form Customization Parameters

Wizard

点击“Re-Package IP”完成 IP 的修改

![img](https://alidocs.dingtalk.com/core/api/resources/img/5eecdaf48460cde52bc55d42b53da73d39576dfe9d17afb0ac1d964c3b7cbdddf7141c81ae695a8065a117e96928706495e4e5c58d332ec584a00629fc2c4067d8c5cce2aed97741b34ad9da5be1935eca8017a7b4c404cb1051f7e0fe55f913?tmpCode=5ffc922d-49dc-4826-ab7d-d3176f3eef33)













参考：

[ZYNQ PS与PL基于AXI-Lite通信（超详细开发流程） - 知乎](https://zhuanlan.zhihu.com/p/582335657)

[zynq设计学习笔记6——自定义含AXI4接口IP核-ps与pl的交互_zynq 自定义axi ip核-CSDN博客](https://blog.csdn.net/qq_42025108/article/details/113134186?spm=1001.2014.3001.5506)

[zynq开发系列6：创建AXI IP实现PS对PL的数据配置（步骤三配置SDK）_使用ps配置pl中的led频率寄存器-CSDN博客](https://blog.csdn.net/xiong_xin/article/details/115493339)