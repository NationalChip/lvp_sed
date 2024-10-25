# lvp_sed
低功耗声音事件检测SDK，支持哭声检测

## 环境安装
linux环境编译

sudo apt-get install libncurses5-dev

## 工具链下载和安装
### 工具链下载地址：https://ai.nationalchip.com/api/v1/assets/32/download

### 安装:
1. sudo mkdir -p /opt/csky-abiv2-elf/; cd /opt/csky-abiv2-elf/; 新建并进入路径
2. sudo tar xvf csky-elfabiv2-tools-x86_64-minilibc-*.tar.gz; 解压到当前路径
3. 然后需要编辑 ~/.profile或者 ~/.bashrc，将/opt/csky-abiv2-elf/bin加入到PATH路径中

## 编译命令：
1. cp ./configs/release/nationalchip/grus_gx8002b_dev_1v_sed_0_1_1.config .config
2. make menuconfig
3. 然后保存退出
4. make clean;make

## 固件烧录
1. cd tools/bootx/
2. sudo ./bootx -m grus -c download 0x0 ../../output/mcu_nor.bin -d /dev/ttyUSB0
3. 重启设备,等待烧录完成
4. 打开串口终端,重启设备,查看串口输出

