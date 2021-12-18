/* FileIO.c 
 * Includes functions:
 * LoadImage() 
 * SaveImage() */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "FileIO.h"
#include "Constants.h"

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
} /*End of LoadImage function*/

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
} /*End of SaveImage*/

/*EOF*/
