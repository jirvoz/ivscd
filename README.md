
# IVSCD CALCULATOR
 README for school project of subject "Practical aspects of software design"
 ***
 
 IVSCD Calculator can evaluate expressions with operators **+-*/^**, **brackets** and few basic **functions** like **sin**, **cos**, **tan**, and **natural and common logarithm**.

## Platforms
Ubuntu 64bit


## Authors
**CoreDumped**
 *  *xvozar04* Jiri Vozar
 *  *xlabud05* Dominika Labudova
 *  *xmeryj00* Jozef Mery
 *  *xradse00* Vlastimil Radsetoulal


## License
This program is provided under GNU General Public License v2.0.More in *LICENSE* file.

## Build
Building main application:
```
$ cd src    # cd to source code
$ qmake     # generate makefile
$ make      # compile main application
```
Tests:
```
$ cd src       # cd to source
$ qmake        # generate makefile
$ make tests   # build and run tests
```

## Install
Debian package:
```
$ cd src       # cd to source
$ qmake        # generate makefile
$ make deb     # create debian package
$ dpkg -i ivs_1.0-1.deb	 # install with dpkg
```
Direct installation:
```
$ cd src        # cd to source
$ qmake         # generate makefile
$ make install  # install app (make unistall to remove)
```
================================SLOVAK VERSION================================


# IVSCD CALCULATOR
 README súbor pre projekt z predmetu "Praktické aspekty vývoja software"
 ***
 
 IVSCD Calculator je kalkulačka počítajúca základné matematické funkcie, **výberovú smerodatnú odchýlku**, **faktoriál**,
 **logaritmus**, **prirodzený logaritmus** a **goniometrické funkcie**.

## Prostredie
Ubuntu 64bit


## Autori
**CoreDumped**
 *  *xvozar04* Jiri Vozar
 *  *xlabud05* Dominika Labudova
 *  *xmeryj00* Jozef Mery
 *  *xradse00* Vlastimil Radsetoulal
 

## Licencia
This program is provided under GNU General Public License v2.0.More in *LICENSE* file.

## Kompilácia
Building main application:
```
$ cd src    # cd to source code
$ qmake     # generate makefile
$ make      # compile main application
```
Testy:
```
$ cd src       # cd to source
$ qmake        # generate makefile
$ make tests   # build and run tests
```

## Inštalácia
Debian balíček:
```
$ cd src       # cd to source
$ qmake        # generate makefile
$ make deb     # create debian package
$ dpkg -i ivs_1.0-1.deb	 # install with dpkg
```
Priama inštalácia:
```
$ cd src        # cd to source
$ qmake         # generate makefile
$ make install  # install app (make unistall to remove)
 

