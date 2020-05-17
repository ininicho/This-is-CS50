#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    typedef uint8_t  BYTE;

    //Checks command line input
    if (argc != 2)
    {
        printf("Usage: ./recover [filename].\n");
        return 1;
    }

    //Open SD Card
    FILE *infile = fopen(argv[1], "r");
    FILE *outfile = NULL;

    BYTE buffer[512];
    char filename[10];
    int numfile = 0;
    int checkfound = 0;


    if (infile == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    //Read the file
    while (fread(&buffer, sizeof(BYTE), 512, infile) == 512)
    {
        //Search for JPEG starting byte
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //Check whether a new file is found, and closes the old one
            if (checkfound == 1)
            {
                fclose(outfile);
            }

            else
            {
                checkfound = 1;
            }

            //Create Output File
            sprintf(filename, "%03i.jpg", numfile);
            outfile = fopen(filename, "w");
            numfile++;
        }

        if (checkfound == 1)
        {
            fwrite(buffer, sizeof(BYTE), 512, outfile);
        }
    }

    fclose(infile);
    fclose(outfile);
}
