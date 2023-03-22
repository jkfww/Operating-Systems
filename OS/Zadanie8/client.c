#include "lib.h"

struct mq_attr attr;

int main(int argc, char *argv[])//argv1 = client name
{

    sleep(1);
    srand(time(NULL));
    char clientName[50];
    sprintf(clientName, "/%i", getpid());

    //Obsluga CTRL-C
    if(signal(SIGINT, my_sighandler) == SIG_ERR) 
    {
        perror("my_sighandler error");
        exit(1);
    }

    //potrzebne zeby dzialalo 
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MSG_LENGTH;
    attr.mq_curmsgs = 0;

    printf("\n------ CLIENT ------\n");
    
    //Tworzenie kolejki klienta
    mqd_t cdes = que_create(clientName, O_CREAT | O_RDONLY | O_EXCL, 0777, &attr);

    //otwieranie kolejki klienta
    que_open(clientName, O_RDONLY);
    printf("CLIENT Queue descriptor =  %i\n", cdes);
    que_getattr(cdes, &attr);

    printf("Maximum # of messages on queue:   %ld\n", attr.mq_maxmsg);
    printf("Maximum message size:             %ld\n", attr.mq_msgsize);

    //otwieranie kolejki serwera
    mqd_t sdes = que_open(serw_name1, O_RDWR);
    
    char input[MSG_LENGTH];
    char sresult[MSG_LENGTH];
    unsigned int prio[2] = {1, 2};
    char nameCopy[100];
    printf("\nCLIENT input: \n");
    while(fgets(input, MSG_LENGTH, stdin)!=NULL)
    {
    
        strcpy(nameCopy, clientName);
        strcat(nameCopy, " ");
        strcat(nameCopy, input);

        //wyslanie dzialania
        que_send(sdes, nameCopy, MSG_LENGTH, prio[0]);
        memset(nameCopy, 0, MSG_LENGTH);

        //odebranie wyniku
        randSleep(MAX_RAND);
        printf("CLIENT ");
        que_receive(cdes, sresult, MSG_LENGTH, prio);
        printf("%s\n", sresult);
        memset(input, 0, MSG_LENGTH);
        printf("\nCLIENT input: \n");

    }

    printf("CLIENT no. %i ended work\n", getpid());





    que_close(cdes);

    que_unlink(clientName);

return 0;
}
