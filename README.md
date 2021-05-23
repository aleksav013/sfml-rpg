# sfml-rpg
Simple C++ SFML school project.
## Compiling
### Linux
- Install sfml package from your package manager:
	- [**libsfml-dev**](https://packages.debian.org/buster/libsfml-dev) for Debian based distributions
	- [**sfml**](https://archlinux.org/packages/community/x86_64/sfml/) for Arch based distributions
```
g++ -std=c++14 -O2 -o sfml-rpg main.cpp -lsmfl-graphics -lsfml-window -lsfml-system
```
	
### Windows
- Download [latest stable version](https://www.sfml-dev.org/download.php) of SFML
- Install [mingw-w64](http://mingw-w64.org/doku.php/download/mingw-builds)
- Add mingw64\bin to $PATH
```
g++ -std=c++14 -O2 -o sfml-rpg main.cpp -I SFML-2.5.1\include -L SFML-2.5.1\lib -lsfml-graphics -lsfml-window -lsfml-system
```
> If you use Visual Studio or Code::Blocks you can follow [official tutorial](https://www.sfml-dev.org/tutorials) for setting up SFML.
## Requirements
- SFML 2.5+ version
