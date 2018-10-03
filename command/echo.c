#include "stdio.h"

int main(int argc, char * argv[])
{
	int i=1;

	int argc_con=argc;//??????????
	char** argv_con=argv;

	for(i;i<argc_con;i++){
		printf("i:%s\n",argv_con[i]);
	}

	return 123;
}