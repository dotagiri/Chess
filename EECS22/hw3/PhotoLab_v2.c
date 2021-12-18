/*********************************************************************/
/* PhotoLab.c: homework assignment #3, for EECS 22,  Winter 2020     */
/*                                                                   */
/* Author: EECS 22 Team and Daisuke Otagiri                          */
/* Date:   2/7/20                                                    */
/*                                                                   */
/* Comments: Enjoy Learning new things!:)                            */
/*                                                                   */
/* Please use this template to submit your hw3.                      */
/*********************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define WIDTH 600	/* image width */
#define HEIGHT 400	/* image height */
#define SLEN 80     /* maximum length of file names and string*/
#define SUCCESS 0   /* return code for success */
#define EXIT 7      /* menu item number for EXIT */
#define PI 3.14159265358979323846264338327950288

void PrintMenu();

/* read image from a file */
int LoadImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* save a processed image */
int SaveImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* change a color image to black & white */
void BlackNWhite(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* sharpen the image */
void Sharpen(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* chaneg the image hue */
void Hue(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], int degree);

/* add noise to an image */
void Noise( int n, unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* sharpen the image */
void Sharpen(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* posterize the image */
void Posterize(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], unsigned int rbits, unsigned int gbits, unsigned int bbits);

/* Test all functions */
void AutoTest(void);

/* Bonus: motion blur */
void MotionBlur(int BlurAmount, unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);


int main() {
    unsigned char   R[WIDTH][HEIGHT];	/* use three 2-D arrays to store R, G, B components */
    unsigned char   G[WIDTH][HEIGHT];
    unsigned char   B[WIDTH][HEIGHT];

    int option;			/* user input option */
    char fname[SLEN];		/* input file name */
    // char colorOption[SLEN]; /* color option place holder */

    PrintMenu();
    scanf("%d", &option);

    int rc = -1;			/* return code of ReadImage() */
    int hue = 0;            // degree of hue change


    while (option != EXIT)
    {
        if (option == 1)
        {
            printf("Please input the file name to load: ");
            scanf("%s", fname);
            rc = LoadImage(fname, R, G, B);
        }
        /* menu item 2 - 10 requires image is loaded first */
        else if (option >= 2 && option <= 5)
        {
            if (rc != SUCCESS)
            {
                printf("No image is read.\n");
            }
            /* now image is loaded */
            else
            {
                switch(option)
                {
                    case 2:
                        printf("Please input the file name to save: ");
                        scanf("%s", fname);
                        SaveImage(fname, R, G, B);
                        break;
                    case 3:
                        BlackNWhite(R, G, B);
                        printf("\"Black & White\" operation is done!\n");
                        break;
                    case 4:
                        Sharpen(R, G, B);
                        printf("\"Sharpen\" operation is done!\n");
                        break;
                    case 5:
                        printf("Please input the degree of changing hue: ");
                        scanf("%d", &hue);
                        Hue(R, G, B, hue);
                        printf("\"Hue\" operatin is done!\n");
                        break;
                    default:
                        break;
                }
            }
        }
        else if (option == 6) {
            AutoTest();
            rc = SUCCESS;	/* set returned code SUCCESS, since image is loaded */
        }
        else {
            printf("Invalid selection!\n");
        }

        /* Process finished, waiting for another input */
        PrintMenu();
        scanf("%d", &option);
    }
    printf("You exit the program.\n");
    return 0;
}


int LoadImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
    FILE           *File;
    char            Type[SLEN];
    int             Width, Height, MaxValue;
    int             x, y;
    char            ftype[] = ".ppm";
    char            fname_tmp[SLEN];
    strcpy(fname_tmp, fname);
    strcat(fname_tmp, ftype);

    File = fopen(fname_tmp, "r");
    if (!File) {
        printf("Cannot open file \"%s\" for reading!\n", fname);
        return 1;
    }
    fscanf(File, "%79s", Type);
    if (Type[0] != 'P' || Type[1] != '6' || Type[2] != 0) {
        printf("\nUnsupported file format!\n");
        return 2;
    }
    fscanf(File, "%d", &Width);
    if (Width != WIDTH) {
        printf("\nUnsupported image width %d!\n", Width);
        return 3;
    }
    fscanf(File, "%d", &Height);
    if (Height != HEIGHT) {
        printf("\nUnsupported image height %d!\n", Height);
        return 4;
    }
    fscanf(File, "%d", &MaxValue);
    if (MaxValue != 255) {
        printf("\nUnsupported image maximum value %d!\n", MaxValue);
        return 5;
    }
    if ('\n' != fgetc(File)) {
        printf("\nCarriage return expected!\n");
        return 6;
    }
    for (y = 0; y < HEIGHT; y++)
        for (x = 0; x < WIDTH; x++) {
            R[x][y] = fgetc(File);
            G[x][y] = fgetc(File);
            B[x][y] = fgetc(File);
        }
    if (ferror(File)) {
        printf("\nFile error while reading from file!\n");
        return 7;
    }
    printf("%s was read.\n", fname_tmp);
    fclose(File);
    return 0;
}

int SaveImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
    FILE	*File;
    int	x, y;
    char	SysCmd[SLEN * 5];

    char	ftype[] = ".ppm";
    char	fname_tmp[SLEN];  /*avoid to modify on the original pointer, 11/10/10, X.Han*/
    char	fname_tmp2[SLEN];

    strcpy(fname_tmp, fname);
    strcpy(fname_tmp2, fname);
    strcat(fname_tmp2, ftype);

    File = fopen(fname_tmp2, "w");
    if (!File) {
        printf("Cannot open file \"%s\" for writing!\n", fname);
        return 1;
    }
    fprintf(File, "P6\n");
    fprintf(File, "%d %d\n", WIDTH, HEIGHT);
    fprintf(File, "255\n");

    for (y = 0; y < HEIGHT; y++)
        for (x = 0; x < WIDTH; x++) {
            fputc(R[x][y], File);
            fputc(G[x][y], File);
            fputc(B[x][y], File);
        }

    if (ferror(File)) {
        printf("\nFile error while writing to file!\n");
        return 2;
    }
    fclose(File);
    printf("%s was saved. \n", fname_tmp2);

    /*
     * rename file to image.ppm, convert it to ~/public_html/<fname>.jpg
     * and make it world readable
     */
    sprintf(SysCmd, "/users/grad2/doemer/eecs22/bin/pnmtojpeg_hw3.tcsh %s", fname_tmp2);
    if (system(SysCmd) != 0) {
        printf("\nError while converting to JPG:\nCommand \"%s\" failed!\n", SysCmd);
        return 3;
    }
    printf("%s.jpg was stored.\n", fname_tmp);
    return 0;
}

