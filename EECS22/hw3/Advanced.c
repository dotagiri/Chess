/* Advanced.c for new filters:
 * Noise()
 * Posterize()
 * MotionBlur() */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "Advanced.h"
/* add noise to an image */
void Noise( int n, unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	srand(time(NULL));
	int x,y;
	int noise_percent = n*WIDTH*HEIGHT/100;
	for (int i = 0; i<noise_percent; i++){
		x = rand() % WIDTH;
		y = rand() % HEIGHT;
		R[x][y] = G[x][y] = B[x][y] = 255;
		}
} /*end of noise*/
	
/* posterize the image */
void Posterize(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], unsigned int rbits, unsigned int gbits, unsigned int bbits)
{
	int r,g,b;
	int i,j,k;
	/* create binary of 0's that has 1 in the nth bit*/
	/* use later to make sure only nth bit changes to 0*/
        i = 1 << (rbits-1);
	j = 1 << (gbits-1);
	k = 1 << (bbits-1); 

        for (int x = 0; x < WIDTH; x++){ /*go through every pixel*/
                for (int y = 0; y<HEIGHT; y++){	
			r=g=b=0;  /*reset all values for each pixel to shift properly*/
                        
			for (int pbits = 0; pbits<rbits-1; pbits++){
                                r = (r<<1) +1; /*create binary of 1's until n-1th bit*/
                                } /*rof*/

                        R[x][y] = R[x][y] | r; /* turn everything until n-1 bit into 1's*/
                        R[x][y] = R[x][y] & ~i; /*turn nth bit into 0*/


			/*posterize green values*/
                        for (int pbits = 0; pbits<gbits-1; pbits++){
                                g = (g<<1) +1;
                                } /*rof*/
                        G[x][y] = G[x][y] | g;
                        G[x][y] = G[x][y] & ~j;


			/* posterize blue values*/
                        for (int pbits=0; pbits<bbits-1;pbits++){
                                b = (b<<1)+1; /*binary of 1's until n-1th bith*/
                                } /*rof*/
                        B[x][y] = B[x][y] | b; /* makes every bit until n-1 into a 1*/
                        B[x][y] = B[x][y] & ~k;
                        } /*rof*/       		
        } /*rof*/			
}

/*motion blur*/
void MotionBlur(int BlurAmount, unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	/*declare temp values to store values later*/
	unsigned int tempR[WIDTH][HEIGHT], tempG[WIDTH][HEIGHT], tempB[WIDTH][HEIGHT];
	int sumR, sumG, sumB;
	int z;
	for (int x = 0; x < WIDTH; x++){
		for (int y = 0; y < HEIGHT; y++){	
			/* store original pixel's half value*/	
			tempR[x][y] = R[x][y];
			tempG[x][y] = G[x][y];
			tempB[x][y] = B[x][y];
			} /*rof*/
		} /*rof*/

	
        for (int x = 0; x < WIDTH; x++){ /*go through every pixel*/
                for (int y = 0 ; y<HEIGHT; y++){
			sumR=sumG=sumB=0;	
			for ( z=1; z<=BlurAmount+1; z++){
				/* check if pixel is at the border*/
				/* if so, weight should be averaged for every pixel*/
				if ((y-z) < HEIGHT && (y-z)>0){
					sumR += tempR[x][y-z];
					sumG += tempG[x][y-z];
					sumB += tempB[x][y-z];

					R[x][y] = 0.5*tempR[x][y] + 0.5 * (sumR/BlurAmount);
					G[x][y] = 0.5*tempG[x][y] + 0.5 * (sumG/BlurAmount);
					B[x][y] = 0.5*tempB[x][y] + 0.5 * (sumB/BlurAmount);
					} /*fi*/		
				
				else{
				
					R[x][y] = tempR[x][y];
					G[x][y] = tempG[x][y];
					B[x][y] = tempB[x][y];
					}

				} /*rof*/	
			} /*rof*/
		} /*rof*/		
}
/*EOF Advanced.c*/
