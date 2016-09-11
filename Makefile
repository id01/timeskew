libtimeskew.so.0.0.0: override.c Makefile
		gcc -shared -fPIC -o libtimeskew.so.0.0.0 override.c -ldl
		g++ -o timeskew main.cpp
		ln -fs libtimeskew.so.0.0.0 libtimeskew.so.0
		ln -fs libtimeskew.so.0.0.0 libtimeskew.so
