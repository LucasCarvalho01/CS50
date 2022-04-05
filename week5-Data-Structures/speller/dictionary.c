// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"

int number_words = -1;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
// 26 + 27
const unsigned int N = 53;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int compare;

    // Hashing word to obtain hash value
    int index = hash(word);

    // Accessing linked list associated to hash value
    node *aux = malloc(sizeof(node));
    aux = table[index]->next;

    // Comparing each word in list to passed string
    while (aux != NULL)
    {
        // If strcasecmp returns 0, both words are the same
        compare = strcasecmp(word, aux->word);
        if (compare == 0)
        {
            return true;
        }
        else
        {
            aux = aux->next;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Bucket number based on the first 2 letters
    int value = toupper(word[0]) - 'A';

    // Second char is a letter
    if (toupper(word[1]) >= 'A' && toupper(word[1]) <= 'Z')
    {
        value += toupper(word[1]) - 'A';
    }

    // If there is a second char, and it is ', consider it as 26
    else if (word[1] == '\'')
    {
        value += 26;
    }

    // If there is no second char, just returns the value of first char
    return value;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Opening dictionary file
    FILE *dictionary_input = fopen(dictionary, "r");
    char currentWord[LENGTH + 1];
    int index = -1;

    // If could not open dictionary file, load returns false
    if (dictionary_input == NULL)
    {
        return false;
    }

    // Starting a head node on each list
    for(int i = 0; i < N; i++)
    {
        node *head = malloc(sizeof(node));
        if (head == NULL)
        {
            printf("Error allocating head nodes on each list of hash table\n");
            return false;
        }

        table[i] = head;
        head->next = NULL;
        strcpy(head->word, "HeadNode");
    }

    // Reading each dictionary's line
    while (fscanf(dictionary_input, "%s", currentWord) != EOF)
    {
        // Create a new node
        node *new = malloc(sizeof(node));
        if (new == NULL)
        {
            return false;
        }

        // Copying word read from dictionary to node
        strcpy(new->word, currentWord);
        new->next = NULL;

        // Hashes node to correct bucket in hash table
        index = hash(new->word);
        new->next = table[index]->next;
        table[index]->next = new;

        number_words++;
    }

    fclose(dictionary_input);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (number_words == -1)
    {
        return 0;
    }

    return number_words + 1;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *tmp = malloc(sizeof(node));
    node *cursor = malloc(sizeof(node));

    if (tmp == NULL || cursor == NULL)
    {
        printf("error unloading dictionary\n");
        return false;
    }

    for (int i = 0; i < N; i++)
    {
        cursor = table[i];
        tmp = cursor;

        while (cursor != NULL)
        {
            tmp = tmp->next;
            free(cursor);
            cursor = tmp;
        }
    }

    free(cursor);
    free(tmp);
    number_words = -1;

    return true;
}
