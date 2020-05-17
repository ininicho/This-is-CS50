#include <stdio.h>

int main(void)
{
    char name;
    
    printf("What's your name?\n");
    scanf("%s", &name);
    //Gets name and stores in a variable called name
    printf("hello, %s\n", &name);
}