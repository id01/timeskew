#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "directories.h"
#include <string>
using std::string;
#define SKEWF 0
#define SKEWD 1
#define SHIFT 2

void help()
{
	printf("Usage:\n\n\ttimeskew [mode] [args] [command]\n\nModes:\n\nGUI:\nskewf [decimal]\nskewd [numerator] [denomenator]\nshift [integer]\n");
	printf("\nTERMINAL:\ntskewf [decimal]\ntskewd [numerator] [denominator]\n");
}

int main(int argc, char *argv[])
{
	system("rm /tmp/.timeskew");
	char mode;
	bool nogui=false;
	string command;
	string args;
	char pathtoself[128];
	MF_getdir(pathtoself, 128);
	string pathtodir = pathtoself;
	if (argc==1) { help(); return 1; }
	if (strcmp(argv[1], "skewf")==0) { mode=SKEWF; }
	if (strcmp(argv[1], "skewd")==0) { mode=SKEWD; }
	if (strcmp(argv[1], "shift")==0) { mode=SHIFT; }
	if (strcmp(argv[1], "tskewf")==0) { mode=SKEWF; nogui=true; }
	if (strcmp(argv[1], "tskewd")==0) { mode=SKEWD; nogui=true; }
	if (mode==SKEWF) { if (argc>=4) {
		for (int i=4; i<argc; i++) { args+=" "; args+=argv[i]; }
		command="TIMESKEW=\""; command+=argv[2]; command+="\" LD_PRELOAD="; command+=pathtodir; command+="/libtimeskew.so "; command+=argv[3]; command+=args; command+=" &"; system(command.c_str()); }
		else { help(); return 1; } }
	if (mode==SKEWD) { if (argc>=5) {
		for (int i=5; i<argc; i++) { args+=" "; args+=argv[i]; }
		command="TIMESKEW=\""; command+=argv[2]; command+=" "; command+=argv[3]; command+="\" FRACTION=\"1\" LD_PRELOAD="; command+=pathtodir; command+="/libtimeskew.so "; command+=argv[4]; command+=args; command+=" &"; system(command.c_str()); }
		else { help(); return 1; } }
	if (mode==SHIFT) { if (argc>=4) {
		for (int i=4; i<argc; i++) { args+=" "; args+=argv[i]; }
		command="TIMESHIFT=\""; command+=argv[2]; command+="\" LD_PRELOAD="; command+=pathtodir; command+="/libtimeskew.so "; command+=argv[3]; command+=args; command+=" &"; system(command.c_str()); }
		else { help(); return 1; } }
	if (nogui==true || mode==SHIFT) { return 0; }
	command=pathtodir; command+="/timeskew-editor ";
	if (mode==SKEWF) { command+="0"; }
	if (mode==SKEWD) { command+="1"; }
	usleep(50000);
	if (system(command.c_str())==2) { printf("Could not start realtime time editing.\n"); }
}