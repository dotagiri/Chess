/*********************************************************************/
/* PhotoLab.c: Assignment 2 for EECS 22, Winter 2020                 */
/* 								     */
/* modifications: 						     */
/* 09/27/17 	RD	adjusted for lecture usage		     */
/* 10/1/18  	MC  	adjusted for F18			     */
/* 01/11/20 	Wendy	adjusted for W20			     */
/*********************************************************************/
/* Enter your name, last name and UCInet ID below:
 * ***************************************************************** *
 * First Name: Daisuke	
 * Last Name: Otagiri	
 * UCInet ID: dotagiri
 */

/*** header files ***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*** global definitions ***/

#define WIDTH  600		/* image width */
#define HEIGHT 400		/* image height */
#define SLEN    64		/* maximum length of file names */
#define PI     3.14159265       /* value of pi for Hue function*/

/*** function declarations ***/
/* print a menu */
void PrintMenu(void)
{
	printf("----------------------------------------------\n");
	printf("1: Load a PPM image\n");
	printf("2: Save the image in PPM and JPEG format\n");
	printf("3: Change the color image to black and white\n");
	printf("4: Sharpen the image\n");
	printf("5: Change the hue of image\n");
	printf("6: Test all functions\n");
	printf("7: Exit\n");	
	printf("----------------------------------------------\n");
	printf("Please make your choice:");
	
}
/* read image from a file */
/* written for you; should not been modified */
int LoadImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* save image from file*/
int SaveImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
    FILE *File;
    char ftype[] = ".ppm";
    char fname_ext[SLEN + sizeof(ftype)];
    char SysCmd[SLEN * 5];
    int  x, y;

    strcpy(fname_ext, fname);
    strcat(fname_ext, ftype);

    File = fopen(fname_ext, "w");
    if (!File) {
        printf("\nCannot open file \"%s\" for writing!\n", fname);
        return 1;
    }
    fprintf(File, "P6\n");
    fprintf(File, "%d %d\n", WIDTH, HEIGHT);
    fprintf(File, "255\n");

    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {
            fputc(R[x][y], File);
            fputc(G[x][y], File);
            fputc(B[x][y], File);
        }
    }

    if (ferror(File)) {
        printf("\nFile error while writing to file!\n");
        return 2;
    }
    fclose(File);
    printf("%s was saved successfully. \n", fname_ext);

    /*
     * rename file to image.ppm, convert it to ~/public_html/<fname>.jpg
     * and make it world readable
     */
    sprintf(SysCmd, "~eecs22/bin/pnmtojpeg_hw2.tcsh %s", fname_ext);
    if (system(SysCmd) != 0) {
        printf("\nError while converting to JPG:\nCommand \"%s\" failed!\n", SysCmd);
        return 3;
    }
    printf("%s.jpg was stored for viewing. \n", fname);

    return 0;
} /* end of SaveImage*/

