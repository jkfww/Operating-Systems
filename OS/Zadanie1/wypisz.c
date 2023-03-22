#include <stdio.h>
#include "biblioteka.h"
#include <sys/wait.h>
#include <unistd.h>

void wypisz(void)
{
    printf("\nPID = %d UID = %d GID = %d PPID = %d PGID = %d\n\n", getpid(), getuid(), getgid(), getppid(), getpgrp());
   
}