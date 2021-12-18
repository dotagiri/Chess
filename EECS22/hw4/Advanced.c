#include "Advanced.h"
#include "Constants.h"

#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

/* Add noise to an image */
IMAGE *Noise(IMAGE *image, int n)
{
	assert(image);
	int x, y, i;
	int num; /* number of noise added */
	num = ( n*ImageHeight(image)*ImageWidth(image) )/100;
	srand(time(NULL));

	for ( i = 0; i < num; i++ ) {
		x = ( (double)rand()/RAND_MAX )*(ImageWidth(image)-1);
		y = ( (double)rand()/RAND_MAX )*(ImageHeight(image)-1);

		SetPixelR(image, x, y, 255);
		SetPixelG(image, x, y, 255);
		SetPixelB(image, x, y, 255);
	}
	return image;
}

/* make the image posterized */
IMAGE *Posterize(IMAGE *image, int rbits, int gbits, int bbits)
{
	assert(image);
	int x, y;
	int temp_rbit, temp_gbit, temp_bbit;
	int rbit2,gbit2,bbit2;
	for(x=0; x<ImageWidth(image); x++) {
		for(y=0; y<ImageHeight(image); y++) {
			unsigned char one = 1;
			int i;
			for(i=0; i<rbits-1; i++) {
				rbit2 = GetPixelR(image, x, y);
				rbit2 |= one;
				one <<= 1;
				SetPixelR(image, x, y, rbit2);
			}
			temp_rbit = GetPixelR(image,x,y);
			one = ~one;
			temp_rbit &= one;
			SetPixelR(image, x, y, temp_rbit);

			one = 1;
			for(i=0; i<gbits-1; i++) {
				gbit2 = GetPixelG(image, x, y);
				gbit2 |= one;
				one <<= 1;
				SetPixelG(image, x, y, gbit2);
			}
			temp_gbit = GetPixelG(image,x,y);
			one = ~one;
			temp_gbit &= one;
			SetPixelG(image, x, y, temp_gbit);
			one = 1;

			for(i=0; i<bbits-1; i++) {
				bbit2 = GetPixelB(image, x, y);
				bbit2 |= one;
				one <<= 1;
				SetPixelB(image, x, y, bbit2);
			}
			temp_bbit = GetPixelB(image,x,y);
			one = ~one;
			temp_bbit &= one;
			SetPixelB(image, x, y, temp_bbit);
		} /*rof*/
	} /*rof*/
	return image;
}

/* add motion blur to the image */
IMAGE *MotionBlur(IMAGE *image, int BlurAmount)
{
	assert(image);
	int x,y,m;
	int temp_r , temp_g , temp_b;
	int newTempR, newTempG, newTempB;	

	for (x = 0; x < ImageWidth(image); x++)
	{
        	for (y = ImageHeight(image) - 1; y >= 0 ; y--)
		{
			int count = 0;
			temp_r = temp_g = temp_b = 0.0;
			for (m = 1; m<=BlurAmount ; m++)
			{
				//if ((x-m) >= 0)
				if((y-m) >= 0)
				{
					temp_r += GetPixelR(image, x, y-m);
					temp_g += GetPixelG(image, x, y-m);
					temp_b += GetPixelB(image, x, y-m);
					count++;
				}
			}
			count = (count==0)?1:count;
			newTempR = temp_r / 2.0 / count + GetPixelR(image, x, y) / 2.0;	
			newTempG = temp_g / 2.0 / count + GetPixelG(image, x, y) / 2.0;
			newTempB = temp_b / 2.0 / count + GetPixelB(image, x, y) / 2.0;
			
			SetPixelR(image, x, y, newTempR);
			SetPixelG(image, x, y, newTempG);

		} /*rof*/
	} /*rof*/		
	return image;
}

