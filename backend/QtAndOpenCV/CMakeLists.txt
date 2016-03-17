cmake_minimum_required(VERSION 2.8)

set(QtAndOpenCv_SOURCES
    src/QtAndOpenCvTools.cpp
    src/QtAndOpenCvTools.h
)

add_definitions(-fPIC)

add_library(QtAndOpenCv ${QtAndOpenCv_SOURCES})
