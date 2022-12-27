# sfml-tower-defense
## Table of Contents
  * [Overview](#Overview)
  * [How To Make a Build](#How-To-Make-a-Build)
 
## Overview
This is the trunk of a 2D top down tower defense game developed in C++ and using SFML as graphics library.
This project is developed and tested with Ubuntu 22.04.1 LTS. In order to compile and run the project in Windows, you will need to modify the CMakeList file to correctly reference project dependencies.
***

## How To Make a Build
Please note the following steps assumes all the necessary libraries and tools required to compile C++ programs has been installed n your local machine.
### I. Install CMake
This project uses cmake to generate C++ makefile. Use the following command to install cmake:
```
sudo apt-get -y install cmake
```

### II. Install boost
This project uses multiple packages from the boost library. Note the following command will install the entire boost library for you.
```
sudo apt-get install libboost-all-dev
```

### III. Install rapidJson
This project uses rapidJson for in-game data serialization & deserialization. Use the following command to install rapidJson:
```
sudo apt-get install -y rapidjson-dev
```

### IV. Install SFML
This project uses SFML as its multimedia library. Use the following command to install SFML:
```
sudo apt-get install libsfml-dev
```

### V. Build and install LDtk Loader
This project uses LdtkLoader to load LDtk tile maps into game. First, you need to run git-checkout to obtain a local copy of the project from github: https://github.com/Madour/LDtkLoader. Next, go into the root directory of your local copy of the project, run the following command to build the project on your local machine:
```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release
```
Next, from the build directory, run the following command to install it:
```
cmake [-DCMAKE_INSTALL_PREFIX=/install/path/LDtkLoader] ..
sudo cmake --install . --config Release
```

### VI. Make Build
Now you should have installed all the dependencies of the project, and it is time to make a build! First you need to generate makefile with cmake:
```
cmake .
```
Now you can build the game with the generated makefile:
```
make install
```
This command will create a new folder in your project directory called 'install', which will contain the game executable and all the assets it requires.  

