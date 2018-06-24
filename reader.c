#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>



#define WRITER_KEY_PATHNAME "/tmp/mqueue_WRITER_key"
#define PROJECT_ID 90
#define QUEUE_PERMISSIONS 0660


//structure for message queue

struct buffer{
	long type;
	char text[200];
}message;

int main()
{
	key_t key; /*Message queue key*/
	int msid; /* queue id*/
	

/*---- ERROR HANDLING---*/
 // GENERATING UNIQUE KEY FOR QUEUE

	if((key= ftok(WRITER_KEY_PATHNAME, PROJECT_ID)) == -1)
	{ 
		perror("ftok");
		exit(1);
	}

// CREATING A MESSAGE QUEUE 

	if((msid= msgget(key, IPC_CREAT| QUEUE_PERMISSIONS))==-1)
	{
		perror("msgget");
		exit(1);
	}


	printf("RECIEVING MESSAGE. \n");

//RECIEVING MESSAGE
	msgrcv(msid, &message, sizeof(message), 1,0);
	printf("MESSAGE RECIEVED: %s\n",  message.text);


//DESTROY QUEUE
	msgctl(msid, IPC_RMID, NULL);

return 0;

}



	


