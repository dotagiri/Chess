/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2017                     */
/*                                                                   */
/* Author: Tim Schmidt                                               */
/* Date: 11/09/2017                                                  */
/*                                                                   */
/* Movie.c: source file for basic movie manipulations                */
/*                                                                   */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Movie.h"

/* Allocate the memory space for the movie and the memory space */
/* for the frame list. Return the pointer to the movie. */
MOVIE *CreateMovie(void)
{
	/*allocate space for movie*/
	MOVIE *movie = (MOVIE *)malloc(sizeof(MOVIE));
	/*check if theres space*/
	if(!movie){
		perror("Out of memory! Aborting...");
		exit(10);
		}/*fi*/
	movie->Frames = NULL;
	movie->Frames = CreateImageList();
	return movie;
} /*end of CreateMovie*/	

/* Release the memory space for the frame list. */
/* Release the memory space for the movie. */
void DeleteMovie(MOVIE *movie)
{
	assert(movie);
	DeleteImageList(movie->Frames);
	free(movie);	
} /*end of DeleteMovie*/

/*clip function*/
int clip(int x){
	if (x<=0){
		return 0;
		} /*fi*/
	if (x >= 255){
		return 255;
		} /*fi*/
	else{
		return x;
		}
	} /*end of clip*/


/* Convert a YUV movie to a RGB movie */
void YUV2RGBMovie(MOVIE *movie)
{	
	assert(movie);	
	int C,D,E;	
	int R,G,B;
	int Y,U,V;
	IENTRY *e, *n;
	
	/*point to images in the ImageEntry structure*/
	YUVIMAGE *yuv;	
	IMAGE *i;

	e = (movie->Frames)->First;
	while(!e){ /*go through every frame*/
		n = e->Next;	
		yuv = e->YUVImage;
		i = e->RGBImage;
		i = CreateImage((e->YUVImage)->W, (e->YUVImage)->H);
		
		/*print error message if space for image wasn't allocated*/
		if (!i){
			perror("Out of memory! Aborting...");
			exit(10);
			} /*fi*/

		for(int x=0; x<MovieWidth(movie); x++){
			for(int y=0; y<MovieHeight(movie); y++){
				Y = GetPixelY(yuv,x,y);
				U = GetPixelU(yuv,x,y);
				V = GetPixelV(yuv,x,y);
					
				C = Y - 16;
				D = U - 128;
				E = V - 128;
				R = clip((298 * C + 409 * E + 128) >> 8);
				G = clip((298 * C - 100 * D - 208) >> 8);
				B = clip((298 * C + 516 * D - 128) >> 8);
				
				SetPixelR(i, x, y, R);
				SetPixelG(i, x, y, G);
				SetPixelB(i, x, y, B);
			} /*rof*/
		}/*rof*/
		
		/*free the leftover image*/
		DeleteYUVImage(yuv);
		yuv = NULL;

		/*make entry point to next entry to change next frame*/
		e -> RGBImage = i;
		e = n;
		} /*elihw*/			
} /*end of YUV2RGB*/

/* Convert a RGB movie to a YUV movie */
void RGB2YUVMovie(MOVIE *movie)
{
	assert(movie);
	int Y,U,V;
	int R,G,B;
	int width, height;
	IENTRY *e, *n;
	
	/*point to images in ImageEntry structure*/
	YUVIMAGE *yuv;
	IMAGE *i;

	width = MovieWidth(movie);
	height = MovieHeight(movie);
	e = movie->Frames -> First;
	while(e){ //going through every entry to change image to movie
		n = e->Next;
		yuv = e->YUVImage;
		i = e->RGBImage;
		yuv = CreateYUVImage(width, height);

		/*print error message if space for image wasn't allocated*/
		if (!yuv){
			perror("Out of memory! Aborting...");
			exit(10);
			} /*fi*/
		for (int x=0; x<width; x++){
			for(int y=0; y<height; y++){
				R = GetPixelR(i, x, y);
				G = GetPixelG(i, x, y);
				B = GetPixelB(i, x, y);		
					
				Y = clip(((66*R + 129*G + 25*B + 128)>>8)+16);
				U = clip(((-38*R - 74*G + 112*B + 128)>>8)+128);
				V = clip(((112*R - 94*G - 18*B + 128)>>8)+128);
					
				SetPixelY(yuv, x, y, Y);
				SetPixelU(yuv, x, y, U);
				SetPixelV(yuv, x, y, V);
			}/*rof*/
		}/*rof*/
		/*free the leftover image*/
		DeleteImage(i);
		i = NULL;
		
		/*make entry point to next entry*/
		e -> RGBImage = NULL;
		e -> YUVImage = yuv;
		e = n;
		} /*elihw*/

} /*end of RGB2YUV*/



int MovieLength(const MOVIE *movie)
{
	assert(movie);
	assert(movie->Frames);
    return movie->Frames->length;
}

int MovieHeight(const MOVIE *movie)
{
	assert(movie);
	assert(movie->Frames);
    if(movie->Frames->First->RGBImage)
    {
        return movie->Frames->First->RGBImage->H;
    }//fi

    else if(movie->Frames->First->YUVImage)
    {
        return movie->Frames->First->YUVImage->H;
    }//fi esle

    else
    return 0;
}

int MovieWidth(const MOVIE *movie)
{
	assert(movie);
	assert(movie->Frames);
    if(movie->Frames->First->RGBImage)
        {
                return movie->Frames->First->RGBImage->W;
        }//fi

        else if(movie->Frames->First->YUVImage)
        {
                return movie->Frames->First->YUVImage->W;
        }//fi esle

        else
        return 0;
}

/* EOF */
