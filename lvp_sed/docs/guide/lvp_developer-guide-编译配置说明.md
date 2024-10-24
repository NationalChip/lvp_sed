# LVP工程编译配置说明(20201107-1)

## 执行 `make menuconfig` 进入编译配置首页
```
 .config - NationalChip Low-Power Voice Process Configuration
 ────────────────────────────────────────────────────────────────────────────────────
  ┌───────────── NationalChip Low-Power Voice Process Configuration ──────────────┐
  │  Arrow keys navigate the menu.  <Enter> selects submenus ---> (or empty       │  
  │  submenus ----).  Highlighted letters are hotkeys.  Pressing <Y> includes,    │  
  │  <N> excludes, <M> modularizes features.  Press <Esc><Esc> to exit, <?> for   │  
  │  Help, </> for Search.  Legend: [*] built-in  [ ] excluded  <M> module  < >   │  
  │ ┌───────────────────────────────────────────────────────────────────────────┐ │  
  │ │        Chipset selects: (Grus Family [GX8002])  --->                      │ │  
  │ │        Vendor selects: (NationalChip)  --->                               │ │  
  │ │        Board selects: (GX8002B DEV Board V1.0)  --->                      │ │  
  │ │        Board version selects:  (V1.0)  --->                               │ │  
  │ │        Microphone Type selects:  --->                                     │ │  
  │ │                                                                           │ │  
  │ │        MCU settings  --->                                                 │ │  
  │ │        NPU settings  --->                                                 │ │  
  │ │        Frequency settings  --->                                           │ │  
  │ │                                                                           │ │  
  │ │        LVP Workmode settings  --->                                        │ │  
  │ │        I/O Buffer Settings  --->                                          │ │  
  │ │        VUI Settings  --->                                                 │ │  
  │ │                                                                           │ │  
  │ │        LVP Application Settings  --->                                     │ │  
  │ │                                                                           │ │  
  │ │        Common Function Settings  --->                                     │ │  
  │ │                                                                           │ │  
  │ └───────────────────────────────────────────────────────────────────────────┘ │  
  ├───────────────────────────────────────────────────────────────────────────────┤  
  │           <Select>    < Exit >    < Help >    < Save >    < Load >            │  
  └───────────────────────────────────────────────────────────────────────────────┘  
``` 
## 板级配置部分
* Chipset selects : 芯片族选择，目前LVP工程只有Grus
```
          ┌────────────────────── Chipset selects: ───────────────────────┐
          │  Use the arrow keys to navigate this window or press the      │  
          │  hotkey of the item you wish to select followed by the <SPACE │  
          │  BAR>. Press <?> for additional information about this        │  
          │ ┌───────────────────────────────────────────────────────────┐ │  
          │ │                 (X) Grus Family [GX8002]                  │ │  
          │ └───────────────────────────────────────────────────────────┘ │  
          ├───────────────────────────────────────────────────────────────┤  
          │                    <Select>      < Help >                     │  
          └───────────────────────────────────────────────────────────────┘ 
```

* Vendor selects : 板子供应商选择，目前只有杭州国芯  

```
          ┌─────────────────────── Vendor selects: ───────────────────────┐
          │  Use the arrow keys to navigate this window or press the      │  
          │  hotkey of the item you wish to select followed by the <SPACE │  
          │  BAR>. Press <?> for additional information about this        │  
          │ ┌───────────────────────────────────────────────────────────┐ │  
          │ │                     (X) NationalChip                      │ │  
          │ └───────────────────────────────────────────────────────────┘ │  
          ├───────────────────────────────────────────────────────────────┤  
          │                    <Select>      < Help >                     │  
          └───────────────────────────────────────────────────────────────┘  

```

* Board selects : 板级选择，需要选择与硬件板子相匹配的选项，最常用的板子是`DEV`
```
          ┌─────────────────────── Board selects: ────────────────────────┐
          │  Use the arrow keys to navigate this window or press the      │  
          │  hotkey of the item you wish to select followed by the <SPACE │  
          │  BAR>. Press <?> for additional information about this        │  
          │ ┌───────────────────────────────────────────────────────────┐ │  
          │ │               ( ) GX8002A FAN Board V1.0                  │ │  
          │ │               ( ) GX8002B AIOT Board V1.1                 │ │  
          │ │               ( ) GX8002B DEBUG Board V1.0                │ │  
          │ │               (X) GX8002B DEV Board V1.0                  │ │  
          │ │               ( ) GX8002 FPGA Board V1.0                  │ │  
          │ │               ( ) GX8002 SLIGHT Board V1.0                │ │  
          │ └───────────────────┴(+)────────────────────────────────────┘ │  
          ├───────────────────────────────────────────────────────────────┤  
          │                    <Select>      < Help >                     │  
          └───────────────────────────────────────────────────────────────┘ 
```

* Board version selects : 板级版本选择，有些板级有不同的版本，对应不同的硬件或软件配置  
```
          ┌─────────────────── Board version selects:  ───────────────────┐
          │  Use the arrow keys to navigate this window or press the      │  
          │  hotkey of the item you wish to select followed by the <SPACE │  
          │  BAR>. Press <?> for additional information about this        │  
          │ ┌───────────────────────────────────────────────────────────┐ │  
          │ │      (X) V1.0                                             │ │  
          │ └───────────────────────────────────────────────────────────┘ │  
          ├───────────────────────────────────────────────────────────────┤  
          │                    <Select>      < Help >                     │  
          └───────────────────────────────────────────────────────────────┘ 
```

* Microphone Type selects : 麦克风类型配置，不同的板级可能有不同的配置项。 
  配置的总mic数量应当等于 `I/O Buffer Settings` 菜单中 `MIC Channel Number`项配置的数量  
