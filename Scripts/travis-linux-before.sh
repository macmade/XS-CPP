#!/bin/bash

declare -r UBUNTU_14=`uname -v | grep trusty`

if [ ! -z $UBUNTU_14 ]; then
    sudo dpkg --add-architecture i386
    sudo apt-get update
fi

# Installs dependancies
sudo apt-get -y install make
sudo apt-get -y install clang
sudo apt-get -y install libc6
sudo apt-get -y install libc6:i386
sudo apt-get -y install libc6-dev
sudo apt-get -y install libc6-dev:i386

if [ ! -z $UBUNTU_14 ]; then
    sudo apt-get -y install libc++1
    sudo apt-get -y install libc++1:i386
    sudo apt-get -y install libc++-dev
    sudo apt-get -y install libc++-dev:i386
else
    export LIBRARY_PATH=/usr/lib/i386-linux-gnu/
    export C_INCLUDE_PATH=/usr/include/i386-linux-gnu
    export CPLUS_INCLUDE_PATH=/usr/include/i386-linux-gnu
fi
