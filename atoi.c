#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int convert(string input, int counter);
int lastnum;
int total;


int convert(string input, int counter)
{
    // 123
    if(counter>0)
    {
    lastnum = input[counter-1]-48; // this is because string is an array of char. In ascii "1" is represented with 49.
    counter--;
    total = lastnum + 10*(convert(input, counter));
    return total;
    }
    else
    {
        return 0;
    }
}

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }
int counter  = strlen(input);
    lastnum = input[counter];
    // Convert string to int
    printf("%i\n", convert(input, counter));
}
