#include <stdio.h>
#include <stdlib.h>

int _unsetenv(const char *name)
{
    if (unsetenv(name) != 0)
    {
        perror("unsetenv failed!");
        return (1);
    }

    return (0);
}

int main(int argc, char **argv)
{

    if (argc < 2)
    {
        printf("usage: %s name\n", argv[0]);
        return (1);
    }

    _unsetenv(argv[1]);

    printf("env unset : %s\n", getenv(argv[1]));
}