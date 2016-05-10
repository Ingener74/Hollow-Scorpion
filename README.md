# Hollow-Scorpion

Зависимости для сборки
* Qt 5.5+
* OpenCV 2.4.12+

Команды для сборки
```
pavel@pavel-vb:~$ git clone https://github.com/Ingener74/Hollow-Scorpion.git
Cloning into 'Hollow-Scorpion'...
remote: Counting objects: 97, done.
remote: Compressing objects: 100% (72/72), done.
remote: Total 97 (delta 27), reused 89 (delta 22), pack-reused 0
Unpacking objects: 100% (97/97), done.
Checking connectivity... done.
pavel@pavel-vb:~$ cd Hollow-Scorpion/build-linux/
pavel@pavel-vb:~/Hollow-Scorpion/build-linux$ ./build.sh 
Gtk-Message: GtkDialog mapped without a transient parent. This is discouraged.
-- The C compiler identification is GNU 5.2.1
-- The CXX compiler identification is GNU 5.2.1
-- Check for working C compiler: /usr/bin/cc
-- Check for working C compiler: /usr/bin/cc -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Check for working CXX compiler: /usr/bin/c++
-- Check for working CXX compiler: /usr/bin/c++ -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: /home/pavel/Hollow-Scorpion/build-linux
Scanning dependencies of target HollowScorpion_automoc
Scanning dependencies of target QtAndOpenCv_automoc
[  8%] Automatic moc for target HollowScorpion
[ 16%] Automatic moc for target QtAndOpenCv
Generating moc_MainWidget.cpp
[ 16%] Built target QtAndOpenCv_automoc
Scanning dependencies of target QtAndOpenCv
[ 25%] Building CXX object backend/QtAndOpenCV/CMakeFiles/QtAndOpenCv.dir/QtAndOpenCv_automoc.cpp.o
[ 33%] Building CXX object backend/QtAndOpenCV/CMakeFiles/QtAndOpenCv.dir/src/QtAndOpenCvTools.cpp.o
[ 33%] Built target HollowScorpion_automoc
[ 41%] Linking CXX static library libQtAndOpenCv.a
[ 41%] Built target QtAndOpenCv
[ 50%] Generating qrc_resources.cpp
[ 58%] Generating ui_mainwidget.h
Scanning dependencies of target HollowScorpion
[ 66%] Building CXX object frontend/CMakeFiles/HollowScorpion.dir/qrc_resources.cpp.o
[ 75%] Building CXX object frontend/CMakeFiles/HollowScorpion.dir/src/MainWidget.cpp.o
[ 83%] Building CXX object frontend/CMakeFiles/HollowScorpion.dir/HollowScorpion_automoc.cpp.o
[ 91%] Building CXX object frontend/CMakeFiles/HollowScorpion.dir/src/main.cpp.o
[100%] Linking CXX executable HollowScorpion
[100%] Built target HollowScorpion
pavel@pavel-vb:~/Hollow-Scorpion/build-linux$ ./frontend/HollowScorpion 
```

![Github Logo](/help/1.png)
![Github Logo](/help/2.png)
![Github Logo](/help/3.png)
![Github Logo](/help/4.png)
![Github Logo](/help/5.png)

