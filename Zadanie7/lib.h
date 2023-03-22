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
#include <sys/mman.h> //shm_open
#include <sys/stat.h>  //shm_open
#include <string.h> //itoa 

#define RANDMAX 4
#define BUFF_SIZE 10 //rozmiar bufora
#define NBUF 5 //rozmiar elementu bufora (jednostki towaru) w bajtach ilosc listy
#define NELE 10 //liczba elementow bufora ilosc string
#define NAMESIZE 100
#define RSIZE 10


extern const char * const sys_siglist[]; /*nazwy sygnalow w tablicy*/

extern const char* semProd;
extern const char* semCon;

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

int mem_open(const char *name, int flags, mode_t mode);

void mem_unlink(const char *name);

void mem_length(int fd, off_t length);

int *mem_map(void *addr, size_t length, int prot, int flags, int fd, off_t offset);

void mem_close(void *addr, size_t length);


//char *itostr(int n);

#endif 