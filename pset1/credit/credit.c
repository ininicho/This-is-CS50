#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>


int main(void)
{
    //Step 1: Get Card Number
    long cardnum;
    do
    {
        cardnum = get_long("Enter Card Number :");
    }
    while (cardnum < 1);
    char card[256];
    sprintf(card, "%ld", cardnum);

    //Step 2: Run Luhn's Algorithm
    int multi_sum = 0;
    int n = 0;
    while (n < strlen(card))
    {
        int multi = (card[n] - '0') * 2;
        int multi_num = multi / 10 + multi % 10;
        multi_sum = multi_sum + multi_num;
        n += 2;
    }

    int not_multi = 0;
    int i = 1;
    while (i < strlen(card))
    {
        not_multi = not_multi + (card[i] - '0');
        i += 2;
    }

    int check = multi_sum + not_multi;

    //Step 3: Output
    if (check % 10 == 0)
    {
        if (card[0] == '3' && (card[1] == '4' || card[1] == '7') && strlen(card) == 15)
        {
            printf("AMEX\n");
        }
        else if (card[0] == '5' && ((card[1] - '0') > 0 || (card[1] - '0') < 6) && strlen(card) == 16)
        {
            printf("MASTERCARD\n");
        }
        else if (card[0] == '4' && (strlen(card) == 13 || strlen(card) == 16))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }

    }
    else
    {
        printf("INVALID\n");
    }
}