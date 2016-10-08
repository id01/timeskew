// Import required libraries
#include <unistd.h>

// Prototypes
void MF_todirname(char * input, int inputlength);
void MF_uplevel(char * input, int inputlength, int levels);
void MF_getdir(char * input, int inputlength);

// Function to get directory of program.
void MF_getdir(char * input, int inputlength)
{
	readlink("/proc/self/exe", input, inputlength);
	MF_todirname(input, inputlength);
}

// Function to change a file name to the name of the directory containing it.
void MF_todirname(char * input, int inputlength)
{
	int previous=0;
	for (int i=0; i<inputlength; i++)
	{
		if (input[i]== 0 ) { input[previous]=0; return; }
		if (input[i]=='/') { previous=i; }
	}
}

// Function to go up a few levels
void MF_uplevel(char * input, int inputlength, int levels)
{
	for (int i=0; i<levels; i++)
	{
		MF_todirname(input, inputlength);
	}
}