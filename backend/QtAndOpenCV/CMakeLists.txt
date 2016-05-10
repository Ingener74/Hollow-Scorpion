cmake_minimum_required(VERSION 3.0)

set(QtAndOpenCv_SOURCES
    src/QtAndOpenCvTools.cpp
    src/QtAndOpenCvTools.h
)

if(NOT WIN32)
	add_definitions(-fPIC)
endif()

add_library(QtAndOpenCv ${QtAndOpenCv_SOURCES})
