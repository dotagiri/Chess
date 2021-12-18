/*Author: Daisuke Otagiri
 * ID#: 12823053
 * Program includes all Digital Image Processes*/

#include "DIPs.h"
#include "Image.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>

/* Example of DIP */
/* make the picture color black & white */

/* make the picture color black & white */
IMAGE *BlackNWhite(IMAGE *image)
{
	assert(image);
    int x, y;
	
	unsigned char temp;
	/*assert image pointer*/
	assert(image);	

    for (x = 0; x < ImageWidth(image); x++)
	    {	   
		for(y = 0; y < ImageHeight(image); y++)
			{   
				temp = (GetPixelR(image, x, y) + GetPixelG(image, x, y) + GetPixelB(image, x, y))/3;
				SetPixelR(image, x, y, temp);
				SetPixelG(image, x, y, temp);
				SetPixelB(image, x, y, temp);
			} /*rof*/
		} /*rof*/		
	return image;
}

// Sharpen function
IMAGE *Sharpen(IMAGE *image)
{
	assert(image);
    int x, y;
    int tmpr = 0, tmpg = 0, tmpb = 0;
    unsigned char R_temp[ImageWidth(image)][ImageHeight(image)];
    unsigned char G_temp[ImageWidth(image)][ImageHeight(image)];
    unsigned char B_temp[ImageWidth(image)][ImageHeight(image)];

	/*assert image pointer*/
	assert(image);

    for (x = 0; x < ImageWidth(image); x++)
    {   for(y = 0; y < ImageHeight(image); y++)
        {   R_temp[x][y] = GetPixelR(image, x, y);
            G_temp[x][y] = GetPixelG(image, x, y);
            B_temp[x][y] = GetPixelB(image, x, y);
        } /*rof*/
    } /*rof*/
    for (x = 1; x < ImageWidth(image) - 1; x++)
    {   for (y = 1; y < ImageHeight(image) - 1; y++)
        {   tmpr = 9 * GetPixelR(image,x,y) - GetPixelR(image,x-1,y-1) - GetPixelR(image,x-1,y) - GetPixelR(image,x-1,y+1) - GetPixelR(image,x,y-1) - GetPixelR(image,x,y+1) - GetPixelR(image,x+1,y-1) - GetPixelR(image, x+1, y) -
		GetPixelR(image,x+1,y+1);

            tmpg = 9 * GetPixelG(image, x, y) - GetPixelG(image, x-1, y-1) - GetPixelG(image, x-1, y) - GetPixelG(image, x-1, y+1) - GetPixelG(image, x, y-1) - GetPixelG(image, x, y+1) - GetPixelG(image, x+1, y-1) - 
		GetPixelG(image, x+1, y) - GetPixelG(image, x+1, y+1);

            tmpb = 9 * GetPixelB(image, x, y) - GetPixelB(image, x-1, y-1) - GetPixelB(image, x-1, y) - GetPixelB(image, x-1, y+1) - GetPixelB(image, x, y-1) - GetPixelB(image, x, y+1) - GetPixelB(image, x+1, y-1) -
		GetPixelB(image, x+1, y) - GetPixelB(image, x+1, y+1);

        R_temp[x][y] = (tmpr > 255)?255:(tmpr < 0)?0:tmpr;
        G_temp[x][y] = (tmpg > 255)?255:(tmpg < 0)?0:tmpg;
        B_temp[x][y] = (tmpb > 255)?255:(tmpb < 0)?0:tmpb;
        tmpr = tmpg = tmpb = 0;
        } /*rof*/	
    } /*rof*/
    for (x = 0; x < ImageWidth(image); x++)
    {   for(y = 0; y < ImageHeight(image); y++)
        {	SetPixelR(image, x, y, R_temp[x][y]);
		SetPixelG(image, x, y, G_temp[x][y]);
		SetPixelB(image, x, y, B_temp[x][y]);
        } /*rof*/
    } /*rof*/
	return image;
}


// Hue function
IMAGE *Hue(IMAGE *image, int degree)
{
	assert(image);
    int x, y;
    double a, b, r;
    double d = degree * PI / 180.0;
    double tmp_r, tmp_g, tmp_b;	
	double new_tempR, new_tempG, new_tempB;

	/*assert image pointer*/
	assert(image);
    a = (2 * cos(d) + 1.0) / 3.0;
    b = (1.0 - cos(d)) / 3.0 - sin(d) / sqrt(3.0);
    r = (1.0 - cos(d)) / 3.0 + sin(d) / sqrt(3.0);

    for (x = 0; x < WIDTH; x++)
    {   for (y = 0; y < HEIGHT; y++)
        {   tmp_r = GetPixelR(image, x, y) * a + GetPixelG(image, x, y) * b + GetPixelB(image, x, y) * r;
            tmp_g = GetPixelR(image, x, y) * r + GetPixelG(image, x, y) * a + GetPixelB(image, x, y) * b;
            tmp_b = GetPixelR(image, x, y) * b + GetPixelG(image, x, y) * r + GetPixelB(image, x, y) * a;


	    new_tempR =  (tmp_r > 255)?255:(tmp_r < 0)?0:tmp_r;
            new_tempG = (tmp_g > 255)?255:(tmp_g < 0)?0:tmp_g;
            new_tempB = (tmp_b > 255)?255:(tmp_b < 0)?0:tmp_b;

		SetPixelR(image, x, y, new_tempR);
		SetPixelG(image, x, y, new_tempG);
		SetPixelB(image, x, y, new_tempB); 
        } /*rof*/
    } /*rof*/
	
	return image;
}



/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
