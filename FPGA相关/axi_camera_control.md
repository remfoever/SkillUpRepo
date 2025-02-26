# axi_camera_control IP核设计



![image-20250225165348722](https://picture-1344593885.cos.ap-beijing.myqcloud.com/image-20250225165348722.png)

camera寄存器	reg 0

|   Filed Name   |  Bits  | Type | Reset Value | Description |
| :------------: | :----: | :--: | :---------: | :---------: |
| rst_data_width |   0    |  rw  |     0x0     | 高电平复位  |
|     S_sel      | [5:1]  |  rw  |     0x0     |   8/10/12   |
|      resv      | [31:6] |  rw  |     0x0     |    resv     |



PS地址有效输出寄存器	reg1

|    Filed Name     |  Bits  | Type | Reset Value |  Description   |
| :---------------: | :----: | :--: | :---------: | :------------: |
| syn_addr_a1_valid |   0    |  rw  |     0x0     | 地址A1设置有效 |
| syn_addr_a2_valid |   1    |  rw  |     0x0     | 地址A2设置有效 |
|       resv        | [31:2] |  rw  |     0x0     |      resv      |





解串模块设置寄存器	reg2

|   Filed Name   |  Bits  | Type | Reset Value | Description  |
| :------------: | :----: | :--: | :---------: | :----------: |
| hp_trig_1_intr |   0    |  r   |     0x0     |              |
| hp_trig_2_intr |   1    |  r   |     0x0     |              |
| slv_reg2[31:2] | [31:2] |  r   |     0x0     | 计数中断个数 |



解串模块设置寄存器	reg6

|   Filed Name   |  Bits   | Type | Reset Value | Description |
| :------------: | :-----: | :--: | :---------: | :---------: |
|   cur_status   | [26:0]  |  rw  |     0x0     |  当前状态   |
| slv_reg6[26:0] | [31:27] |  rw  |     0x0     |   计数器    |



