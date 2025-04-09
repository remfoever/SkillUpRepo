# 手动设置环境变量

## 步骤：

#### 找到 Xilinx 工具的安装路径，例如：

- Vitis 的 bat 文件路径一般为 : `D:\Xilinx\Vitis\<版本号>\bin\xsct.bat`
- 
- xsct.bat路径:         D:\Xilinx\Vitis\2020.1\bin      （找到自己的路径）

![image-20250312235143347](https://picture-1344593885.cos.ap-beijing.myqcloud.com/image-20250312235143347.png)

#### 打开环境变量设置：

- 右键点击“此电脑”或“我的电脑”，选择“属性”。
- 点击“高级系统设置”。
- 在“系统属性”窗口中，点击“环境变量”。

![image-20250312222728827](https://picture-1344593885.cos.ap-beijing.myqcloud.com/image-20250312222728827.png)

![image-20250312222831596](https://picture-1344593885.cos.ap-beijing.myqcloud.com/image-20250312222831596.png)



#### 添加新的系统环境变量：

- 在“系统变量”部分，点击“新建”。
- 输入变量名（统一复制 `XILINX_VITIS`）和变量值（例如 ` D:\Xilinx\Vitis\2020.1\bin\xsct.bat`）。
- 点击“确定”保存。

![image-20250312222907642](https://picture-1344593885.cos.ap-beijing.myqcloud.com/image-20250312222907642.png)

在刚才的`D:\Xilinx\Vitis\2020.1\bin`路径下继续浏览文件到`xsct.bat`文件（这个文件在倒数几个，从后往前找）

![image-20250312235555347](https://picture-1344593885.cos.ap-beijing.myqcloud.com/image-20250312235555347.png)

![image-20250312235237650](https://picture-1344593885.cos.ap-beijing.myqcloud.com/image-20250312235237650.png)

上图为最终路径到`xsct.bat`.     环境变量名一定保持一致   `XILINX_VITIS`



更改环境变量后，四个bat文件都无需更改路径，直接使用即可











# 配置环境变量
## 使用环境变量的原因
在团队协作或多人使用环境下，每位用户的Xilinx工具安装路径可能不同（例如：有人安装在`C:\Xilinx`，有人安装在`D:\Program Files\Xilinx`）。如果批处理脚本中直接使用绝对路径，每次不同用户使用时都需要修改脚本内容，这会导致：

1. 使用不便 - 每次运行前都要编辑脚本
2. 容易出错 - 可能忘记修改或修改错误
3. 维护困难 - 需要为每个用户维护不同版本的脚本

**解决方案：使用环境变量**

通过配置系统或用户级别的环境变量，可以解决路径差异问题：

1. **统一性**：所有用户使用相同的脚本
2. **灵活性**：每个用户只需设置一次自己的环境变量
3. **可维护性**：脚本无需因用户不同而修改

## 推荐配置环境变量方法

**建议设置以下步骤配置环境变量：**

步骤 ：

1. 先找到 Xilinx 工具的安装路径，例如：Vitis 的 bat 文件路径一般为 : `C:\Xilinx\Vitis\<版本号>\bin\xsct.bat`

2. 打开环境变量设置：

   - 右键点击“此电脑”或“我的电脑”，选择“属性”。
   - 点击“高级系统设置”。
   - 在“系统属性”窗口中，点击“环境变量”。

   ![image-20250312222728827](https://picture-1344593885.cos.ap-beijing.myqcloud.com/image-20250312222728827.png)

   ![image-20250312222831596](https://picture-1344593885.cos.ap-beijing.myqcloud.com/image-20250312222831596.png)

3. 添加新的系统环境变量：

   - 在“系统变量”部分，点击“新建”。
   - 输入变量名（统一复制 `XILINX_VITIS`）和变量值（笔者环境变量为 ` D:\Xilinx\Vitis\2020.1\bin\xsct.bat`，以用户安装实际路径为准）。
   - 点击“确定”保存。

   ![image-20250312222907642](https://picture-1344593885.cos.ap-beijing.myqcloud.com/image-20250312222907642.png)

   在刚才的`D:\Xilinx\Vitis\2020.1\bin`路径下继续浏览文件到`xsct.bat`文件（这个文件在倒数几个，从后往前找）

   ![image-20250312235555347](https://picture-1344593885.cos.ap-beijing.myqcloud.com/image-20250312235555347.png)

   ![image-20250312235237650](https://picture-1344593885.cos.ap-beijing.myqcloud.com/image-20250312235237650.png)

   上图为最终路径到`xsct.bat`.     环境变量名一定保持一致   `XILINX_VITIS`







































