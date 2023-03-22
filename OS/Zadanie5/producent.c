#include <stdio.h>
#include <fcntl.h> //bo O_RDONLY
#include <unistd.h> //bo sleep
#include <stdlib.h> //bo exit()
#include <sys/stat.h> //bo rozmiar pliku
#define RSIZE 3 // liczba bajtow danych czytanych z pliku we



int main(int argc, char *argv[]) //potok, nazwa input
{

    if(argc<3)
    {
        perror("producent.c - Brak argumentow wywolania programu");
        exit(1);
    }

    char *potok = argv[1];
    char *namein = argv[2];

    /*--------- otwarcie pliku we -------------- */

    
    int in = open(namein, O_RDONLY);
    if(in==-1)
    {
        perror("input file error");
        exit(1);
    }

    /* ----------- rozmiar pliku ------------ */
    struct stat st;
    if(stat(namein, &st)==-1)
    {
        perror("stat function error");
        exit(2);
    }
    int fsize = st.st_size;
    if(fsize==0)
    {
        perror("input file empty");
        return 0;
    }

    /*--------- otwarcie potoku -------------- */
    int p = open(potok, O_RDWR);
    if(p==-1)
    {
        perror("potok error");
        exit(1);
    }

    int rsize; //liczba bajtow przeczytanych z pliku
    int sent = 0; //ilosc bajtow wyslanych do potoku
    char buff[RSIZE];


    /*PRODUCENT*/

        
        while(sent<fsize)
        {
            rsize = read(in, buff, RSIZE); // czytaj z pliku
            if(rsize==-1)
            {
                perror("read file error");
                exit(EXIT_FAILURE);

            }

            if(write(p, buff, rsize)==-1) // do potoku
            {
                perror("write error");
                exit(EXIT_FAILURE);
            }

            printf("\n  - producent ");
            if(write(1, buff, rsize)==-1) // na cout
            {
                perror("write cout error");
                exit(EXIT_FAILURE);
            }
            printf("\n");
            sent = sent + rsize;
            sleep(1);

        }

        close(in);
        close(p);

return 0;
}