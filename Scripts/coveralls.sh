#!/bin/bash

source Scripts/xcenv.sh
declare -r DIR_BUILD="${OBJECT_FILE_DIR_normal}/${CURRENT_ARCH}/"
xcode-coveralls --include XS-C++ "${DIR_BUILD}"
