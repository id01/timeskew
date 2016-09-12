## Timeshift
A program that changes (sometimes) how a program percieves time.

## Installation
Install:
```
make  
sudo make install
```
Uninstall:
```
sudo make uninstall
```

## Project
Credit for original project goes to [vi](https://github.com/vi).  
This includes override.c and some of makefile  
Original project can be found [here](https://github.com/vi/timeshift), under the MIT license.  
Modifications made by id01.  
This project is distributed under the GNU GPLv3.

## Improvements
created main.cpp  
Usage: timeskew \[mode\] \[args\] \[command\]  
created editor.c  
Executed on xterm when in GUI mode. Will upgrade to GTK soon.  
modified Makefile  
Enabled "make install" and "make uninstall"  
modified override.c  
Enabled float, moved file to /tmp/.timeskew.