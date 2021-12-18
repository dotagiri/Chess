/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2018                     */
/*                                                                   */
/* Author: Jordan Bonecutter                                         */
/*                                                                   */
/* IterativeFilter.c: file for iterative filters                     */
/*                                                                   */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "IterativeFilter.h"

MOVIE *doIterativeFilter(IMAGE *image, iterableFilter filter, int start, int end, int change)
{
	/*create pointers*/
	MOVIE *new_movie = CreateMovie();
	ILIST *movie_frames = new_movie->Frames;
	IMAGE *new_image;

	//declare index variable
	float x;
	/*if statement to apply filter in both directions, start>end and start<end*/ 
	if (start<end){	
		for(x=start; x<=end; x+=change){
			new_image = CopyImage(image);
			new_image = filter(new_image,x);
			AppendRGBImage(movie_frames, new_image);
			} /*rof*/	
		} /*fi*/
		
	else if (start>end){ /*reverse direction*/
		/*steps must be reversed since start>end*/
		for(x=start; x>=end; x-=change){
			new_image = CopyImage(image);
			new_image = filter(new_image,x);
			AppendRGBImage(movie_frames, new_image);
			} /*rof*/
		} /*esle*/

	/*convert the RGB values to the movie*/
	RGB2YUVMovie(new_movie);
	return new_movie;	
}
