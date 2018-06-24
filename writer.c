/* this program demonstrates Queues*/


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
	char data[200];
	

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



	printf("WRITER: SENDING MESSAGE. \n");
// MESSAGE TO BE SENT
	strcpy(message.text, "HELLO FRIEND");
	message.type=1;


//SENDING MESSAGE
	msgsnd(msid, &message, sizeof(message), 0);
	printf("MESSAGE SENT");


return 0;

}



	



