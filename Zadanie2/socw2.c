#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char *argv[])
{   

    if(argc<2)
    {
        perror( "Brak argumentu. Zakoncz program ");
        exit(1);
    }
 /*Wypisanie ID procesu-rodzica*/
    printf("\nParent process:");

    printf("\nPID = %d UID = %d GID = %d PPID = %d PGID = %d\n\n", getpid(), getuid(), getgid(), getppid(), getpgrp());
  
    /*jako ułatwienie przy wykonywaniu funkcji exec zmienne nazwa i nazwax*/
   const char *nazwa = strdup(argv[1]);
   char nazwax[100] = "./"; 
   strcat(nazwax, nazwa);
  
   


    for(int i=1; i<=3; i++) /*Petla z wywolaniami funkcji fork*/
    {
        switch(fork())
        {

        case -1:

            /*Jesli blad zamknij program*/
            perror( "Blad utworzenia procesu potomnego\n" );
            exit(EXIT_FAILURE);
            
            break;

        case 0:

            /*Wypisanie ID procesow-dzieci*/
            printf("Child process:");
            if(execlp(nazwax, nazwa, NULL) == -1)
            {
                perror( "Exec failed" );
                exit(EXIT_FAILURE);
            }
            

            break;
        
        default:

            /*Zaczekaj na procesy potomne*/
            if(wait(NULL) == -1)
            {
                perror( "Wait error" ); /*Jesli blad funkcji wait*/
                exit(EXIT_FAILURE);
            }
           /* printf("Parent process2\n");*/
            
            break;
        }
        
    }

   

    return 0;
}