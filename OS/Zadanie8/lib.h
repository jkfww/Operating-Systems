#include <stdio.h>
#include <fcntl.h> //mq_open
#include <sys/stat.h> //mq_open
#include <mqueue.h> //mq_open
#include <stdlib.h> //exit
#include <signal.h> //SIGINT
#include <unistd.h> //_exit
#include <string.h> //strcpy
#include <sys/wait.h> //wait
#include <time.h> //time
//#include <stdlib> //srand

#define MSG_LENGTH 50
#define MAX_RAND 5


extern const char *serw_name1;
//Deklaracje funkcji

void randSleep(int max);

mqd_t que_create(const char *name, int oflag, mode_t mode, struct mq_attr *attr);

mqd_t que_open(const char *name, int oflag);

void que_unlink(const char* name);

void que_close(mqd_t mqdes);

void que_getattr(mqd_t mqdes, struct mq_attr *attr);

void que_setattr(mqd_t mqdes, struct mq_attr *newattr, struct mq_attr *oldattr);

void que_send(mqd_t mqdes, const char *msg_ptr, size_t msg_len, unsigned int msg_prio);

void que_receive(mqd_t mqdes, char *msg_ptr, size_t msg_len, unsigned int *msg_prio);

void exitCloseSerw(void);

//void exitCloseClient(void);

void my_sighandler(int n);

int countOperation(char *input, int pos);