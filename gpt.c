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
    ssize_t read;
    size_t n = 0;
    char *buf = NULL;
    char *delim = ":";
    char *path, *token;

    while (1)
    {
        printf("GATES OF SHELL :}  ");
        fflush(stdout);

        read = getline(&buf, &n, stdin);
        if (read == -1)
        {
            printf("\nEOF received, exiting.\n");
            free(buf);
            exit(0);
        }

        // Remove trailing newline
        if (read > 0 && buf[read - 1] == '\n')
            buf[read - 1] = '\0';

        // Duplicate PATH to tokenize safely
        path = strdup(getenv("PATH"));
        if (!path)
        {
            fprintf(stderr, "PATH not found\n");
            continue;
        }

        pid = fork();
        if (pid < 0)
        {
            perror("failed to create a process!");
            free(path);
            free(buf);
            return (-1);
        }

        if (pid == 0) // Child process
        {
            char *full_path;

            token = strtok(path, delim);
            while (token != NULL)
            {
                // Allocate buffer to hold token + "/" + buf + '\0'
                size_t len = strlen(token) + 1 + strlen(buf) + 1;
                full_path = malloc(len);
                if (!full_path)
                {
                    perror("malloc failed!");
                    free(path);
                    free(buf);
                    exit(1);
                }

                // Build the full path string safely
                snprintf(full_path, len, "%s/%s", token, buf);

                if (access(full_path, X_OK) == 0)
                {
                    char *argv[] = {full_path, NULL};
                    execve(full_path, argv, NULL);
                    // If execve returns, there was an error
                    perror("error executing");
                    free(full_path);
                    free(path);
                    free(buf);
                    exit(1);
                }

                free(full_path);
                token = strtok(NULL, delim);
            }

            fprintf(stderr, "%s: command not found\n", buf);
            free(path);
            free(buf);
            exit(127);  // Command not found exit code
        }
        else // Parent process
        {
            wait(&status);
            free(path);
            // Don't free buf here, reuse for next iteration
        }
    }

    free(buf);
    return 0;
}
