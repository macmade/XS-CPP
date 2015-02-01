#!/bin/bash

# Update packages
sudo dpkg --add-architecture i386
sudo apt-get update

# Installs dependancies
sudo apt-get -y install make
sudo apt-get -y install clang
sudo apt-get -y install libc++1
sudo apt-get -y install libc++1:i386
sudo apt-get -y install libc++-dev
sudo apt-get -y install libc++-dev:i386
sudo apt-get -y install libc6
sudo apt-get -y install libc6:i386
sudo apt-get -y install libc6-dev
sudo apt-get -y install libc6-dev:i386
