#include "lib.h" //wlasna biblioteka


const char* semname = "semafor"; //definicja tylko tutaj, dla reszty plikow to jest extern

//Function to sleep randomly
void randSleep(int max)
{
    int r = rand() % max;
    sleep(r);
}

//CREATE SEMAPHORE
sem_t *s_create(const char *name, mode_t mode, unsigned int value)
{
    sem_t *adress = sem_open(name, O_CREAT | O_EXCL, mode, value);

    if(adress==SEM_FAILED)
    {
        perror("s_create error");
        exit(1);
    }

    printf("sem created\n");
    return adress;
}

//OPEN SEMAPHORE
sem_t *s_open(const char *name, int oflag)

{
    sem_t *adress = sem_open(name, oflag);

    if(adress==SEM_FAILED)
    {
        perror("s_open error");
        exit(1);
    }

    printf("sem opened\n");
    return adress;
}

//CLOSE SEMAPHORE
int s_close(sem_t *sem)
{
    if(sem_close(sem)==-1)
    {
        perror("s_close error");
        exit(1);
    }

    printf("sem closed\n");
    return 0;
}

//UNLINK SEMAPHORE
int s_unlink(const char *name)
{
    if(sem_unlink(name)==-1)
    {
        perror("s_unlink error");
        exit(1);
    }

    printf("sem unlinked\n");
    return 0;
}

//PODNIES SEMAFOR
int s_post(sem_t *sem)
{
    if(sem_post(sem)==-1)
    {
        perror("s_post error");
        exit(1);
    }
    return 0;
}

//OPUSC SEMAFOR
int s_wait(sem_t *sem)
{
    if(sem_wait(sem)==-1)
    {
        perror("s_wait error");
        exit(1);
    }
    return 0;
}

int s_getvalue(sem_t *sem)
{
    int sval;
    if(sem_getvalue(sem, &sval)==-1)
    {
        perror("sem_getvalue error");
        exit(1);
    }
    
    return sval;
}

//FUNKCJA DO KONCZENIA PROGRAMU (atexit)
void exitClose(void)
{
    printf("Konczenie atexit()\n");
    if(s_unlink(semname)==-1)
    {
        perror("s_unlink error");
        exit(1);
    }
    // TU NIE MOZE BYC EXIT(1)
}

//DO OBSLUGI CTRL-C
void my_sighandler(int n)
{
    printf("\n\nOtrzymano SIGINT\n\n");
    exitClose();
    _exit(0);
    
}


/*
START NOTES

Problematyczne semname:

const char* semname = "semafor";    - w pliku z funkcjami .c
extern const char* semname;         - w pliku main, bibliotece i wszystkich innych

prawdopodobnie definicja ma byc tutaj bo funkcje pierwsze tego potrzebuja ??


END NOTES
*/