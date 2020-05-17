#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int n, i, a, b;
    //Ask for height, repeat if not an integer
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1);
    //Code for printing the bricks
    for (i = 1; i <= n; i++)
    {
        for (b = n - i; b > 0; b = b - 1)
        {
            printf(" ");
            //Prints blank spaces
        }
        for (a = 1; a <= i; a++)
        {
            printf("#");
            //Prints bricks
        }
        printf("\n");
    }
}