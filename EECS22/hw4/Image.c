/*Author: Daisuke Otagiri
 * ID#: 12823053
 * Image.c file*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Image.h"
#include "Constants.h"
#include "FileIO.h"

#include <assert.h>

/* Get the R intensity of pixel (x, y) in image */
unsigned char GetPixelR(const IMAGE *image, unsigned int x,  unsigned int y)
{
	/*assertions for image, intensity values, and borders*/
	assert(image);
	assert(image->R);
	assert(image->G);
	assert(image->B);
	assert(x<=(image->W));
	assert(y<=(image->H));

	unsigned char tempR;
	tempR = image->R[x+y*(ImageWidth(image))];
	return tempR;
}
/* Get the G intensity of pixel (x, y) in image */
unsigned char GetPixelG(const IMAGE *image, unsigned int x,  unsigned int y)
{
	/*assertions for image, intensity values, and borders*/
	assert(image);
	assert(image->R);
	assert(image->G);
	assert(image->B);
	assert(x<=(image->W));
	assert(y<=(image->H));

	unsigned char tempG;
	tempG = image->G[x+y*(ImageWidth(image))];
	return tempG;
}

/* Get the B intensity of pixel (x, y) in image */
unsigned char GetPixelB(const IMAGE *image, unsigned int x,  unsigned int y)
{
	/*assertions for image, intensity values, and borders*/
	assert(image);
	assert(image->R);
	assert(image->G);
	assert(image->B);
	assert(x<=(image->W));
	assert(y<=(image->H));

	unsigned char tempB;
	tempB = image->B[x+y*(ImageWidth(image))];
	return tempB;
}

/* Set the R intensity of pixel (x, y) in image to r */
void SetPixelR(IMAGE *image, unsigned int x,  unsigned int y, unsigned char r)
{
	/*assertions for image, intensity values, and borders*/
	assert(image);
	assert(image->R);
	assert(image->G);
	assert(image->B);
	assert(x<=(image->W));
	assert(y<=(image->H));

	image->R[x+y*(ImageWidth(image))] = r; 
}
/* Set the G intensity of pixel (x, y) in image to g */
void SetPixelG(IMAGE *image, unsigned int x,  unsigned int y, unsigned char g)
{
	assert(image);
	assert(image->R);
	assert(image->G);
	assert(image->B);
	assert(x<(image->W));
	assert(y<(image->H));

	image->G[x+y*(ImageWidth(image))] = g;
}
/* Set the B intensity of pixel (x, y) in image to b */
void SetPixelB(IMAGE *image, unsigned int x,  unsigned int y, unsigned char b)
{
	assert(image);
	assert(image->R);
	assert(image->G);
	assert(image->B);
	assert(x<(image->W));
	assert(y<(image->H));

	image->B[x+y*(ImageWidth(image))] = b;
}
/* Allocate the memory space for the image structure and the memory spaces for the */ 
/* color intensity values. Return the pointer to the image, or NULL in case of error */
IMAGE *CreateImage(unsigned int Width, unsigned int Height)
{
	IMAGE *image;
	image = malloc(sizeof(IMAGE));
	if (!image) /*check if memory for image is left*/
		{
		perror("Out of memory. Aborting. . .");
		exit(10);
		} /*fi*/	

	/*allocate width and height*/
	image->W = Width;
	image->H = Height;
	
	/*allocate memory for unsigned char RGB values*/
	image->R = malloc(sizeof(unsigned char)*Width*Height);
	image->G = malloc(sizeof(unsigned char)*Width*Height);
	image->B = malloc(sizeof(unsigned char)*Width*Height);
	
	return(image);	
}
/* Release the memory spaces for the pixel color intensity values Deallocate all the */
/* memory spaces for the image. Set R/G/B pointers to NULL */
void DeleteImage(IMAGE *image)
{
	assert(image);

	/*freeing RGB values*/
	free(image->R);
	free(image->G);
	free(image->B);

	/*free image*/
	free(image);
}
/* Return the image's width in pixels */
unsigned int ImageWidth(const IMAGE *image)
{
	return image->W;	
}
/* Return the image's height in pixels */
unsigned int ImageHeight(const IMAGE *image)
{
	return image->H;	
}
/*EOF Image.c*/
