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
#include <sys/ipc.h>





int main(int argc, char* argv[])
{
	key_t key = ftok(".",'p');
	int id;
	if(id =  semget(key, 1, IPC_CREAT | 0600)) ==-1)
	 		

}
