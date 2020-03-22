#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N  10000

int nothing()
{
	int x=0;
	return x+1;
}


int main()
{
	float dif;
	int counter=0;
	int index=0;
	time_t start,end;
	time(&start);
	int father=getpid();
	int pid[N];
	printf("Arxikh timh deuterolepton %ld seconds.\n", start);
	while(counter<=N && father==getpid())
	{
		pid[counter]= fork();
		counter++;
		
	}
	if(father==getpid())
	{
		for (index=0; index<=N; index++)
		{
			waitpid(pid[index]);
		}
	}	
	nothing();
	time(&end);
	if(father==getpid())
	{
		printf("Teliki timh deuterolepton %ld seconds.\n",end);
		dif=end-start;
		printf("DIARKEIA %f seconds.\n", dif);
		printf("MESOS XRONOS %f seconds.\n", dif/N);
	}
	return 0;
}