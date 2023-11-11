#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading
    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Read header
    WAVHEADER header;
    fread(&header, sizeof(WAVHEADER), 1, input);

    // Use check_format to ensure WAV format
    if (check_format(header) == 0)
    {
        printf("Invalid WAV Format\n");
        return 1;
    }

    // Open output file for writing
    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not write file.\n");
        return 1;
    }

    // Write header to file
    fwrite(&header, sizeof(WAVHEADER), 1, output);

    // Use get_block_size to calculate size of block
    int size = get_block_size(header);

    BYTE buffer[size];

    int counter = 1;
    int position = ftell(input);

    fseek(input, 0, SEEK_END);

    fseek(input, 0 - size, SEEK_END);

    while (ftell(input) > (sizeof(WAVHEADER) - size))
    {

        int sizeb = get_block_size(header);

        counter++;

        fread(&buffer, sizeb, 1, input);

        fwrite(&buffer, sizeb, 1, output);



        fseek(input, 0 - (size * 2), SEEK_CUR);

    }

    fclose(input);
    fclose(output);
    return 0;
}

int check_format(WAVHEADER header)
{

    for (int i = 0; i < 4; i++)
    {

        BYTE wave[] = {'W', 'A', 'V', 'E'};
        if (header.format[i] != wave[i])
        {
            return 0;
        }
    }
    return 1;
}

int get_block_size(WAVHEADER header)
{
    int s = header.numChannels * (header.bitsPerSample / 8);
    return s;
}
