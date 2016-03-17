cmake_minimum_required(VERSION 2.8)

# add_subdirectory(3rdparty)

# find Qt5
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Concurrent REQUIRED)
include_directories(
        ${Qt5Widgets_INCLUDE_DIRS}
        ${Qt5Core_INCLUDE_DIRS}
        ${Qt5Concurrent_INCLUDE_DIRS}
)

#find OpenCV
find_package(OpenCV REQUIRED)
include_directories(
        ${OpenCV_INCLUDE_DIRS}
)

add_definitions(-std=c++11)

include_directories(
        ${CMAKE_BINARY_DIR}/frontend/src/
        backend/QtAndOpenCV/src
)

add_subdirectory(backend)

add_subdirectory(frontend)