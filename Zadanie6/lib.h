#ifndef LIB_H
#define LIB_H
#include <stdio.h>
#include <semaphore.h> //wszystkie funkcje semafora
#include <stdlib.h> //rand()
#include <unistd.h> //sleep()
#include <time.h> //time() in rand
#include <fcntl.h> //O_RDWR
#include <string.h> //stoi
#include <sys/wait.h> //wait
#include <signal.h> //SIGINT

#define RANDMAX 5

extern const char * const sys_siglist[]; /*nazwy sygnalow w tablicy*/

extern const char* semname;

void randSleep(int);

sem_t *s_create(const char *name, mode_t, unsigned int);

sem_t *s_open(const char *name, int);

int s_close(sem_t *sem);

int s_unlink(const char *name);


int s_post(sem_t *sem);

int s_wait(sem_t *sem);

int s_getvalue(sem_t *sem);

void exitClose(void);

void my_sighandler(int);

#endif 