
# 1.5.0

-------------
-------------

## 版本信息


* 产品
    Lower-Power Voice Process
* 版本号
    v1.5.0
* 发布日期
    2021年8月12日
* 客户支持
    更多的信息和支持，可联系贾立鹏（邮箱：jialp@nationalchip.com）

-------------
-------------

## 最近修改
-------------
-------------

相比v1.4.0，本版本主要修复或实现了以下的问题:

1. 286073: 将out_buffer从context中分离出来，使用连续的buffer通过context_header管理
2. 285166: 同步scpu提交到lvp，解决Os编译出现挂掉
3. 286787: auto_model增加kws同value功能
4. 285867: mp3双声道差分播放demo 增加dac输出的可配置项
5. 257653: 驱动更新
6. 289042: lvp的phripherals/ 从driver/ 挪入 common/
7. 281219: 支持tws模式和denoise模式使用不同的iobuffer settings
8. 291142: lvp新的时钟配置方案以解决串口乱码问题，使用PLL替代OSC24M
9. 281388: 增加对audioin i2s输入的fft recover支持
10. 257653: 优化lvp 板级频率配置的宏设置
11. 291859: 支持大小模型切换, 添加计算1秒【可配】待机比例和上电后的待机比例

-------------
-------------