IMAGE *Enlarge(IMAGE *image, int enlarge_percentage)
{
	assert(image);	

	/*declare parameters for newly scaled image*/
	int new_x, new_y;
	int scaled_x, scaled_y;	

	/*scale original pixels*/
	scaled_x = ImageWidth(image) * (enlarge_percentage / 100.00);
	scaled_y = ImageHeight(image) * (enlarge_percentage / 100.00);

	/*allocate space for new image*/
	IMAGE *new_image = NULL;
	new_image = CreateImage(scaled_x, scaled_y);

	/*cases for each percent size*/
	/*new image is same as original so just return image*/	
	if (enlarge_percentage == 100){
		return image;
		}
	
	/*enlarge if percentage>100*/
	if (enlarge_percentage > 100){
		for(int x=0; x< ImageWidth(new_image); x++){
			for(int y=0; y< ImageHeight(new_image); y++){

				/*scale image depending on how large inputted percentage is*/
				new_x = x*(100.00/enlarge_percentage);
				new_y = y*(100.00/enlarge_percentage);
				
				SetPixelR(new_image, x, y, GetPixelR(image, new_x, new_y));
				SetPixelG(new_image, x, y, GetPixelG(image, new_x, new_y));
				SetPixelB(new_image, x, y, GetPixelB(image, new_x, new_y));	
			} /*rof*/ 
		} /*rof*/
	} /*fi*/
	/*return new image*/
	DeleteImage(image);
	image = NULL;
	return new_image;
}

IMAGE *Square(IMAGE *image, int x_offset, int y_offset, int square_size)
{
	assert(image);
	
	/*set borders to inputted square size*/
	int new_W = square_size; 
	int new_H = square_size;
	int cropped_x, cropped_y;

	if (new_W>ImageWidth(image)){
		new_W = ImageWidth(image);
		} /*fi*/
	if (new_H>ImageHeight(image)){
		new_H = ImageHeight(image);
		} /*fi*/

	if(x_offset + new_W > ImageWidth(image)){
		new_W = ImageWidth(image) - x_offset;
		} /*fi*/
	if(y_offset + new_H > ImageHeight(image)){
		new_H = ImageHeight(image) - y_offset;
		} /*fi*/
	
	/*create new image*/
	IMAGE *new_square = NULL;
	new_square = CreateImage(new_W, new_H);

	for(int x=0; x<ImageWidth(new_square); x++){
		for(int y=0; y<ImageHeight(new_square); y++){
			/*define cropped pixels from offset and new square size*/
			cropped_x = x_offset + x;
			cropped_y = y_offset + y;
			
			/*set the new pixels in the square image*/
			SetPixelR(new_square, x, y, GetPixelR(image, cropped_x, cropped_y));
			SetPixelG(new_square, x, y, GetPixelG(image, cropped_x, cropped_y));
			SetPixelB(new_square, x, y, GetPixelB(image, cropped_x, cropped_y));
			} /*rof*/
		}/*rof*/

	/*return new image*/
	DeleteImage(image);
	image = NULL;
	return new_square;
}

IMAGE *BrightnessandContrast(IMAGE *image, int brightness, int contrast)
{
	assert(image);

	/*declare variables here*/
	int new_R, new_G, new_B;
	int bright_R, bright_G, bright_B;
	double factor = (double)(259*(contrast+255))/(double)(255*(259-contrast));

	for(int x=0; x<ImageWidth(image); x++){
		for(int y=0; y<ImageHeight(image); y++){
			/*adjust brightness*/
			bright_R = GetPixelR(image, x, y) + brightness;
			bright_G = GetPixelG(image, x, y) + brightness;
			bright_B = GetPixelB(image, x, y) + brightness;
			/*compute new pixel value from formula in slides*/
			new_R = (int)(factor * (bright_R - 128) + 128);							
			new_G = (int)(factor * (bright_G - 128) + 128);
			new_B = (int)(factor * (bright_B - 128) + 128);	
			
			if (new_R<0){
				new_R = 0;
				}
			else if (new_R>255){
				new_R = 255;
				} /*fi for red values*/

			if (new_G<0){
				new_G = 0;
				}
			else if (new_G>255){
				new_G = 255;
				} /*fi for green values*/

			if (new_B<0){
					new_B = 0;
				}
			else if (new_B > 255){
				new_B = 255;
				} /*fi for blue values*/

			/*Set new RGB values*/

			SetPixelR(image, x, y, new_R);
			SetPixelG(image, x, y, new_G);
			SetPixelB(image, x, y, new_B); 
			} /*rof*/
		} /*rof*/	
	return image;
}

/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
/*EOF Advanced.c*/
