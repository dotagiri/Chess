/* FileIO.h header file for declaring LoadImage and SaveImage*/
#include "Constants.h"
#ifndef FILEIO_H
#define FILEIO_H

int LoadImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

int SaveImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);
#endif /* FILEIO_H */

/*EOF FileIO.h*/


