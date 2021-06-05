#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    int q = 0; //initialize variables
    int nick = 0;
    int d = 0;
    int p = 0;
    float x;

    do
    {
        x = get_float("Change owed: "); //get change in dollars
    }
    while (x < 0); //repromt user if change is less than 0

    int n = round(x * 100); //convert change to cents and round to nearest penny

    while (n >= 25)
    {
        q = n / 25; //figure out how many quarters fit in the sum
        n = n - (q * 25); //update value of n (remaining change that needs to be sorted)
    }

    while (n >= 10)
    {
        d = n / 10; //figure out how many dimes fit in the sum
        n = n - (d * 10); //update value of n
    }

    while (n >= 5)
    {
        nick = n / 5; //figure out how many nickels fit in the sum
        n = n - (nick * 5); //update value of n
    }

    while (n >= 1)
    {
        p = n; //remaining change can be sorted into pennies
        n = 0; //update final value of n (all change has been sorted)
    }

    int coin = q + nick + d + p; //add up total number of coins used

    printf("%i\n", coin); //output coins used
}