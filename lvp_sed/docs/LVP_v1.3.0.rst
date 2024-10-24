
# 1.3.0

-------------
-------------

## 版本信息


* 产品
    Lower-Power Voice Process
* 版本号
    v1.3.0
* 发布日期
    2020年5月16日
* 客户支持
    更多的信息和支持，可联系贾立鹏（邮箱：jialp@nationalchip.com）

-------------
-------------

## 最近修改
-------------
-------------

相比v1.2.0，本版本主要修复或实现了以下的问题:

1. 解决ADC低压下工作异常问题
2. 解决grus 同时使用两个pwm时会出现状态混乱
3. lvp.zip增加下载配置文件，供win dowload gui工具使用
4. 增加FFT录音功能
5. lvp添加模式fft_recover，用于验证硬件FFT
6. 优化开机log
7. 更新kws算法部署工具
8. 支持npu nc_npu vp_npu等section使用动态LMA
9. 增加外部spi flash程序动态加载功能
10. 调整清理bss段的调用位置以规避可能的风险
11. 解除vad触发后回退使用logfbank数据时对context buffer的依赖
12. 修正串口协议接口中的一处bug

13. 支持双麦 mvdr 唤醒
14. vad 与 context 解耦

-------------
-------------


