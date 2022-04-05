#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

const int BLOCK_SIZE = 512;

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Error handling: user passed none or more than one command line argument
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        // If could not open file to read
        return 1;
    }

    // Buffer to store the bytes of a block
    BYTE buffer[BLOCK_SIZE];

    // Counter to help naming jpg files
    int counter = 0;

    // string that stores the name of files
    char filename[8];

    // Flag to know when an image is being copied
    int started = 0;

    sprintf(filename, "%03i.jpg", counter);
    FILE *img = fopen(filename, "w");

    while (fread(buffer, 1, BLOCK_SIZE, input))
    {
        // Check if it's the beginning of a new block
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // If it's the first img, just write data into the already opened file
            if (counter == 0)
            {
                fwrite(buffer, 1, BLOCK_SIZE, img);
                started = 1;
                counter++;
            }

            // From the second and so on, close the last file, open a new one and write to it
            else
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", counter);
                img = fopen(filename, "w");

                fwrite(buffer, 1, BLOCK_SIZE, img);
                counter++;
            }
        }

        // If it's not a new img, just write the data to the file
        else if (started == 1)
        {
            fwrite(buffer, 1, BLOCK_SIZE, img);
        }
    }

    fclose(img);
    fclose(input);
}