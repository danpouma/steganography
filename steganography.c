#include <stdio.h>
#include <stdlib.h>
#include "bitmap.h"


int main(int argc, char** argv)
{
	BITMAP* bmp = NULL;
	char* in_file_name;
	char* out_file_name;

	FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("sample.txt", "r");
    if (fp == NULL)
    {
        exit(EXIT_FAILURE);
    }
	
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

			while ( (read = getline(&line, &len, fp) ) != -1 ) 
		    {
		        printf("Retrieved line of length %zu :\n", read);
		        printf("%s", line);

		        for (int i = 0; i < read; i++)
		        {
		        	for ( int bit = (8 * sizeof(BYTE))-1; bit >= 0; bit-- )
					{
						// Convert  to int
						int convertedLine = line[i] - '0';
						int currentBit = (convertedLine >> bit) & 1;
						
						if (currentBit == 0)
						{
							// Clear least sig bit to 0
							p->red &= ~(1 << 0);
							printf("%d\n", (p->red >> 0) & 1);
						}
						else
						{
							// Set least sig bit to 1
							p->red |= 1 << 0;
							printf("%d\n", (p->red >> 0) & 1);
						}
						p = (bmp->data + pixel);
						pixel++;
					}
					puts( "" );

					p = (bmp->data + pixel);
					pixel++;
		        }
		    }

		    p = (bmp->data + pixel);

		    fclose(fp);
		    if (line)
		    {
		        free(line);
		    }

		    p = (bmp->data + pixel);
		}

		puts("");

		// Total number of available pixels
		printf("%d\n", numberOfPixelsForHiding);
		printf("%d\n",numberOfPixelsForHiding / 8);
		puts("");

		//write the bmp to a file
		write_bitmap(out_file_name, bmp);
	}

	return 0;
}
/*

		// Load text file
		
		FILE *fp;
		char buff[255];

		fp = fopen("/sample.txt", "r");
		fscanf(fp, "%s", buff);
		printf("1 : %s\n", buff );

		fgets(buff, 255, (FILE*)fp);
		printf("2: %s\n", buff );

		fgets(buff, 255, (FILE*)fp);
		printf("3: %s\n", buff );
		fclose(fp);
		

		
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

			//char* message = "This is a test";

			

			//int currentBit = 0;//(number >> x) & 1;

			// Clear least sig bit to 0
			p->red &= ~(1 << 0);
			p->blue &= ~(1 << 0);
			p->green &= ~(1 << 0);
		
		
			// Set least sig bit to 1
			p->red |= 1 << 0;	
			p->blue |= 1 << 0;
			p->green |= 1 << 0;
			

			print_bits(p->red);
			print_bits(p->blue);
			print_bits(p->green);	

			// Start at data
			p = (bmp->data + pixel);
		}

		puts("");


		//write the bmp to a file
		//write_bitmap(text_file_name, bmp);
	}

	return 0;
}
*/