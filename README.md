# Application for transferring video files from webcam to Orange Pi (using OpenCV)

This application records webcam video to files and transfers these files to a file server based on cloud storage

Это приложение записывает видео с вебкамеры в файлы и передает эти файлы на файловый сервер на базе облачного хранилища

## How to use

First you need to connect to Orange Pi via ssh and perform updates
Для начала необходимо подключиться к Orange Pi по ssh и выполнить обновления

    ssh root@<ip_Address_OrangePi>
    cd online_monitoring/

Then you need to install the dependencies
Затем необходимо установить зависимости

    sudo apt-get update
    sudo apt-get upgrade

    sudo apt-get install build-essential cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev

    sudo apt-get install python3.9-dev python3-numpy libtbb2 libtbb-dev 

    sudo apt-get install libjpeg-dev libpng-dev libtiff5-dev libdc1394-22-dev libeigen3-dev libtheora-dev libvorbis-dev libxvidcore-dev libx264-dev sphinx-common libtbb-dev yasm libfaac-dev libopencore-amrnb-dev libopencore-amrwb-dev libopenexr-dev libgstreamer-plugins-base1.0-dev libavutil-dev libavfilter-dev libavresample-dev

    sudo apt-get install libopencv-dev

The next step is to clone the repositories with OpenCV sources and create a folder for the build
Следующим шагом необходимо клонировать репозитории с иходниками OpenCV и создать папку для сборки

    sudo -s
    cd /opt
    git clone https://github.com/Itseez/opencv.git
    git clone https://github.com/Itseez/opencv_contrib.git
    cd opencv
    mkdir release 
    cd release


Now all that remains is to complete the building and installing
Теперь осталось лишь выполнить сборку и установку
    cmake -D BUILD_TIFF=ON -D WITH_CUDA=OFF -D ENABLE_AVX=OFF -D WITH_OPENGL=OFF -D WITH_OPENCL=OFF -D WITH_IPP=OFF -D BUILD_TBB=ON -D WITH_EIGEN=OFF -D WITH_V4L=OFF -D WITH_VTK=OFF -D BUILD_TESTS=OFF -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSRALL_PREFIX=/usr/local -D OPENCV_EXTRA_MODULES_PATH=/opt/opencv_contrib/modules/ /opt/opencv
    make -j4
    make install
    ldconfig
    exit
    cd ~

Checking the version
    pkg-config --modversion opencv4

Copy source files
    scp main.cpp root@192.168.47.6:~/workdir

Compile
    g++ ~/workrir/main.cpp -o ~/workrir/output `pkg-config --cflags --libs opencv4`
or add a variable to file: /etc/envariment
    $CMAKE_PREFIX_PATH="/opt/opencv/release"

Copy files to localhost
    scp -r root@192.168.47.6:~/workdir/*.mkv ~/workdir

## Links

    https://docs.opencv.org/master/d0/d76/tutorial_arm_crosscompile_with_cmake.html
    https://www.youtube.com/watch?v=6pABIQl1ZP0
    http://techawarey.com/programming/install-opencv-c-c-in-ubuntu-18-04-lts-step-by-step-guide/
    https://robotclass.ru/articles/raspberrypi-3-opencv-3-install/