```
.config - NationalChip Low-Power Voice Process Configuration
 > Microphone Type selects: ─────────────────────────────────────────────────────────
  ┌────────────────────────── Microphone Type selects: ───────────────────────────┐
  │  Arrow keys navigate the menu.  <Enter> selects submenus ---> (or empty       │  
  │  submenus ----).  Highlighted letters are hotkeys.  Pressing <Y> includes,    │  
  │  <N> excludes, <M> modularizes features.  Press <Esc><Esc> to exit, <?> for   │  
  │  Help, </> for Search.  Legend: [*] built-in  [ ] excluded  <M> module  < >   │  
  │ ┌───────────────────────────────────────────────────────────────────────────┐ │  
  │ │    [ ] DMIC                                                               │ │  
  │ │    [*] AMIC                                                               │ │  
  │ │    (1)   AMIC Number                                                      │ │  
  │ └───────────────────────────────────────────────────────────────────────────┘ │  
  ├───────────────────────────────────────────────────────────────────────────────┤  
  │           <Select>    < Exit >    < Help >    < Save >    < Load >            │  
  └───────────────────────────────────────────────────────────────────────────────┘  
```



* Board Options : 板级相关的配置项，主要是pin脚复用  
  目前只在选中 `GX8002B DEBUG Board V1.0` 或 `GX8002B DEV Board V1.0` 时出现
```
.config - NationalChip Low-Power Voice Process Configuration
 > Board Options:  ──────────────────────────────────────────────────────────────────
  ┌─────────────────────────────── Board Options:  ───────────────────────────────┐
  │  Arrow keys navigate the menu.  <Enter> selects submenus ---> (or empty       │  
  │  submenus ----).  Highlighted letters are hotkeys.  Pressing <Y> includes,    │  
  │  <N> excludes, <M> modularizes features.  Press <Esc><Esc> to exit, <?> for   │  
  │  Help, </> for Search.  Legend: [*] built-in  [ ] excluded  <M> module  < >   │  
  │ ┌───────────────────────────────────────────────────────────────────────────┐ │  
  │ │        This Options depend PIN`s Function                                 │ │  
  │ │        some options may be conflict             -WATCH OUT!-              │ │  
  │ │        Select what you want                                               │ │  
  │ │        -----------------------------------------------------              │ │  
  │ │    [ ] Disable DMIC                                                       │ │  
  │ │    [ ] Support JTAG                                                       │ │  
  │ │    [ ] Support I2C0                                                       │ │  
  │ │    [ ] Support HW I2C                                                     │ │  
  │ │    [ ] Support I2C1                                                       │ │  
  │ │    [ ] Support UART0                                                      │ │  
  │ │    [*] Support UART1  --->                                                │ │  
  │ │    [ ] Support SPI                                                        │ │  
  │ │    [ ] Support AudioIn Master mode                                        │ │  
  │ │    [ ] Support AudioIn Slave mode                                         │ │  
  │ │    [ ] Support I2S five wire mode, audio in I2S master + audio out I2S sla│ │  
  │ └───────────────────────────────────────────────────────────────────────────┘ │  
  ├───────────────────────────────────────────────────────────────────────────────┤  
  │           <Select>    < Exit >    < Help >    < Save >    < Load >            │  
  └───────────────────────────────────────────────────────────────────────────────┘  
```

* 上述选项皆是板级相关的配置，依次具有树状层级关系，请根据硬件情况依次进行配置。

## MCU 编译配置
* MCU settings :

```
 .config - NationalChip Low-Power Voice Process Configuration
 > MCU settings ─────────────────────────────────────────────────────────────────────
  ┌──────────────────────────────── MCU settings ─────────────────────────────────┐
  │  Arrow keys navigate the menu.  <Enter> selects submenus ---> (or empty       │  
  │  submenus ----).  Highlighted letters are hotkeys.  Pressing <Y> includes,    │  
  │  <N> excludes, <M> modularizes features.  Press <Esc><Esc> to exit, <?> for   │  
  │  Help, </> for Search.  Legend: [*] built-in  [ ] excluded  <M> module  < >   │  
  │ ┌───────────────────────────────────────────────────────────────────────────┐ │  
  │ │    [*] Enable Uart printf(...)                                            │ │  
  │ │          Not become effective, if not enable any uart port !              │ │  
  │ │    [ ]   Enable Float printf                                              │ │  
  │ │          Uart Port for prinf (UART 1)  --->                               │ │  
  │ │                                                                           │ │  
  │ │        Build Schema (Optimized for Size (-Os))  --->                      │ │  
  │ │    [ ] Enbale JTAG debug                                                  │ │  
  │ │                                                                           │ │  
  │ │                                                                           │ │  
  │ │    (1) MAIN Stack Minimum Size (KBytes)                                   │ │  
  │ │    [ ] Enable Stack Monitoring                                            │ │  
  │ │                                                                           │ │  
  │ │    [*] Enable XIP                                                         │ │  
  │ │          XIP Strategy (Default Text In Sram)  --->                        │ │  
  │ │    [ ]   NPU Run In Flash                                                 │ │  
  │ │                                                                           │ │  
  │ │        System Counter selects: (systick_counter, lower power consumption) │ │  
  │ │                                                                           │ │  
  │ │    [ ] Build CSKY Math Lib From Source Code                               │ │  
  │ └───────────────────────────────────────────────────────────────────────────┘ │  
  ├───────────────────────────────────────────────────────────────────────────────┤  
  │           <Select>    < Exit >    < Help >    < Save >    < Load >            │  
  └───────────────────────────────────────────────────────────────────────────────┘  

