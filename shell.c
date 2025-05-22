#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - Entry point
 *
 * Return: Always 0 (Success)
 */

int main(void)
{
    pid_t pid;
    int status;
    size_t read;

    
    char *delim = ":";
    char *token;
    size_t n = 20;
    char *buf =  malloc(sizeof(char) * n);

    while (1)
    {

        printf("GATES OF SHELL :}  ");
        fflush(stdout);

        read = getline(&buf, &n, stdin);

        if (read > 0 && buf[read - 1] == '\n')
        {
            buf[read - 1] = '\0';
        }

        if (read == -1)
        {
            perror("EOF recieved!");
            exit(0);
        }

        char *path =  strdup(getenv("PATH"));

        if (!path)
        {
            fprintf(stderr, "PATH not found\n");
            continue;
        }

        token = strtok(path, delim);

        pid = fork();

        if (pid < 0)
        {
            perror("failed to create a process!");
            return (-1);
        }

        if (pid == 0)
        {
            

            if (buf == NULL)
            {
                perror("buffer failed!");
            }

            while (token != NULL)
            {
                size_t len = strlen(token);
                char *full_path = malloc(len + 2);  /* // +1 for '/' and +1 for '\0  */

                if (full_path == NULL)
                {
                    perror("malloc failed!");
                    return (-1);
                }

                strcpy(full_path, token);
                strcat(full_path, "/");
                
                if (access(strcat(full_path, buf), X_OK) == 0)
                {
                    char *argv[] = {full_path, NULL};
                    int val = execve(argv[0], argv, NULL);

                    if (val == -1)
                    {
                        perror("error executing!");  
                        break; 
                    }
                }

                free(full_path);
                token = strtok(NULL, delim);


            }

            free(buf);

        }
        else
        {
            wait(&status);
        }

    }

    return (0);

}

