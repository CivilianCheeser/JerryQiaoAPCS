// Jerry

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void readprint(void); // Read: reader give file, print it as is
void addcreate(void); // Create: Make a new file. Maybe let user write in it?
void search(void);    // Search: Linear vs binary search
void sort(void);      // Gives the user an organized list from a random list
int repeat(void);   // Ask the user if the want to repeat the menu
int main(void)
{
    int choice;
    do
    {
        printf("||~~~~~~~~~---MENU---~~~~~~~~||");
        printf("\n**         1. Read           **\n**         2. Add/Create     **\n**         3. Search         **\n**         4. Sort "
               "          **\n**         5. EXIT           **\n");
        choice = get_int("\nEnter The Number Bewtween 1 to 5 for the desired action: ");
        switch (choice)
        {
            case 1:
                readprint();
                break;

            case 2:
                addcreate();
                break;

            case 3:
                search();
                break;

            case 4:
                sort();
                break;

            case 5:
                printf("Hasta Luego\n");
                return 0;
                break;

            default:
                printf("ERROR: Number must be between 1 to 5\n");
                break;
        }
        choice = repeat();
    }
    while (choice != 5); // 5 means code terminates
}

void search(void)
{
    printf("\nThis option find the number in a file \n");
    printf("\nYou have the option of Linear Search or Binary Search \n");
    printf("\nLinear Search may be faster than Binary Search in small amounts\n");
    printf("Linear Search may be faster than Binary Search in large amounts\n");
    printf("BINARY SEARCH WILL ONLY WORK IF THE LIST IS SORTED\n");

    string filename = get_string("\nPlease enter file NAME including .txt ");
    FILE *file = (fopen(filename, "r"));
    if (!file)
    {
        printf("Unable to open: %s\n", filename);
    }
    else
    {
        int size = get_int("\nHow many numbers does the file contain?");
        char option[size][5]; // array to put all the numbers form the file

        for (int i = 0; i < size; i++)
        {
            fscanf(file, "%s", option[i]);
        }
        fclose(file);
        // linear search
        bool valid;

        do
        {
            char action = get_char("\npress L for Linear Search or B for Binary Search: ");
            int num;
            bool found = false;
            switch (action)
            {
                case 'l':
                case 'L': // Linear Search

                    valid = true;
                    num = get_int("\nplease enter a positive number ");
                    for (int i = 0; i < size; i++)
                    {
                        if (atoi(option[i]) == num)
                        {
                            printf("linear search is looking for %i\n", num);
                            printf("linear search found at index %i\n", (i + 1));
                            found = true;
                            break;
                        }
                    }
                    if (!found)
                    {
                        printf("ERROR: The number was not found. \n");
                        printf("TIP: This may be because the number is invalid or you did not include all the numbers in a file\n");
                    }
                    break;

                case 'b':
                case 'B': // binary search
                    valid = true;
                    num = get_int("pls enter a number");
                    int upper = (sizeof(option) / sizeof(option[0]));
                    int lower = 0;
                    int mid = (upper / 2);
                    printf("\nBinary Search only works when the list is sorted. \n");
                    printf("You may need to restart the program. \n");
                    do
                    {
                        mid = (upper + lower) / 2;
                        if (atoi(option[mid]) == num)
                        {
                            printf("binary search is looking for %i\n", num);
                            printf("binary search found at %i\n", (mid + 1));
                            break;
                        }
                        else
                        {
                            if (mid >= num)
                            {
                                upper = mid;
                            }
                            else
                            {
                                lower = mid;
                            }
                        }
                    }
                    while (atoi(option[mid]) != num);
                    break;

                default:
                    valid = false;
                    printf("\nOnly L and B is accepted as input\n");
                    break;
            }
        }
        while (!valid);
    }
}

void addcreate(void)
{
    printf("\nThis option creates a text file. \n");
    bool valid;

    printf(
        "\nTIP: If you WRITE a new file with the same name as a pre-existing file, you will wipe all the data on the old file\n");
    printf("\nDo you want to ADD to an existing file or WRITE a new one?\n");
    do
    {
        char action = get_char("press A for add or W for write: ");
        FILE *file;
        string filename;
        string content;
        switch (action)
        {
            case 'A':
            case 'a':
                valid = true;
                filename = get_string("Enter the name of file you want to add to ");
                content = get_string("Enter the content you want in the file\n: ");
                file = fopen(filename, "a");
                if (file == NULL)
                {
                    printf("Error opening file\n");
                    break;
                }
                fputs(content, file);
                fclose(file);
                printf("Done \n");
                break;

            case 'W':
            case 'w':
                valid = true;
                filename = get_string("Enter the name of file you want to create ");
                content = get_string("Enter the content you want int the file\n: ");
                file = fopen(filename, "w");
                if (file == NULL)
                {
                    printf("Error opening file\n");
                    break;
                }
                fputs(content, file);
                fclose(file);
                printf("Done \n");
                break;

            default:
                valid = false;
                printf("ERROR: The program only accepts A or W \n");
                break;
        }
    }
    while (!valid);
}

