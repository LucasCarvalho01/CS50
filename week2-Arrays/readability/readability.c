#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int Coleman_Liau_alg(int letters, int sentences, int words);

int letterCounter(string text);

int wordCounter(string text);

int sentenceCounter(string text);

int main(void)
{
    // Getting the text
    string text = get_string("Text: ");

    int numLetters = letterCounter(text);
    int numWords = wordCounter(text);
    int numSentences = sentenceCounter(text);

    // printf("letters: %d\n", numLetters);
    // printf("words: %d\n", numWords);
    // printf("senteces: %d\n", numSentences);

    int grade = Coleman_Liau_alg(numLetters, numSentences, numWords);

    // If it is before grade 1
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }

    // If it is 16 or above
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }

    else
    {
        printf("Grade %d\n", grade);
    }

    return 0;
}

int Coleman_Liau_alg(int letters, int sentences, int words)
{
    // Implemented based on the Coleman-Liau algorithm to determine the reading level of a text
    float L = ((float) letters / words * 100);
    float S = ((float) sentences / words * 100);

    float grade = 0.0588 * L - 0.296 * S - 15.8;

    return round(grade);
}

int letterCounter(string text)
{
    int counter = 0;

    for (int i = 0, len = strlen(text); i < len; i++)
    {
        // Checking if the char is alphabetical
        if (isalpha(text[i]))
        {
            counter++;
        }
    }

    return counter;
}

int wordCounter(string text)
{
    int counter = 0;

    for (int i = 0, len = strlen(text); i < len; i++)
    {
        // Checking if the char ascii value == 32, which is space
        if ((int) text[i] == 32)
        {
            counter++;
        }
    }

    // Number of words in a text == number of spaces + 1
    return counter + 1;
}

int sentenceCounter(string text)
{
    int counter = 0;

    for (int i = 0, len = strlen(text); i < len; i++)
    {
        // Checking if the char is . or ! or ?
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            counter++;
        }
    }

    return counter;
}