```

* Enable Uart printf      : 使能串口log输出，串口端口选择由板级代码决定，波特率为115200
* Enable Float printf     : 使能log输出的float打印功能，开启后才可以使用printf接口打印float数据
* Uart Port for prinf     : 选择log输出使用的串口
* Build Schema            : 编译等级配置
* MAIN Stack Minimum Size : MCU预留的最小栈空间
* Enable Stack Monitoring : 使能栈空间监控，开启后在栈空间快满时会有警告log输出
* Enable XIP              : 使能XIP功能
* XIP Strategy            : 选择`text`段运行位置，选中flash时，因为部分代码必须在sram中运行，所以依然在sram中

```
          ┌──────────────────────── XIP Strategy ─────────────────────────┐
          │  Use the arrow keys to navigate this window or press the      │  
          │  hotkey of the item you wish to select followed by the <SPACE │  
          │  BAR>. Press <?> for additional information about this        │  
          │ ┌───────────────────────────────────────────────────────────┐ │  
          │ │                 (X) Default Text In Sram                  │ │  
          │ │                 ( ) Default Text In Flash                 │ │  
          │ └───────────────────────────────────────────────────────────┘ │  
          ├───────────────────────────────────────────────────────────────┤  
          │                    <Select>      < Help >                     │  
          └───────────────────────────────────────────────────────────────┘  
```
* NPU Run In Flash        : 选择将npu模型放到XIP中运行
* System Counter selects  : 系统定时器选择

```
          ┌─────────────────── System Counter selects: ───────────────────┐
          │  Use the arrow keys to navigate this window or press the      │  
          │  hotkey of the item you wish to select followed by the <SPACE │  
          │  BAR>. Press <?> for additional information about this        │  
          │ ┌───────────────────────────────────────────────────────────┐ │  
          │ │       (X) systick_counter, lower power consumption        │ │  
          │ │       ( ) gx_counter, accurater                           │ │  
          │ └───────────────────────────────────────────────────────────┘ │  
          ├───────────────────────────────────────────────────────────────┤  
          │                    <Select>      < Help >                     │  
          └───────────────────────────────────────────────────────────────┘  
```
* Build CSKY Math Lib From Source Code : 选择通过源码编译、链接csky数学库


## NPU 编译配置
* NPU settings: 

```
 .config - NationalChip Low-Power Voice Process Configuration
 > NPU settings ─────────────────────────────────────────────────────────────────────
  ┌──────────────────────────────── NPU settings ─────────────────────────────────┐
  │  Arrow keys navigate the menu.  <Enter> selects submenus ---> (or empty       │  
  │  submenus ----).  Highlighted letters are hotkeys.  Pressing <Y> includes,    │  
  │  <N> excludes, <M> modularizes features.  Press <Esc><Esc> to exit, <?> for   │  
  │  Help, </> for Search.  Legend: [*] built-in  [ ] excluded  <M> module  < >   │  
  │ ┌───────────────────────────────────────────────────────────────────────────┐ │  
  │ │    (125) Sram kept for NPU (KBytes)                                       │ │  
  │ │                                                                           │ │  
  │ │    [ ] Enable Npu Debug (Open Printf)                                     │ │  
  │ │                                                                           │ │  
  │ │    [ ] Enable Data Preparation Cycle Statistic                            │ │  
  │ │    [ ] Enable Npu Cycle Statistic                                         │ │  
  │ │    [ ] Enable CTC Softmax Cycle Statistic                                 │ │  
  │ │    [ ] Enable CTC Decoder Cycle Statistic                                 │ │  
  │ │    [ ] Enable BM Cycle Statistic                                          │ │  
  │ └───────────────────────────────────────────────────────────────────────────┘ │  
  ├───────────────────────────────────────────────────────────────────────────────┤  
  │           <Select>    < Exit >    < Help >    < Save >    < Load >            │  
  └───────────────────────────────────────────────────────────────────────────────┘  
```
* Sram kept for NPU    : sram中为npu预留的空间
* Enable Npu Debug     : 使能npu中部分调试log输出  
  Enable Data Preparation Cycle Statistic  :  打印准备一个context周期数据时间  
  Enable Npu Cycle Statistic               : 打印npu处理一个context周期任务的周期时间  
  Enable CTC Softmax Cycle Statistic       : 打印CTC softmax处理一个context周期数据的时间  
  Enable CTC Decoder Cycle Statistic       : 打印CTC Decoder处理一个context周期数据的时间  
  Enable BM Cycle Statistic                : 打印BM Search的花费的时间  
  `这几条皆为调试功能，通过统计的出来的耗时与context周期进行对比可评估算力`  
  `会稍微影响性能，一般不开启 `

## 频率配置
* Frequency settings: 此处开放了grus部分时钟配置接口

```
.config - NationalChip Low-Power Voice Process Configuration
 > Frequency settings ───────────────────────────────────────────────────────────────
  ┌───────────────────────────── Frequency settings ──────────────────────────────┐
  │  Arrow keys navigate the menu.  <Enter> selects submenus ---> (or empty       │  
  │  submenus ----).  Highlighted letters are hotkeys.  Pressing <Y> includes,    │  
  │  <N> excludes, <M> modularizes features.  Press <Esc><Esc> to exit, <?> for   │  
  │  Help, </> for Search.  Legend: [*] built-in  [ ] excluded  <M> module  < >   │  
  │ ┌───────────────────────────────────────────────────────────────────────────┐ │  
  │ │        System Frequency selects: (Customize)  --->                        │ │  
  │ │                                                                           │ │  
  │ │        |||############################################################||| │ │  
  │ │        ||#                                                            #|| │ │  
  │ │        |#    Make sure the voltage entering core less or equal 1.2v    #| │ │  
  │ │        #              to avoid burning chip !!!!!!!!                    # │ │  
  │ │        |#             Because enabled bypass core-LDO                  #| │ │  
  │ │        ||#                                                            #|| │ │  
  │ │        |||############################################################||| │ │  
  │ │        |/                                                                 │ │  
  │ │        |                                                                  │ │  
  │ │    -*- Enable bypass core ldo                                             │ │  
  │ │                                                                           │ │  
  │ │        MCU Work Frequency: (50M)  --->                                    │ │  
  │ │        NPU Work Frequency: (24M)  --->                                    │ │  
  │ │        SRAM Work Frequency: (24M)  --->                                   │ │  
  │ │        Flash Work Frequency: (50M)  --->                                  │ │  
  │ │                                                                           │ │  
  │ └───────────────────────────────────────────────────────────────────────────┘ │  
  ├───────────────────────────────────────────────────────────────────────────────┤  
  │           <Select>    < Exit >    < Help >    < Save >    < Load >            │  
  └───────────────────────────────────────────────────────────────────────────────┘ 

