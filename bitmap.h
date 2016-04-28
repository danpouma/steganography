#ifndef BITMAP_H
#define BITMAP_H

#include <stdio.h>
#include <stdlib.h>

typedef struct bitmap BITMAP; 
typedef struct header HEADER; //bitmap file header
typedef struct info INFO; //bitmap image info header


typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;

//uncomment pixel_32 type def and comment pixel_24 to use 32 bit
//typedef struct pixel_32 PIXEL; //Pixel if using 32 bit bmp
typedef struct pixel_24 PIXEL; //pixel if using 24 bit bmp

//-------END TYPEDEF---------

//--------STRUCTURES--------

struct bitmap
{
	HEADER* header; //bitmap file header
	INFO* info; //bitmap image info header
	BYTE* extra; //color table, padding, etc
	PIXEL* data; //image data
};

#pragma pack(push, 1)
struct header //14 bytes - info aabout the file
{
	WORD signature; //BM for bitmap
	DWORD file_size; //Size of the entire BMP file
	WORD reserved1;  //reserved; must be 0
	WORD reserved2;  //reserved; must be 0
	DWORD offset; //the location of the image data
};
#pragma pack(pop)

#pragma pack(push, 1)
struct info //40 bytes - info about the image
{
	DWORD struct_size; //size of this struct - 40 bytes
	DWORD width;//width of the image
	DWORD height;//height of the image
	WORD planes;//layers in image
	WORD bitcount;//number of bits per pixel
	DWORD compression;///spcifies the type of compression
	DWORD img_size;  //size of image in bytes
	DWORD x_pixels_meter; //number of pixels per meter in x axis
	DWORD y_pixels_meter; //number of pixels per meter in y axis
	DWORD colors_used; //number of colors used in the bitmap
	DWORD important_colors; //number of important colors
};
#pragma pack(pop)

#pragma pack(push, 1)
struct pixel_24  //24 bit pixel,
{
	BYTE blue;
	BYTE green;
	BYTE red;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct pixel_32 //32 bit pixel
{
	BYTE alpha; //only for 32 bit bmp
	BYTE blue;
	BYTE green;
	BYTE red;
};
#pragma pack(pop)

BITMAP* read_bitmap(char* file);
void write_bitmap(char* file, BITMAP* bitmap);
void print_bits( BYTE color );

#endif // BITMAP_H