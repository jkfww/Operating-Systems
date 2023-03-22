#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "biblioteka.h"

int main()
{   
    /*Wypisanie ID procesu-rodzica*/
    printf("\nParent process:");
    wypisz();

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
            wypisz();

            break;
        
        default:

            /*Zaczekaj na procesy potomne*/
            if(wait(NULL) == -1)
            {
                perror( "Wait error" ); /*Jesli blad funkcji wait*/
                exit(EXIT_FAILURE);
            }
            
            break;
        }
        
    }
    
    return 0;
}