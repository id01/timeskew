libtimeskew.so.0.0.0: override.c main.cpp editor.c Makefile
		gcc -shared -fPIC -o libtimeskew.so.0.0.0 override.c -ldl
		g++ -o timeskew main.cpp
		gcc -o timeskew-editor editor.c
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

.PHONY: install
.PHONY: uninstall