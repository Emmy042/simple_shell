#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/**
 * main - stat example
 *
 * Return: Always 0.
 */
int main(int ac, char **av)
{
    char *path =  getenv("PATH");
    char *delim = ":";
    char *token;

    token = strtok(path, delim);

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

    if (access(strcat(full_path, av[1]), X_OK) == 0)
    {
        printf("%s\n", full_path);
        break;

    }
    
    free(full_path);

    token = strtok(NULL, delim);
    

}

    return (0);
}