#!/bin/bash

# Installs dependancies
sudo apt-get install gcc
sudo apt-get install clang
sudo apt-get install yasm
sudo apt-get install make
sudo apt-get install cmake
sudo apt-get install libtool
sudo apt-get install libc++1
sudo dpkg --add-architecture i386
sudo apt-get install libc++1:i386
sudo dpkg --remove-architecture i386
