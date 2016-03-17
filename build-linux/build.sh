#!/usr/bin/env bash

cmake .. -DCMAKE_PREFIX_PATH=$(zenity --file-selection --directory) -DCMAKE_BUILD_TYPE=Debug
make -j4