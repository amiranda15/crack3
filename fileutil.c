#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileutil.h"

// Load the text file from the given filename.
// Return a pointer to the array of strings.
// Sets the value of size to be the number of valid entries in the array .
char (*loadFile2D(char *filename, int *size))[COLS]
{
    FILE *in = fopen(filename, "r");
    if (!in)
    {
        perror("Can't open file");
        exit(1);
    }

    int cap = 10;
    char (*arr)[COLS] = malloc(cap * sizeof(*arr));

    if (!arr)
    {
        perror("malloc failed");
        fclose(in);
        exit(1);
    }

    *size = 0;

    while (fgets(arr[*size], COLS, in))
    {
        char *nl = strchr(arr[*size], '\n');
        if (nl) *nl = '\0';

        (*size)++;

        if (*size >= cap)
        {
            cap *= 2;
            char (*temp)[COLS] = realloc(arr, cap * sizeof(*arr));
            if (!temp)
            {
                perror("realloc failed");
                free(arr);
                fclose(in);
                exit(1);
            }
            arr = temp;
        }
    }

    fclose(in);
    return arr;
}

// Searches the array for the target string using exact match.
char *exactSearch2D(char *target, char (*arr)[COLS], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (strcmp(arr[i], target) == 0)
        {
            return arr[i];
        }
    }
    return NULL;
}

// Frees the memory used by the 2D array.
void free2D(char (*arr)[COLS])
{
    free(arr);
}