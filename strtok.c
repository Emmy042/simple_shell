#include <stdio.h>
#include <string.h>

int main(void)
{

char str[] = "coding is hard!!";
char *delim = "-";
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