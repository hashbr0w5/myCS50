#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int cipher(int k, char p);
int main(int argc, string argv[])
{
    if (argc == 2) //one argument was passed at command ine
    {
        string text = argv[1]; //save argument in a string
        int b = strlen(text); //count number of characters in text

        for (int i = 0; i < b; i++) //check all charaters in string
        {
            if (text[i] >= '0' && text[i] <= '9') //char is a decimal digit
            {

            }

            else //char is not a decimal digit
            {
                printf("Usage: ./caesar key\n");
                return 1; //break
            }
        }

        int key = atoi(text); //convert string to int (this is our key)

        string ptext = get_string("plaintext: "); //get plaintext
        int n = strlen(ptext); //count number of characters in plaintext
        char ctext[n + 1]; //ciphertext array

        for (int i = 0; i < n; i++) //check each character and shift accordingly
        {
            if (ptext[i] >= 'A' && ptext[i] <= 'Z') //letter is uppercase
            {
                ctext[i] = cipher(key, ptext[i]); //store encrypted letter in array
            }

            else if (ptext[i] >= 'a' && ptext[i] <= 'z') //letter is lowercase
            {
                char x = cipher(key, toupper(ptext[i])); //enter an uppercase letter in function
                ctext[i] = tolower(x); //change back to lowercase and save in array
            }

            else //char is a space, symbol or integer
            {
                ctext[i] = ptext[i]; //char remains unchanged
            }
        }

        ctext[n] = '\0'; //add null operator to end of array

        printf("ciphertext: %s\n", (string) ctext); //output ciphertext
        return 0;
    }

    else //multiple or no arguments were passed at command line
    {
        printf("Please enter a valid key\n");
        return 1; //break
    }
} //end of main

int cipher(int k, char p) //letter encryption function
{
    char alpb[26]; //alphabet array
    char letter = 'A'; //initialize first letter to 'A'

    for (int j = 0; j < 26; j++)
    {
        alpb[j] = letter; //store letter in array
        letter++; //update letter
    }

    int j = 0; //initialize index counter

    while (p != alpb[j]) //letter does not match that in array
    {
        j++; //update index value
    }

    int c = (j + k) % 26; //calculate Caesar's algorithm
    return alpb[c]; //return encrypted letter
}