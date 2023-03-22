#include <stdio.h>
#include <fcntl.h> //bo O_RDONLY
#include <unistd.h> //bo sleep
#include <stdlib.h> //bo exit()
#include <sys/stat.h> //bo rozmiar pliku
#define WSIZE 3 // liczba bajtow danych czytanych z pliku we



int main(int argc, char *argv[]) //potok, nazwa input
{

    if(argc<3)
    {
        perror("producent.c - Brak argumentow wywolania programu");
        exit(1);
    }

    char *potok = argv[1];
    char *nameout = argv[2];


    /*--------- otwarcie pliku we -------------- */
    int out = open(nameout, O_WRONLY);
    if(out==-1)
    {
        perror("output file error");
        exit(1);
    }


    /*--------- otwarcie potoku -------------- */
    int p = open(potok, O_RDWR);
    if(p==-1)
    {
        perror("potok error");
        exit(1);
    }

    int wsize; //liczba bajtow przeczytanych z potoku
    char buff[WSIZE];


    /*KONSUMENT*/

        sleep(1);

        
        do
        {
            wsize = read(p, buff, WSIZE); // czytaj z potoku

            if(wsize==-1)
            {
                perror("read error");
                exit(EXIT_FAILURE);

            }

            if(wsize==0)
            {
                
                close(out);
                close(p);
                return 0;
            }

            printf("\n - konsument ");
            if(write(1, buff, wsize)==-1) // na cout
            {
                perror("write cout error");
                exit(EXIT_FAILURE);
            }
            printf("\n");
        
            if(write(out, buff, wsize)==-1) // do pliku
            {
                perror("write file error");
                exit(EXIT_FAILURE);
            }
            printf("\n");
            sleep(1);


        }while(wsize==WSIZE);

/*NAPRAWIC ZAMYKANIE */

close(out);
close(p);

return 0;
}