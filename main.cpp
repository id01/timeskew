#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <libgen.h>
#include <string>
using std::string;
#define SKEWF 0
#define SKEWD 1
#define SHIFT 2

void help()
{
	printf("Usage:\n\n\ttimeskew [mode] [args] [command]\n\nModes:\n\nskewf [decimal]\nskewd [numerator] [denomenator]\nshift [integer]\n");
}

int main(int argc, char *argv[])
{
	short mode;
	string command;
	char pathtoself[100];
	readlink("/proc/self/exe", pathtoself, 100);
	string pathtodir = dirname(pathtoself);
	if (argc==1) { help(); return 1; }
	if (strcmp(argv[1], "skew")==0 || strcmp(argv[1], "skewf")==0 || strcmp(argv[1], "skew=float")==0) { mode=SKEWF; }
	if (strcmp(argv[1], "skewfraction")==0 || strcmp(argv[1], "skewd")==0) { mode=SKEWD; }
	if (strcmp(argv[1], "shift")==0) { mode=SHIFT; }
	if (mode==SKEWF) { if (argc==4) { command="TIMESKEW=\""; command+=argv[2]; command+="\" LD_PRELOAD="; command+=pathtodir; command+="/libtimeskew.so "; command+=argv[3]; system(command.c_str()); } else { help(); return 1; } }
	if (mode==SKEWD) { if (argc==5) { command="TIMESKEW=\""; command+=argv[2]; command+=argv[3]; command+="\" FRACTION=\"1\" LD_PRELOAD="; command+=pathtodir; command+="/libtimeskew.so "; command+=argv[3]; system(command.c_str()); } else { help(); return 1; } }
	if (mode==SHIFT) { if (argc==4) { command="TIMESHIFT=\""; command+=argv[2]; command+="\" LD_PRELOAD="; command+=pathtodir; command+="/libtimeskew.so "; command+=argv[3]; system(command.c_str()); } else { help(); return 1; } }
}