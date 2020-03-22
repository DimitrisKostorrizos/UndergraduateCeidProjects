#include<stdio.h> 
  
int main() 
{ 
	int counter;
        for(counter=0;counter<4;counter++)
        { 
        	if(fork() == 0) 
        	{ 
            		printf("[child] process id %d from [parent] process id %d\n",getpid(),getppid()); 
            		exit(0); 
        	}	 
    	} 
	return 0;
}
