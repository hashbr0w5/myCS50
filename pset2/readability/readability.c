#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>

int word_count(int n, string array);
int count_letters(int i, string array);
int count_sentences(int i, string array);
int main(void)
{
    string text = get_string("Text: "); //get text
    int n = strlen(text); //count number of characters in text

    int hund[word_count(n, text) / 100]; //number of entries is equal to number of 100s in wordsum
    int h = 1;
    int j = 0; //hundreds array counter
    int wsum = 0;

    for (int i = 0; i < n; i++)
    {
        if (i == n - 1) //reached last character (cannot be a space)
        {
            wsum++; //update wsum to account for last word

            if (wsum == 100 * h) //check if word count is a hundred exactly
            {
                hund[j] = i; //save index value in array
            } //don't have to update j or h becaues we've finished analyzing the text

            else
            {

            }
        }

        else if (text[i] == ' ') //check for spaces
        {
            wsum++;

            if (wsum == 100 * h) //check if word count is a hundred exactly
            {
                hund[j] = i; //save index value in array
                j++;
                h++; //increment h so the next time it will check if the word count is equal to 200, 300, etc.
            }

            else
            {

            }
        }

        else
        {

        }
    }

    int i = 0; //index counter
    int p = 0; //hundreds array counter
    float lsum = 0, lavg = 0, lcount = 0;
    float ssum = 0, savg = 0, scount = 0;

    while (wsum >= 100)
    {
        while (i < hund[p]) //analyze characters every 100 words
        {
            lsum = lsum + count_letters(i, text); //calculate lsum
            ssum = ssum + count_sentences(i, text); //calculate ssum
            i++;
        }

        lavg = lavg + (lsum / 100); //add mini avg (avg calculated every 100 words) to big avg sum
        lsum = 0; //reset lsum
        lcount++; //count number of additions being made to lavg

        savg = savg + (ssum / 100);
        ssum = 0; //reset ssum
        scount++; //count number of additions being made to savg

        p++; //updating array index value
        wsum = wsum - 100; //update wsum (already taken the averages we needed from the nth 100 block)
    }

    while (wsum < 100)
    {
        while (i < n) //run index until we reach the final character
        {
            lsum = lsum + count_letters(i, text);
            ssum = ssum + count_sentences(i, text);
            i++;
        }

        lavg = lavg + (lsum * 100 / wsum); //correct the avg ratio since we're not dividing it by 100 words
        lcount++;
        savg = savg + (ssum * 100 / wsum);
        scount++;

        break;
    }

    float L = lavg / lcount; //calculate final L average
    float S = savg / scount; //calculate final S average
    float index = round(0.0588 * L - 0.296 * S - 15.8); //calculate Coleman-Liau index

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }

    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }

    else
    {
        for (int b = 1; b < 16; b++)
        {
            if (index == b)
            {
                printf("Grade %i\n", b);
            }

            else
            {

            }
        }
    }
} //end of main

int word_count(int n, string array) //word count function
{
    int wsum = 1; //initialize word sum

    for (int b = 0; b < n; b++)
    {
        if (array[b] == ' ') //check for spaces
        {
            wsum++; //update word sum
        }

        else //space character was not detected
        {

        }
    }
    return wsum;
}

int count_letters(int i, string array) //letter check function
{
    if (array[i] >= 'A' && array[i] <= 'Z') //check for uppercase letters
    {
        return 1; //return value of 1 to be added to lsum
    }

    else if (array[i] >= 'a' && array[i] <= 'z') //check for lowercase letters
    {
        return 1;
    }

    else
    {
        return 0;
    }
}

int count_sentences(int i, string array) //sentence check function
{
    if (array[i] == '.' || array[i] == '!' || array[i] == '?') //check ending punctuation
    {
        return 1; //return value of 1 to be added to ssum
    }

    else
    {
        return 0;
    }
}