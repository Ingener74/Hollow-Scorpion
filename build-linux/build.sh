#!/usr/bin/env bash

cmake .. -DCMAKE_PREFIX_PATH=$(zenity --file-selection --directory --title="<home>/Qt5.6.0/5.6/gcc_64/lib/cmake") -DCMAKE_BUILD_TYPE=Debug
make -j4
