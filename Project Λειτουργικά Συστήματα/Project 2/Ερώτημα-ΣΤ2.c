#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <sys/syscall.h>
#include <time.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <semaphore.h>      
#include <fcntl.h>          
#include <errno.h> 
#include <sys/wait.h>

#define K 6

//Αυτο δεν τρεχει αλλα ειναι πιο πιστο στην εκφωνηση.
void concatenate(char *str )
{
  int random_int = rand()%100 +1;
  int finish= random_int*5000;
	write(1, str , 1);
	usleep(finish);
  
}

sem_t *synch;
key_t shmkey;

int main()
{
	synch = sem_open ("Sem1", O_CREAT | O_EXCL, 0644, 1);
    pid_t father=getpid();
    pid_t pid[K];
    srand(time(NULL));
    char word[K] ="Hello";
    int tempint,index=0;
	int position;
    char *p,*h;
    char character;
	int shmid1,shmid2; 
	shmkey = ftok ("/dev/null",K);       
    shmid1 = shmget (shmkey, sizeof (char), 0644 | IPC_CREAT);
	p  = (char *) shmat (shmid1, NULL, 0);
	shmid2 = shmget (shmkey, sizeof (int), 0644 | IPC_CREAT);
	position  = (int) shmat (shmid2, NULL, 0);
    p = (char*)malloc(sizeof(char)*K);
	position=0;
    for(index=0;index<K;index++)
    {
        if (father==getpid())
        {
			fork();
            pid[index]=getpid();
			printf("pid of %d = %d\n",index,pid[index]);
        }
    }

	if (getpid() == father)
	{
		
     
		for(index =0; index<K; index++){
		wait(NULL);}
		
        printf (" Parent: All children have exited.\n");
		printf (" *p = %d\n", *p);
		
        shmdt (p);
        shmctl (shmid1, IPC_RMID, 0);
		shmdt (position);
        shmctl (shmid2, IPC_RMID, 0);

        
        sem_unlink ("Sem1");   
        sem_close(synch);  
    }
	else
	{
	
				sem_wait(synch);//Αν βγαλουμε τους σημαφορους δεν θα βγαινει νοημα στην εξοδο
				tempint=position;				
				character=word[tempint];
				*p=character;
				concatenate(p);
				tempint++;
				position=tempint;
				sem_post(synch);		
			
	
	}
 return 0;
   
}