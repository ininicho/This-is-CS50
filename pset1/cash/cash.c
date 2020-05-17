#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float input;
    int q = 25, d = 10, n = 5, change, total;

    do
    {
        input = get_float("Change :");
        //Gets change
    }
    while (input <= 0);
    change = round(input * 100);
    //Rounds of float to integer
    
    total = (change / q) + ((change % q) / d) + ((change % q) % d) / n + ((change % q) % d) % n;
    //Finds the total amount of coins needed for the change
    printf("%d", total);
}