# Tianjin university robomaster team "PeiYang Robot" 
This code is based on the SJTU-RM-CV2019, thanks to their code.
To satisfy our team's normal camera KS2A17, I change the camera class and cancel the serial class temporaryly to test in our home without USB-TTL, you can run this code easily in your device and make comparison with our algorithm code to better improve our code.

# NOTICE : IF YOU WANT TO RUN THIS PROGRAM , YOU NEED TO DO THIS
1.choose from video file 
2.input 0
3.  ./run --help to get the mode you like
GOOD LUCK!!!




# 上海交通大学 RoboMaster 2019赛季 视觉代码

本代码是上海交通大学RoboMaster2019赛季步兵车辆的视觉部分，分为三个模块:**装甲板识别**，**能量机关**，以及**封装的设备驱动和配置文件**。可以提取能量机关以外的模块并修改main函数直接作为哨兵识别代码。 

本代码统一使用**640×480**大小的图像进行处理

| 作者   | 负责部分       | 微信号               |
| ------ | -------------- | -------------------- |
| 唐欣阳 | 自瞄装甲板识别 | xinyang_tang         |
| 卫志坤 | 自瞄装甲板识别 |                      |
| 孙加桐 | 能量机关识别   | SJTxixiliadorabarryU |
| 罗嘉鸣 | 能量机关识别   |                      |

**如有BUG或者想交流的朋友欢迎积极联系我们**

**分享部分比赛时摄像头录制的视频:**

链接: https://pan.baidu.com/s/1LwxEpeYYblX3cSzb59MTVg 提取码: 84ju 复制这段内容后打开百度网盘手机App，操作更方便哦

---

运行效果：自瞄帧率120（摄像头最大帧率）,识别距离根据环境不同大约8米左右(5mm焦距镜头)。

