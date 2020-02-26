#include <stdio.h>
#include <stdlib.h>
#include "bunker.h"
#include "country.h"
#include "countries.h"

#define FILE_ERR_CODE 1
#define FILE_ERR_MESS "Error opening file"

FILE* openFile(char* name, char* mode)
{
    FILE* newFile = fopen(name, mode);
    if(newFile==NULL)
    {
        perror(FILE_ERR_MESS);
        exit(FILE_ERR_CODE);
    }
    return newFile;
}

int main() {
    FILE* inFile = openFile("input.dat", "r");
    FILE* outFile = openFile("output.dat", "w");

    Bunker myBunker = createBunker();
    readDataOfBunker(&myBunker, inFile);
    allCountries myCountries = createAllCountries();
    readDataOfAllCountries(&myCountries, inFile);

    Country strongestC = strongestCountry(&myCountries);
    int strongestCanWinAlone = canDefeatAlone(&strongestC, &myBunker) + 1 >= size(&myBunker.sentinels);

    attackWhileNeeded(&myCountries, &myBunker);

    if(isDefeated(&myBunker))
    {
        fprintf(outFile, "The tyrant was killed!\n");
        fprintf(outFile, "The last hit was done by %s\n", myCountries.countryWithHBlow.name);
    }
    else fprintf(outFile, "The tyrant was NOT killed!\n");

    fprintf(outFile, "The strongest country was: %s\n", strongestC.name);
    fprintf(outFile, "The weakest country was: %s\n", weakestCountry(&myCountries).name);

    if(strongestCanWinAlone) fprintf(outFile, "The strongest country could have defeated all the sentinels alone\n");
    else fprintf(outFile, "No country could have defeated all the sentinels.\n");

    return 0;
}