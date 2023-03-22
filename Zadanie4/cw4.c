#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#define RSIZE 4 // liczba bajtow danych czytanych z pliku we
#define WSIZE 4 // liczba bajtow danych czytanych z potoku
#define RANDMAX 5 // liczba max sekund sleep()


int main(int argc, char *argv[])
{

    if(argc<3)
    {
        printf("Niewystarczajaca liczba argumentow\n1 - nazwa pliku wejsciowego\n2 - nazwa pliku wyjsciowego\n");
        return 0;
    }  

    sleep(1);
    if(system("clear")==-1)
    {
        perror("clean error");
        exit(1);
    }

    

    char buff[RSIZE];
    char buff2[WSIZE];

    char *namein = argv[1];
    char *nameout = argv[2];

    printf("Pobieranie danych z pliku %s, zapisywanie do %s\n\n", namein, nameout);
    
    /*--------- otwarcie plikow we i wy --------- */
    int in = open(namein, O_RDONLY);
    if(in==-1)
    {
        perror("input file error");
        exit(EXIT_FAILURE);
    }
    int out = open(nameout, O_WRONLY);
    if(out==-1)
    {
        perror("output file error");
        exit(EXIT_FAILURE);
    }

    
    //rozmiar pliku
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


    int rsize; //liczba bajtow przeczytanych z pliku
    int wsize; //liczba bajtow przeczytanych z potoku
    int filedes[2]; //filedescriptor


    if(pipe(filedes)<0)
    {
        perror("pipe error");
        exit(EXIT_FAILURE);
    }

    int sent = 0; //ilosc bajtow wyslanych do potoku
    int red  = 0; // ilosc bajtow przeslanych do pliku

    switch(fork())
    {
        case -1: /* --------------------------------- CASE -1*/
        perror("fork error");
        exit(EXIT_FAILURE);


        /*PRODUCENT*/

        case 0: /* --------------------------------- CASE 0*/
        close(filedes[0]);
        while(sent<fsize)
        {
            rsize = read(in, buff, RSIZE); // czytaj z pliku
            if(rsize==-1)
            {
                perror("read file error");
                exit(EXIT_FAILURE);

            }

            if(write(filedes[1], buff, rsize)==-1) // do potoku
            {
                perror("write error");
                exit(EXIT_FAILURE);
            }

            printf("\n  - producent ");
            if(write(1, buff, rsize)==-1) // do pliku
            {
                perror("write cout error");
                exit(EXIT_FAILURE);
            }
            printf("\n");


            int r = rand() % RANDMAX; //sleep randomly
            sleep(r);
            sent += rsize;
        }
        close(filedes[1]);
        exit(1);
        break;


        /*KONSUMENT*/

        default: /* --------------------------------- CASE DEFAULT*/
        sleep(1);
        close(filedes[1]);
        
        while(red<fsize)
        {
            wsize = read(filedes[0], buff2, WSIZE); // czytaj z potoku
            if(wsize==-1)
            {
                perror("read error");
                exit(EXIT_FAILURE);

            }

            printf("\n - konsument ");
            if(write(1, buff2, wsize)==-1) // do pliku
            {
                perror("write cout error");
                exit(EXIT_FAILURE);
            }
            printf("\n");
        
            if(write(out, buff2, wsize)==-1) // do pliku
            {
                perror("write file error");
                exit(EXIT_FAILURE);
            }

            int r = rand() % RANDMAX; //sleep randomly
            sleep(r);
            red += wsize;
        }
        close(filedes[0]);
        break;

    }


    close(in);
    close(out);

    printf("\nPobieranie i zapisywanie danych zakonczone.\n\n");
    return 0;
}