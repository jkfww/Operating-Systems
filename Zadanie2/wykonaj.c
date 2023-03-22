#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main() 
{
    printf("\nPID = %d UID = %d GID = %d PPID = %d PGID = %d\n\n", getpid(), getuid(), getgid(), getppid(), getpgrp());

    
}