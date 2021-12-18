/* DIPS.c 
 * DIP funciton declarations from Assignment 2
 * BlackNWhite
 * Sharpen
 * Hue */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "Constants.h"
#include "DIPs.h"


/* make the picture color black & white */
void BlackNWhite(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
    int x, y;
    for (x = 0; x < WIDTH; x++)
    {   for(y = 0; y < HEIGHT; y++)
        {   R[x][y] = G[x][y] = B[x][y] = (R[x][y] + G[x][y] + B[x][y]) / 3;
        }
    }
}

// Sharpen function
void Sharpen(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
    int x, y;
    int tmpr = 0, tmpg = 0, tmpb = 0;
    unsigned char R_temp[WIDTH][HEIGHT];
    unsigned char G_temp[WIDTH][HEIGHT];
    unsigned char B_temp[WIDTH][HEIGHT];
    for (x = 0; x < WIDTH; x++)
    {   for(y = 0; y < HEIGHT; y++)
        {   R_temp[x][y] = R[x][y];
            G_temp[x][y] = G[x][y];
            B_temp[x][y] = B[x][y];
        }
    }
    for (x = 1; x < WIDTH - 1; x++)
    {   for (y = 1; y < HEIGHT - 1; y++)
        {   tmpr = 9 * R[x][y] - R[x-1][y-1] - R[x-1][y] - R[x-1][y+1] - R[x][y-1] - R[x][y+1] - R[x+1][y-1] - R[x+1][y] - R[x+1][y+1];
            tmpg = 9 * G[x][y] - G[x-1][y-1] - G[x-1][y] - G[x-1][y+1] - G[x][y-1] - G[x][y+1] - G[x+1][y-1] - G[x+1][y] - G[x+1][y+1];
            tmpb = 9 * B[x][y] - B[x-1][y-1] - B[x-1][y] - B[x-1][y+1] - B[x][y-1] - B[x][y+1] - B[x+1][y-1] - B[x+1][y] - B[x+1][y+1];
        R_temp[x][y] = (tmpr > 255)?255:(tmpr < 0)?0:tmpr;
        G_temp[x][y] = (tmpg > 255)?255:(tmpg < 0)?0:tmpg;
        B_temp[x][y] = (tmpb > 255)?255:(tmpb < 0)?0:tmpb;
        tmpr = tmpg = tmpb = 0;
        }
    }
    for (x = 0; x < WIDTH; x++)
    {   for(y = 0; y < HEIGHT; y++)
        {   R[x][y] = R_temp[x][y];
            G[x][y] = G_temp[x][y];
            B[x][y] = B_temp[x][y];
        }
    }
}

// Hue function
void Hue(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], int degree)
{
    int x, y;
    double a, b, r;
    double d = degree * PI / 180.0;
    double tmp_r, tmp_g, tmp_b;

    a = (2 * cos(d) + 1.0) / 3.0;
    b = (1.0 - cos(d)) / 3.0 - sin(d) / sqrt(3.0);
    r = (1.0 - cos(d)) / 3.0 + sin(d) / sqrt(3.0);

    for (x = 0; x < WIDTH; x++)
    {   for (y = 0; y < HEIGHT; y++)
        {   tmp_r = R[x][y] * a + G[x][y] * b + B[x][y] * r;
            tmp_g = R[x][y] * r + G[x][y] * a + B[x][y] * b;
            tmp_b = R[x][y] * b + G[x][y] * r + B[x][y] * a;

            R[x][y] = (tmp_r > 255)?255:(tmp_r < 0)?0:tmp_r;
            G[x][y] = (tmp_g > 255)?255:(tmp_g < 0)?0:tmp_g;
            B[x][y] = (tmp_b > 255)?255:(tmp_b < 0)?0:tmp_b;
        }
    }
}

/* EOF DIPs.c */
