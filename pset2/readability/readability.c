#include <cs50.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    //Step 1: Get the text from user
    string text = get_string("Text: ");

    //Step 2: Count number of letters, words, and sentences
    int letter = count_letters(text);
    int word = count_words(text);
    int sentence = count_sentences(text);

    //Step 3: Calculate grade with the Coleman-Liau Formula
    float av_letterword = ((float)letter / (float)word) * 100;
    float av_sentenceword = ((float)sentence / (float)word) * 100;
    float index = (0.0588 * av_letterword) - (0.296 * av_sentenceword) - 15.8;

    //Step 4: Give grade output
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.0f\n", index);
    }
}

int count_letters(string text)
{
    //Function works by adding counter if the character is an alphabet
    int n = strlen(text);
    int letter_sum = 0;
    for (int i = 0; i < n; i++)
    {
        if ((65 <= text[i] && text[i] <= 90) || (97 <= text[i] && text[i] <= 122))
        {
            letter_sum++;
        }
    }
    return letter_sum;
}

int count_words(string text)
{
    //Function works by adding counter if there is a space after word
    int n = strlen(text);
    int word_sum = 1;
    for (int i = 0; i < n; i++)
    {
        if (text[i] == 32)
        {
            word_sum++;
        }
    }
    return word_sum;
}

int count_sentences(string text)
{
    //Function works by adding counter if encounters ".","!","?"
    //Exception for fullstop in name. Ex. "Mr.Dursley"
    int n = strlen(text);
    int sentence_sum = 0;
    for (int i = 0; i < n; i++)
    {
        if (text[i] == 33 || text[i] == 46 || text[i] == 63)
        {
            sentence_sum++;
        }
    }
    return sentence_sum;
}