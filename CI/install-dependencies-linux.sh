#!/bin/sh
set -ex

# OBS Studio deps
sudo add-apt-repository ppa:kirillshkrogalev/ffmpeg-next -y
sudo apt-get -qq update
sudo apt-get install -y \
        build-essential \
        checkinstall \
        cmake \
        libasound2-dev \
        libavcodec-ffmpeg-dev \
        libavdevice-ffmpeg-dev \
        libavfilter-ffmpeg-dev \
        libavformat-ffmpeg-dev \
        libavutil-ffmpeg-dev \
        libcurl4-openssl-dev \
        libfontconfig-dev \
        libfreetype6-dev \
        libgl1-mesa-dev \
        libjack-jackd2-dev \
        libjansson-dev \
        libpulse-dev \
        libqt5x11extras5-dev \
        libspeexdsp-dev \
        libswresample-ffmpeg-dev \
        libswscale-ffmpeg-dev \
        libudev-dev \
        libv4l-dev \
        libvlc-dev \
        libx11-dev \
        libx264-dev \
        libxcb-shm0-dev \
        libxcb-xinerama0-dev \
        libxcomposite-dev \
        libxinerama-dev \
        pkg-config \
        qtbase5-dev

# obs-websocket deps
sudo apt-get install -y libqt5websockets5-dev

# Build obs-studio
cd ..
git clone https://github.com/jp9000/obs-studio ./obs-studio
cd obs-studio

mkdir build && cd build
cmake -DUNIX_STRUCTURE=1 -DCMAKE_INSTALL_PREFIX=/usr ..
make -j4 && sudo make install