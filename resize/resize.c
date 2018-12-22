// Copies a BMP file

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

    // remember filenames
    int *n = malloc(sizeof(int));
    *n = atoi(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];


    if (*n < 0 || *n > 100)
    {
        fprintf(stderr, "Range must consist of [1- 100]\n");
        return 5;
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
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);






    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    BITMAPFILEHEADER Bfh;
    Bfh = bf;

    BITMAPINFOHEADER Bih;
    Bih = bi;
    // Horizontally(Width) and Vertically(Height) by n
    Bih.biWidth = bi.biWidth * *n;
    Bih.biHeight = (bi.biHeight * *n);

    printf("Width: %i Height: %i\n", bi.biWidth, bi.biHeight);

    // determine padding for scanlines
    int outPadding = (4 - (Bih.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // Calculates the image the file relating to pixels
    // Same process but for the file in bytes
    Bih.biSizeImage = (Bih.biWidth * sizeof(RGBTRIPLE) + outPadding) * abs(Bih.biHeight);
    printf("Resized Image: %i\n", Bih.biSizeImage);

    // specific number of bytes the header takes up
    Bfh.bfSize = Bih.biSizeImage + 54;

    // write outfile's BITMAPFILEHEADER
    fwrite(&Bfh, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&Bih, sizeof(BITMAPINFOHEADER), 1, outptr);



    // iterate over infile's scanlines
    for (int sLine = 0, biHeight = abs(bi.biHeight); sLine < biHeight; sLine++)
    {


        // iterate over rows in scanline
        for (int rows = 0; rows < *n; rows++)
        {
            // printf("%i\n", rows);


            // iterate over pixels in scanline
            for (int pixels = 0; pixels < bi.biWidth; pixels++)
            {
                //  printf("%i\n", pixels);

                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                for (int pixell = 0; pixell < *n; pixell++)
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }

                printf("%i%i%i\n", triple.rgbtRed, triple.rgbtGreen, triple.rgbtBlue);
            }

            // skip over padding, if any
            fseek(inptr, padding, SEEK_CUR);

            // then add it back (to demonstrate how)
            for (int k = 0; k < outPadding; k++)
            {
                fputc(0x00, outptr);
            }

            if (rows < *n - 1)
            {
                // send the infile cursor back, IF n is less an -1 as well as
                // # of bytes for cursor to go back
                long off = bi.biWidth * sizeof(RGBTRIPLE) + padding;
                fseek(inptr, -off, SEEK_CUR);
            }
        }
    }

    // allocating n
    free(n);

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
