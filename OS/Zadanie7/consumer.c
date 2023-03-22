#include "lib.h"

typedef struct {
char bufor[NBUF][NELE]; // Wspolny bufor danych
int insert, takeout; // Pozycje wstawiania i wyjmowania z bufora
int read;
} Product;


extern char *memory_name;
extern const char* semProd; //nazwy semaforow
extern const char* semCon;



int main(int argc, char *argv[])
{
    if(argc!=2)
    {
        printf("\tERROR %s: invalid number of arguments\n", argv[0]);
        exit(1);
    }

    
    printf("\n\n -- CONSUMER --\n\n");


    int filedes = mem_open(memory_name, O_RDWR | O_EXCL, 0644);
 
    //otworzyc prestrzen adresowa trzeba chyba tutaj
    Product *BC = (Product *) mem_map(NULL, 100, PROT_READ | PROT_WRITE, MAP_SHARED, filedes, 0);
    
    
    printf("P");
    sem_t *addressC = s_open(semCon, O_RDWR | O_EXCL); //otworzenie semafora Producenta

    printf("Semaphore address: %p \nShared memory descriptor: %d\n", (void*)addressC, filedes);

    /*--------- otwarcie pliku wy -------------- */

    fclose(fopen(argv[1], "w")); //clear file before


    int out = open(argv[1], O_WRONLY | O_CREAT, 0644);
    if(out==-1)
    {
        perror("output file error");
        exit(1);
    }


    /* ----------- petla czytajaca dane z pliku ------------ */

    int sent = 0;
    int tosend;
    int i = 0;
    int sending;

    
    sleep(2);

    do
    {
        s_wait(addressC);
        
        if(i==NBUF)
        {
            i=0; //aby lista była cykliczna
        }

        printf("\nConsumer:\nIndex = %i\nS = %i\n", i, s_getvalue(addressC));

        tosend = BC->insert - sent; //ile do wyslania

        if(tosend>RSIZE) //zeby nie wysylac wszystkiego naraz
        {
            sending = RSIZE;
            tosend = tosend - RSIZE;

        }
        else
        {
            sending = tosend;
        }

        if(sending>0)
        {
            if(write(out, BC->bufor[i], sending)==-1)
            {
                perror("write error");
                exit(1);
            }
            i++; //indeks
        }

        //char *text = BC->bufor[i];
        
        //printf("%s (%i bytes)", text, sending);
        printf(" (%i bytes)", sending);
        if(write(1, BC->bufor[i], sending)==-1) // na cout
        {
            perror("write cout error");
            exit(EXIT_FAILURE);
        }
        printf("\n");

        sent = sent + sending; //ogolnie wyslane zwieksz o te teraz wyslane
        
        s_post(addressC); 
        printf("S = %i\n", s_getvalue(addressC));

        randSleep(RANDMAX);
        
    }while(BC->insert>sent || BC->bufor[0][0] != '0'); //zeby zakonczyc petle inser rowny sent i producent wyslac znak ze koniec

    printf(" \n\n=== Ending the work of Producer and Consumer === \n");
    sleep(2);

    printf("C");
    s_close(addressC);

    printf("C");
    mem_close(BC, BUFF_SIZE);
    
    close(out);

    exit(0);
}
