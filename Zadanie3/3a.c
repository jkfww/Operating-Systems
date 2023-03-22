#define _POSIX_C_SOURCE 200112L
#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

extern const char * const sys_siglist[]; /*nazwy sygnalow w tablicy*/

int signr;

/*int sygnaly[] = {0, SIGHUP, SIGINT, SIGQUIT, SIGILL, SIGTRAP, 
SIGABRT, SIGBUS, SIGFPE, SIGKILL, SIGUSR1, SIGSEGV, SIGUSR2, 
SIGPIPE, SIGALRM, SIGTERM, SIGCHLD, SIGCONT, SIGSTOP, SIGTSTP,
SIGTTIN, SIGTTOU, SIGURG, SIGXCPU, SIGXFSZ, SIGVTALRM, SIGPROF,
SIGWINCH, SIGIO, SIGPWR, SIGSYS};*/

/*Funkcja do wlasnej oblsugi sygnalu*/
void my_sighandler(int n)
{
    printf("Jestes w my_sighandler\n");
    printf("Nr: %i, nazwa: %s\n", signr, sys_siglist[signr]);
}

/*----------------------------MAIN----------------------------*/
int main(int argc, char *argv[])
{
    printf("--------------3a:-------------\n"); /*zeby orientowac sie w ktorym programie jestesmy*/
    char *koniec;
    if(argc<3)
    {
        perror("Niewystarczajaca liczba argumentow");
        exit(EXIT_FAILURE);
    }

    signr = strtol(argv[2], & koniec, 0); /*signr jako long int*/
    if(signr<1 || signr>31)
    {
        perror("Nr sygnalu od 1 do 31");
        exit(EXIT_FAILURE);
    }
    char *option = argv[1];
    
    
    printf("PID = %i\n\n\n", getpid());

/*      OPCJA IGNORE        */
    if(!strcmp(option, "ignore")) 
    {
        if(signal(signr, SIG_IGN) == SIG_ERR)
        {
            perror( " Blad funkcji signal (SIG_IGN) " );
            exit(EXIT_FAILURE);
        }
    } 

/*      OPCJA DEFAULT        */
    else if(!strcmp(option, "default"))
    {
        if(signal(signr, SIG_DFL) == SIG_ERR)
            {
                perror( " Blad funkcji signal (SIG_DFL) " );
                exit(EXIT_FAILURE);
            }
    }

/*      OPCJA MYSIGHANDLER        */
    else if(!strcmp(option, "mysighandler"))
    { 
        if(signal(signr, my_sighandler) == SIG_ERR)
            {
                perror( " Blad funkcji signal (my_sighandler) " );
                exit(EXIT_FAILURE);
            }
    }

/*      NIEPRAWIDLOWA OPCJA        */
    else
    {
        perror( "Nieprawidlowa opcja\n");
        exit(EXIT_FAILURE);
    }


    pause(); /* czekaj na sygnal */
    
    printf("\n\n");
    return 0;
}

