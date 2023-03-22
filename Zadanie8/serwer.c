#include "lib.h"

struct mq_attr attr;

int main(int argc, char *argv[])//argv1 = client name
{

    srand(time(NULL));

    //Obsluga CTRL-C
    if(signal(SIGINT, my_sighandler) == SIG_ERR) 
    {
        perror("my_sighandler error");
        exit(1);
    }

    //atexit
    if(atexit(exitCloseSerw)==-1)
    {
        perror("atexit error");
        exit(1);
    }

    //potrzebne zeby dzialalo 
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MSG_LENGTH;
    attr.mq_curmsgs = 0;


    printf("\n------ SERWER ------\n");
    //Tworzenie kolejki serwera
    mqd_t des = que_create(serw_name1, O_CREAT | O_RDONLY | O_EXCL, 0777, &attr);
    char strdes[100];
    sprintf(strdes, "%d", des);
    printf("SERWER Queue descriptor =  %s\n", strdes);
    
    

    //otwieranie kolejki serwera
    que_open(serw_name1, O_RDONLY);

    que_getattr(des, &attr);

    printf("Maximum # of messages on queue:   %ld\n", attr.mq_maxmsg);
    printf("Maximum message size:             %ld\n", attr.mq_msgsize);

    char input[MSG_LENGTH];
    char output[MSG_LENGTH];
    unsigned int prio[2] = {1, 2};
    while(1)
    {
        //czekaj na dzialanie
        printf("SERWER ");
        randSleep(MAX_RAND);
        que_receive(des, input, MSG_LENGTH, prio);
        printf("%s", input);

        //odczytaj pid
        char pid[10];
        int i;
        for(i=0; input[i]!=' '; i++)
        {
            i++;
        }
        strncpy(pid, input, i);

        //policz dzialanie
        int result = countOperation(input, i+1);

        printf("SERWER result: %i\n", result);

        

        sprintf(output, "%i", result);

        mqd_t cdes = que_open(pid, O_WRONLY);

        que_send(cdes, output, MSG_LENGTH, prio[0]);

        que_close(cdes);

        printf("\n\n");

    }


    if(wait(NULL)==-1)
    {
        perror("wait error");
        exit(1);
    }

    //zamykanie kolejki
    que_close(des);

    return 0;
}