![front](https://github.com/lloi7/SJTU-RM-CV-2019/blob/master/picture0.png)
![side](https://github.com/lloi7/SJTU-RM-CV-2019/blob/master/picture1.png)

## 一、代码运行环境

| 硬件设备                                             | 操作系统                                     | 运行库                                                       | ToolChain                                                  |
| ---------------------------------------------------- | -------------------------------------------- | ------------------------------------------------------------ | ---------------------------------------------------------- |
| IntelNUC<br />MindVision工业相机×１<br />USB转TTL×１ | Ubuntu18.04<br />Ubuntu16.04<br />Ｗindows10 | OpenCV3.4.5<br />OpenCV_contrib3.4.5<br />Eigen3<br />MindVision相机驱动 | Ubuntu18/16 : cmake3+gcc7+g++7 <br />Win10 : cmake3+VS2019 |

**关于Windows环境下的运行支持，仅保证程序可以编译运行。对与部分辅助功能，如生成自启动脚本则不支持。**

**实际装载在步兵和哨兵上的运行环境为Ubuntu18.04。**

相机驱动下载地址：[相机驱动](https://www.mindvision.com.cn)

OpenCV下载地址：[OpenCV](https://github.com/opencv)

OpenCV安装教程 : [linux](https://docs.opencv.org/3.4.5/d7/d9f/tutorial_linux_install.html)  [Windows](https://docs.opencv.org/3.4.5/d3/d52/tutorial_windows_install.html)

Eigen下载方法：
* Ubuntu16/18: ```sudo apt install libeigen3-dev```
* Windows10 : [Eigen下载地址](http://eigen.tuxfamily.org/)

## 二、程序编译运行以及调试方式

### 1.编译运行

* Ubuntu16/18（在项目文件夹下）

```shell
mkdir build
cd build
cmake ..
make -j8
sudo ./run
```

* Windows10

  打开cmake-gui，选择项目文件夹和build文件夹，生成VS工程。在VS中编译项目。

### 2.调试方式

```./run --help```可以查看所有命令行参数及其作用。所有调试选项都集成到了命令行参数中。

**不使用任何参数直接运行将没有任何图像显示。**

需要调参的部分：主要需要根据车辆情况而调参的参数存放在others/include/config/setconfig.h中

### 3.工作条件

* 对于自瞄，由于使用了数字识别，务必保证光照充足，图像上数字清晰可见。光照不足时，调整摄像头曝光或增益数值，直到数字清晰可见。
* 务必保证摄像头焦距正确，同时镜片干净无污物。

## 三、文件目录结构
```
.
├── armor                       // 存放自瞄主要算法代码
│   ├── include                 // 自瞄头文件
│   └── src                     // 自瞄源码
├── CMakeLists.txt              // cmake工程文件
├── energy                      // 存放能量机关主要算法代码
│   ├── include                 // 能量机关头文件
│   └── src                     // 能量机关源码
├── main.cpp                    // 主函数
├── others                      // 存放摄像头、串口、配置文件等
│   ├── include                 // others头文件
│   ├── libmvsdk.dylib          // mac相机驱动链接库
│   ├── libMVSDK.so             // linux相机驱动链接库
│   ├── MVCAMSDK_X64.dll        // win10相机驱动链接库
│   ├── MV-UB31-Group0.config   // 相机配置文件
│   └── src                     // others源码
└── tools                       // 存放分类器训练代码及参数，自启动脚步等
    ├── auto-pull.sh            // 自动代码更新脚本
    ├── create-startup.sh       // 自启动文件创建脚本
    ├── monitor.bat             // win10进程守护脚本
    ├── monitor.sh              // linux进程守护脚本
    ├── para                    // 分类器参数
    └── TrainCNN                // 分类器训练源码
```
## 四、关键类解析

| 类名            | 主要成员                                                     | 主要接口               | 类的作用                                                |
| --------------- | ------------------------------------------------------------ | ---------------------- | ------------------------------------------------------- |
| ArmorFinder     | 过多，不做赘述                                               | void run(cv::Mat &src) | 将一帧图像中装甲板的detection以及数据发送封装为一个类   |
| Energy          | 过多，不做赘述                                               | void run(cv::Mat &src) | 将一帧图像中能量机关的detection以及数据发送封装为一个类 |
| EnergyPartParam | 过多，不做赘述                                               | 无                     | 能量机关所有参数的集合                                  |
| LightBlob       | 灯条位置<br />灯条颜色                                   | 无                     | 灯条类定义                                              |
| ArmorBox        | 装甲板位置<br />装甲板的两个灯条<br />装甲板颜色<br />装甲板数字id | 无                     | 装甲板类定义                                            |

## 五、程序运行基本流程

　　　　　　　　　　　　↗  大能量机关 ↘

各项初始化→读取当前状态  → 小能量机关  → 回到读取状态

　　↓　　　　　　　　　↘　　自瞄　　↗

数据接收线程

## 六、识别方式

### 1.自瞄装甲板识别方式

​    首先对图像进行通道拆分以及二值化操作，再进行开闭运算，通过边缘提取和条件限制得出可能为灯条的部分。再对所有可能的灯条进行两两匹配，根据形状大小特性进行筛选，得出可能为装甲板的候选区。然后把所有候选区交给分类器判断，得出真实的装甲板及其数字id。最后根据优先级选取最终击打目标以及后续处理。
​     ![autoaim](https://github.com/lloi7/SJTU-RM-CV-2019/blob/master/自瞄流程图.png)
### 2.能量机关识别方式

​    首先对图像进行二值化操作，然后进行一定腐蚀和膨胀，通过边缘提取和条件限制得出待击打叶片（锤子形）。在待击打叶片范围内进一步用类似方法寻找目标装甲板和流动条，在二者连线上寻找中心的“R”。根据目标装甲板坐标和中心坐标计算极坐标系下的目标角度，进而预测待击打点的坐标（小符为装甲板本身，大符需要旋转）。最后将待击打点坐标和图像中心的差值转换为yaw和pitch轴角度，增加一环PID后发送给云台主控板。

## 七、通信协议

### 1.通信方式

使用USB转TTL进行串口通信

### 2.数据接收结构体

```c++
struct McuData {
    float curr_yaw;      // 当前云台yaw角度
    float curr_pitch;    // 当前云台pitch角
    uint8_t state;       // 当前状态，自瞄-大符-小符
    uint8_t mark;        // 云台角度标记位
    uint8_t anti_top;    // 是否为反陀螺模式
    uint8_t enemy_color; // 敌方颜色
    int delta_x;         // 能量机关x轴补偿量
    int delta_y;         // 能量机关y轴补偿量
};
```

每个数据帧后使用字符```'\n'```作为帧尾标志

### 3.数据发送结构体

```c++
struct SendData {
    char start_flag;      // 帧头标志，字符's'
    int16_t yaw;          // float类型的实际角度(以度为单位)/100*(32768-1)
    int16_t pitch;        // float类型的实际角度(以度为单位)/100*(32768-1)
    uint16_t shoot_delay; // 反陀螺模式下的发射延迟
    char end_flag;        // 帧尾标识，字符'e'
};
```

实际发送代码中没有使用这个结构体，而是使用uint8_t类型数组直接赋值代替

## 八、代码命名规范

函数名：使用首字母小写的驼峰命名法

类型名：使用首字母大写的驼峰命名法

变量名：使用下划线分割命名法

## 九、未来的优化方向
* 基于灯条的候选区生成由于利用了灯条在其附近区域亮度是最高的这一先验知识，当摄像头曝光和增益较高，同时灯条旁边有其他较亮的物体(如反光、光晕过大等)，该灯条将无法被识别。反应在算法上即体现在二值化这一步骤之上。所以本项目采用多二值化阈值同时进行灯条提取最后进行合并的办法，有一定改善，但没有解决本质问题。**所以第一个优化方向便是环境适应力更强的灯条提取或者候选区提取**。
* 代码中使用CNN分类器对灯条候选区进行筛选以及数字识别，但分类器总是不能做到100%的正确率，同时许多明显为背景的候选区有时也会被误判成装甲板，导致误识别。**所以第二个优化方向是更低的误识别率(可以从候选区生成入手或者从分类器入手)**。
* 由于陀螺这样的机械设计基本上是强队的标准配置，所以我们也首次尝试了从视觉层面对陀螺有一个专门的击打方式，但实际应用场景较少(当前仅针对原地旋转的陀螺)，且对操作手不太友好(要求手动对准陀螺中心)，所以没有取得很大的实战价值。**所以第三个优化方向便是一个有着自动击打动态陀螺的系统**。

---
**觉得对你有帮助请点个STAR哦:)**
