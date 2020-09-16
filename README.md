# Bolt [![Build Status][Build Status]][Travis]
#### A simple 2D game engine written in C++ with SDL2
-------
Bolt is designed to be a minimal base for implementing greater functionality then SDL provides on its own, as well as being usable for a wide variety of 2D projects, and utilizes a variation on the typical ECS pattern to provide an easily extensible framework for further implementation and self-modification.

## Compiling
-------
### Requirements
- C\++17 support (Tested on Clang 7 and GCC/G\++ 7)
- cmake 3.12 or greater

### Linux
The simplest compilation is as follows:
```
$ git clone https://github.com/JackVandergriff/Bolt.git
$ cd Bolt
$ cmake .
$ cmake --build .
```
To indicate to cmake to build the C++20 version of the project, run ```export STD_VERSION=20``` before invoking cmake.
This generates a libBolt.so file that can be linked against, and the headers can be copied from the ```src``` folder into a location of your choosing. The SDL2 headers can also be copied from ```extras/SDL2/include``` or installed via your package manager.

### Mac OSX
If SDL2 is not already installed on your system, then run:
```
$ brew install sdl2 sdl2_image sdl2_ttf
```
Then compile as follows, which will work for default homebrew settings:
```
$ git clone https://github.com/JackVandergriff/Bolt.git
$ cd Bolt
$ cp -r /usr/local/Cellar/sdl2/*/lib/* extras/SDL2/lib
$ cp -r /usr/local/Cellar/sdl2_image/*/lib/* extras/SDL2/lib
$ cp -r /usr/local/Cellar/sdl2_ttf/*/lib/* extras/SDL2/lib
$ cmake .
$ cmake --build .
```
The post-compilation process is the same as Linux, except compilation will produce libBolt.dylib instead of libBolt.so.

[Build Status]: https://travis-ci.com/JackVandergriff/Bolt.svg?branch=master
[Travis]: https://travis-ci.com/github/JackVandergriff/Bolt