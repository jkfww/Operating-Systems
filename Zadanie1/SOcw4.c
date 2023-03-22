#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "biblioteka.h"
#include <string.h>

int main()
{   

    printf("\nParent process:");

    wypisz();

    for(int i=1; i<=3; i++)
    {
        
        switch(fork())
        {
            
        case -1:

            perror( "Blad utworzenia procesu potomnego\n" );
            exit(EXIT_FAILURE);
            
            break;

        case 0:
            
            wypisz();
            
            break;
        

        default:

            sleep(5);

            break;
        }

    }
   
    return 0;
}