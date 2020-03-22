#include <stdio.h> 
#include <stdlib.h> 
#include <semaphore.h> /* sem_open(), sem_destroy(), sem_wait().. */ 
#include <fcntl.h> /* O_CREAT, O_EXEC */ 
#include <sys/types.h> 

void Delta1()
{
	system("echo I am process D1."); 
}

void Delta2() 
{
	system("echo I am process D2."); 
} 

void Delta3() 
{
	system("echo I am process D3."); 
} 

void Delta4() 
{ 
	system("echo I am process D4."); 
} 
void Delta5() 
{
	system("echo I am process D5."); 
}

sem_t *synch12; 
sem_t *synch34;
	
int main() {
	synch12 = sem_open ("Sem1", O_CREAT | O_EXCL, 0644, 0);
	synch34 = sem_open ("Sem2", O_CREAT | O_EXCL, 0644, 0);
	pid_t pid[5];
	int index=0;
	pid_t father=getpid();
	for (index=0; index<5; index++)
	{
		if (father==getpid())
		{
			fork();
			pid[index]=getpid();
		}
	}
	if (getpid()!=father)
	{
		if(getpid()== pid[0])
		{
			Delta1();
			sem_post(synch12);
		}
		else
		{
			if(getpid()== pid[1])
			{
				Delta2();
				sem_post(synch12);
			}
			else
			{
				if(getpid()== pid[2])
				{
					Delta3();
					sem_post(synch34);
				}
				else
				{
					if (getpid()== pid[3])
					{
						sem_wait(synch12);
						sem_wait(synch12);
						Delta4();
						sem_post(synch34);
					}
					else
					{
						if (getpid()== pid[4])
						{
							sem_wait(synch34);
							sem_wait(synch34);
							Delta5();
						}
					}
				}
			}
		}
	}
	sem_unlink ("Sem1");
	sem_close(synch12);
	sem_unlink ("Sem2");
	sem_close(synch34);
	return 0;
}
