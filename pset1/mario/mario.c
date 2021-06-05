#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int n;

    do
    {
        n = get_int("Height: "); //get height
    }
    while (n < 1 || n > 8); //if number is not within the 1-8 range, repeat prompt

    for (int i = 1; i <= n; i++) //creates pyramid height
    {
        for (int b = 0; b < (n - i); b++) //creates spaces
        {
            printf(" ");
        }

        for (int c = 0; c < i; c++) //creates hashes
        {

            printf("#");
        }

        printf("  ");

        for (int c = 0; c < i; c++) //creates adjacent hashes
        {
            printf("#");
        }

        printf("\n"); //move prompt to next line
    }

}