```
* System Frequency selects : 选择时钟频率配置方式，只有选中`Customize`时允许自由配置时钟

```
          ┌────────────────── System Frequency selects: ──────────────────┐
          │  Use the arrow keys to navigate this window or press the      │  
          │  hotkey of the item you wish to select followed by the <SPACE │  
          │  BAR>. Press <?> for additional information about this        │  
          │ ┌───────────────────────────────────────────────────────────┐ │  
          │ │                    ( ) Standard Speed                     │ │  
          │ │                    ( ) High Speed                         │ │  
          │ │                    (X) Customize                          │ │  
          │ └───────────────────────────────────────────────────────────┘ │  
          ├───────────────────────────────────────────────────────────────┤  
          │                    <Select>      < Help >                     │  
          └───────────────────────────────────────────────────────────────┘  
```
* Enable bypass core ldo : 使能 bypass core ldo 功能，只有选中`Customize`时允许配置

* MCU Work Frequency : 配置MCU时钟频率，当选中`50M`时会显示出警示说明。  
    因为当选中`50M`时将 bypass core ldo，这个操作需要core供电小于等于1.2v，否则将烧毁芯片

```
          ┌───────────────────── MCU Work Frequency: ─────────────────────┐
          │  Use the arrow keys to navigate this window or press the      │  
          │  hotkey of the item you wish to select followed by the <SPACE │  
          │  BAR>. Press <?> for additional information about this        │  
          │ ┌───────────────────────────────────────────────────────────┐ │  
          │ │                          ( ) 8M                           │ │  
          │ │                          ( ) 12M                          │ │  
          │ │                          ( ) 24M                          │ │  
          │ │                          (X) 50M                          │ │  
          │ └───────────────────────────────────────────────────────────┘ │  
          ├───────────────────────────────────────────────────────────────┤  
          │                    <Select>      < Help >                     │  
          └───────────────────────────────────────────────────────────────┘
```

* NPU Work Frequency:NPU 频率配置

```
          ┌───────────────────── NPU Work Frequency: ─────────────────────┐
          │  Use the arrow keys to navigate this window or press the      │  
          │  hotkey of the item you wish to select followed by the <SPACE │  
          │  BAR>. Press <?> for additional information about this        │  
          │ ┌───────────────────────────────────────────────────────────┐ │  
          │ │                          (X) 8M                           │ │  
          │ │                          ( ) 12M                          │ │  
          │ │                          ( ) 24M                          │ │  
          │ └───────────────────────────────────────────────────────────┘ │  
          ├───────────────────────────────────────────────────────────────┤  
          │                    <Select>      < Help >                     │  
          └───────────────────────────────────────────────────────────────┘  
```

* System Frequency selects 中选中`Standard Speed`或 `High Speed` 时将使用预设的频率方案

``` 
  │ ┌───────────────────────────────────────────────────────────────────────────┐ │  
  │ │        System Frequency selects: (Standard Speed)  --->                   │ │  
  │ │        |                                                                  │ │  
  │ │        \__.--> MCU 8M; SRAM 8M; NPU 8M; Flash 24M                         │ │  
  │ └───────────────────────────────────────────────────────────────────────────┘ │  
```

``` 
  │ ┌───────────────────────────────────────────────────────────────────────────┐ │  
  │ │        System Frequency selects: (High Speed)  --->                       │ │  
  │ │        |                                                                  │ │  
  │ │        \__.--> MCU 24M; SRAM 24M; NPU 24M; Flash 50M                      │ │  
  │ └───────────────────────────────────────────────────────────────────────────┘ │  
 
```

# 工作模式配置
* LVP Workmode settings: 工作模式选择与配置

```
 .config - NationalChip Low-Power Voice Process Configuration
 > LVP Workmode settings ────────────────────────────────────────────────────────────
  ┌──────────────────────────── LVP Workmode settings ────────────────────────────┐
  │  Arrow keys navigate the menu.  <Enter> selects submenus ---> (or empty       │  
  │  submenus ----).  Highlighted letters are hotkeys.  Pressing <Y> includes,    │  
  │  <N> excludes, <M> modularizes features.  Press <Esc><Esc> to exit, <?> for   │  
  │  Help, </> for Search.  Legend: [*] built-in  [ ] excluded  <M> module  < >   │  
  │ ┌───────────────────────────────────────────────────────────────────────────┐ │  
  │ │        Initial Workmode selects: (TWS)  --->                              │ │  
  │ │    [*] Has TWS workmode  ----                                             │ │  
  │ │    [ ] Has record workmode  ----                                          │ │  
  │ │    [ ] Has feed workmode, get logfbank data from uart  ----               │ │  
  │ └───────────────────────────────────────────────────────────────────────────┘ │  
  ├───────────────────────────────────────────────────────────────────────────────┤  
  │           <Select>    < Exit >    < Help >    < Save >    < Load >            │  
  └───────────────────────────────────────────────────────────────────────────────┘  
```

* Initial Workmode selects : 在使能多个mode时，选择一个mode启动；目前只用到使用1个mode的情况

```
          ┌────────────────── Initial Workmode selects: ──────────────────┐
          │  Use the arrow keys to navigate this window or press the      │  
          │  hotkey of the item you wish to select followed by the <SPACE │  
          │  BAR>. Press <?> for additional information about this        │  
          │ ┌───────────────────────────────────────────────────────────┐ │  
          │ │                          (X) TWS                          │ │  
          │ └───────────────────────────────────────────────────────────┘ │  
          ├───────────────────────────────────────────────────────────────┤  
          │                    <Select>      < Help >                     │  
          └───────────────────────────────────────────────────────────────┘  
