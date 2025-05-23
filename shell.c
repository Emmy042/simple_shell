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
    extern char **environ;
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
            free(buf);
            exit(0);
        }
        
        char *count_args[20];
        int i = 0;
        char *args = strtok(buf, " ");
        while (args && i < 19)
        {
            count_args[i++] = args;
            args = strtok(NULL, " ");
        }
        count_args[i] = NULL;



        char *path =  strdup(getenv("PATH"));

        if (!path)
        {
            fprintf(stderr, "PATH not found\n");
            break;
        }


        pid = fork();

        if (pid < 0)
        {
            perror("failed to create a process!");
            free(path);
            free(buf);
            return (-1);
        }

        if (strcmp(count_args[0], "exit") == 0)
        {
            exit(0);
        }

        if (strcmp(count_args[0], "env") == 0)
        {
            for (int j = 0; environ[j] != NULL; j++)
            {
                printf("%s\n", environ[j]);
            }
            continue;
        }

        if (pid == 0)
        {
            
            token = strtok(path, delim);

            if (buf == NULL)
            {
                perror("buffer failed!");
            }

            while (token != NULL)
            {
                char *full_path = malloc(strlen(token) + strlen(buf) + 2);
  /* // +1 for '/' and +1 for '\0  */

                if (full_path == NULL)
                {
                    perror("malloc failed!");
                    free(path);
                    free(buf);
                    exit(1);
                }

                strcpy(full_path, token);
                strcat(full_path, "/");
                
                if (access(strcat(full_path, count_args[0]), X_OK) == 0)
                {
                    execve(full_path, count_args, NULL);

            
                    perror("error executing!");  
                    free(full_path);
                    free(path);
                    free(buf);
                    exit(1);
                    
                }

                free(full_path);
                token = strtok(NULL, delim);
            }
            
            fprintf(stderr, "%s: command not found :{ \n", buf);
            free(buf);
            free(path);
            exit(127);

        }
        else
        {
            wait(&status);
            free(path);
        }

    }

    free(buf);
    return (0);

}

