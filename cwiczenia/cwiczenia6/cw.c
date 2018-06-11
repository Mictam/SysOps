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


int msgqid, rc;
int done;

struct msg_buf
{
  long mtype;
  char mtext[128];
} msg;

struct msg_buf2
{
  long mtype;
  char mtext[128];
} msg2;


int main(int argc, char* argv[])
{
	
	msgqid = msgget(IPC_PRIVATE, 0600|IPC_CREAT|IPC_EXCL);
  	

  	if(msgqid>-1)printf("message queue created successfully\n");
	else {return 1;}
	
	msg.mtype = 1; 
  	sprintf (msg.mtext, "%s\n", "Witaj swiecie"); 

  	rc = msgsnd(msgqid, &msg, sizeof(msg.mtext), 0); 
  	

	msg.mtype = 1; 
  	sprintf (msg.mtext, "%s\n", "Cala naprzod"); 

  	rc = msgsnd(msgqid, &msg, sizeof(msg.mtext), 0); 
  	
	
	 rc = msgrcv(msgqid, &msg2, sizeof(msg2.mtext), 0, 0); 
	
	  if(rc>-1)printf("received message: %s\n", msg2.mtext);
	else return 1;
	 
 	  rc = msgrcv(msgqid, &msg2, sizeof(msg2.mtext), 0, 0); 
	 
	  if(rc>-1)printf("received message: %s\n", msg.mtext);
	else return 1;
	  
	  rc=msgctl(msgqid,IPC_RMID,NULL);
	  
	  if(rc>-1)printf("message queue %d is closed\n",msgqid);
	else return 1;
	return 0;
}
