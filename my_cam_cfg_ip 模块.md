## my_cam_cfg_ip 模块

![image-20250402164255364](https://picture-1344593885.cos.ap-beijing.myqcloud.com/image-20250402164255364.png)

 ### 简介

这个相机模块主要用于控制相机：

1. 写入PS端DDR4的地址(addr[31:0])
2. 写入PS端DDR4地址的有效使能(addr_valid)
3. 复位解串模块引脚(rst_data_width)
4. 解串模块的位深设置(S_sel[3:0])
5. (im_cfg_reg_valid)
6. im_cfg_reg_addr[7:0]
7. im_cfg_reg[31:0]



### 用户数据输入输出

等我补充吧，先忙了...   T~T

### 寄存器定义

 相机控制预留寄存器64个

| 寄存器序列 | 寄存器名称               | 寄存器类型 | 寄存器功能                                                   | 备注 |
| ---------- | ------------------------ | ---------- | ------------------------------------------------------------ | ---- |
| slv_reg0   | reserve                  | 读写       |                                                              |      |
| slv_reg1   | reserve                  | 读写       |                                                              |      |
| slv_reg2   |                          | 只读       | 位域[0]    trig_ps_1_intr<br />位域[1]    trig_ps_2_intr <br />位域[5:2]    ps_1_pix_width<br />位域[9:6]    ps_2_pix_width<br />位域[13:10]    ps_1_resolution_ratio<br />位域[17:14]    ps_2_resolution_ratio<br />位域[18]    trig_ps_zx_intr  读取质心数据中断信号 |      |
| slv_reg3   | reserve                  | 读写       |                                                              |      |
| slv_reg4   | reserve                  | 读写       |                                                              |      |
| slv_reg5   | reserve                  | 读写       |                                                              |      |
| slv_reg6   | 地址AB桶计数和状态寄存器 | 只读       | 位域[26:0]    addr_wr_success   计数<br />位域[31:27]    cur_status    当前地址AB桶状态 |      |
| slv_reg7   | reserve                  | 读写       |                                                              |      |
| slv_reg8   | sum_x_hi                 | 读写       | sum_x    高32位                                              |      |
| slv_reg9   | sum_x_lo                 | 读写       | sum_x    低32位                                              |      |
| slv_reg10  | sum_y_hi                 | 读写       | sum_y    高32位                                              |      |
| slv_reg11  | sum_y_lo                 | 读写       | sum_y   低32位                                               |      |
| slv_reg12  | sum_all_hi               | 读写       | sum_all    高32位                                            |      |
| slv_reg13  | sum_all_lo               | 读写       | sum_all    低32位                                            |      |
| slv_reg14  | sum_resolution           | 读写       | 位域[3:0]:    分辨率                                         |      |
| slv_reg15  | camclk_cnt_hi            | 读写       | camclk_cnt    高32位                                         |      |
| slv_reg16  | camclk_cnt_lo            | 读写       | camclk_cnt    低32位                                         |      |