/* aging the photo */
/* sample function to get you started */
void Aging(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* change a color image to black & white */
void BlackNWhite(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	/* use x and y from SaveImage function*/
	/* x represents width and y is height */
	for (int x = 0; x < WIDTH; x++){ /*go through every pixel*/
		for (int y = 0; y<HEIGHT; y++){
			R[x][y] = G[x][y] = B[x][y] = (R[x][y] + G[x][y] + B[x][y])/3; /*formula from slides applied here*/ 
			} /*rof*/
		} /*rof*/	
}
/* sharpen the image */
void Sharpen(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	int x,y;
	/*set up an array for R, G and B*/
	int tempR[WIDTH][HEIGHT];
	int tempG[WIDTH][HEIGHT];
	int tempB[WIDTH][HEIGHT];

	/*array to store sharpened pixels*/
	/* set to type int to check for boundaries later*/
	int newtempR[WIDTH][HEIGHT];
	int newtempG[WIDTH][HEIGHT];
	int newtempB[WIDTH][HEIGHT];

	/*array to store new RGB values that are replaced by sharpened values later*/
	unsigned char new_R[WIDTH][HEIGHT];
	unsigned char new_G[WIDTH][HEIGHT];
	unsigned char new_B[WIDTH][HEIGHT];

	/*store original RGB values into temp*/	
	for (x=0; x<WIDTH; x++){
		for (y=0; y<HEIGHT; y++){
			tempR[x][y] = R[x][y];
			tempG[x][y] = G[x][y];
			tempB[x][y] = B[x][y];
			} /*rof*/
		} /*rof*/

	for (x = 1; x < WIDTH-1; x++){ /* set range to x=1 and width-1 so borders are ignored*/
		for (y=1; y<HEIGHT-1; y++){

			/*use formula new_E = 9*E-A-B-C-D-F-G-H-I*/
			newtempR[x][y] = 9*tempR[x][y]-tempR[x-1][y+1]-tempR[x][y+1]-tempR[x+1][y+1]-tempR[x-1][y]-tempR[x+1][y]-tempR[x-1][y-1]-tempR[x][y-1]-tempR[x+1][y-1];
			newtempG[x][y] = 9*tempG[x][y]-tempG[x-1][y+1]-tempG[x][y+1]-tempG[x+1][y+1]-tempG[x-1][y]-tempG[x+1][y]-tempG[x-1][y-1]-tempG[x][y-1]-tempG[x+1][y-1];
			newtempB[x][y] = 9*tempB[x][y]-tempB[x-1][y+1]-tempB[x][y+1]-tempB[x+1][y+1]-tempB[x-1][y]-tempB[x+1][y]-tempB[x-1][y-1]-tempB[x][y-1]-tempB[x+1][y-1];
			
			/*adjusting boundaries for new pixel values*/
			/*if values exceed 255, set to 255 */
			/*if values go below 0, set to 0 */
			if (newtempR[x][y]>255){
				newtempR[x][y] = 255;
				}/*fi*/
			else if (newtempR[x][y]<0){
				newtempR[x][y] = 0;
				}/*fi*/
							
			if (newtempG[x][y]>255){
				newtempG[x][y] = 255;
				}/*fi*/
			else if (newtempG[x][y]<0){
				newtempG[x][y] = 0;
				}/*fi*/
			
			if (newtempB[x][y]>255){
				newtempB[x][y] = 255;
				}/*fi*/
			else if (newtempB[x][y]<0){
				newtempB[x][y] = 0;
				}/*fi*/

			/*plug in intensity values for new RGB values*/ 
			new_R[x][y] = newtempR[x][y];
			new_G[x][y] = newtempG[x][y];
			new_B[x][y] = newtempB[x][y];
		
			/*plug in new RGB values into original values*/
			R[x][y] = new_R[x][y];
			G[x][y] = new_G[x][y];
			B[x][y] = new_B[x][y];	
		} /*rof*/
	} /*rof*/	
} /*end of Sharpen*/
/* change the image hue */
void Hue(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], int degree)
{
	double  alpha, beta, gamma;
	int x,y; 
	unsigned char R_new[WIDTH][HEIGHT]; /*declare new RGB variables to store values after Hue Formula*/
	unsigned char G_new[WIDTH][HEIGHT];
	unsigned char B_new[WIDTH][HEIGHT];	
	
	/* setting up alpha, beta, gamma equations */
	alpha = (2*cos (degree*PI/180)+1)/3;
	beta  = ((1-cos (degree*PI/180))/3)-((sin (degree*PI/180))/sqrt(3));
	gamma = ((1-cos (degree*PI/180))/3)+((sin (degree*PI/180))/sqrt(3));

	for (x=0; x<WIDTH; x++){
		for (y=0; y<HEIGHT; y++){
			R_new[x][y] = (R[x][y]*alpha)+(G[x][y]*beta)+(B[x][y]*gamma);	/*calculating for new color values*/
			G_new[x][y] = (R[x][y]*gamma)+(G[x][y]*alpha)+(B[x][y]*beta);
			B_new[x][y] = (R[x][y]*beta)+(G[x][y]*gamma)+(B[x][y]*alpha);
			
			R[x][y] = R_new[x][y]; /*replace old color values with new one*/
			G[x][y] = G_new[x][y]; 
			B[x][y] = B_new[x][y];

			if (R[x][y]>255){ /*check if color values don't exceed 255 and dont go below 0*/
				R[x][y] = 255;
				}/*fi*/
			else if(R[x][y]<0){ /*checks if color goes negative, if so set to 0*/
				R[x][y] = 0;
				}/*fi*/

			if (G[x][y]> 255){ /*check if green is in range*/
				G[x][y] = 255;
				}/*fi*/
			else if(G[x][y]<0){
				G[x][y] = 0;
				} /*fi*/
			
			if (B[x][y]> 255){ /*check if blue is in range*/
				B[x][y] = 255;
				}/*fi*/
			else if(B[x][y]<0){
				B[x][y] = 0;
				} /*fi*/
		
			} /*rof*/
		} /*rof*/					
} /* end of Hue */
/* test all functions */
void AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

