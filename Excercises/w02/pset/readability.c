#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string str);
int count_words(string str);
int count_sentences(string str);
int main(void)
{
    string s = get_string("Text: ");
    int len = strlen(s);
    int letters = count_letters(s);
    // printf("%i letters\n", letters);
    int words = count_words(s);
    // printf("%i words\n", words);
    int sentences = count_sentences(s);
    // printf("%i sentences\n", sentences);
    float L = (float) letters * (100 / (float) words);
    float S = (float) sentences * (100 / (float) words);
    float index = 0.0588 * L - 0.296 * S - 15.8;
    printf("%f L\n", L);
    printf("%f S\n", S);
    printf("%f index\n", index);
    int grade = round(index);
    // L is the average number of letters per 100 words in the text
    // S is the average number of sentences per 100 words in the text

    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade <= 15)
    {
        printf("Grade %i\n", grade);
    }
    else
    {
        printf("Grade 16+\n");
    }
}

int count_letters(string str)
{
    int let = 0;
    int len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        if (isalpha(str[i]))
        {
            let++;
        }
    }
    return let;
}

int count_words(string str)
{
    int words = 0;
    int len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        if (isspace(str[i]))
        {
            words++;
        }
    }
    words++;
    return words;
}
int count_sentences(string str)
{
    int sent = 0;
    int len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        if (str[i] == '.' || str[i] == '!' || str[i] == '?')
        {
            sent++;
        }
    }
    if (sent < 1)
    {
        sent = 1;
    }
    return sent;
}
