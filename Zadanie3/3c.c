#define _POSIX_C_SOURCE 200112L
#define _XOPEN_SOURCE 500
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>



/*----------------------------MAIN----------------------------*/

int main(int argc, char *argv[])
{
    int status;
    int pidc2;
    char *koniec;
    /*konwersja argumentu z string do int*/
    int isignr = strtol(argv[2], & koniec, 0);
    if(isignr<1 || isignr>31)
    {
        perror("Nr sygnalu od 1 do 31");
        exit(EXIT_FAILURE);
    } 

    printf("\n------------3c-------------\n\n");
    
    if(argc<3)
    {
        perror("Niewystarczajaca liczba argumentow");
        exit(EXIT_FAILURE);
    }

    pid_t pidc = fork();
   
    switch (pidc)
    {
    case -1:

    perror( "Blad utworzenia procesu potomnego\n" );
    exit(EXIT_FAILURE);
            
    break;

    case 0:
        /*potomek*/
        printf("PID potomka 'rodzica' to %i\n\n\n", getpid());

        /*Uruchmiany jest program ig.c ktory tworzy procesy potomne*/
        if(execlp("./ig.x", "ig.x", argv[1], argv[2], NULL) == -1)
                    {
                        perror( "Exec failed" );
                        exit(EXIT_FAILURE);
                    }

         
    break;

    default:
    /*macierzysty*/

    sleep(5);

    pidc2 = getpgid(pidc); 

    printf("\n\n\nWysylam do grupy: %i\n\n", pidc2);
   if(killpg(pidc2, 0)==-1) /*Sprawdzenie czy procesy o danym PGID istnieja*/
    {
        perror( "process problem ");
        exit(EXIT_FAILURE);
    }
    
    if(killpg(pidc2, isignr)==-1) /*sygnal jest wysylany do grupy*/
    {
        perror( "kill function error ");
        exit(EXIT_FAILURE);
    }


    if(wait(&status) == -1)
                {
                    perror( "Wait error" ); 
                    exit(EXIT_FAILURE);
                }
    printf("3c wait status = %i\n\n", status);
    

    break;

    }
}
