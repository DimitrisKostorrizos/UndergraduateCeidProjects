#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // For open, close, read, write, fsync
#include <sys/syscall.h>
#include <time.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <semaphore.h>      /* sem_open(), sem_destroy(), sem_wait().. */
#include <fcntl.h>          /* O_CREAT, O_EXEC*/
#define N 5

void concatenate(char *str , int n)
{
  int counter;
  int random_int = rand()%10 +1;
  int finish= random_int*50000;
  for(counter=0; counter<n; counter++ )
  {
	write(1, (str+counter) , 1);
	usleep(finish);
  }
}

sem_t *synch;
key_t shmkey;

int main()
{
	synch = sem_open ("Sem1", O_CREAT | O_EXCL, 0644, 1);
    pid_t father=getpid();
    pid_t pid[10];
    srand(time(NULL));
    char word[N] ="hello";
    int index,position=0;
    char *p;
    char c;
	int shmid; 
	shmkey = ftok ("/dev/null", 5);       
    shmid = shmget (shmkey, sizeof (char), 0644 | IPC_CREAT);
	p  = (char *) shmat (shmid, NULL, 0);
	shmid = shmget (shmkey, sizeof (int), 0644 | IPC_CREAT);
	position  = (int ) shmat (shmid, NULL, 0);
    p = (char*)malloc(sizeof(char)*10);
    for(index=0;index<10;index++)
    {
        if (father==getpid())
        {
            fork();
			int random_pos=rand()%5;
            pid[index]=getpid();
            c=word[random_pos];
			sem_wait(synch);
            p[position]=c;
            position++;
			sem_post(synch);
        }
        
    }
    wait(NULL);
    if(father==getpid())
	{
		concatenate(p,strlen(p));
		printf("\n");
	}
	sem_unlink ("Sem1");
	sem_close(synch);
    return 0;
}