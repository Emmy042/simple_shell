#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{

char *str = getenv("PATH");
char *delim = ":";
char *token;

token = strtok(str, delim);

while (token != NULL)
{
    printf("%s\n", token);
    token = strtok(NULL, delim); 
    /* the NULL value here states that strtok continue in that 
     * same string 
     */
}

}
