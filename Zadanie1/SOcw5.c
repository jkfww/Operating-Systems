#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "biblioteka.h"
#include <string.h>

void wypisz();
int main()
{
    int i; /*iterator*/

    /*Wypisanie ID rodzica*/
    printf("\nParent process:");
    wypisz();
    
   
    for(i=1; i<=3; i++) /*petla fork*/
    {
        
        switch(fork())
        {

        case -1:

            /*Jesli blad*/
            perror( "Blad utworzenia procesu potomnego\n" );
            exit(EXIT_FAILURE);
            
            break;

        case 0:
            
            printf("Child process:");
            
            if(setpgid(0, 0)==-1)
            {
                perror( "setpgid error");
                exit(EXIT_FAILURE);

            } /*ustawienie PGID na taki jak PID == kazdy jest liderem swojej grupy*/
           
            wypisz(); /*wypisanie zmienionych ID potomkow*/

            break;
        

        default:

            if(wait(NULL)==-1) /*poczekaj az sie zakoncza*/
            {
                perror( " Wait error "); /*Jesli blad*/
                exit(EXIT_FAILURE);
            } 

            break;
        }
        
    }

    return 0;

}    