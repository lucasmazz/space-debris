# Space Debris

Space Debris is a simple game made with C++ and Qt.

The game basically consists of using a spaceship to clear asteroids that are on their way to your home planet, which could cause a mass extinction.

![Alt text](https://github.com/lucasmazz/space-debris/blob/master/images/space-debris.gif?raw=true)

The speed and the number of asteroids appearing at the same time increases with playing time. 

## Install

### Linux:

First, install the following dependencies:

```
sudo apt install build-essential libgl1-mesa-dev qt5-default qt5-qmake qtmultimedia5-dev libqt5multimediawidgets5 libqt5multimedia5-plugins libqt5multimedia5
```

Then, clone this repository, generate the Makefile and compile the source code: 

```
git clone https://github.com/lucasmazzetto/space-debris.git
cd space-debris
mkdir ./build
cd build
/usr/lib/qt5/bin/qmake -o Makefile ../SpaceDebris.pro
make
```

if the code was successfully compiled, then run the game:

```
./SpaceDebris
```

Good game.

## Credits:

All sprites was downloaded from https://itch.io/ and https://opengameart.org/.

All Sound effects was downloaded from https://freesound.org/.

Background Music was made by Nuclear Ghost (https://nclrghst.bandcamp.com/).
