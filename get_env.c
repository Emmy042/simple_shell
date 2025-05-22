#include <stdio.h>
#include <stdlib.h>

char *_getenv(const char *name);

int main(void)
{

    _getenv("PATH");

   return (0); 
}

char *_getenv(const char *name)
{
    char *path = getenv(name);

    if (path)
    {
        printf("%s\n", path);
    }
    else
    {
        printf("variable not found\n");
    }

    return (0);

}
