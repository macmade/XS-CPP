#!/bin/bash

declare -r UBUNTU_14=`uname -v | grep trusty`

if [ -z $UBUNTU_14 ]; then
    
    echo "Ubuntu 14 Trusty is required"
    exit 1

fi

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
