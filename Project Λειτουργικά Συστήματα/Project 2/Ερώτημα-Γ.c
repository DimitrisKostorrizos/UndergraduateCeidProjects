#include <stdio.h>
#include <stdlib.h>



int main()
{
	int counter;
	int pid;

	for (counter=0; counter<5; counter++)
	{
		pid = fork();
		if (pid > 0)
		{
			if(counter==0)
			{
				printf(" Id = %i, Child = %i\n", getpid(), pid);
				wait(NULL);
				break;
			}
			else
			{
			printf(" Father = %i, Id = %i, Child = %i\n", getppid(), getpid(), pid);
			wait(NULL);
			break;
			}
		}
	}
	return (0);
}
