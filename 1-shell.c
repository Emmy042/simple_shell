#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h> 


int main (void)
{

pid_t pid;
size_t n = 0;
size_t read;
char *buf ;
char *argv[2];
int status;

   
   while (1)
   {

     printf("{GATES OF SHELL:} ");
            fflush(stdout);

            read = getline(&buf, &n, stdin);
            if (read < 0)
            {
                printf("\n");
                break;
            }

            if (buf[read -1] == '\n')
            {
                buf[read -1] = '\0';
            }

            pid = fork();
            if (pid < 0)
            {
                perror("failed!");
                return (-1);
            }

            if (pid == 0)
            {
                argv[0] = buf;
                argv[1] = NULL;

                if (execve(buf, argv, NULL) == -1)
                {
                    perror("execve failed");
				    return (-1);
                }

            }

            else
            {
                wait(&status);        
            }
   }

free(buf);
return (0);

}