```

* Has TWS workmode : tws模式，使能了`audio in`和`npu`，具有待机状态管理和kws功能；可实现大多数功能，是最常用的模式  
  Has record workmode :  record模式，纯粹的录音模式，只开启了audio in，没有kws和待机状态管理
  Has feed workmode, get logfbank data from uart : feed模式，支持将npu的数据源支持从`audio in`切换到串口，上位机可通过此模式向grus `FEED` 数据进行处理  
* 当在这里不使能任何模式时，自动使用`idle`模式工作

# 工作Buffer配置

* I/O Buffer Settings ： 此处的配置全部用与音频处理流水线，其中audio in的部分通过context管理

```
 .config - NationalChip Low-Power Voice Process Configuration
 > I/O Buffer Settings ──────────────────────────────────────────────────────────────
  ┌───────────────────────────── I/O Buffer Settings ─────────────────────────────┐
  │  Arrow keys navigate the menu.  <Enter> selects submenus ---> (or empty       │  
  │  submenus ----).  Highlighted letters are hotkeys.  Pressing <Y> includes,    │  
  │  <N> excludes, <M> modularizes features.  Press <Esc><Esc> to exit, <?> for   │  
  │  Help, </> for Search.  Legend: [*] built-in  [ ] excluded  <M> module  < >   │  
  │ ┌───────────────────────────────────────────────────────────────────────────┐ │  
  │ │    (1) MIC Channel Number                                                 │ │  
  │ │    (1) Logfbank Channel Number                                            │ │  
  │ │        Frame settings:                                                    │ │  
  │ │        Sample Rate selects: (16KHz)  --->                                 │ │  
  │ │        PCM Frame Length selects: (10ms)  --->                             │ │  
  │ │                                                                           │ │  
  │ │        Context settings:                                                  │ │  
  │ │    (6) PCM Frame Number in a Context                                      │ │  
  │ │    (1) Context Gap                                                        │ │  
  │ │                                                                           │ │  
  │ │        Buffer settings:                                                   │ │  
  │ │    (6) PCM Frame Number in a Channel                                      │ │  
  │ │    (42) Logfbank Frame Number                                             │ │  
  │ │    (6) Context Number                                                     │ │  
  │ │                                                                           │ │  
  │ │        Audio out buffer settings:                                         │ │  
  │ │    (12) audio out buffer size (KBytes)                                    │ │  
  │ └───────────────────────────────────────────────────────────────────────────┘ │  
  ├───────────────────────────────────────────────────────────────────────────────┤  
  │           <Select>    < Exit >    < Help >    < Save >    < Load >            │  
  └───────────────────────────────────────────────────────────────────────────────┘  
```

* MIC Channel Number : mic buffer 的通道数量，应当与板级配置中设置的mic数量相等
* Logfbank Channel Number : audio in输出logfbank数据的通道数，因为这里audio in只能处理一个通道的音频，所以该项为 1
* Sample Rate selects : audio in 录音的采样率

```
          ┌──────────────────── Sample Rate selects: ─────────────────────┐
          │  Use the arrow keys to navigate this window or press the      │  
          │  hotkey of the item you wish to select followed by the <SPACE │  
          │  BAR>. Press <?> for additional information about this        │  
          │ ┌───────────────────────────────────────────────────────────┐ │  
          │ │                         ( ) 8KHz                          │ │  
          │ │                         (X) 16KHz                         │ │  
          │ │                         ( ) 48KHz                         │ │  
          │ └───────────────────────────────────────────────────────────┘ │  
          ├───────────────────────────────────────────────────────────────┤  
          │                    <Select>      < Help >                     │  
          └───────────────────────────────────────────────────────────────┘  
```
* PCM Frame Length selects ： audio in录音后上报中断的周期，也是一帧音频的时长

```
          ┌────────────────── PCM Frame Length selects: ──────────────────┐
          │  Use the arrow keys to navigate this window or press the      │  
          │  hotkey of the item you wish to select followed by the <SPACE │  
          │  BAR>. Press <?> for additional information about this        │  
          │ ┌───────────────────────────────────────────────────────────┐ │  
          │ │                         (X) 10ms                          │ │  
          │ │                         ( ) 16ms                          │ │  
          │ └───────────────────────────────────────────────────────────┘ │  
          ├───────────────────────────────────────────────────────────────┤  
          │                    <Select>      < Help >                     │  
          └───────────────────────────────────────────────────────────────┘  
