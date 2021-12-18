/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Winter 2020                   */
/*                                                                   */
/* Author: Bo Tsai                                                   */
/*                                                                   */
/* MovieLab.c: source file for the main function                     */
/*                                                                   */
/* Please use this template for your HW5.                            */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FileIO.h"
#include "DIPs.h"
#include "Movie.h"
#include "Constants.h"
#include "Image.h"
#include "MovieIO.h"
#include "IterativeFilter.h"

int main(int argc, char *argv[])
{
	IMAGE *input = NULL;
	MOVIE *movie = NULL;

	int importFlag = 0;
	int reverseFlag =0; //since ReverseImageList needs to be called outside of loop 
	int frameNum = 0;
	float start = 0;
	float end = 0;
	float step = 0;
	unsigned int width, height;

	iterableFilter filter_func = NULL;
	
	char *movieInput = NULL;
	char *movieOutput = NULL;
    // allocate necessary variables

    // loop through each argument for the main function
    for(int n = 0; n < argc; n++)
    {
        // If the user wants to import an image
        if(!strcmp(argv[n], "-i"))
        {
		n++; //changed -i code due to seg faults
            // If they are at the last argument
            if(n < argc)
	    {	
           	input = LoadImage(argv[n]);
		//Let the program know a image has successfully been imported
		importFlag = 1;
	    }
            if(!input)
            {
		printf("\n\tPlease provide the name of the image you want to import\n");
                return 0;
            }

        }

        // If the user wants to import a movie
        else if(!strcmp(argv[n], "-m"))
        {       
		n++; 
		if(n <  argc){
			movieInput = argv[n];
			importFlag = 2;
			} /*fi*/
			
		else{	
			printf("\n\tPlease provide the name of the movie you want to import\n");
			return 0;
			} /*fi*/
            // Let the program know a movie has succesfully been imported
            importFlag = 2;
	}
        /*movie frames*/
        else if(!strcmp(argv[n], "-f"))
	{
		n++;
		if(n < argc){
			/* convert string to int*/
			frameNum = atoi(argv[n]);
			}/*fi*/					
		
		else{
			printf("Missing argument for the number of frames!\n");
			return 0;
			}/*esle*/
	}
	/*movie size*/
	else if(!strcmp(argv[n], "-s"))
	{
		n++;
		if(n < argc){
			sscanf(argv[n], "%dx%d", &width, &height);	
			} /*fi*/
		else{
			printf("\n\tMissing argument for the resolution of the frame!\n");
			return 0;
			} /*esle*/		
	}

	/*movie output*/
	else if(!strcmp(argv[n], "-o"))
	{
		n++;
		if(n < argc){
			movieOutput = argv[n];
			}/*fi*/
		else{
			printf("\n\tPlease provide the name of the output file\n");
			return 0;
			} /*esle*/
	}
	/*start frame*/
	else if(!strcmp(argv[n], "-start"))
	{
		n++;
		if(n < argc){
			start = atoi(argv[n]);
			} /*fi*/
		else{
			printf("\n\tPlease provide the start parameter\n");
			return 0;
			} /*esle*/
	}
	/*end frame*/
	else if(!strcmp(argv[n], "-end"))
	{
		n++;
		if(n < argc){
			end = atoi(argv[n]);
			} /*fi*/
		else{
			printf("\n\tPlease provide the end parameter\n");
			return 0;
			} /*esle*/
	}
	/*frame steps*/
	else if(!strcmp(argv[n], "-step"))
	{
		n++;
		if(n < argc){
			step = atoi(argv[n]);
		} /*fi*/
		else {
			printf("\n\tPlease provide the step parameter\n");
			return 0;
		} /*esle*/
	}
	/*reverse*/
	else if(!strcmp(argv[n], "-reverse"))
	{
		reverseFlag = 1;
	}
	/*hue filter*/
	else if(!strcmp(argv[n], "-hue"))
	{
		if(n < argc){
			filter_func = &HueRotate;
			//Let program know filter has been applied
			importFlag = 1;
		} /*fi*/
	}	
	/*black and white filter*/
	else if(!strcmp(argv[n], "-bw"))
	{
		if(n < argc){
			filter_func = &BlackNWhite;
			//Let program know filter has been applied
			importFlag = 1;
		} /*fi*/
	} 
    }

    // Load the default image if no argument was specified
    if(!importFlag)
    {
	    printf("\nNo -i nor -m for input file to read\n");
	    return 0;
    }
    else if(importFlag == 1)
    {
	    movie = doIterativeFilter(input, filter_func, start, end, step);
	    SaveMovie(movieOutput, movie);
	    DeleteImage(input);
	    DeleteMovie(movie);
	    return 0;
    }
    else if(importFlag == 2)
    {
	movie = LoadMovie(movieInput, frameNum, width, height);	
	if (reverseFlag == 1){ // if -reverse command was ran
		ReverseImageList(movie -> Frames);	
		printf("Operation Reverse is done\n");
		} /*fi*/
	SaveMovie(movieOutput, movie);
	DeleteMovie(movie);
	return 0;
    }
    return 0;
}

/* EOF */
