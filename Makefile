libtimeskew.so.0.0.0: override.c main.cpp Makefile
		gcc -shared -fPIC -o libtimeskew.so.0.0.0 override.c -ldl
		g++ -o timeskew main.cpp
		ln -fs libtimeskew.so.0.0.0 libtimeskew.so.0
		ln -fs libtimeskew.so.0.0.0 libtimeskew.so

install: timeskew libtimeskew.so.0.0.0
		cp libtimeskew.so.0.0.0 /usr/lib/libtimeskew.so.0.0.0
		cp timeskew /usr/bin/timeskew
		ln -fs /usr/lib/libtimeskew.so.0.0.0 /usr/bin/libtimeskew.so

.PHONY: install