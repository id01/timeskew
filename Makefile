default:
		# Run "Make build" to build.
		# Run "Make nogui" to build without GUI.
		# Run "Make install" to install.
		# Run "Make uninstall" to uninstall.

build: override.c main.cpp editor.cpp Makefile
		gcc -shared -fPIC -o libtimeskew.so.0.0.0 override.c -ldl
		g++ -O -o timeskew main.cpp
		g++ -O -std=c++11 -o timeskew-editor editor.cpp `pkg-config gtkmm-3.0 --cflags --libs`
		ln -fs libtimeskew.so.0.0.0 libtimeskew.so

nogui: override.c main.cpp editor_nogui.c Makefile
		gcc -shared -fPIC -o libtimeskew.so.0.0.0 override.c -ldl
		g++ -O -o timeskew main.cpp
		gcc -O -o timeskew-editor editor_nogui.c
		ln -fs libtimeskew.so.0.0.0 libtimeskew.so

install: timeskew timeskew-editor libtimeskew.so.0.0.0
		cp libtimeskew.so.0.0.0 /usr/lib/libtimeskew.so.0.0.0
		cp timeskew /usr/bin/timeskew
		cp timeskew-editor /usr/bin/timeskew-editor
		ln -fs /usr/lib/libtimeskew.so.0.0.0 /usr/bin/libtimeskew.so

uninstall: 
		rm /usr/lib/libtimeskew.so.0.0.0
		rm /usr/bin/timeskew-editor
		rm /usr/bin/libtimeskew.so
		rm /usr/bin/timeskew

.PHONY: build
.PHONY: install
.PHONY: uninstall
.PHONY: nogui
