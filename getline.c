#include <stdio.h>
#include <stdlib.h>

int main (void)
{

    size_t n = 20;
    char *buf =  malloc(sizeof(char) * n);
    /* sometime we use NULL as buf value to allow getline allocate 
     * memory dynamically
     * or better still resize the memory size if buf is larger than given size
     */

    printf("enter something :)  ");
    getline(&buf, &n, stdin);

    printf("hello %s", buf);

    free(buf);

}