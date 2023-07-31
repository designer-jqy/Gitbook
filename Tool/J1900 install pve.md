# 软路由安装

## 安装PVE
### 1. 制作启动U盘
1. 下载镜像
2. 刷写U盘，[官方之作方法](https://pve.proxmox.com/wiki/Prepare_Installation_Media#installation_prepare_media)包含Linux、Windows和MacOS上的三种不同的制作方法<br>
    以MacOS为例:
    1. Open the terminal (query Terminal in Spotlight).
    2. Convert the .iso file to .dmg format using the convert option of hdiutil, for example:
        ```shell
        # hdiutil convert proxmox-ve_*.iso -format UDRW -o proxmox-ve_*.dmg
        ```
        >Tip: macOS tends to automatically add .dmg to the output file name.
    3. To get the current list of devices run the command:
        ```shell
        # diskutil list
        ```
    4. Now insert the USB flash drive and run this command again to determine which device node has been assigned to it. (e.g., /dev/diskX).
    =
        ```shell
        # diskutil list
        # diskutil unmountDisk /dev/diskX
        ```
        >Note:	replace X with the disk number from the last command.
        ```shell
        # sudo dd if=proxmox-ve_*.dmg bs=1M of=/dev/rdiskX
        ```
        >Note: rdiskX, instead of diskX, in the last command is intended. It will increase the write speed.

### 2. 主板BIOS配置
1. 处理器支持虚拟化的开启虚拟化
2. 关闭安全启动
3. 配置从U盘启动
    > UEFI模式启动的话，关闭其他所有的启动项，仅留U盘作为唯一启动项; 不这样配置的话，在最终的安装中可能会报: `failed to prepare EFI boot using Grub on '/dev/sda2': unable to install the EFI boot loader on '/dev/sda'` <br>
    > 可以通过`Ctrl+Alt+Fn(n为1-6)`来切换文本终端查看具体的日志详情 <br>
    > 本人安装过程中遇到的问题如下;
    ```log
    grub-install.real: warning: Cannot set EFI variable Boot0000
    grub-install.real: warning: efivarfs_set_variable: writing to fd 6 failed: Input/output error. 
    grub-install.real: warning: _efi_set_variable_model: ops->set_vaariable() failed: Input/output error.
    grub-install.real: error: failed to register the EFI boot entry: Input/output error.
    Generating grub configuration file ...
    Found linux image: /boot/vmlinuz-6.2.16-3-pve
    Found initrd image: /boot/initrd.img-6.2.16-3-pve
    Found memtest86+ 64bit EFI image: /boot/memtest86+x64.efu
    done
    bootloader setup errors:
    - failed to prepare EFI boot using Grub on '/dev/sda2': unable to install the EFI boot loader on '/dev/sda'
    dpkg-diver: warning: please specify --no-rename explicitly, the dafault will change to --rename in 1.20.x
    ```
    > 最终通过安装低版本的7.4-1镜像解决(原本安装的是最新版本8.0-2)

### 3. 配置PVE源
1. 参考清华镜像源配置

    一般情况下，将 `/etc/apt/sources.list` 文件中 Debian 默认的源地址 http://deb.debian.org/ 替换为镜像地址即可。
    Debian Buster 以上版本默认支持 HTTPS 源。如果遇到无法拉取 HTTPS 源的情况，请先使用 HTTP 源并安装：
    ```shell
    sudo apt install apt-transport-https ca-certificates
    ```

    ```shell
    # 默认注释了源码镜像以提高 apt update 速度，如有需要可自行取消注释
    deb https://mirrors.tuna.tsinghua.edu.cn/debian/ bullseye main contrib non-free
    # deb-src https://mirrors.tuna.tsinghua.edu.cn/debian/ bullseye main contrib non-free

    deb https://mirrors.tuna.tsinghua.edu.cn/debian/ bullseye-updates main contrib non-free
    # deb-src https://mirrors.tuna.tsinghua.edu.cn/debian/ bullseye-updates main contrib non-free

    deb https://mirrors.tuna.tsinghua.edu.cn/debian/ bullseye-backports main contrib non-free
    # deb-src https://mirrors.tuna.tsinghua.edu.cn/debian/ bullseye-backports main contrib non-free

    # deb https://mirrors.tuna.tsinghua.edu.cn/debian-security bullseye-security main contrib non-free
    # # deb-src https://mirrors.tuna.tsinghua.edu.cn/debian-security bullseye-security main contrib non-free

    deb https://security.debian.org/debian-security bullseye-security main contrib non-free
    # deb-src https://security.debian.org/debian-security bullseye-security main contrib non-free
    ```
    不过，一般来说，为了更及时地获得安全更新，不推荐使用镜像站安全更新软件源，因为镜像站往往有同步延迟。参考 https://www.debian.org/security/faq.en.html#mirror

    > The purpose of security.debian.org is to make security updates available as quickly and easily as possible.
    > 
    > Encouraging the use of unofficial mirrors would add extra complexity that is usually not needed and that can cause frustration if these mirrors are not kept up to date.
 2. `apt update`更新源

## 安装OpenWrt


## 参考
1. [PVE官网](https://pve.proxmox.com/wiki/Main_Page)
2. [清华镜像](https://mirrors.tuna.tsinghua.edu.cn/help/debian/)
3. [PVE 监控增加温度显示](https://tty228.github.io/2022/06/18/%E3%80%90Proxmox%20VE%E3%80%91PVE%20%E9%A6%96%E9%A1%B5%E6%98%BE%E7%A4%BA%20CPU%E3%80%81%E4%B8%BB%E6%9D%BF%E3%80%81NVME%E3%80%81%E7%A1%AC%E7%9B%98%20%E6%B8%A9%E5%BA%A6%E7%AD%89%E4%BF%A1%E6%81%AF/)
4. [openwrt安装](https://www.right.com.cn/forum/thread-4059779-1-1.html)