#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{


pid_t pid;


printf("before calling fork!\n");
printf("My pid is %u\n", getpid());

pid = fork();

if (pid == -1)
{
perror("unsuccessful!");
return (-1);
}

if (pid == 0)
{
    
    printf("\n{GATES OF SHELL:} \n");
    sleep(10);

}
else
{

wait(NULL);
printf("am the parent\n");

}


return (0);
}