int main(void)
{
    /* Two dimensional arrays to hold the current image data, */
    /* one array for each color component.                    */
    unsigned char   R[WIDTH][HEIGHT];
    unsigned char   G[WIDTH][HEIGHT];
    unsigned char   B[WIDTH][HEIGHT];

    /* Please replace the following code with proper menu  */
    /* with function calls for DIP operations	           */
	int choice;
	char imageName[SLEN];
	while(1){
		PrintMenu(); /*print menu here*/
		scanf("%d", &choice); /*after printing, scan for user's choice*/
		
		switch(choice) {
			case 1:
				printf("Please input the file name to load: "); /*ask user for imageName*/
				scanf("%s", imageName);
				LoadImage(imageName, R, G, B); /*Load image*/
				break;
			case 2:
				printf("Please input the file name to save: ");
				scanf("%s", imageName);
				SaveImage(imageName, R, G, B); /*Save the image*/
				break;
			case 3:			
				if (strlen(imageName)==0) { /*Check if user loaded an image before applying filters*/
					printf("No image loaded\n");
					break;
					} /*fi*/
				LoadImage(imageName, R, G, B); /*Get the image that was loaded by user*/
				BlackNWhite(R, G, B); /*Run BlackNWhite function*/
				SaveImage("bw", R, G, B); /* Save image after bw filter */
				break;
			case 4:	
				if (strlen(imageName)==0) { /*Check if user loaded an image before applying filters*/
					printf("No image loaded\n");
					break;
					} /*fi*/
				LoadImage(imageName, R, G, B); /*Get original image loaded by user*/
				Sharpen(R, G, B); /*sharpen loaded image*/
				SaveImage("sharpen", R, G, B); /* save sharpened image*/
				printf("Sharpen operation is done!\n");
				break;
			case 5:
				if (strlen(imageName)==0) { /*Check if user loaded an image before applying filters*/
					printf("No image loaded\n");
					break;
					} /*fi*/
				LoadImage(imageName, R, G, B); /*Load Image*/
				Hue(R, G, B, 120); /*apply hue to image*/
				SaveImage("hue", R, G, B); /*save*/
				printf("Hue operation is done!\n");
				break;
			case 6:
				if (strlen(imageName)==0) { /*Check if user loaded an image*/
					printf("No image loaded\n");
					break; /*go back to menu*/
					} /*fi*/
				AutoTest(R, G, B); /*autotest call to test all filters*/
				printf("AutoTest complete!\n");
				break;
			case 7:
				exit(1); /*quit*/
				break;
			default:
				break;
			} /* end of switch*/
		} /* end of while*/
    return 0;
} /*end of main()*/

/* takes in a file name without extension */
/* writes file into R, G, B arrays */
int LoadImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
    FILE *File;
    char Type[SLEN];
    int  Width, Height, MaxValue;
    int  x, y;
    char ftype[] = ".ppm";
    char fname_ext[SLEN + sizeof(ftype)];

    strcpy(fname_ext, fname);
    strcat(fname_ext, ftype);

    File = fopen(fname_ext, "r");
    if (!File) {
        printf("\nCannot open file \"%s\" for reading!\n", fname);
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
    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {
            R[x][y] = fgetc(File);
            G[x][y] = fgetc(File);
            B[x][y] = fgetc(File);
        }
    }
    if (ferror(File)) {
        printf("\nFile error while reading from file!\n");
        return 7;
    }
    printf("%s was read successfully!\n", fname_ext);
    fclose(File);
    return 0;
}

/* age the image to make it look like old picture */
void Aging(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
    int x, y;

    for( y = 0; y < HEIGHT; y++ ) {
        for( x = 0; x < WIDTH; x++ ) {
	    B[x][y] = ( R[x][y]+G[x][y]+B[x][y] )/5;
            R[x][y] = (unsigned char) (B[x][y]*1.6);
            G[x][y] = (unsigned char) (B[x][y]*1.6);
	}
    }
}

/* Test all functions */
void AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{

    LoadImage("applestore", R, G, B);
    Aging(R, G, B);
    SaveImage("aging", R, G, B);
    printf("Aging tested!\n\n");
    /* add more tests here */
	/*Black and White*/
	LoadImage("applestore", R, G, B); /*Load original image so BnW is not applied to aging image*/
	BlackNWhite(R, G, B);
	SaveImage("bw", R, G, B);
	printf("Black and White tested!\n\n");

	/*Sharpen*/
	LoadImage("applestore", R, G, B); /*Load original image so Sharpen is not applied to bw*/
	Sharpen(R, G, B);
	SaveImage("sharpen", R, G, B);
	printf("Sharpen tested!\n\n");

	/*Hue*/
	LoadImage("applestore", R, G, B); /*Load original image so Hue is not applied to Sharpen*/
	Hue(R, G, B, 120);
	SaveImage("hue", R, G, B);
	printf("Hue tested!\n\n");         
}

/**************************************************************/
/* Please add your function definitions here...               */
/**************************************************************/
/* PrintMenu - prints the menu
 * main - calls every function depending on user input
 * 	- uses switch cases
 * BlackNWhite
 * 	- applied black and white filter using formula
 * Sharpen
 * 	- intensified every pixel in image except borders
 * Hue
 * 	- changes hue of image using given formula from slides
 * AutoTest
 * 	- calls every filter (Aging, BlackNWhite, Sharpen, Hue)
 * 	- Loads original image before every filter call
 * 	- Saves after filter function is called
 */

/* EOF */
