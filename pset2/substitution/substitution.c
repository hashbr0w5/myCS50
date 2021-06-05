#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char cipher(char p, string key);
int duplicate_check(string key);
int main(int argc, string argv[])
{
    if (argc == 2) //one command line argument is entered
    {
        string key = argv[1]; //store key in string variable
        int n = strlen(key); //count number of characters in key

        if (n == 26) //26 characters exactly
        {
            for (int i = 0; i < 26; i++) //check all 26 char in key are letters
            {
                if (key[i] >= 'A' && key[i] <= 'Z') //letter is detected
                {

                }

                else if (key[i] >= 'a' && key[i] <= 'z') //letter is detected
                {
                    key[i] = toupper(key[i]); //change lowercase letters in key to uppercase
                }

                else //letter is not detected
                {
                    printf("All 26 characters must be letters.\n");
                    return 1;
                }
            }

            if (duplicate_check(key) == 1) //duplicate check failed
            {
                return 1;
            }

            //**KEY IS VALID**

            else //duplicate check passed
            {
                string ptext = get_string("plaintext: "); //get plaintext
                int b = strlen(ptext); //count number of char in plaintext

                char ptext_2[b + 1]; //uppercase plaintext array
                char ctext[b + 1]; //ciphertext array

                for (int i = 0; i < b; i++) //creating all uppercase plaintext string (ptext_2)
                {
                    if (ptext[i] >= 'a' && ptext[i] <= 'z') //letter is lowercase
                    {
                        ptext_2[i] = toupper(ptext[i]); //store as uppercase letter
                    }

                    else //if uppercase letter, number or other symbol
                    {
                        ptext_2[i] = ptext[i]; //keep the same
                    }
                }

                ptext_2[b] = '\0';

                for (int i = 0; i < b; i++) //encryption
                {
                    if (ptext[i] >= 'A' && ptext[i] <= 'Z')
                    {
                        ctext[i] = cipher((char) ptext_2[i], key); //store encrypted letter in array
                    }

                    else if (ptext[i] >= 'a' && ptext[i] <= 'z')
                    {
                        char x = cipher((char) ptext_2[i], key); //put uppercase letter through cipher
                        ctext[i] = tolower(x); //store it's lowercase in array
                    }

                    else //char is not a letter
                    {
                        ctext[i] = ptext[i]; //store as is
                    }
                }

                ctext[b] = '\0'; //add null operator at end of ciphertext

                printf("ciphertext: %s\n", (string) ctext); //print ciphertext
            }
        }

        else //key does not have 26 letters
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
    }

    else //multiple or no arguments entered
    {
        printf("Usage: ./substitution key\n");
        return 1; //break
    }
} //end of main

int duplicate_check(string key)
{
    int i; //main index counter (shows current letter we are looking for duplicates of)
    int a = 25; //number of times we want to run comparison check

    for (i = 0; i < 25; i++)
    {
        int c = 1; //side index counter (shows letter being used in the comparison)

        for (int j = 0; j < a; j++)
        {
            if (key[i] == key[i + c]) //comparison check
            {
                printf("Be careful not to duplicate letters in your key.\n");
                return 1; //break
            }

            else
            {

            }

            c++; //update side counter
        }

        a--;
    }

    return 0; //key is valid
}

char cipher(char p, string key) //both char and key given will be uppercase
{
    char alph[26]; //initialize alphabet array
    char l = 'A'; //initialize first letter

    for (int j = 0; j < 26; j++) //create alphabet array
    {
        alph[j] = l; //store letter in array
        l++; //update letter
    }

    int k = 0;

    while (p != alph[k]) //find letter in alphabet that matches p
    {
        k++; //use index value in alph array (k) to pull same position letter from key
    }

    return key[k]; //return corresponding (uppercase) letter from key
}