#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "md5.h"
#include "fileutil.h"

#define PASS_LEN 50     // Maximum length any password will be.

int main(int argc, char *argv[])
{
    if (argc < 3) 
    {
        printf("Usage: %s hash_file dictionary_file\n", argv[0]);
        exit(1);
    }

    // TODO1: Read the hashes file into a 2D array.
    int size;
    char (*hashes)[HASH_LEN] = loadFile2D(argv[1], &size);

    // TODO2: Open the dictionary file for reading.
    FILE *dict = fopen(argv[2], "r");
    if (!dict)
    {
        perror("Failed to open dictionary file");
        exit(1);
    }

    char line[PASS_LEN];
    int cracked = 0;

    // TODO3: Loop through each password in the dictionary.
    while (fgets(line, sizeof(line), dict))
    {
        // Remove newline
        char *nl = strchr(line, '\n');
        if (nl) *nl = '\0';

        // Hash the password
        char *hashStr = md5(line, strlen(line));

        //  linear search to see if the hash is in the list
        if (exactSearch2D(hashStr, hashes, size))
        {
            printf("%s => %s\n", hashStr, line);
            cracked++;
        }

        free(hashStr);
    }

    // TODO4: Close file, free memory, print total found
    fclose(dict);
    free2D(hashes);
    printf("Total cracked: %d\n", cracked);

    return 0;
}