#include <stdio.h>
#include <cs50.h>


int main(int argc, char *argv[])
{
    // if there is not 2 arguements return error
    if (argc != 2)
    {
        fprintf(stderr, "Please enter one arguement\n");
        return 1;
    }

    // Create a raw_files for recovering , read as the infile
    FILE *raw_files = fopen(argv[1], "r");

    // If file is not found then let the user know
    if (raw_files == NULL)
    {
        fprintf(stderr, "Couldn't open %s\n", argv[1]);
        return 1;
    }

    //Create outfile
    // Similar to how resize was with their infile and outfile
    FILE *reso = NULL;

    // Making a buffer
    unsigned char buffer[512];

    // Setting a statement or indication of when an Image is found
    bool image = false;

    // jpeg counter
    int counter = 0;

    // create array for jpgs
    char jpgs[10];

    // reads the 512 bytes in a block
    while (fread(buffer, 512, 1, raw_files) == 1)
    {
        // checks if either beginning or end of the jpeg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (image == true)
            {
                fclose(reso);
            }
            else
            {
                image = true;
            }
            sprintf(jpgs, "%03i.jpg", counter);
            reso = fopen(jpgs, "w");
            counter++;
        }

        if (image == true)
        {
            fwrite(buffer, 512, 1, reso);
        }
    }

    // close open or remaining files
    fclose(raw_files);
    fclose(reso);

    return 0;

}