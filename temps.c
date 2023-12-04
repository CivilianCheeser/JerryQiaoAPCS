// Practice working with structs
// Practice applying sorting algorithms

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define NUM_CITIES 10
// should make struct global
typedef struct // in this way this struct is a data type, it can be other data type too
{
    string city;
    int temp;
} atemp; // atemp = the average temperature

atemp temps[NUM_CITIES];

void sort_cities(void); // sorts temps from coldest to hottest
int findsmall(atemp copytemp[NUM_CITIES], int prevtemp, string prevname);

int main(void)
{
    temps[0].city = "Austin";
    temps[0].temp = 97;

    temps[1].city = "Boston";
    temps[1].temp = 82;

    temps[2].city = "Chicago";
    temps[2].temp = 85;

    temps[3].city = "Denver";
    temps[3].temp = 90;

    temps[4].city = "Las Vegas";
    temps[4].temp = 105;

    temps[5].city = "Los Angeles";
    temps[5].temp = 82;

    temps[6].city = "Miami";
    temps[6].temp = 97;

    temps[7].city = "New York";
    temps[7].temp = 85;

    temps[8].city = "Phoenix";
    temps[8].temp = 107;

    temps[9].city = "San Francisco";
    temps[9].temp = 66;

    sort_cities();

    printf("\nAverage July Temperatures by City\n\n");

    for (int i = (NUM_CITIES - 1); i > 0; i--) // because temp is arranged ascending, the print function is backwards
    {
        printf("%s: %i\n", temps[i].city, temps[i].temp);
    }
}

// TODO: Sort cities by temperature in descending order
void sort_cities(void)
{
    atemp copytemp[NUM_CITIES]; // designed to make a copy of temps
    for (int i = 0; i < NUM_CITIES; i++)
    {
        copytemp[i].city = temps[i].city; // making a copy of the temp
        copytemp[i].temp = temps[i].temp;
        temps[i].city = "VOID"; // clearing temps so we can manipulate it
        temps[i].temp = 0;
    }

    int prevtemp = 0; // the previous temp, a counter of finding the smallest number
    string prevname;
    for (int i = 0; i < NUM_CITIES; i++)
    {
        temps[i].temp =
            copytemp[findsmall(copytemp, prevtemp, prevname)].temp; // setting a value of temps to the smallest in copytemp
        temps[i].city = copytemp[findsmall(copytemp, prevtemp, prevname)].city;
        prevtemp = temps[i].temp; // reset. This tell us the last city we sorted
        prevname = temps[i].city;
    }
}

int findsmall(atemp copytemp[NUM_CITIES], int prevtemp, string prevname)
{
    int smallnum = 99999;
    /*
    what exactly does smallnum do?
    essentially, the smallnum is a candidate for the next smallest number in copytemp
    if a smaller number than smallnum is found, then smallnum will be replace by that smaller number
    This replacement wont happen if the city is a repeat
    */
    int index = 0;
    for (int i = 0; i < NUM_CITIES; i++)
    {
        if (copytemp[i].temp < smallnum && copytemp[i].temp >= prevtemp) // the next smallest number may be found
        {
            bool repeat = false;
            for (int k = 0; k < NUM_CITIES; k++) // did we already record this city?
            {
                if (temps[k].city == copytemp[i].city)
                {
                    repeat = true;
                }
            }
            if (repeat == false) // if not, then record it
            {
                smallnum = copytemp[i].temp;
                index = i;
            }
        }
    }
    return index;
}
