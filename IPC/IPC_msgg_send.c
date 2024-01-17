#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXSIZE 128
void die(char *s)
{
	perror(s);
	exit(1);
}
typedef struct msgbuf
{
	long mtype; /* message type, must be > 0 */
	char mtext[MAXSIZE];
};
void main()
{
	int msqid;
	int msgflg = IPC_CREAT | 0666;
	key_t key;
	struct msgbuf sbuf;
	size_t buflen;
	key = 1234;
	if ((msqid = msgget(key, msgflg )) < 0) //Get the message queue ID for the given key
	die("msgget");
	//Message Type
	sbuf.mtype = 1;
	for(int i = 1; i <= 5; i++)
	{
		printf("Enter a message to add to message queue : ");
		scanf("%[^\n]",sbuf.mtext);
		getchar();
		buflen = strlen(sbuf.mtext) + 5 ;
		if (msgsnd(msqid, &sbuf, buflen, IPC_NOWAIT) < 0)
		{
			printf ("%d, %d, %s, %d\n", msqid, sbuf.mtype, sbuf.mtext, buflen);
			die("msgsnd");
		}
		else
			printf("Message Sent\n");
	}
	exit(0);
}
