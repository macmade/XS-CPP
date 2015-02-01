#!/bin/bash

. /etc/lsb-release

if [ $(echo "$DISTRIB_RELEASE < 14" | bc) -eq 1 ]; then
    
    echo "Ubuntu 14 Trusty is required"
    exit 1

fi

sudo dpkg --add-architecture i386
sudo apt-get update

sudo apt-get -y install make
sudo apt-get -y install clang
sudo apt-get -y install libc6
sudo apt-get -y install libc6:i386
sudo apt-get -y install libc6-dev
sudo apt-get -y install libc6-dev:i386
sudo apt-get -y install libc++1
sudo apt-get -y install libc++1:i386
sudo apt-get -y install libc++-dev
sudo apt-get -y install libc++-dev:i386
