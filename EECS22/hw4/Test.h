#ifndef TEST_H
#define TEST_H

/* Test all DIPs */
int AutoTest(void);

/* test parameters used in AutoTest() */

/* parameter used for Hue */
#define DEGREE 120

/* parameter used for Noise*/
#define NOISE_PERCENTAGE 30

/* parameters used for Posterize */
#define RBITS 7
#define GBITS 7
#define BBITS 7

/* parameter used for motion blur */
#define BLURAMOUNT 50

/* parameter used for enlarge */
#define ENLARGE_PERCENTAGE 170

/* parameters used for square */
#define X_OFFSET 100
#define Y_OFFSET 0
#define SQUARE_SIZE 400

/* brightness */
#define BRIGHTNESS 20
#define CONTRAST 200
#endif /* TEST_H */
