#include <cs50.h>
#include <stdio.h>
#include <string.h>

int check(string arg1);
string substitute(string plain, string key);

int main(int argc, string argv[])
{
    //Step 1: Ask user for key
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (strlen(argv[1]) != 26 )
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    //Step 2: Check Key
    int checker = 0; int n = strlen(argv[1]);
    for (int i = 0; i < n; i++)
    {
        if (!((argv[1][i] > 64 && argv[1][i] < 91) || (argv[1][i] > 96 && argv[1][i] < 123)))
        {
            checker++;
            break;
        }
        for (int a = i+1; a < n; a++)
        {
            if (argv[1][i] == argv[1][a])
            {
                checker++;
                break;
            }
        }

    }

    if (checker != 0)
    {
        printf("Wrong key.\n");
        return 1;
    }

    //Step 3: Ask for plain text
    string plain = get_string("plaintext: ");

    //Step 4: Run the substitution function
    string cipher = substitute(plain, argv[1]);

    //Step 5: Output
    printf("ciphertext: %s\n", cipher);
    return 0;
}

string substitute(string plain, string key)
{
    int n = strlen(plain);
    for (int i = 0; i < n; i++)
    {
        //Uppercase letters
        if (plain[i] > 64 && plain[i] < 91)
        {
            int x1 = (int)plain[i] - 65;
            //Case 1: Key Uppercase
            if (key[x1] > 64 && key[x1] < 91)
            {
              plain[i] = key[x1];
            }
            //Case 2: Key Lowercase
            else if (key[x1] > 96 && key[x1] < 123)
            {
                plain[i] = key[x1] - 32;
            }
        }

        //Lowercase letters
        else if (plain[i] > 96 && plain[i] < 123)
        {
            int y1 = (int)plain[i] - 97;
            //Case 1: Key Uppercase
            if (key[y1] > 64 && key[y1] < 91)
            {
               plain[i] = (int)key[y1] + 32;
            }
            else if (key[y1] > 96 && key[y1] < 123)
            {
                plain[i] = key[y1];
            }
        }
    }
    return plain;
}