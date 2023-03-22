// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <cs50.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;


// Number of buckets in hash table
const unsigned int N = 24693;

bool dic_load;
long count = 0; //# of words loaded into dictionary

// Hash table
node *table[N];


// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    //make a lowercase copy of word

    int n = strlen(word); //number of letters
    char new_word[n + 1];

    for (int i = 0; i < n; i++)
    {
        if (word[i] >= 'A' && word[i] <= 'Z') //identify capital letter
        {
            new_word[i] = tolower(word[i]); //store lowercase equivalent
        }

        else //lowercase, apostrophes, etc.
        {
            new_word[i] = word[i];
        }
    }

    new_word[n] = '\0';

    unsigned int x = hash(new_word); //hash value
    node *tmp = table[x]; //index into hash table

    //loop through linked list looking for a match

    while (tmp != NULL)
    {
        if (strcmp(new_word, tmp->word) == 0)
        {
            return true; //found a match
        }

        tmp = tmp->next; //move pointer to next node
    }

    return false; //word is not in dictionary
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    //Using Dan Bernstein's DJB2 Hashing Algorithm

    unsigned int hash = 5381;
    int c = *word++; //ascii value of letter

    while (c != 0) //loop through word until NULL
    {
        hash = ((hash << 5) + hash) + c;
        c = *word++; //grab next ascii value
    }

    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *fptr = fopen(dictionary, "r"); //open dictionary

    if (fptr != NULL) //dictionary exists
    {
        char *buffer = malloc(LENGTH + 1);
        if (buffer == NULL)
        {
            return false; //not enough memory
        }

        for (int i = 0; i < N; i++) //initialize pointers to NULL
        {
            table[i] = NULL;
        }

        while (fscanf(fptr, "%s", buffer) != EOF)
        {
            node *n = malloc(sizeof(node));
            if (n == NULL)
            {
                return false; //not enough memory
            }

            strcpy(n->word, buffer); //copy word into node
            n->next = NULL; //set pointer to NULL

            unsigned int x = hash(n->word); //compute hash index

            //store word in hash table

            if (table[x] != NULL) //reset head pointer if there's an existing linked list
            {
                n->next = table[x];
                table[x] = n;
            }

            else //point to new node (first in linked list)
            {
                table[x] = n;
            }

            count++; //update word count
        }

        fclose(fptr); //close file
        free(buffer); //free buffer

        dic_load = true;
        return true; //dictionary successfully loaded
    }

    fclose(fptr); //close file

    dic_load = false;
    return false; //file does not exist
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (dic_load == true)
    {
        return count;
    }

    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++) //loop through array
    {
        node *tmp = table[i];

        while (table[i] != NULL) //free individual linked list
        {
            if (tmp->next == NULL) //last node
            {
                free(tmp); //free last node
                table[i] = NULL; //set head pointer to NULL
            }

            else
            {
                tmp = tmp->next;
                free(table[i]);
                table[i] = tmp;
            }
        }
    }

    return true;
}