#include <stdio.h>
#include <unistd.h>

/**
 * main - PID
 *
 * Return: Always 0.
 */
int main(void)
{
    pid_t my_pid;
    pid_t my_ppid;

    my_ppid = getppid();
    my_pid = getpid();
    printf("%u is the child process\n", my_pid);
    printf("%u is the parent process\n", my_ppid);
    return (0);
}