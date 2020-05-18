// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 17576;

// Hash table
node *table[N];

//Global Dictionary Counter
int dict_counter = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Change word to lower case
    int i = strlen(word);
    char *dummy = malloc(sizeof(char) * i);
    strcpy(dummy, word);

    char *lower_word = malloc(sizeof(char) * i);

    for (int n = 0; n < i; n++)
    {
        if (dummy[n] > 64 && dummy[n] < 91)
        {
            lower_word[n] = dummy[n] + 32;
        }
        else
        {
            lower_word[n] = dummy[n];
        }
    }

    // Run hash function to word
    int num = hash(lower_word);

    // Check if word is on hash table
    for (node *tmp = table[num]; tmp != NULL; tmp = tmp->next)
    {
        if (strcmp(tmp->word, lower_word) == 0)
        {
            return true;
            break;
        }
    }

    // Free Memory
    free(dummy);
    free(lower_word);
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Run Hash Function (Add three first letters)
    int x;
    // Condition 1: if len word = 1
    if (strlen(word) == 1)
    {
       x = (word[0] - 97) * 26 * 26;
    }
    // Condition 2: if len word = 2
    else if (strlen(word) == 2)
    {
        x = ((int)word[0] - 97) * 26 * 26 + ((int)word[1] - 97) * 26;
    }
    // Condition 3: if more than 2
    else
    {
        x = ((int)word[0] - 97) * 26 * 26 + ((int)word[1] - 97) * 26 + (int)word[2] - 97;
    }
    return x;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *dictfile = fopen(dictionary, "r");

    // Check if file is openable
    if (dictfile == NULL)
    {
        return false;
    }

    // Allocate memory for scanned word
    char *word_scan = malloc(sizeof(char) * LENGTH);

    // Check if enough memory can be allocated
    if (word_scan == NULL)
    {
        return false;
    }

    // Scan word line by line by using fscanf until the end of page
    while (fscanf(dictfile, "%s", word_scan) != EOF)
    {
        // Allocate memory for dictionary word
        node *dict_word = malloc(sizeof(node) * LENGTH);
        dict_word->next = NULL;

        // Check if enough memory can be allocated
        if (dict_word == NULL)
        {
            return false;
        }

        // Copy scanned word to dictionary word
        strcpy(dict_word->word, word_scan);

        // Run Hash Function
        int hashnum = hash(dict_word->word);

        // Add word to the end of the linked list of the table
        if (table[hashnum] == NULL)
        {
            table[hashnum] = dict_word;
        }
        else
        {
            node *tmp = table[hashnum];
            while (tmp->next != NULL)
            {
                tmp = tmp->next;
            }
            tmp->next = dict_word;
        }

        // Add global counter
        dict_counter++;
    }

    // Free memory
    free(word_scan);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // Return global counter
    return dict_counter;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Free memory by checking every bucket in hash table
    for (int i = 0; i < N; i++)
    {
        // Run cursor through table
        node *cursor = table[i];

        // Check every next and cleans the node
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);

        }
    }
    return true;
}
