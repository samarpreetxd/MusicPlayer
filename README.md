# Qt Music Player

A simple C++/Qt6 music player built with CLion and CMake.  
It supports playlists, playback controls, volume, and progress sliders.

## Features
- Play, pause, stop, next, and previous track controls
- Playlist with double-click to play
- Volume and progress sliders
- Supports MP3, WAV, and OGG formats
- Automatically continues to next track

## Requirements
- [Qt 6](https://www.qt.io/download) with Multimedia module installed
- CMake 3.16+
- A C++17 compatible compiler (e.g. MinGW, MSVC, clang)

## Build Instructions
```bash
git clone https://github.com/samarpreetxd/qt-music-player.git
cd qt-music-player
mkdir build && cd build
cmake ..
cmake --build .
````

## Run

```bash
./untitled
```

## Project Structure

```
├── CMakeLists.txt
├── main.cpp
├── mainwindow.cpp
├── mainwindow.h
├── mainwindow.ui
└── README.md
```