```

* PCM Frame Number in a Context ： 一个context中的音频帧数量
* Context Gap : context 循环buffer读写指针间隙，读写指针间隙应大于这个至才能流畅运行
* PCM Frame Number in a Channel : 一个通道的mic buffer能够容纳的音频数据帧数  
  `应当是 PCM Frame Number in a Context 和 Context Number 的公倍数`
* Logfbank Frame Number : 一个通道的logfband buffer对应的音频数据帧数  
  `应当是 PCM Frame Number in a Context 和 Context Number 的公倍数`
* Context Number : context buffer中的context数量
* audio out buffer size : voice player中为audio out设置的buffer，不使用voice player时不生效
* `上述这一部分配置与npu算法模型、录音功能和内存分配紧密相关，请注意！`

# 语音交互配置

* VUI Settings : 语音算法相关配置

```
 .config - NationalChip Low-Power Voice Process Configuration
 > VUI Settings ─────────────────────────────────────────────────────────────────────
  ┌──────────────────────────────── VUI Settings ─────────────────────────────────┐
  │  Arrow keys navigate the menu.  <Enter> selects submenus ---> (or empty       │  
  │  submenus ----).  Highlighted letters are hotkeys.  Pressing <Y> includes,    │  
  │  <N> excludes, <M> modularizes features.  Press <Esc><Esc> to exit, <?> for   │  
  │  Help, </> for Search.  Legend: [*] built-in  [ ] excluded  <M> module  < >   │  
  │ ┌───────────────────────────────────────────────────────────────────────────┐ │  
  │ │        VAD Settings:                                                      │ │  
  │ │    [ ] Enable FFT Vad                                                     │ │  
  │ │    (3) Fallback Context Number When FFTVAD Valid                          │ │  
  │ │    [*] ENABLE G sensor Vad (NEW)                                          │ │  
  │ │                                                                           │ │  
  │ │        ENV Noise Judgment Settings:                                       │ │  
  │ │    [ ] Enable Noise Judgment                                              │ │  
  │ │                                                                           │ │  
  │ │    [ ] Enable Standby                                                     │ │  
  │ │                                                                           │ │  
  │ │    [*] Enable Keyword Recognition                                         │ │  
  │ │          Keyword Deocder Type (Ctc Decoder)  --->                         │ │  
  │ │          KeyWord select: (yilian fan)  --->                               │ │  
  │ │          Model select: (LVP_KWS_YILIAN_FAN_V0DOT0DOT1_2020_0803)  --->    │ │  
  │ │          Model Param Setting:  --->                                       │ │  
  │ │          Kws List Settings  --->                                          │ │  
  │ │    [*]   Model Use Recurrent Neural Network                               │ │  
  │ │    [ ]   Enable CTC Score Compensator                                     │ │  
  │ │    [ ]   Enable Optimize short instructions                               │ │  
  │ │    [ ]   Enable BIONIC To Reduce False Activation                         │ │  
  │ │                                                                           │ │  
  │ │    [*] Enable Voice Print Recognition                                     │ │  
  │ │          Vpr word select: (xiao du xiao du)  --->                         │ │  
  │ │          Model select: (LVP_VPR_XDXD_V0DOT1DOT0_2020_0104)  --->          │ │  
  │ │          Model Param Setting:  ----                                       │ │  
  │ └───────────────────────────────────────────────────────────────────────────┘ │  
  ├───────────────────────────────────────────────────────────────────────────────┤  
  │           <Select>    < Exit >    < Help >    < Save >    < Load >            │  
  └───────────────────────────────────────────────────────────────────────────────┘  
```

* Enable FFT Vad : 使能fftvad，有audio in提供，tws模式的待机状态管理和kws对应任务的取舍依赖于它，持续一段时间没有vad触发才会进待机，只有vad触发时npu才处理数据。
* Fallback Context Number When FFTVAD Valid : 当系统从安静状态切换到vad触发状态时需要处理的历史数据量，以context周期为单位；  
安静状态vad不触发时及待机时，audio in依然工作，音频保存在buffer中。
* ENABLE G sensor Vad : 使能Gvad，即通过加速度传感器判断耳机佩戴者有无说话的动作。

* Enable Noise Judgment : 用于根据环境噪声动态调整fft vad阈值

```
 [*] Enable Noise Judgment                                              
  (150) High Noise Maintain Time [unit of context] (NEW)                  
  (150) Low Noise Maintain Time [unit of context] (NEW)  
```

* Enable Standby : 使能待机功能，待机功能的状态管理在tws模式中
* Disable XIP While Code Run At Sram : 在使能xip时，当执行sram中代码时关掉flash，当需要执行flash中代码时再将flash打开


* Enable Keyword Recognition : 使能关键词识别(kws)功能  
* Keyword Deocder Type : 选择Decoder方式，如下所示分别为  
 `Ctc Decoder` 输出对kws list的打分，  
 `Beamsearch Decoder without CTC` 输出模型识别到的拼音序列，  
 `CTC And Beamsearch Decoder` ctc decoder 后通过 Beamsearch 进行校验，可降低误激活   `User Deocder` 用户自定义的解码方式，用于第三方算法集成

```
          ┌──────────────────── Keyword Deocder Type ─────────────────────┐
          │  Use the arrow keys to navigate this window or press the      │  
          │  hotkey of the item you wish to select followed by the <SPACE │  
          │  BAR>. Press <?> for additional information about this        │  
          │ ┌───────────────────────────────────────────────────────────┐ │  
          │ │            (X) Ctc Decoder                                │ │  
          │ │            ( ) CTC And Beamsearch Decoder                 │ │  
          │ │            ( ) Beamsearch Decoder without CTC             │ │  
          │ │            ( ) User Deocder                               │ │  
          │ └───────────────────────────────────────────────────────────┘ │  
          ├───────────────────────────────────────────────────────────────┤  
          │                    <Select>      < Help >                     │  
          └───────────────────────────────────────────────────────────────┘  
```
* KeyWord select ： 从按主唤醒词分类的模型组中选择需要的模型组

```
          ┌─────────────────────── KeyWord select: ───────────────────────┐
          │  Use the arrow keys to navigate this window or press the      │  
          │  hotkey of the item you wish to select followed by the <SPACE │  
          │  BAR>. Press <?> for additional information about this        │  
          │ ┌─────────^(-)──────────────────────────────────────────────┐ │  
          │ │     ( ) xiao ai tong xue[Big model, need run in xip]      │ │  
          │ │     (X) xiao du xiao du[xatx, tmjl for tws]               │ │  
          │ │     ( ) xiao ku xiao ku[xiao ai xiao ai]                  │ │  
          │ │     ( ) xiao le xiao le                                   │ │  
          │ │     ( ) xiao wei xiao wei                                 │ │  
          │ │     ( ) yilian fan                                        │ │  
          │ └───────────────────────────────────────────────────────────┘ │  
          ├───────────────────────────────────────────────────────────────┤  
          │                    <Select>      < Help >                     │  
          └───────────────────────────────────────────────────────────────┘  
