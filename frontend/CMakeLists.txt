cmake_minimum_required(VERSION 2.8)

qt5_add_resources(HOLLOW_SCORPION_RESOURCES res/resources.qrc)

qt5_wrap_ui(HOLLOW_SCORPION_UI res/mainwidget.ui)

add_executable(HollowScorpion ${HOLLOW_SCORPION_RESOURCES} ${HOLLOW_SCORPION_UI}
        src/main.cpp
        src/MainWidget.h
        src/MainWidget.cpp
        src/Median.h
        src/Median.cpp
        src/Canny.h
        src/Canny.cpp
        )

target_link_libraries(HollowScorpion
        Qt5::Widgets
        Qt5::Core
        Qt5::Concurrent
        ${OpenCV_LIBS}
        QtAndOpenCv
        )