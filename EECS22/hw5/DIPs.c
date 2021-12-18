/*********************************************************************/
/* 02/27/20 Bo Tsai      updated for EECS22 assignment Winter2020    */
/* Author: Tim Schmidt Date: 11/09/2017                              */
/*                                                                   */
/* DIPs.c: source file for DIP operations                            */
/*                                                                   */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "DIPs.h"
#include "Constants.h"
#include <math.h>

IMAGE *BlackNWhite(IMAGE *image, int percent)
{
	assert(image);
	int x, y;
	/*variable declarations for hw5*/
	int gray;
	int R,G,B;
	int R_offset, G_offset, B_offset;
	float new_R, new_G, new_B;
	float percentage;
	/*convert percent to 0.0-1.0*/
  	percentage = (float)percent/100;

	for (x = 0; x < image->W; x++){
        	for(y = 0; y < image->H; y++){
			/*using formulas from slides*/
			R = GetPixelR(image,x,y);
			G = GetPixelG(image,x,y);
			B = GetPixelB(image,x,y);	

			gray = (R + G + B)/3;
		
			R_offset = gray - R;
			G_offset = gray - G;
			B_offset = gray - B;			
	
			new_R = R + (R_offset) * percentage;
			new_G = G + (G_offset) * percentage;
			new_B = B + (B_offset) * percentage;
		
			SetPixelR(image, x, y, new_R);
           		SetPixelG(image, x, y, new_G);
           	 	SetPixelB(image, x, y, new_B);
			} /*rof*/
		} /*rof*/
	return image;
}

IMAGE *HueRotate(IMAGE *image, int percent)
{
    double degree; // modified this line to make it work
	double percentage;
	//convert percent to decimal range ( 0.0 to 1.0)
	 percentage = (double)percent/100;
	//convert percent to degree change
	degree = 360 * percentage;
	
    double a, b, r;
    double d = degree * PI / 180.0;
    double tmpr, tmpg, tmpb;

	

    a = (2 * cos(d) + 1.0) / 3.0;
    b = (1.0 - cos(d)) / 3.0 - sin(d) / sqrt(3.0);
    r = (1.0 - cos(d)) / 3.0 + sin(d) / sqrt(3.0);

    for (int x = 0; x < image->W; x++)
    {   for (int y = 0; y < image->H; y++)
        {
            tmpr = GetPixelR(image, x, y) * a + GetPixelG(image, x, y) * b + GetPixelB(image, x, y) * r;
            tmpg = GetPixelR(image, x, y) * r + GetPixelG(image, x, y) * a + GetPixelB(image, x, y) * b;
            tmpb = GetPixelR(image, x, y) * b + GetPixelG(image, x, y) * r + GetPixelB(image, x, y) * a;

            SetPixelR(image, x, y, (tmpr > MAX_PIXEL)?MAX_PIXEL:(tmpr < 0)?0:tmpr);
            SetPixelG(image, x, y, (tmpg > MAX_PIXEL)?MAX_PIXEL:(tmpg < 0)?0:tmpg);
            SetPixelB(image, x, y, (tmpb > MAX_PIXEL)?MAX_PIXEL:(tmpb < 0)?0:tmpb);
        }
    }
    return image;
}

/* EOF */