void sort(void)
{
    printf("\nThis option sorts the numbers in a file in ascending order \n");
    string filename = get_string("\nPlease enter file NAME including .txt ");
    FILE *file = (fopen(filename, "r"));
    if (!file)
    {
        printf("Unable to open: %s\n", filename);
    }
    else
    {
        int size = get_int("\nHow many numbers does the file contain?");
        char option[size][5]; // array to put all the numbers form the file
        int sortedarray[size];
        for (int i = 0; i < size; i++)
        {
            fscanf(file, "%s", option[i]);
        }
        fclose(file);
        printf("\nYou have the option of Bubble Sort or Selection Sort \n");
        bool valid;
        int prevnum;
        int smallnum;
        int counter;
        int numswap;
        do
        {
            char action = get_char("\npress B for Bubble Sort or S for Selection Sort: ");
            switch (action)
            {
                case 'S':
                case 's': // selectioon sort

                    valid = true;
                    size =
                        (sizeof(sortedarray) /
                         sizeof(
                             sortedarray[0])); // why is it that if we just do sizeof(sortedarray) it gives me4*(number in bracket)?
                    prevnum = 0;               // the previous number, a counter of finding the smallest number
                    for (int i = 0; i <= size; i++)
                    {
                        smallnum = size;

                        for (int k = 0; k < size; k++)
                        {
                            if (atoi(option[k]) < smallnum && atoi(option[k]) > prevnum)
                            {
                                smallnum = atoi(option[k]);
                            }
                        }
                        sortedarray[i] = smallnum; // set the corresponding number to the corresponding minimum number
                        prevnum = sortedarray[i];  // reset the smallest number
                    }
                    for (int i = 0; i < size; i++) // ascending
                    {
                        printf("%i\t", sortedarray[i]);
                    }
                    // for (int i = size; i >= 0; i--) //descending
                    // {
                    //     printf("%i\n", sortedarray[i]);
                    // }
                    break;

                case 'b':
                case 'B': // bubble
                    valid = true;
                    for (int i = 0; i < size; i++) // loading options into a easier file
                    {
                        sortedarray[i] = atoi(option[i]);
                    }

                    counter = 1; // decare counter

                    while (counter != 0)
                    {
                        counter = 0; // counter reset
                        for (int i = 0; i < size; i++)
                        {
                            if (sortedarray[i] >
                                sortedarray[i + 1]) // a bigger number is detected! i-1 is needed, i+1 comparisons dont work...
                            {
                                numswap = sortedarray[i];
                                sortedarray[i] = sortedarray[i + 1];
                                sortedarray[i + 1] = numswap;
                                counter++;
                            }
                        }
                    }

                    for (int i = 0; i < size; i++) // verify
                    {
                        printf("%i\n", sortedarray[i]);
                    }
                    break;

                default:
                    valid = false;
                    printf("\nOnly B and S are accepted as inputs\n");
                    break;
            }
        }
        while (!valid);
    }
}

int repeat(void) // does the user want to start over?
{
    char repeat = get_char("Press Y to Return to the Menu ");
    switch (repeat)
    {
        case 'Y':
        case 'y':
            return 3;
            break;

        default:
            printf("Hasta Luego\n");
            return 5;
            break;
    }
}

void readprint(void)
{
    // start of readprint
    printf("\nThis option lets you read44 the text in a file. \n");

    string filename = get_string("\nPlease enter file NAME including .txt ");
    int filesize = get_int("\nHow many lines to be printed? ");
    printf("\n");
    FILE *file = (fopen(filename, "r"));
    if (!file)
    {
        printf("Unable to open: %s\n", filename);
    }

    char option[filesize][10]; // array to put all the numbers form the file
    for (int i = 0; i < filesize; i++)
    {
        fscanf(file, "%s", option[i]);
    }
    fclose(file);
    for (int i = 0; i < filesize; i++)
    {
        printf("%s\n", option[i]);
    }
    printf("\nTIP: Any unusual characters may be cause by wanting more lines than the text has\n");
}
