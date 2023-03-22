#include <cs50.h>
#include <stdio.h>
#include <strings.h>

int main(void)
{
    string s1 = get_string("s1: ");
    string s2 = get_string("s2: ");
    if (strcasecmp(s1, s2) == 0)
    {
        printf("Those are the same, ignoring case.\n");
    }
    else
    {
        printf("Those are different, even ignoring case.\n");
    }
}