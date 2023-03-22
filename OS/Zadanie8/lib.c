#include "lib.h"
/*Plik zawierajacy funkcje do obslugi kolejki komunikatow*/

const char *serw_name1 = "/SerwerQueue11";

void randSleep(int max)
{
    int r = rand() % max;
    sleep(r);
}

mqd_t que_create(const char *name, int oflag, mode_t mode, struct mq_attr *attr)
{
    mqd_t des = mq_open(name, oflag, mode, attr);
    if(des==-1)
    {
        perror("que_create error");
        exit(1);
    }
    printf("'%s' Queue created\n", name);
    return des;
}


mqd_t que_open(const char *name, int oflag)
{
    mqd_t des = mq_open(name, oflag);
    if(des==-1)
    {
        perror("que_open error");
        exit(1);
    }
    printf("'%s' Queue opened\n", name);
    return des;
}

void que_unlink(const char* name)
{
    if(mq_unlink(name)==-1)
    {
        perror("mq_unlink error");
        exit(1);
    }
    printf("'%s' Queue unlinked\n", name);
    return;
}

void que_close(mqd_t mqdes)
{
    if(mq_close(mqdes)==-1)
    {
        perror("que_close error");
        exit(1);
    }
    printf("Queue closed\n");
    return;
}

void que_getattr(mqd_t mqdes, struct mq_attr *attr)
{
    if(mq_getattr(mqdes, attr)==-1)
    {
        perror("que_getattr error");
        exit(1);
    }
    return;
}

void que_setattr(mqd_t mqdes, struct mq_attr *newattr, struct mq_attr *oldattr)
{
    if(mq_setattr(mqdes, newattr, oldattr)==-1)
    {
        perror("que_setattr error");
        exit(1);
    }
    printf("que_setattr successed\n");
    return;
}

void que_send(mqd_t mqdes, const char *msg_ptr, size_t msg_len, unsigned int msg_prio)
{
    if(mq_send(mqdes,msg_ptr, msg_len, msg_prio)==-1)
    {
        perror("que_send error");
        exit(1);
    }
    printf("message sent ->\n");
    return;
}

void que_receive(mqd_t mqdes, char *msg_ptr, size_t msg_len, unsigned int *msg_prio)
{
    if(mq_receive(mqdes, msg_ptr, msg_len, msg_prio)==-1)
    {
        perror("que_receive error");
        exit(1);
    }
    printf("received: ");
    return;
}

void exitCloseSerw(void)
{
    printf("Ending with atexit()\n");

    que_unlink(serw_name1);
    
}

//DO OBSLUGI CTRL-C
void my_sighandler(int n)
{
    printf("\n\nReceived SIGINT\n\n");
    exitCloseSerw();
    _exit(0);
    
}

int countOperation(char *input, int pos)
{
    int i=pos;
    int n =0;
    //char num1[10], num2[10];
    while(input[pos]!='+' && input[pos]!='-' && input[pos]!='*' && input[pos]!='/' && input[pos]!='\0')
    {
        pos++;
        n++;
    }
    
    char num1[n];
    strncpy(num1, input+i, n);
    num1[n] = '\0'; //zero added manually
    n=0;
    
    char op = input[pos];
    if(op=='\0')
    {
        return atoi(num1);
    }
    pos++;
    i=pos;
    
    while(input[pos]!='\0')
    {
        pos++;
        n++;
    }
    
    char num2[n];
    strncpy(num2, input+i, n);
    num2[n] = '\0'; //zero added manually
    int result;
    switch(op)
    {
        case '-':
            result = atoi(num1)-atoi(num2);
            break;

        case '+':
            result = atoi(num1)+atoi(num2);
            break;

        case '*':
            result = atoi(num1)*atoi(num2);
            break;
        
        case '/':
            result = atoi(num1)/atoi(num2);
        break;

        default:
        printf("Undefined\n");
        exit(0);

    }

    return result;


}