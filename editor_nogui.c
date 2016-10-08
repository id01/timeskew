#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define SKEWF 0
#define SKEWD 1

int main(int argc, char *argv[])
{
	int num; int denom; float skewamount;
	if (argc==1) { return 0; }
	int mode=atoi(argv[1]);
	while (true)
	{
		printf("Change Timeskew: _________\033[9D");
		if (mode==SKEWF) { scanf("%f", &skewamount); num=(int)(skewamount*1000); denom=1000; }
		if (mode==SKEWD) { scanf("%i %i", &num, &denom); }
		FILE* tsf=fopen("/tmp/.timeskew","w");
		if (tsf) {
			fprintf(tsf, "%i %i", num, denom);
			fclose(tsf);
		} else { printf("Could not start realtime time editing.\n"); return 2; }
	}
}