/*******************************************/
/* Function implementations should go here */
/*******************************************/

void PrintMenu()
{
    printf("\n-------------------------\n");
    printf("1: Load a PPM image\n");
    printf("2: Save the image in PPM and JPEG format\n");
    printf("3: Change the color image to black and white\n");
    printf("4: Sharpen the image\n");
    printf("5: Change the hue of image\n");
	printf("6: Add noise to an image\n");
	printf("7: Posterize an image\n");
	printf("8: Motion Blur\n");
    printf("9: Test all functions\n");
    printf("10: Exit\n");
    printf("--------------------------\n");
    printf("Please make your choice: ");
}

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


void AutoTest(void) {

    unsigned char R[WIDTH][HEIGHT] , G[WIDTH][HEIGHT], B[WIDTH][HEIGHT];
    char fname[SLEN] = "CrystalChurch";

    LoadImage(fname, R, G, B);
    BlackNWhite(R, G, B);
    SaveImage("bw", R, G, B);
    printf("Black and White tested!\n\n");

    LoadImage(fname, R, G, B);
    Sharpen(R, G, B);
    SaveImage("sharpen", R, G, B);
    printf("Sharpen tested!\n\n");

    LoadImage(fname, R, G, B);
    Hue(R, G, B, 120);
    SaveImage("hue", R, G, B);
    printf("Hue tested!\n\n");

    /* add more tests here */
}
