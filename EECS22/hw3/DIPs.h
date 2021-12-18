/* DIPs.h: Header file for all DIPs.c functions from Assignment 2*/
#include "Constants.h"
#ifndef DIPS_H
#define DIPS_H

/* Change color to black and white*/
void BlackNWhite(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* Sharpen an image*/
void Sharpen(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/*Change the hue of an image*/
void Hue(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], int degree);


#endif /*DIPs_H*/

/*EOF DIPs.h*/
