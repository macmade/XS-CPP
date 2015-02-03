#!/bin/bash

. /etc/lsb-release

declare -r MAJOR=$(echo "$DISTRIB_RELEASE" | perl -e "s/([0-9]+).*/\1/" -pi)

if [ $MAJOR -lt 14 ]; then
    
    echo "Ubuntu 14 or greater is required"
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
