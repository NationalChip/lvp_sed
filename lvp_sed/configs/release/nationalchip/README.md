# 编译配置功能简介
---
## 1.常用录音配置
* grus_gx8002b_debug_2dmic_record.config                        :
    dev板，录音两路Dmic音频
* grus_gx8002b_debug_amic+dmic_record.config                    :
    dev板，录音1路Amic和1路Dmic音频，不支持同时录两路
* grus_gx8002b_debug_amic_record.config                         :
    dev板，录音1路Amic音频
* grus_gx8002b_debug_dmic_record.config                         :
    dev板，录音1路Dmic音频
* grus_gx8002b_dev_1v_record_gsensor.config                     :
    dev板，录音G-sensor数据
* grus_gx8002b_dev_1v_fft_record.config                         :
    dev板，录音fft数据，Dmic，1000000波特率
* grus_gx8002b_dev_1v_fft_recover_demo.config                   :
    dev板，可串口录制和Aout输出硬件fft数据recover后获得的音频
* grus_gx8002b_dev_1v_adpcm_uart_record_demo.config             :
    dev板，adpcm编解码demo，串口0输出音频

---
## 2. 常用示例demo配置
* grus_gx8002b_dev_1v.config                                    :
    dev板，低频率方案示例配置，可“天猫精灵”唤醒后串口1输出相应log
* grus_gx8002b_dev_1v_code_xip_npu_sram.config                  :
    dev板，内存精简方案示例配置，sram留出近160KB空闲空间，可“天猫精灵”唤醒后串口1输出相应log
* grus_gx8002b_dev_1v_external_flash_dynamic_load_demo.config   :
    dev板，从外部flash动态加载程序运行demo
* grus_gx8002b_dev_1v_flash_demo.config                         :
    dev板，flash读写demo
* grus_gx8002b_dev_1v_leo_mini_uart_upgrade_demo.config         :
*   dev板，8002通过串口升级8008c demo
* grus_gx8002b_dev_1v_iic_test_master.config
    iic测试示例 master编译配置
* grus_gx8002b_dev_1v_iic_test_slave.config
    iic测试示例 slave编译配置
* grus_gx8002b_dev_1v_low_power_test.config
    低功耗测试比编译配置,小度小度，天猫精灵
* grus_gx8002b_dev_1v_tmjl_demo.config
    npu编译示例：天猫精灵
* grus_gx8002b_dev_1v_xdxd_short_instruction_v0.2.2_v0.1.9_hybrid_bm_ctc.config    :
    291859: 支持大小模型切换, 添加计算1秒【可配】待机比例和上电后的待机比例
* grus_gx8002c_dev_1v_noflash.config :
    8002c dev板子 无flash启动方案
---
## 3. 英文模型示例配置
* grus_gx8002b_dev_1v_en[heysiri_okgoogle]_v0.1.0.config        :
* grus_gx8002b_dev_1v_en[heysiri_okgoogle]_v0.1.1.config        :
* grus_gx8002b_dev_1v_en[heysiri_okgoogle]_v0.1.3.config        :
* grus_gx8002b_dev_1v_en[heysiri_okgoogle]_v0.1.4.config        :
* grus_gx8002b_dev_1v_en[heysiri_okgoogle]_v0.1.5.config        :
* grus_gx8002b_dev_1v_en[heysiri_okgoogle]_v0.1.8.config        :
    dev板，英文模型示例配置

---
## 4. 中文模型示例配置
* grus_gx8002b_dev_1v_xatx_tmjl_short_instruction_v0.1.3.config :
* grus_gx8002b_dev_1v_xatx_tmjl_short_instruction_v0.1.4.config :
* grus_gx8002b_dev_1v_xatx_tmjl_short_instruction_v0.1.5.config :
* grus_gx8002b_dev_1v_xatx_tmjl_short_instruction_v0.1.6.config :
    dev板，中文模型示例配置


---
## 5. 中性词示例配置
* grus_gx8002b_dev_1v_xkxk_xaxa_short_instruction_v0.1.0.config :
* grus_gx8002b_dev_1v_xkxk_xaxa_short_instruction_v0.1.1.config :
    dev板, 小酷小酷 小艾小艾 中性词模型示例配置

---
## 6. 耳机样机示例配置
* grus_gx8002b_dev_1v_xatx_tmjl_short_instruction_v0.1.6_OVVP.config :
    耳机样机，带Gvad功能(DA662)的耳机方案示例
* grus_gx8002b_dev_erji_tmjl.config                             :
    耳机样机，耳机无Gvad耗方案示例
* grus_gx8002b_dev_erji_tmjl_Gvad.config                        :
    耳机样机，带Gvad功能的耳机方案示例

---
## 7. AIOT语音回复配置
* grus_gx8002b_aiot_1v_voice_player.config                      :
    AIOT板， 小红小红唤醒 语音回复 风扇方案
* grus_gx8002b_aiot_1v_voice_player_low_power.config            :
    AIOT板， 小红小红唤醒 语音回复 低功耗待机 风扇方案
* grus_gx8002b_aiot_1v_kejia.config            :
    AIOT板， 你好小可唤醒 语音回复  晾衣架方案


