// Implements a dictionary's functionality
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include "dictionary.h"
#include <cs50.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = (LENGTH + 1)  * 'z';

// Hash table
int num_words = 0;
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    //get hash index
    int index = hash(word);

    //access linked list at the hash table
    node *cursor = table[index];

    //traverse the linked list using strcasecmp()
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int sum = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        sum += tolower(word[i]); //adds up the sum of the ascii values
    }
    return (sum % N);
    //return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    //1
    //use fopen
    //remember to check if return value is null

    //Open dictionary file
    FILE *file = fopen(dictionary, "r'");
    if (file == NULL)
    {
        return false;
    }
    //2 - read strings from the file
    //use fscanf(file, "%s", word) in a loop
    //fscanf will return EOF at the end of the file
    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF)
    {
        //read in words by making a new node using malloc
        node *nn = malloc(sizeof(node));
        if (nn == NULL)
        {
            return false;
        }
        //3 -create a new node using malloc
        //use strcpy to copy the word to node
        strcpy(nn->word, word);
        nn->next = NULL;

        //4 - insert this node into the hash table
        //use the hash function in dictionary.c
        int index = hash(word);
        if (table[index] == NULL)
        {
            table[index] = nn;
        }
        //prepends (insert at front of linked list) to existing node if it already exists
        else
        {
            nn->next = table[index];
            table[index] = nn;
        }
        num_words++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return num_words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    //free the linked list
    for (int i = 0; i < N; i ++)
    {
        node *head = table[i];
        node *cursor = head;
        node *tmp = head;

        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
    }
    return true;
}
