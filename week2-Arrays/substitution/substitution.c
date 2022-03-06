#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

string lower_string(string word);

int main(int argc, string argv[])
{
    // Error Handling: user passed no command-line arguments
    if ((argc != 2))
    {
        printf("Usage: ./substitution key\n");

        return 1;
    }

    // Error handling: user passed a key with length != 26
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters\n");

        return 1;
    }

    // Program itself
    string key = argv[1];
    string plainText = get_string("plaintext:  ");

    // Lowercasing the whole key, to facilitate computing of cyphertext
    key = lower_string(key);

    // Array that stores the dislocation relative to ascii values of the letters
    int values[26];

    // Ascii of 'a' is 97
    int initialAscii = 97;

    for (int i = 0; i < 26; i++)
    {
        // stores ascii value of current letter of the key
        int aux = key[i];
        values[i] = aux - initialAscii;
        initialAscii++;
    }

    // Make the correct substitution of the letters
    int len = strlen(plainText);
    int j = 0;
    int valueAsciiCurrentLetter = 0;
    while (j < len)
    {
        // Occurs only if the char is a letter
        if (((int) plainText[j] >= 65 && (int) plainText[j] <= 90) || ((int) plainText[j] >= 97 && (int) plainText[j] <= 122))
        {
            // If the letter is in lowercase, value referent to ascii values from 97, 'a'
            if (islower(plainText[j]))
            {
                valueAsciiCurrentLetter = values[(int) plainText[j] - 97];
            }

            // If it is capitalized, value from 65, 'A'
            else
            {
                valueAsciiCurrentLetter = values[(int) plainText[j] - 65];
            }

            plainText[j] = (char)(valueAsciiCurrentLetter + (int) plainText[j]);
        }

        j++;
    }

    // Printing the text encrypted
    printf("ciphertext: %s\n", plainText);

    return 0;
}


string lower_string(string word)
{
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        word[i] = tolower(word[i]);
    }

    return word;
}