---
## 8. 华为大模型配置
* grus_gx8002b_dev_1v_huawei_watch_v0.1.0_bm_ctc.config         :
* grus_gx8002b_dev_1v_huawei_watch_v0.1.2_bm_ctc.config         :
    DEV板，华为大模型, 小易小易，示例配置，有唤醒log输出，269977
* grus_gx8002b_dev_1v_huawei_watch_v0.1.2_bm_ctc_open_standby.config :
    DEV板，华为大模型, 小易小易，示例配置，有唤醒log输出，269977
* grus_gx8002b_dev_1v_huawei_watch_v0.1.6_ctc.config    :
    DEV板，数字麦，华为大模型， 小易小易，示例配置，有唤醒log输出，273007
* grus_gx8002b_dev_1v_huawei_watch_v0.1.7_ctc.config    :
    DEV板，数字麦，华为大模型， 小易小易，示例配置，有唤醒log输出，273008
* grus_gx8002b_dev_1v_huawei_watch_dmic_v0.1.5_lm_v0.0.2_bm_ctc_open_standby.config    :
    DEV板，数字麦，华为大模型，语音模型v0.0.2, 小易小易，示例配置，有唤醒log输出，272480
* grus_gx8002b_dev_1v_huawei_watch_amic_v0.1.5_lm_v0.0.2_bm_ctc_open_standby.config    :
    DEV板，模拟麦，华为大模型，语音模型v0.0.2, 小易小易，示例配置，有唤醒log输出，272480
* grus_gx8002b_dev_1v_huawei_watch_v0.1.1_bm_ctc.config         :
    DEV板，华为大模型，语音模型v0.0.1, 小易小易，示例配置，有唤醒log输出，269977
* grus_gx8002b_dev_1v_huawei_watch_v0.1.2_lm_v0.0.2_bm_ctc_open_standby.config         :
    DEV板，华为大模型，语音模型v0.0.2, 小易小易，示例配置，有唤醒log输出，269977
* grus_gx8002b_dev_1v_npu_xip_standby.config
    DEV 板　华为手表模型 模型xip 用于功耗测试


---
## 9. 精益方案示例配置
* grus_gx8002b_dev_1v_kws_state_demo_v0.0.1.config:
    DEV板,kws_state_demo 小艾小艾,298820
* grus_gx8002b_dev_1v_jingyi_drying_rack_v0.1.1_lm_v0.0.1.confg :
    DEV板,精益晾衣架遥控器，模型v0.1.1，语言模型v0.1.1
* grus_gx8002b_dev_1v_jingyi_drying_rack_v0.1.2_lm_v0.0.1.confg :
    DEV板,精益晾衣架遥控器，模型v0.1.2，语言模型v0.0.1
* grus_gx8002b_dev_1v_jingyi_sunshade_v0.1.1_lm_v0.0.1.confg    :
    DEV板,精益遮阳棚遥控器，模型v0.1.1，语言模型v0.0.1
* grus_gx8002b_aiot_1v_adpcm_voice_palyer.config
    AIOT板,adpcm编码音频播放demo
* grus_gx8002b_dev_1v_jingyi_projection_screen_v0.1.1_lm_v0.0.1.config   :
    DEV板,精益遮阳棚i+投影幕遥控器，模型v0.1.1，语言模型v0.0.1
* grus_gx8002b_dev_1v_jingyi_remote.config
    精益浴霸面板遥控器方案
---

## 10. 奥普晾衣架配置
* configs/grus_gx8002b_dev_1v_taitaile_drying_rack_v0.1.0_lm_v0.0.1.confg :
    DEV板,太太乐晾衣架，模型v0.1.0，语言模型v0.0.1
* grus_gx8002b_dev_1v_aupu_drying_rack_v0.1.0_lm_v0.0.1.confg   :
    aupu板 dev板级，奥普晾衣架遥控器，模型v0.1.1，语言模型v0.0.1
* grus_gx8002b_aiot_1v_aupu_drying_rack_voiceplayer_v0.1.0_lm_v0.0.1.config :
    AIOT板 奥普晾衣架遥控器播报demo，模型v0.1.1，语言模型v0.0.1

---
## 11. 阿里晾衣架demo配置
* grus_gx8002b_aiot_1v_curtain_bingshen_has_voice_player.config
    阿里丙申测试编译配置，带播报版本，唤醒词小丙小丙，小申小申
* grus_gx8002b_dev_1v_curtain_bingshen_has_low_power_test.config
    阿里丙申低功耗测试编译配置，模型开合帘0.2.0,唤醒词:小丙小丙，小申小申

---
## 12. 补光灯配置
* grus_gx8002b_dev_1v_slight_zh_4key_v0.1.5.config              :
    补光灯板，４个按键和语音调光，262200
* grus_gx8002b_dev_1v_slight_zh_6key_v0.1.5.config              :
    补光灯板，６个按键和语音调光，262200
---
## 13. 其他方案
* grus_gx8002b_dev_1v_shanghaijingyi_hghg_v0.0.1.config:
    DEV板,上海景逸晾衣架（好哥好哥),295238
* grus_gx8002b_dev_1v_xxxx_short_instruction_v0.1.0.config      :
    DEV板，今日头条, 小贤小贤，示例配置，有唤醒log输出，269523
* grus_gx8002b_dev_1v_helmet_v0.0.2.config              :
    DEV板 浩聚头盔
* grus_gx8002b_dev_1v_wei_mai_tong_demo.config                  :
    维迈通方案demo
