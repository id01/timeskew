## Timeshift
A program that changes (sometimes) how a program percieves time.

## Installation
Install:
```
(GUI)  
make build  
sudo make install  
  
(no GUI)
make nogui  
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
Gtkmm library used from [here](www.gtkmm.org), under GNU LGPL.  
Directoris.h from [here](https://github.com/id01/my-c-custom-libs), under GNU GPL.  
This project is distributed under the GNU GPLv3.

## Improvements
created editor.cpp  
GTK GUI! Requires gtkmm to build. Edit makefile if you are not using gtkmm-3.0.  
created main.cpp  
Usage: timeskew \[mode\] \[args\] \[command\]  
created editor.c  
Executed on when compiled with nogui, instead of the GTK editor.  
rewritten Makefile  
See above for instructions.  
modified override.c  
Enabled float, moved file to /tmp/.timeskew.