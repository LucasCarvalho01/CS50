#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int ascii_value(char c);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Printing the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }

    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }

    else
    {
        printf("Tie\n");
    }

    
}

int compute_score(string word)
{
    // First, change the string to lowercase, being able to compare all words equally
    int len = strlen(word);

    for (int i = 0; i < len; i++)
    {
        word[i] = tolower(word[i]);
    }

    // loop to sum the value of a letter, if it's not a letter, it is ignored
    int j = 0;
    int sum = 0;
    int aux = 0;

    while (j < len)
    {
        aux = ascii_value(word[j]);

        // If the value is non-zero, then it is a letter
        if (aux)
        {
            // The ascii value of 'a' is 97, in the arr POINTS, will be at index 0
            sum += POINTS[aux - 97];
        }

        j++;
    }

    return sum;
}

int ascii_value(char c)
{
    // Returning the ascii value of a character
    // If it's not a letter, returns 0
    if ((int) c >= 97 && (int) c <= 122)
    {
        return (int) c;
    }

    return 0;
}
