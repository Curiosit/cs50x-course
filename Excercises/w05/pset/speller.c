// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26 * 26 * 26 * 26;

// Hash table
node *table[N];
int d_size = 0;
// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int hashed = hash(word);
    // printf("Word: %s ", word);
    // printf("hashed as: %i \n", hashed);

    node *nd = table[hashed];
    while (nd != NULL)
    {
        // printf("Node %i: %s \n", hashed, nd->word);
        // printf("Comparing with: %s \n", word);
        if (strcasecmp(word, nd->word) == 0)
        {
            // printf("Found: %s \n", word);
            return true;
        }
        nd = nd->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{

    // TODO: Improve this hash function
    int len = strlen(word);
    int w2 = 0;
    int w3 = 0;
    int w4 = 0;
    if (len > 3)
    {

        w4 = (toupper(word[3]) - 'A') * 25;
        if (w4 < 0)
        {
            w4 = 0;
        }

        if (len > 2)
        {
            w3 = (toupper(word[2]) - 'A') * 25;
            if (w3 < 0)
            {
                w3 = 0;
            }
        }
        if (len > 1)
        {
            w2 = (toupper(word[1]) - 'A') * 25;
            if (w2 < 0)
            {
                w2 = 0;
            }
        }
    }

    int hashed = (toupper(word[0]) - 'A') + w2 + w3 + w4;
    // printf("#1: %i \n",  (toupper(word[0]) - 'A'));

    // printf("#2 * 25: %i \n",  w2);
    // printf("Hashed: %i \n", hashed);
    return hashed;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("Could not open file.\n");
        unload();
        return false;
    }

    char line[LENGTH + 1];

    node *start;
    while (fscanf(dict, "%s", line) != EOF)
    {
        // printf("%s", line);
        char *word = strtok(line, " \n\t");
        node *nd = calloc(1, sizeof(node));
        if (nd == NULL)
        {
            fclose(dict);
            return false;
        }
        strcpy(nd->word, word);

        int index = hash(nd->word);
        // printf("%i \n", index);

        nd->next = table[index];
        table[index] = nd;
        d_size++;
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return d_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {

        node *nd = table[i];
        while (nd != NULL)
        {
            node *tmp = nd;

            nd = nd->next;

            free(tmp);
        }
        if (nd == NULL && i == N - 1)
        {
            return true;
        }
    }
    return true;
}
