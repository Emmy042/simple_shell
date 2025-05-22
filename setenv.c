#include <stdio.h>
#include <stdlib.h>

int _setenv(const char *name, const char *value, int overwrite)
{
    if (setenv(name, value, 0) != 0)
    {
        perror("setenv failed!!");
        return (1);

    }
return (0);
}

int main(int argc, char **argv)
{

    if (argc < 4)
    {
        printf("usage:  %s value 1/0 (0 for nothing and 1 or overwrite) ", argv[0]);
        return (1);
    }

    _setenv(argv[1], argv[2], atoi(argv[3]));

    printf("value : %s\n",getenv(argv[1]));



}