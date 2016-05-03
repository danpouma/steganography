#include <stdio.h>
#include <stdlib.h>
#include "bitmap.h"


int main(int argc, char** argv)
{
	BITMAP* bmp = NULL;
	char* in_file_name;
	char* out_file_name;
	
	int error;

	// Verify the user input
	if(argc < 2)
	{
		puts("ERROR: Program Input");
		error = 1;
	}
	else
	{ 
		// No error...
		error = 0;

		// Get the file names from arguments
		in_file_name = argv[1];
		out_file_name = argv[2];

		// Read the bmp via file name
		bmp=read_bitmap(in_file_name);

		// Verify the bmp file was loaded properly
		if(bmp == NULL)
		{
			error = 1;
			puts("ERROR: Loading File");
		}
	}

	if( !error )
	{
		//things look ok
		//Visit Every Pixel
		int i;
		int num_pixels = bmp->info->width * bmp->info->height;

		//test variable to track num of valid pixels for data hiding
		int numberOfPixelsForHiding = 0;

		// Loop once to see the data
		for (int pixel = 0; pixel < num_pixels; pixel++)
		{
			//create a pixel pointer for first image
			PIXEL* p;

			// As of right now I'm considerring
			// pixels with value greater than 10
			// as valid for flipping the bit
			// without affecting the pixel to the 
			// naked eye
			p = (bmp->data + pixel);

			if (p->red > 10)
			{	
				print_bits(p->red);
				numberOfPixelsForHiding++;
			}

			if (p->blue > 10)
			{
				print_bits(p->blue);
				numberOfPixelsForHiding++;
			}

			if (p->green > 10)
			{
				print_bits(p->green);
				numberOfPixelsForHiding++;
			}
		}

		puts("");

		// Total number of available pixels
		printf("%d\n", numberOfPixelsForHiding);
		printf("%d\n",numberOfPixelsForHiding / 8);
		puts("");

		//write the bmp to a file
		//write_bitmap(out_file_name, bmp);
	}

	return 0;
}