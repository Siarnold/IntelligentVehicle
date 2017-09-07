# 主逻辑规划
> 2017.9.5
------
## 设计思想

* 注重功能集成——三种集成模式
* 注重安全——避障与循迹+风扇
* 注重用户体验——CCM模式和BM模式减少对用户接口，而遥控模式给予人全权控制
* 注重可维护性——结构化程序+代码规范：宏定义与命名
* 注重效率——使用中断机制

------

## 基本结构
* 1个主逻辑文件
* 若干.h和.c封装的功能模块

------

## 基本控制

* 遥控可切换模式：
  - 综合行进模式
  - 倒车模式
  - 遥控车模式

------

## 模式定义

* 综合巡航模式：除切换模式指令外不接受遥控
  Comprehensive Cruising Mode (CCM)
  - 循迹：前端红外 * 2
  - 超声报警 + 避障：前端超声 * 1 + 蜂鸣器 * 1
  - 测速 + 在数码管显示：霍尔 * 1 + 数码管 * 1
  - 测温 + 报警：热敏 * 1 + 电子开关 * 1 + 蜂鸣器 * 1
  - 风扇 * 2 始终运行

* 倒车模式：除切换模式指令外不接受遥控
  Backing Mode （BM）
  - 在确定的相对位置倒车：后端超声 * 2
  - 测速 + 在数码管显示：如前
  - 测温 + 报警：如前
  - 风扇始终运行：如前

* 遥控车模式：接受一切遥控
  Remote Control Mode (RCM)
  - 前进/后退/加速前进
  - 左转轮/右转轮
  - 显示速度/显示温度
  - 风扇始终运行：如前

------

## 时钟分配

* TA0
  - PWM
* TA1
  - 0 
  - 1 1*ob_avoid_catch
* TA2 触发中断
  - 0 tracking, ob_avoid, temp, bm
  - 1 2*ob_avoid
* TB
  - 1 v_meas

------

## 引脚分配

| 模块   | 模块引脚  | 单片机引脚   | 功能备注       |
| ---- | ----- | ------- | ---------- |
| 超声波1 | Trig  | 2.2 OUT | 已改     |
|      | Echo  | 2.0 IN  | 避障         |
| 超声波2 | Trig  | 8.1 OUT | **\+需写**   |
|      | Echo  | 2.4 IN  | 倒车**\+需写** |
| 超声波3 | Trig  | 8.2 OUT | **\+需写**   |
|      | Echo  | 2.5 IN  | 倒车**\+需写** |
| PWM1 |       | 1.2 OUT | 舵机         |
| PWM2 |       | 1.4 OUT | 电机         |
| PWM3 |       | 1.5 OUT | 电机+已写 |
| 热敏   |       | 6.0 IN  | ADC        |
| 遥控   | RxD   | 3.3 OUT |            |
|      | TxD   | 3.4 IN  |            |
| 红外1  | D0    | 3.5 IN  | 已改     |
| 红外2  | D0    | 3.6 IN  | 已改     |
| 霍尔模块 | H_OUT | 7.4 IN  |            |
| 蜂鸣器1  |       | 3.0 OUT | 已写   |
| 数码管  | CLK   | 4.1 OUT |            |
|      | DIO   | 4.2 I/O |            |
| 蜂鸣器2  |       | 3.1 OUT | 已写   |

------

## 各模块宏定义

// parameters about the three modes
#define CCM 0
#define BM 1
#define RCM 2

// parameters about the three flag_TA2_0 selects
#define TRAC 1
#define OBAV 2
#define TEMP 3

// parameters about the remote control
#define FWD 5 // forward
#define BWD 8 // backward
#define LWD 4 // leftward
#define RWD 6 // rightward
#define ACC 2 // accelerate
#define VSH 1 // velocity show
#define DSH 3 // temperature show

// parameters about the digit display
#define V_SH 0
#define T_SH 1
#define D_SH 2

// parameters about the steer and motor
#define V_STT 25
#define V_TUR 10
#define V_ACC 35
#define V_BWD 25
#define LEF 77 // steering steer left
#define RIT 63 // right
#define STT 69 // straight
#define DIS_WARN 50

