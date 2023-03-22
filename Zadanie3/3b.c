#define _POSIX_C_SOURCE 200112L
#define _XOPEN_SOURCE 500
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>



/*----------------------------MAIN----------------------------*/

int main(int argc, char *argv[]) /*option, signr*/
{
    
    char *koniec;
    int isignr = strtol(argv[2], & koniec, 0); /*isignr to signr jako int*/
    if(isignr<1 || isignr>31)
    {
        perror("Nr sygnalu od 1 do 31");
        exit(EXIT_FAILURE);
    }

    printf("------------3b-------------\n");
    
    if(argc<3)
    {
        perror("Niewystarczajaca liczba argumentow");
        exit(EXIT_FAILURE);
    }

    printf("PID = %d\n", getpid());

    pid_t pidc = fork();
  
    switch (pidc)
    {
    case-1:

    perror( "Blad utworzenia procesu potomnego\n" );
    exit(EXIT_FAILURE);
            
    break;

    case 0:
    /*potomek*/

    if(execlp("./3a.x", "3a.x", argv[1], argv[2], NULL) == -1)
            {
                perror( "Exec failed" );
                exit(EXIT_FAILURE);
            }
    
    break;

    default:
    /*macierzysty*/

    sleep(1);
    
    
    if(kill(pidc, 0)==-1) /*sprawdzenie czy proces istnieje*/
    {
        perror( "process problem ");
        exit(EXIT_FAILURE);
    }
    
    if(kill(pidc, isignr)==-1) /*wysylany sygnal do niego*/
    {
        perror( "kill function error ");
        exit(EXIT_FAILURE);
    }

    break;

    }
}
