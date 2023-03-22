#include "lib.h"


int main(int argc, char *argv[])
{

    srand(time(NULL));
    int max = RANDMAX;
    
    if(argc<1)
    {
        perror("potomny: Niewystarczajaca liczba argumentow");
        exit(1);
    }

    int k = atoi(argv[4]); //liczba sekcji krytycznych

    FILE *plik;

    char number[10];
    int inumber;


    sem_t *address = s_open(argv[3], O_RDWR);
    
    

    for(int i=0; i<k; i++)
    {
        randSleep(max);
        //SEKCJA KRYTYCZNA
        printf("\n--- potomny %s (PID %i) ---\n", argv[1], getpid());
        printf("SEMAFOR = %i\n", s_getvalue(address));

        s_wait(address); 
        
        printf("\t--- poczatek sekcji krytycznej %i---\n", i+1);
        printf("\tSEMAFOR = %i\n", s_getvalue(address));
        
        plik = fopen(argv[2], "r");
        if(plik==NULL)
        {
            perror("fopen error");
            exit(1);
        }

        fscanf(plik, "%d", &inumber);

        fclose(plik);
        printf("\tread %d\n", inumber);
        
    
        inumber++;
        printf("\t++ = %i\n", inumber);

        
        //randSleep(max);


        number[0] = inumber+'0';

        plik = fopen(argv[2], "w");
        if(plik==NULL)
        {
            perror("fopen error");
            exit(1);
        }

        fprintf(plik, number);
        printf("\twrite %s\n", number);

        fclose(plik);

        s_post(address);
        printf("\t--- koniec sekcji krytycznej %i ---\n", i+1);
        printf("SEMAFOR = %i\n", s_getvalue(address));
        sleep(2);

         //KONIEC SEKCJI KRYTYCZNEJ
    }

   
    
    return 0;
}