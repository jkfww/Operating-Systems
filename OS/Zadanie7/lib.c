#include "lib.h" //wlasna biblioteka


const char* semProd = "semProd"; //definicja tylko tutaj, dla reszty plikow to jest extern
const char* semCon = "semCon";
const char* memory_name = "memory";


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
    printf("Ending with atexit()\n");

    printf("P");
    s_unlink(semCon);
    
    printf("C");
    s_unlink(semProd);

    mem_unlink(memory_name);
    
}

//DO OBSLUGI CTRL-C
void my_sighandler(int n)
{
    printf("\n\nReceived SIGINT\n\n");
    exitClose();
    _exit(0);
    
}

int mem_open(const char *name, int flags, mode_t mode)
{

    int filedes = shm_open(name, flags, mode);
    if(filedes==-1)
    {
        perror("mem_open error");
        exit(1);
    }

    printf("mem opened\n");

    return filedes;
}

void mem_unlink(const char *name)
{
    if(shm_unlink(name)==-1)
    {
        perror("mem_unlink error");
        exit(1);
    }

    printf("mem unlinked\n");
}

void mem_length(int fd, off_t length)
{
    if(ftruncate(fd,length)==-1)
    {
        perror("mem_length error");
        exit(1);
    }
    printf("mem length set as %i\n", (int)length);
} 

int *mem_map(void *addr, size_t length, int prot, int flags, int fd, off_t offset)
{
    int *a =(int*) mmap(addr, length, prot, flags, fd, offset);
    if(a==MAP_FAILED)
    {
        perror("mem_map error");
        exit(1);
    }

    printf("mem_map success\n");

    return a;
}

void mem_close(void *addr, size_t length)
{
    if(munmap(addr,length)==-1)
    {
        perror("mem_close error");
        exit(1);
    }

    printf("mem closed\n");
}

/*
kiedys zrobic 

char *itostr(int n)
{
    char c = n + '0';
    char string[100] = c;
    return string;  
}
*/