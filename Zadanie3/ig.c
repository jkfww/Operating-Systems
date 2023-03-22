#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>


int main(int argc, char* argv[])
{

int i;
int status;
char *koniec;
int signr = strtol(argv[2], &koniec, 0);

/*Ustawienie obslugi na IGNORE */
    if(signal(signr, SIG_IGN) == SIG_ERR)
        {
            perror( "ig.c Blad funkcji signal (SIG_IGN) " );
            exit(EXIT_FAILURE);
        }

if(setpgid(0, 0)==-1) /*staje sie liderem grupy procesow z petli*/
    {
    perror( "ig.c setpgid error");
    exit(EXIT_FAILURE);
    }

        for(i=0; i<3; i++)
        {

            switch(fork())
            {
                case -1:

                perror("ig.c fork error");
                exit(EXIT_FAILURE);
                break;

                case 0:

                printf("I'm a child\n");
                /*male potomki*/
                
                printf("PGID to: %i\n", getpgid(0));

                /*uruchamiany jest program z podpunktu 3a*/
                if(execlp("./3a.x", "3a.x", argv[1], argv[2], NULL) == -1)
                    {
                        perror( "ig.c Exec failed" );
                        exit(EXIT_FAILURE);
                    }

                exit(EXIT_SUCCESS);
                break;

                
                default:
                sleep(1);
                break;
            }           
        }
        
for(i=1; i<=3; i++)
{
    if(wait(&status) == -1)
                    {
                        perror( "Wait error" ); 
                        exit(EXIT_FAILURE);
                    }
    printf("wait status %i = %i\n", i, status);
}
}