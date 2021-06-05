#include <stdio.h>
#include <cs50.h>
#include <math.h>

void checksum(long n);
int main(void)
{
    long n;
    int i = 0;

    do
    {
        n = get_long("Number: "); //get number
    }
    while (n < 0); //reprompt if number is negative or a character is entered

    long j = n; //create a duplicate of n

    while (j > 0) //count number of digits
    {
        j = j / 10; //everytime we divide j by 10 we increment the counter by 1 to acccount for the digit that was there
        i++; //counter
    }

    if (i == 13 || i == 15 || i == 16) //credit card digit lengths
    {
        checksum(n); //find checksum function
    }

    else //number entered is not a credit card
    {
        printf("INVALID\n");
    }
}

void card(long j);
void checksum(long n) //checksum function
{
    long j = n; //duplicate of n
    int x;
    int a = 0; //initialize variables
    int asum = 0;
    int bsum = 0;

    while (n > 0) //while n > 0 keep storing the numbers according to Luhn's algorithm
    {
        a++; //counter

        if (a % 2 == 1) //if a is odd
        {
            x = n % 10; //grab last digit of n
            asum = asum + x; //add x to asum
            n = n / 10; //divide out last digit of n
        }

        else //if a is even
        {
            x = n % 10; //grab digit
            x = 2 * x; //multiply digit by 2

            if (x > 9) //if product has 2 digits
            {
                x = x % 10; //grab last digit
                bsum = bsum + x + 1; //add product's first digit (always 1) and last digit to bsum
                n = n / 10; //divide out last digit of n
            }

            else //if product has 1 digit
            {
                bsum = bsum + x; //add to bsum
                n = n / 10;
            }
        }
    } //end of while loop

    int finalsum = asum + bsum; //calc final sum

    if (finalsum % 10 != 0) //does not meet Luhn's algorithm
    {
        printf("INVALID\n"); //print invalid
    }

    else //meets Luhn's algorithm
    {
        card(j); //find card function
    }
} //end of checksum function

void card(long j) //check if credit card meets starting digit requirements
{
    int i = 0;
    int p;
    long n = j; //another duplicate of n

    while (j > 0)
    {
        j = j / 10;
        i++; //counter for credit card length
    }

    if (i == 13) //13-digit card
    {
        p = n / pow(10, 12); //getting first digit

        if (p == 4) //check if starting digit matches up with VISA requirements
        {
            printf("VISA\n");
        }

        else
        {
            printf("INVALID\n");
        }
    }

    else if (i == 15) //15-digit card
    {
        p = n / pow(10, 13); //getting first two digits

        if (p == 34 || p == 37) //check if starting digits match up with AMEX requirements
        {
            printf("AMEX\n");
        }

        else
        {
            printf("INVALID\n");
        }
    }

    else if (i == 16) //16-digit card
    {
        p = n / pow(10, 15); //getting first digit
        int w = n / pow(10, 14); //getting first two digits

        if (p == 4) //check if starting digit match up with VISA requirements
        {
            printf("VISA\n");
        }

        else if (w == 51 || w == 52 || w == 53 || w == 54 || w == 55) //check if starting digits match up with MASTERCARD requirements
        {
            printf("MASTERCARD\n");
        }

        else
        {
            printf("INVALID\n");
        }
    }
} //end of card function