```
* Model select : 从上一条选中的模型组中选择合适版本

```
          ┌──────────────────────── Model select: ────────────────────────┐
          │  Use the arrow keys to navigate this window or press the      │  
          │  hotkey of the item you wish to select followed by the <SPACE │  
          │  BAR>. Press <?> for additional information about this        │  
          │ ┌───────────────────────────────────────────────────────────┐ │  
          │ │     (X) LVP_KWS_XDXD_V0DOT1DOT0_2019_1001                 │ │  
          │ │     ( ) LVP_KWS_XDXD_V0DOT1DOT1_2020_0427                 │ │  
          │ │     ( ) LVP_KWS_XDXD_V0DOT1DOT2_2020_0706                 │ │  
          │ │     ( ) LVP_KWS_XDXD_V0DOT1DOT3_2020_0805                 │ │  
          │ │     ( ) LVP_KWS_XDXD_V0DOT1DOT4_2020_0813                 │ │  
          │ │     ( ) LVP_KWS_XIAO_DU_XIAO_DU_V0DOT1DOT5_2020_0922      │ │  
          │ └───────────────────────────────────────────────────────────┘ │  
          ├───────────────────────────────────────────────────────────────┤  
          │                    <Select>      < Help >                     │  
          └───────────────────────────────────────────────────────────────┘  
                                                                            
```
* Model Param Setting: 模型参数设置  
`KWS Lantency` ： kws list 的分组数，每个context周期对依次对一个分组进行ctc打分  
`KWS Model Decoder Window Length` ： ctc decoder 的窗长，以context周期为单位

```
 .config - NationalChip Low-Power Voice Process Configuration
 > VUI Settings > Model Param Setting: ──────────────────────────────────────────────
  ┌──────────────────────────── Model Param Setting: ─────────────────────────────┐
  │  Arrow keys navigate the menu.  <Enter> selects submenus ---> (or empty       │  
  │  submenus ----).  Highlighted letters are hotkeys.  Pressing <Y> includes,    │  
  │  <N> excludes, <M> modularizes features.  Press <Esc><Esc> to exit, <?> for   │  
  │  Help, </> for Search.  Legend: [*] built-in  [ ] excluded  <M> module  < >   │  
  │ ┌───────────────────────────────────────────────────────────────────────────┐ │  
  │ │    (1) KWS Lantency (unit of Context)                                     │ │  
  │ │    (25) KWS Model Decoder Window Length (unit of context)                 │ │  
  │ └───────────────────────────────────────────────────────────────────────────┘ │  
  ├───────────────────────────────────────────────────────────────────────────────┤  
  │           <Select>    < Exit >    < Help >    < Save >    < Load >            │  
  └───────────────────────────────────────────────────────────────────────────────┘  

```

* Kws List Settings ： 略

```
 .config - NationalChip Low-Power Voice Process Configuration
 > VUI Settings > Kws List Settings ─────────────────────────────────────────────────
  ┌────────────────────────────── Kws List Settings ──────────────────────────────┐
  │  Arrow keys navigate the menu.  <Enter> selects submenus ---> (or empty       │  
  │  submenus ----).  Highlighted letters are hotkeys.  Pressing <Y> includes,    │  
  │  <N> excludes, <M> modularizes features.  Press <Esc><Esc> to exit, <?> for   │  
  │  Help, </> for Search.  Legend: [*] built-in  [ ] excluded  <M> module  < >   │  
  │ ┌───────────────────────────────────────────────────────────────────────────┐ │  
  │ │    [*] xiao hong xiao hong                                                │ │  
  │ │    (900) The Threshold of xiao hong xiao hong                             │ │  
  │ │    (100) The Kws Value of xiao hong xiao hong                             │ │  
  │ │                                                                           │ │  
  │ │    [*] da kai feng shan                                                   │ │  
  │ │    (865) The Threshold of da kai feng shan                                │ │  
  │ │    (101) The Kws Value of da kai feng shan                                │ │  
  │ │                                                                           │ │  
  │ │    [*] guan bi feng shan                                                  │ │  
  │ │    (865) The Threshold of guan bi feng shan                               │ │  
  │ │    (102) The Kws Value of guan bi feng shan                               │ │  
  │ └────┴(+)───────────────────────────────────────────────────────────────────┘ │  
  ├───────────────────────────────────────────────────────────────────────────────┤  
  │           <Select>    < Exit >    < Help >    < Save >    < Load >            │  
  └───────────────────────────────────────────────────────────────────────────────┘ 
```
* Model Use Recurrent Neural Network :  使能神经网络中的递归网络，当模型使用递归网络时需要勾选，为npu送数据时会有所不同
* Enable CTC Score Compensator ： ctc 打分补偿，略,不勾选 (计划删除它)
* Enable Optimize short instructions  ： 优化短指令激活性能，不勾选 (计划删除它)
* Enable BIONIC To Reduce False Activation ： 使能仿生算法，长时间没有被唤醒时调高阈值，唤醒后恢复  
`(5)     Threshold Step For Bionic(x10) (NEW)`  
阈值调整步进为0.5  
`(40)    Maximum Threshold Adjustment Value For Bionic(x10) (NEW)`  
阈值最大调整幅度为4  
`(1000)  Threshold Adjust time For Bionic(Second) (NEW)`  
每1000秒调整一次  


* Enable Voice Print Recognition : 使能声纹识别模型，目前没有应用到声纹的场景，略。

## LVP应用设置

* LVP Application Settings ： 用于选择需要的应用，并进行相关应用设置

```
 .config - NationalChip Low-Power Voice Process Configuration
 > LVP Application Settings ─────────────────────────────────────────────────────────
  ┌────────────────────────── LVP Application Settings ───────────────────────────┐
  │  Arrow keys navigate the menu.  <Enter> selects submenus ---> (or empty       │  
  │  submenus ----).  Highlighted letters are hotkeys.  Pressing <Y> includes,    │  
  │  <N> excludes, <M> modularizes features.  Press <Esc><Esc> to exit, <?> for   │  
  │  Help, </> for Search.  Legend: [*] built-in  [ ] excluded  <M> module  < >   │  
  │ ┌───────────────────────────────────────────────────────────────────────────┐ │  
  │ │        Applications Selection: (Voice Player App)  --->                   │ │  
  │ │        Application Settings  --->                                         │ │  
  │ └───────────────────────────────────────────────────────────────────────────┘ │  
  ├───────────────────────────────────────────────────────────────────────────────┤  
  │           <Select>    < Exit >    < Help >    < Save >    < Load >            │  
  └───────────────────────────────────────────────────────────────────────────────┘  

