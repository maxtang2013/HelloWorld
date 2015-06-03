#!/bin/bash
# 1, copy the working kernel config
cd ${linux_src}
cp /boot/config-`uname -r` .config

# 2, let the make script detect your hardware
#    it will use lsmod/lspci to determine what drivers you will need.
make localmodconfig

# 3, make some adjustment
make menuconfig


