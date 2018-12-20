# Questions

## What's `stdint.h`?

Header file from the Standard C Library, Means available to all C code

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

 ensure that memory allocation is optimized for the numbers returned in this function and set boundaries on the input and output numbers.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

BYTE = 8, DWORD = 32, LONG = 32, WORD = 16;

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

BM

## What's the difference between `bfSize` and `biSize`?

bfSize is for the size of the bitmap file in bytes and biSize is the size of the bitmap file in pixels

## What does it mean if `biHeight` is negative?

If biHeight is negative, the image's origin is in the lower-left corner

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitcount

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

fopen will return NULL if either the input file or output file cannot be opened for reading or writing respectively.

## Why is the third argument to `fread` always `1` in our code?

Always read one pixel at a time

## What value does line 65 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

1

## What does `fseek` do?

fseek sets the file position of a stream to a given offset value. In this situation,
fseek checks for any padding in the bmp file and skips over it, so as not to distort the image.

## What is `SEEK_CUR`?

is a fseek function constant, moves the file pointer position to a custom giving location within the file.

## Whodunit?

It was professor plum with the candlestick in the library
