# 腾讯云+PicGo+Typora搭建图床

## 1.创建存储桶

[腾讯云COS创建存储桶](https://link.zhihu.com/?target=https%3A//console.cloud.tencent.com/cos/bucket) https://link.zhihu.com/?target=https%3A//console.cloud.tencent.com/cos/bucket

地域选择自己云服务器所在地区就行，私有读写，服务端加密

![image-20250224211446807](%E8%85%BE%E8%AE%AF%E4%BA%91+PicGo.assets/image-20250224211446807.png)

![image-20250224214245123](C:\Users\25794\AppData\Roaming\Typora\typora-user-images\image-20250224214245123.png)

![image-20250224214339957](C:\Users\25794\AppData\Roaming\Typora\typora-user-images\image-20250224214339957.png)

![image-20250224214403672](C:\Users\25794\AppData\Roaming\Typora\typora-user-images\image-20250224214403672.png)

创建完成后点击存储桶，文件列表，创建文件夹(请记住文件夹,等下pigGO配置需要用到)：

![image-20250224214455011](C:\Users\25794\AppData\Roaming\Typora\typora-user-images\image-20250224214455011.png)

## 2.下载PicGo：

官网链接:https://link.zhihu.com/?target=https%3A//picgo.github.io/PicGo-Doc/

安装包链接:https://link.zhihu.com/?target=https%3A//github.com/Molunerfinn/PicGo/releases

![image-20250224212708117](%E8%85%BE%E8%AE%AF%E4%BA%91+PicGo.assets/image-20250224212708117.png)

如果还有其他问题，可以参考官方问题总结：

官方问题总结:https://link.zhihu.com/?target=https%3A//github.com/Molunerfinn/PicGo/blob/dev/FAQ.md



## 3.安装完成后，打开PicGo设置：

![image-20250224212836114](%E8%85%BE%E8%AE%AF%E4%BA%91+PicGo.assets/image-20250224212836114.png)

![image-20250224212911495](https://picture-1344593885.cos.ap-beijing.myqcloud.com/image-20250224212911495.png)

![image-20250224215041435](https://picture-1344593885.cos.ap-beijing.myqcloud.com/image-20250224215041435.png)

获取APPID,SecretId和SecretKey，需要访问腾讯云的API密钥管理

腾讯云API密钥管理:https://link.zhihu.com/?target=https%3A//console.cloud.tencent.com/cam/capi

获取bucket名以及存储区域代号

腾讯云COS存储桶列表:https://link.zhihu.com/?target=https%3A//console.cloud.tencent.com/cos5/bucket

![image-20250224213023773](https://picture-1344593885.cos.ap-beijing.myqcloud.com/image-20250224213023773.png)

![image-20250224213107518](https://picture-1344593885.cos.ap-beijing.myqcloud.com/image-20250224213107518.png)

新建密钥

![image-20250224213246113](https://picture-1344593885.cos.ap-beijing.myqcloud.com/image-20250224213246113.png)

![image-20250224214647694](https://picture-1344593885.cos.ap-beijing.myqcloud.com/image-20250224214647694.png)

设定Bucket:picture

设定Appld:1344593885

设定存储区域：ap-beijing



这样就完成了，上传一张图片，回到腾讯云控制台，相关联的存储桶文件夹就有了。

## 4.Typora设置

![image-20250224214117727](https://md-assets-1344593885.cos.ap-beijing.myqcloud.com/image-20250224214117727.png)









































