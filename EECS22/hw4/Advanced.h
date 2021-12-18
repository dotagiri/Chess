#ifndef ADVANCED_H_INCLUDED_
#define ADVANCED_H_INCLUDED_

#include "Constants.h"
#include "Image.h"

/* add noise to an image */
IMAGE *Noise(IMAGE *image, int n);

/* posterize the image */
IMAGE *Posterize(IMAGE *image, int rbits, int gbits, int bbits);

/* motion blur */
IMAGE *MotionBlur(IMAGE *image, int BlurAmount);

/*set image shape to square*/
IMAGE *Square(IMAGE *image, int x, int y, int L);

/*enlarge an image*/
IMAGE *Enlarge(IMAGE *image, int percentage);

/*adjust brightness and contrast*/
IMAGE *BrightnessandContrast(IMAGE *image, int brightness, int contrast);

#endif /* ADVANCED_H_INCLUDED_ */

/* Vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
