cmake_minimum_required(VERSION 3.0)

qt5_add_resources(HOLLOW_SCORPION_RESOURCES res/resources.qrc)

qt5_wrap_ui(HOLLOW_SCORPION_UI res/mainwidget.ui)

set(HollowScorpion_SOURCES
	${HOLLOW_SCORPION_RESOURCES} 
	${HOLLOW_SCORPION_UI}
	src/main.cpp
	src/MainWidget.h                
	src/MainWidget.cpp
	)

if(WIN32)
		add_executable(HollowScorpion WIN32 ${HollowScorpion_SOURCES} res/resources.rc)
else()
        add_executable(HollowScorpion ${HollowScorpion_SOURCES})
endif()

target_link_libraries(HollowScorpion
        Qt5::Widgets
        Qt5::Core
        Qt5::Concurrent
        ${OpenCV_LIBS}
        QtAndOpenCv
        )
