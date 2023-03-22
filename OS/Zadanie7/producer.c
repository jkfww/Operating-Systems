#include "lib.h"

typedef struct {
char bufor[NBUF][NELE]; // Wspolny bufor danych
int insert, takeout; // Pozycje wstawiania i wyjmowania z bufora
} Product;

extern char* memory_name;
extern const char* semProd; //nazwy semaforow
extern const char* semCon;


int main(int argc, char *argv[])
{
    if(argc!=2)
    {
        printf("\tERROR %s: invalid number of arguments\n", argv[0]);
        exit(1);
    }


    printf("\n\n -- PRODUCER -- \n\n");
    
    int filedes = mem_open(memory_name, O_RDWR | O_EXCL, 0644);

    
    //otworzyc prestrzen adresowa trzeba chyba tutaj
    Product *BP = (Product *) mem_map(NULL, 100, PROT_READ | PROT_WRITE, MAP_SHARED, filedes, 0);
    
    
    printf("P");
    sem_t *addressP = s_open(semProd, O_RDWR | O_EXCL); //otworzenie semafora Producenta

    printf("Semaphore address: %p \nShared memory descriptor: %d\n", (void*)addressP, filedes);


    /*--------- otwarcie pliku we -------------- */

    
    int in = open(argv[1], O_RDWR);
    if(in==-1)
    {
        perror("input file error");
        exit(1);
    }



   /* ----------- rozmiar pliku ------------ */
    struct stat st;
    if(stat(argv[1], &st)==-1)
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

    
   /* ----------- petla czytajaca dane z pliku ------------ */

    int sent = 0;
    int rsize = 0;
    int i = 0;

    printf("\n\n === Starting the work of Producer and Consumer === \n\n");
    
    //sleep(1);

    while(sent<fsize) //dopóki te wysane sa mniejsze niz rozmiar pliku
        {
            s_wait(addressP);

            

            if(i==NBUF)
            {
                i=0; //aby lista była cykliczna
            }

            printf("\nProducer:\nIndex = %i\nS = %i\n", i, s_getvalue(addressP));

            rsize = read(in, BP->bufor[i], RSIZE); // czytaj z pliku

            if(rsize==-1)
            {
                perror("read file error");
                exit(EXIT_FAILURE);

            }
            

            printf(" (%i bytes)", rsize);
            if(write(1, BP->bufor[i], rsize)==-1) // na cout
            {
                perror("write cout error");
                exit(EXIT_FAILURE);
            }
            printf("\n");

            sent = sent + rsize; //ogolnie wysalne powieksz o te wyslane teraz
            i++;  //zwieksz indeks bufora
            BP->insert=sent; //do pamieci dzielonej zapisz liczbe wysalnych ogolnie

            s_post(addressP); 
            printf("S = %i\n", s_getvalue(addressP));
            randSleep(RANDMAX);

        }


        BP->bufor[0][0] = '0'; // daj znac ze zakonczono

        sleep(2);

        printf("P");
        s_close(addressP);

        printf("P");
        mem_close(BP, BUFF_SIZE);

        close(in);

        
    


    exit(0);

}