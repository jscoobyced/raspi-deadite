#!/bin/bash

apt-get update
apt-get upgrade -y
apt-get install -y build-essential module-assistant dkms \
     gcc-arm-linux-gnueabihf gcc-8-arm-linux-gnueabihf \
     gdb-multiarch libc6-armhf-cross libc6-dev-arm64-cross \
     zlib1g