#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    /* code */
    char *filename = (char *)argv[1];

    FILE *binFile;
    binFile = fopen(filename, "rb");         // Open the file
    fseek(binFile, 0, SEEK_END);             //
    long int res = ftell(binFile);           // Read the bytes
    printf("File size %li:\n", res);         // Info
    char *buffer = new char[res];            // Set the buffer for reading
    rewind(binFile);                         // Rewind file
    if (buffer == NULL)                      //
    {                                        //
        fputs("Memory error\n", stderr);     // Check for memory errors
        exit(2);                             // Exit if true
    }                                        //
    size_t result;                           //
    result = fread(buffer, 1, res, binFile); // Read the file.
    if (result != res)                       //
    {                                        //
        fputs("Reading error\n", stderr);    // Check for errors
        exit(3);                             // Exit if true
    }                                        //
    fclose(binFile);                         // Close the file
    // It will read all the file because we set the buffer size to the actual size of the file
    // Calculate the header
    char *header = (char *)malloc(sizeof(unsigned char) * 6);
    for (long int i = 0; i < 6; i++)
    {
        header[i] = buffer[4 + i];
    }
    if (strcmp(header, "ftypqt") || strcmp(header, "ftypmp"))
    {
        std::cout << "Good file format." << std::endl;
    }
    else
    {
        exit(1);
    }
    free(header);
    // Let's look for the atoms
    long int topADDRS, lowADDRS;
    topADDRS = 0;
    lowADDRS = 0;
    for (long int i = 0; i < res; i++)
    {
        // Looking for mdat & moov
        if (buffer[i] == 'm')
        {
            if (buffer[i + 1] == 'd' && buffer[i + 2] == 'a' && buffer[i + 3] == 't')
            {
                topADDRS = i;
            }
            if (buffer[i + 1] == 'o' && buffer[i + 2] == 'o' && buffer[i + 3] == 'v')
            {
                lowADDRS = i;
            }
        }
    }
    if (topADDRS == 0 || lowADDRS == 0)
    {
        std::cout << "Did not catch that address" << std::endl;
        exit(1);
    }

    std::cout << "Top addrs: " << topADDRS << "\nLow addrs: " << lowADDRS << std::endl;
    // Set the can edit zone
    unsigned int heap = 80 * 16;
    long int iterator = lowADDRS - topADDRS - heap;
    long int lowNoEdit = topADDRS + heap;
    long int timesEdited = 0;
    long int rng, lowStart, highEnd, diff, r;
    r = 0;
    sscanf(argv[2], "%li", &rng);
    sscanf(argv[3], "%li", &lowStart);
    sscanf(argv[4], "%li", &highEnd);
    sscanf(argv[5], "%li", &diff);
    if (highEnd > iterator || highEnd == 0)
    {
        highEnd = iterator;
    }
    printf("Editing from %li.\n", lowStart);
    printf("Editing to %li.\n", highEnd);
    for (long int i = lowStart; i < highEnd; i++)
    {
        if (r == rng)
            r = 1;
        if (r == 1)
        {
            for (int ii = 0; ii < diff; ii++)
            {
                buffer[lowNoEdit + i + ii] = buffer[lowNoEdit + i];
            }
            for (int ii = 0; ii < diff; ii++)
            {
                buffer[lowNoEdit + i + ii] = buffer[lowNoEdit + i - diff - diff];
            }

            timesEdited++;
        }
        r++;
    }
    printf("Edited %i times.\n", timesEdited);
    // Build the output file
    FILE *write_ptr;
    write_ptr = fopen("out.mov", "wb");
    unsigned int signal = fwrite(buffer, sizeof(char), res, write_ptr);
    fclose(write_ptr);
    delete[] buffer;
    if (res == signal)
    {
        std::cout << "Good Write" << std::endl;
    }
    else
    {
        std::cout << "Bad Write" << std::endl;
        return 4;
    }
    return 0;
}
