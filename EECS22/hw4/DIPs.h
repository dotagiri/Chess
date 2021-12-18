#ifndef DIPS_H_INCLUDED_
#define DIPS_H_INCLUDED_

#include "Constants.h"
#include "Image.h"

/* change a color image to black & white */
IMAGE *BlackNWhite(IMAGE *image);

/* sharpen the image */
IMAGE *Sharpen(IMAGE *image);

/* chaneg the image hue */
IMAGE *Hue(IMAGE *image, int degree);

#endif /* DIPS_H_INCLUDED_ */

/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
