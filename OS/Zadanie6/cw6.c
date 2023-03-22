#include "lib.h" //wlasna biblioteka


extern const char* semname;

int main(int argc, char *argv[])
{

    if(argc<4) 
    {
        perror("Niewystarczajaca liczba argumentow\n1 - nazwa programu, 2 - liczba procesow, 3 - liczba sekcji krytycznych");
        return 1;
    }

    if(atexit(exitClose)==-1) //rejestrowanie atexit 
    {
        perror("atexit error");
        exit(1);
    }


    if(signal(SIGINT, my_sighandler) == SIG_ERR) //obsluga CTRL-C
    {
        perror( " Blad funkcji signal (my_sighandler) " );
        exit(1);
    }

    
    int max = RANDMAX; //max - maksymalna liczba sekund sleep

    
    int p = atoi(argv[2]); //liczba procesow
    int k = atoi(argv[3]); //liczba sekcji krytycznych
    

    //przygotowanie plikow wykonawczych do uzycia przez execlp
    char execv1[100] = "./";
    strcat(execv1, argv[1]);



    //tworzenie pliku 
    char filename[10] = "numer.txt";
    FILE *plik = fopen(filename, "w");

    if(plik==NULL)
    {
        perror("fopen error");
        exit(1);
    }

    int n=0;
    fprintf(plik, "%i", n); //zapisz do pliku 0

    if(fclose(plik)==EOF)
    {
        perror("fclose error");
        exit(1);
    }

    

    //tworzenie semafora

    printf("\n\n");

    int value = 1; //wartosc przy tworzeniu semafora
    s_create(semname, 0644, value);
    sem_t *address = s_open(semname, O_RDWR); //otworzenie semafora


    //wypisanie adresu i wartosci poczatkowej semafora
    printf("Adres semafora: %p\nWartosc poczatkowa: %i\n\n", (void*)address, s_getvalue(address));

    
    //petla z fork
    char sval[1];
    char *args[3];

    for(int i=0; i<p; i++)
    {
        switch(fork())
        {

            case -1: perror("fork error"); break;

            case 0:

            sval[0] = i+1+'0';
            args[0] = sval;
            args[1] = filename;
            
            //argv[3] to liczba sekcji krytycznych  
            
            randSleep(max);

            if(execlp(execv1, argv[1], args[0], args[1], semname, argv[3],  NULL)==-1)
            /* execlp("./potomny, potomny, 0, numer.txt, semafor, k") */
            {
                perror("execlp error");
                exit(1);
            }

            break;

            default:
            break;


        }
    }


    
    for(int j=0; j<p; j++)
    {
        if(wait(NULL)==-1)
        {
            perror("wait error");
            exit(1);
        }
    }


    sleep(1);
    printf("\n\n\n");
    s_close(address); //zamkniecie semafora


    //Sprawdzenie poprawnosci:

    plik = fopen(filename, "r");
    if(plik==NULL)
    {
        perror("fopen error");
        exit(1);
    }

    fscanf(plik, "%d", &n);

    printf("\nZ pliku odczytano %i\n", n);
    printf("Result: ");
    if(n==(k*p))
    {
        printf("wszystko poszlo dobrze\n");
    }
    else
    {
        printf("cos poszlo nie tak\n");
    }
    
    return 0;
}