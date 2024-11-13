# lvp_sed
* lvp_sed 概述：
    * **lvp_sed** 全称为 Lower-Power Voice Process Sound Event Detection， 是专门为了低功耗哭声检测等事件检测应用而语音信号处理框架，适用于 **GX8002A/GX8002B** 芯片，开发者可以部署自己训练的模型。
* GX8002 是一款专为低功耗领域设计的 **超低功耗 AI 神经网络芯片**，适用于低功耗可穿戴设备和语音遥控器等应用。该芯片具有体积小、功耗低、成本低等显著优势。它集成了杭州国芯微自主研发的第二代神经网络处理器 gxNPU V200，支持 **TensorFlow** 和 **Pytorch** 框架，以及自研的硬件 VAD（语音活动检测），显著降低了功耗。在实际测试场景中，VAD 待机功耗可低至 70uW，运行功耗约为 0.6mW，芯片的平均功耗约为 300uW。
    * [GX8002芯片数据手册](https://nationalchip.gitlab.io/ai_audio_docs/hardware/%E8%8A%AF%E7%89%87%E6%95%B0%E6%8D%AE%E6%89%8B%E5%86%8C/GX8002%E8%8A%AF%E7%89%87%E6%95%B0%E6%8D%AE%E6%89%8B%E5%86%8C/)

## 开发板介绍
* 请阅读：[GX8002_DEV开发板介绍](https://nationalchip.gitlab.io/ai_audio_docs/hardware/%E5%BC%80%E5%8F%91%E6%9D%BF%E7%A1%AC%E4%BB%B6%E5%8F%82%E8%80%83%E8%AE%BE%E8%AE%A1/GX8002/GX8002_DEV%E5%BC%80%E5%8F%91%E6%9D%BF/)，在此页面您可以下载开发板 **硬件规格资料** 和 **硬件设计资料**。

## SDK工具链安装
* 请阅读：[SDK工具链安装](https://nationalchip.gitlab.io/ai_audio_docs/software/lvp/SDK%E5%BC%80%E5%8F%91%E6%8C%87%E5%8D%97/SDK%E5%BF%AB%E9%80%9F%E5%85%A5%E9%97%A8/%E6%90%AD%E5%BB%BA%E5%BC%80%E5%8F%91%E7%8E%AF%E5%A2%83/#1-sdk)

## SDK开发指南
* 请阅读 [https://github.com/NationalChip/lvp_kws/blob/main/README.md](https://github.com/NationalChip/lvp_kws/blob/main/README.md)

## 编译命令：
1. cp ./configs/release/nationalchip/grus_gx8002b_dev_1v_sed_0_1_1.config .config
2. make menuconfig
3. 然后保存退出
4. make clean;make

## 固件烧录：
* 请阅读：[串口升级](https://nationalchip.gitlab.io/ai_audio_docs/software/lvp/SDK%E5%BC%80%E5%8F%91%E6%8C%87%E5%8D%97/SDK%E5%BF%AB%E9%80%9F%E5%85%A5%E9%97%A8/%E4%B8%B2%E5%8F%A3%E5%8D%87%E7%BA%A7/)

