#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

string caesar_cipher(string plain, int key);

int main(int argc, string argv[])
{
    //Step 1: Ask user for key
    if (argc == 2 && atoi(argv[1]) > 0)
    {
        string plain = get_string("plaintext: ");
        int key = atoi(argv[1]);

        //Step 2: Run Caesar Algorithm
        string cipher = caesar_cipher(plain, key);

        //Step 3: Output
        printf("ciphertext: %s\n", cipher);
        return 0;
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}

string caesar_cipher(string plain, int key)
{
    int n = strlen(plain);
    for (int i = 0; i < n; i++)
    {
        if (plain[i] >= 65 && plain[i] <= 90)
        {
            int x = (((int)plain[i] - 65 + key) % 26) + 65;
            if (x > 90)
            {
                plain[i] = x - 26;
            }
            else
            {
                plain[i] = x;
            }
        }
        else if (plain[i] >= 97 && plain[i] <= 122)
        {
            int x = (((int)plain[i] - 97 + key) % 26) + 97;
            if (x > 122)
            {
                plain[i] = x - 26;
            }
            else
            {
                plain[i] = x;
            }
        }
        else
        {
            ;
        }
    }
    return plain;
}