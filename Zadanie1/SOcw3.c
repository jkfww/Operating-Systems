#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "biblioteka.h"
#include <string.h>


int main()
{   
    int i; /*iterator*/

    printf("Po zakonczeniu wypisywania identyfikatorów procesów w nowym oknie terminala wpisać polecenie 'pstree -p'\n");

    /*Wypisanie ID rodzica*/
    printf("\nParent process:");
    wypisz();

    int pidr = getpid(); /*Zmienna trzymająca PID procesu rodzica*/

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
            
            /*Wypisanie ID potomkow*/
            printf("Child process %d:\n", i);
            wypisz();

            break;
        
        default:

            break;
        }
        
    }
    
    /*Warunek: uspij tylko dzieci == aktualne PID musi byc rozne od PID rodzica*/
    if(getpid()!=pidr) 
    {
    sleep(100);
    }
    
   return 0; /*Proces rodzic konczy sie najpierw*/

   /*Aby zobaczyc drzewo procesow gdzie systemd przejmuje osierocone dzieci
   nalezy w nowym oknie terminala wpisac polecenie 'pstree -p'*/

}    