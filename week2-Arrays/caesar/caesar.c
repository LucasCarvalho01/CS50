#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int argumentVerifier(string arg);

int main(int argc, string argv[])
{
    // Error handling: user did not pass a key or passed more than 1 argument
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Error handling: key is not a number
    string key = argv[1];
    int validation = argumentVerifier(key);

    if (!validation)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Program itself

    // dislocator will always be a number between 0 and 25
    int dislocator = atoi(key);
    string plainText = get_string("plaintext:  ");

    // Gettin the ascii index for a and A
    const int index_a = 97;
    const int index_A = 65;

    // Encrypting the plaintext
    for (int i = 0, n = strlen(plainText); i < n; i++)
    {
        // Only occurs when char is alpahbetical
        if (isalpha(plainText[i]))
        {
            // If the letter is capitalized
            if ((int) plainText[i] <= 90)
            {
                plainText[i] = (char)(((int) plainText[i] - index_A + dislocator) % 26) + index_A;
            }

            // Otherwise, is lowercase
            else
            {
                plainText[i] = (char)(((int) plainText[i] - index_a + dislocator) % 26) + index_a;
            }
        }
    }

    printf("ciphertext: %s\n", plainText);

    return 0;
}

// Check if all chars in the key are numbers
int argumentVerifier(string arg)
{
    for (int i = 0, n = strlen(arg); i < n; i++)
    {
        if (!isdigit(arg[i]))
        {
            return 0;
        }
    }

    return 1;
}