#include "lib.h"

// Segment pamieci dzielonej
typedef struct {
char bufor[NBUF][NELE]; // Wspolny bufor danych
int insert, takeout; // Pozycje wstawiania i wyjmowania z bufora
} Product;

Product prodBufor[BUFF_SIZE]; //bufor na produkt

extern const char* semProd; //nazwy semaforow
extern const char* semCon;

extern char* memory_name;


/* --------------------------- MAIN ---------------------------  */

int main(int argc, char *argv[])
{

    prodBufor[1].bufor[1][1] = 'c';
    if(argc!=5)  
    {
        printf("ERROR %s: invalid number of arguments\n1 - producer program name\n2 - consumer program name\n", argv[0]);
        return 1;
    }

    if(atexit(exitClose)==-1) //rejestrowanie atexit 
    {
        perror("atexit error");
        exit(1);
    }

    if(signal(SIGINT, my_sighandler) == SIG_ERR) //obsluga CTRL-C
    {
        perror("mysighandler error");
        exit(1);
    }


    //przygotowanie programow do execlp
    char prodName[NAMESIZE] = "./";
    char consName[NAMESIZE] = "./";
    strcat(prodName, argv[1]);
    strcat(consName, argv[2]);


    // --- utworzenie semaforow --- 
    printf("\n\n");
    int value = 1; //wartosc przy tworzeniu semafora

    printf("P");
    s_create(semProd, 0644, value); //semafor producenta
    printf("C");
    s_create(semCon, 0644, value); //semafor konsumenta

    //Utworzenie pamieci dzielonej
    printf("\n");
    int filedes = mem_open(memory_name, O_RDWR | O_CREAT | O_EXCL, 0644);
    mem_length(filedes, BUFF_SIZE);

    
    char filedesBuff[NAMESIZE];
    sprintf(filedesBuff, "%d", filedes);
    
    //otworzyc prestrzen adresowa trzeba chyba tutaj
    Product *m_address = (Product *) mem_map(NULL, BUFF_SIZE, PROT_READ | PROT_WRITE | O_EXCL, MAP_SHARED, filedes, 0);

    

    //PRODUCENT
    switch(fork())
    {
        case -1:
            perror("fork error");
            exit(1);
            break;
        case 0:

            if(execlp(prodName, argv[1], argv[3], NULL)==-1)
            {
                perror("execlp error");
                exit(1);
            }
            exit(0);
            break;

        default:
        break;
    }

    //KONSUMENT
    switch(fork())
    {
        case -1:
            perror("fork error");
            exit(1);
            break;
        case 0:
            if(execlp(consName, argv[2],  argv[4], NULL)==-1)
            {
                perror("execlp error");
                exit(1);
            }
            exit(0);
            break;

        default:
        break;
    }

   
    int status = 0;
    while(wait(&status) > 0);

    printf("\n\n");


    mem_close(m_address, BUFF_SIZE);

    close(filedes);

    return 0;

}