// Copies a BMP file .. for Resize of bitmap files
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

    // converts 'n' which is the resizer into an integer
    int n = atoi(argv[1]);
    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // resize must be positive and should be less then or equal to 100
    if(n < 0 || n > 100)
    {
        fprintf(stderr, "Resize must be in the range of [1 - 100]\n");
        return 1;
    }



    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);


    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi, Bih;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // creates new infiles for BitmapInfo
    // Used to rescale the width and height for the bitmap


    // Times the width and height of the small.bmp based on the number put for n (this goes for both Width and Height)
    // changes size of bitmap Horizontally and Vertically by n
    Bih.biWidth = bi.biWidth * n;
    Bih.biHeight = abs(bi.biHeight) * n;

    printf("width: %i height: %i\n", Bih.biWidth, Bih.biHeight);

    int outPadding = (4 - (Bih.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    //   Overall grabbing the Sizeimage (in pixels) using the RGBTRIPLE and adding the outfile of BitmapInfo and padding
    //   Computing the absolute value of biHeight for the outfile
    Bih.biSizeImage = ((sizeof(RGBTRIPLE) * Bih.biWidth) + outPadding) * abs(Bih.biHeight);
    bf.bfSize = Bih.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    printf("%i %i\n", Bih.biSizeImage, bf.bfSize);


// ensure infile is (likely) a 24-bit uncompressed BMP 4.0

    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);


    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);


    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;



    // temporary storage
    RGBTRIPLE triple;


    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // each row will be printed out n times
        int rowcounter = 0;

        while(rowcounter < n)
        {

        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {


                // printf("%i\n", j);

                // each pixel will be printed out n times
                int pixelCounter = 0;

               // read RGB triple from infile
               fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                while(pixelCounter < n)
                {
                   // write RGB triple to outfile
                   fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                   pixelCounter++;
                }
        }


        // add new padding
        for (int k = 0; k < outPadding; k++)

            fputc(0x00, outptr);

            if(rowcounter < (n - 1))

                 fseek(inptr, -(Bih.biWidth * sizeof(RGBTRIPLE)), SEEK_CUR);
                 rowcounter++;


        }

    // skip over padding, if any
    fseek(inptr, padding, SEEK_CUR);

    }



    // Empty space to store memory in which is the value of the address of solution
    // realloc(solution);

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