```

* Applications Selection： 选择应用，各应用具体功能需咨询对应的项目负责人

```
          ┌─────────────────── Applications Selection: ───────────────────┐
          │  Use the arrow keys to navigate this window or press the      │  
          │  hotkey of the item you wish to select followed by the <SPACE │  
          │  BAR>. Press <?> for additional information about this        │  
          │ ┌───────────────────────^(-)────────────────────────────────┐ │  
          │ │                   ( ) MP3 Player App                      │ │  
          │ │                   ( ) NeckFans App                        │ │  
          │ │                   ( ) Sample App                          │ │  
          │ │                   ( ) Smart Light App                     │ │  
          │ │                   ( ) Voice Controller                    │ │  
          │ │                   (X) Voice Player App                    │ │  
          │ └───────────────────────────────────────────────────────────┘ │  
          ├───────────────────────────────────────────────────────────────┤  
          │                    <Select>      < Help >                     │  
          └───────────────────────────────────────────────────────────────┘ 
```

* Application Settings : 为选中的应用进行其需要的配置，此处是各个应用的独有配置，不尽相同，略

## 通用功能设置
* Common Function Settings: 用于配置各通用模块，即封装好的接口族

```
 .config - NationalChip Low-Power Voice Process Configuration
 > Common Function Settings ─────────────────────────────────────────────────────────
  ┌────────────────────────── Common Function Settings ───────────────────────────┐
  │  Arrow keys navigate the menu.  <Enter> selects submenus ---> (or empty       │  
  │  submenus ----).  Highlighted letters are hotkeys.  Pressing <Y> includes,    │  
  │  <N> excludes, <M> modularizes features.  Press <Esc><Esc> to exit, <?> for   │  
  │  Help, </> for Search.  Legend: [*] built-in  [ ] excluded  <M> module  < >   │  
  │ ┌───────────────────────────────────────────────────────────────────────────┐ │  
  │ │    [ ] Has Uart Record  ----                                              │ │  
  │ │    [ ] Enable uart record                                                 │ │  
  │ │    [ ] Has G sensor device  ----                                          │ │  
  │ │    [ ] Has voice player  ----                                             │ │  
  │ │    [ ] Has mp3 player  ----                                               │ │  
  │ │    [ ] Has factory mic test                                               │ │  
  │ │    [*] Enable Idle controller  --->                                       │ │  
  │ └───────────────────────────────────────────────────────────────────────────┘ │  
  ├───────────────────────────────────────────────────────────────────────────────┤  
  │           <Select>    < Exit >    < Help >    < Save >    < Load >            │  
  └───────────────────────────────────────────────────────────────────────────────┘  

```

* Has Uart Record: 配置录音模块

```
 .config - NationalChip Low-Power Voice Process Configuration
 > Common Function Settings > Has Uart Record ───────────────────────────────────────
  ┌─────────────────────────────── Has Uart Record ───────────────────────────────┐
  │  Arrow keys navigate the menu.  <Enter> selects submenus ---> (or empty       │  
  │  submenus ----).  Highlighted letters are hotkeys.  Pressing <Y> includes,    │  
  │  <N> excludes, <M> modularizes features.  Press <Esc><Esc> to exit, <?> for   │  
  │  Help, </> for Search.  Legend: [*] built-in  [ ] excluded  <M> module  < >   │  
  │ ┌───────────────────────────────────────────────────────────────────────────┐ │  
  │ │    --- Has Uart Record                                                    │ │  
  │ │    (0)   Uart port (NEW)                                                  │ │  
  │ │    (500000) Uart baudrate (NEW)                                           │ │  
  │ │    [ ]   Enable g_sensor data record (NEW)                                │ │  
  │ └───────────────────────────────────────────────────────────────────────────┘ │  
  ├───────────────────────────────────────────────────────────────────────────────┤  
  │           <Select>    < Exit >    < Help >    < Save >    < Load >            │  
  └───────────────────────────────────────────────────────────────────────────────┘  
```
* Enable uart record : 使能录音功能

* Has G sensor device : 配置G-sensor和G-vad相关参数，详略

```
 .config - NationalChip Low-Power Voice Process Configuration
 > Common Function Settings > Has G sensor device ───────────────────────────────────
  ┌───────────────────────────── Has G sensor device ─────────────────────────────┐
  │  Arrow keys navigate the menu.  <Enter> selects submenus ---> (or empty       │  
  │  submenus ----).  Highlighted letters are hotkeys.  Pressing <Y> includes,    │  
  │  <N> excludes, <M> modularizes features.  Press <Esc><Esc> to exit, <?> for   │  
  │  Help, </> for Search.  Legend: [*] built-in  [ ] excluded  <M> module  < >   │  
  │ ┌───────────────────────────────────────────────────────────────────────────┐ │  
  │ │    --- Has G sensor device                                                │ │  
  │ │    (16)  G sensor Vad frame shift                                         │ │  
  │ │    (13)  G sensor energy Vad threshold ( * 0.01)                          │ │  
  │ │    (128) Window for count efficacious voice frame                         │ │  
  │ │    (9)   Threshold of continuously efficacious voice frame num to trigger │ │  
  │ │    (1)   Threshold of trigged vad stride num to trigger vad               │ │  
  │ │    (1)   G sensor Vad hold context num                                    │ │  
  │ │                                                                           │ │  
  │ └───────────────────────────────────────────────────────────────────────────┘ │  
  ├───────────────────────────────────────────────────────────────────────────────┤  
  │           <Select>    < Exit >    < Help >    < Save >    < Load >            │  
  └───────────────────────────────────────────────────────────────────────────────┘  
```
* Has voice player : 使能音频播放器
* Has mp3 player : 使能MP3播放器
* Has factory mic test : 使能mic厂测功能接口
* Enable Idle controller : 使能cpu idle功能



