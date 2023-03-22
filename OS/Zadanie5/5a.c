#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int mk;

void exit1(void)
{
    printf("Zamykanie funkcja atexit\n\n\n");
    close(mk);
    //exit(1);
    //remove?
}

int main(int argc, char *argv[]) //producent.c, kosnument.c, nazwa pliku potoku, plik we, plik wy
{

    if(argc<6)
    {
        printf("Niewystarczajaca liczba argumentow\n1 - nazwa pliku producenta\n2 - nazwa pliku konsumenta\n3 - nazwa potoku\n");
        printf("4 - nazwa pliku wejsciowego\n5 - nazwa pliku wyjsciowego\n");
        return 0;
    }  

    /*przygotowanie plikow wykonawczych do uzycia przez execlp*/
    char execp[100] = "./";
    char execk[100] = "./";
    strcat(execp, argv[1]);
    strcat(execk, argv[2]);
    char *execs[2];
    execs[0] = execp;
    execs[1] = execk;


    int pids[2]; //tablica na pidy potomnych
   
    /* stworzenie potoku FIFO */

    int mk = mkfifo(argv[3], 0644);

    if(mk==-1)
    {
        perror("mkfifo error");
        exit(1);
    }

    int status;

    int i;

    printf("\nRozpoczeto prace Producenta i Konsumenta\n");



    for(i=0;i<2;i++)
    {
        switch(pids[i] = fork())
        {
            case -1:
            perror("fork error");
            exit(1);
            break;

            case 0:
            printf("%i", getpid());
            if(execlp(execs[i], argv[i+1], argv[3], argv[i+4], NULL) == -1)
            {
                perror( "Exec failed" );
                exit(EXIT_FAILURE);
            }
            exit(1);
            break;


            default:
            break;

        }
    }

    //czekanie na potomne o konkretnych pidach
    for(i=0;i<2;i++)
    {
        if(waitpid(pids[i], &status, 0) == -1)
            {
                perror( "Wait error" ); /*Jesli blad funkcji wait*/
                exit(EXIT_FAILURE);
            }
    }

    printf("Zakonczono prace Producenta i Konsumenta\n");
    
    atexit(exit1);

    return 0;

}