/*********************************************************************/
/* 02/27/20 Bo Tsai      updated for EECS22 assignment Winter2020    */
/* Author: Tim Schmidt Date: 11/09/2017                              */
/*                                                                   */
/* DIPs.h: header file for DIP operations                            */
/*                                                                   */
/*********************************************************************/

#ifndef DIPS_H
#define DIPS_H

#include "Image.h"
#include "FileIO.h"

// BlackNWhite filter
IMAGE *BlackNWhite(IMAGE *image, int percent);

// HueRotate filter
IMAGE *HueRotate(IMAGE *image, int percent);

#endif
