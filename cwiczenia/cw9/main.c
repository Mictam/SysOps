#include <sys/stat.h>
#include <values.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/times.h>
#include <time.h>
#include <dlfcn.h>
#include <fcntl.h>
#include <unistd.h>
#include <memory.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/errno.h>
#include <errno.h>
#include <ctype.h>
#include <mqueue.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <zconf.h>
#include <sys/sem.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <math.h>
#include <pthread.h>

int global=0;
pthread_mutex_t lock;

void* OneThreadTask(void* argv)
{
	pthread_mutex_lock(&lock);

	pthread_t a = pthread_self();
	global++;
	printf("SID:%ld %d\n",a,global);
	
	pthread_mutex_unlock(&lock);

	return NULL;
}


int main(int argc, char* argv[])
{
   
    int NumOfThreadS = atoi(argv[1]);

    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init has failed\n");
        return 1;
    }
 
    
    pthread_t* ThreadArray = malloc(NumOfThreadS * sizeof(pthread_t));

    for(int i=0;i<NumOfThreadS;i++)
    {
        int* arguments = malloc(sizeof(int));
        *arguments = i;
        pthread_create(&ThreadArray[i], NULL, OneThreadTask,arguments);
    }

    int it=0;
    while(it<NumOfThreadS)
    {
        pthread_join(ThreadArray[it],NULL);
        it++;
    }

    pthread_mutex_destroy(&lock);
   
    return 0;
}
