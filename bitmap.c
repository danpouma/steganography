#include <stdio.h>
#include <stdlib.h>
#include "bitmap.h"

void print_bits( BYTE color )
{
	for ( int i = (8 * sizeof(BYTE))-1; i >= 0; i-- )
	{
		printf( "%u", ( (color >> i) & 1) );
	}
	puts( "" );
}

//-----FUNCTIONS----

/**
* loads a bitmap file into memory
* pre: a c string representing a path to the file
* post: a pointer to a BITMAP struct
***/
BITMAP* read_bitmap(char* file)
{
	FILE *in_file = NULL;

	//pointer for bitmap struct
	BITMAP* bmp = malloc(sizeof(BITMAP));

	//initialize bmp struct
	bmp->header = malloc(sizeof(HEADER));
	bmp->info = malloc(sizeof(INFO));
	bmp->extra = NULL;
	bmp->data = NULL;

	int error = 0;

	in_file = fopen(file,"rb");
	if(in_file==NULL)
	{
		puts("ERROR: no input file found");
		error = 1;
	}
	else
	{
		//file exists
		//try reading the header and info header
		fread(bmp->header, sizeof(HEADER), 1, in_file);

		//
		fread(bmp->info, sizeof(INFO), 1, in_file);
	}

	//File loaded and data is bitmap
	if(error == 0)
	{
		//collect everything between the header/info and the img data
		//color table, padding, etc
		int size  = bmp->header->offset - sizeof(HEADER) - sizeof(INFO);
		bmp->extra = malloc(size);
		fread(bmp->extra, size, 1, in_file);

		//collect the actual image data
		bmp->data = malloc(bmp->info->img_size);
		fread(bmp->data, bmp->info->img_size, 1, in_file);

		//PRINT some bitmap info
		puts("--------------");
		puts("BITMAP INFO");
		puts("--------------");
		printf("Name: %s\n", file);
		printf("BitCount:\t%d\n",bmp->info->bitcount);
		printf("Image Size:\t%.2fMB\n",bmp->info->img_size/1000000.0);//B to MB
		printf("Image Width:\t%d\n",bmp->info->width);
		printf("Image Height:\t%d\n",bmp->info->height);
		printf("Image offset:\t%d\n",bmp->header->offset);
		puts("--------------");

	}
	else
	{
		//something went wrong
		//clean up what has been allocated
		//and set bmp (return value) to NULL
		free(bmp->header);
		free(bmp->info);
		free(bmp);
		bmp = NULL;
	}

	//close the file and return bitmap or NULL
	fclose(in_file);
	return bmp;
}

/**
* write a bitmap file into memory
* pre: a c string representing a path to the file and a bitmap struct
*      a file is created if it does not exist.
* post: nothing
***/
void write_bitmap(char* file, BITMAP* bmp)
{
	FILE *out_file;
	//if file does not exist, create it
	out_file = fopen(file,"wb+");

	int size  = bmp->header->offset - sizeof(HEADER) - sizeof(INFO);

	//write all the parts
	fwrite(bmp->header, sizeof(HEADER), 1, out_file);
	fwrite(bmp->info, sizeof(INFO), 1, out_file);
	fwrite(bmp->extra, size, 1, out_file);
	fwrite(bmp->data, bmp->info->img_size, 1, out_file);

	//close the file
	fclose(out_file);
}