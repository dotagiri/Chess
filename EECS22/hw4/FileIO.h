/*********************************************************************/ 
/* FileIO.h: header file for I/O module	                             */ 
/*                                                                   */
/* 02/05/20 Wendy Lin    updated for EECS22 assignmwnt 4 Winter2020  */
/* 11/01/17 Mihnea Chirila updated for EECS22 assignment 4 Fall2017  */
/* 10/31/16 Huan Chen    updated for EECS22 assignment4 Fall2016     */
/* 11/03/15 Guantao Liu  updated for EECS22 assignment4 Fall2015     */
/* 10/29/13 Alex Chu     updated for EECS22 assignment4 Fall2013     */
/* 10/30/12 Weiwei Chen  updated for EECS22 assignment4 FAll2012     */
/* 10/07/11 Weiwei Chen: initial solution version                    */
/*                       for EECS22 assignment3 FAll2011             */
/*********************************************************************/ 
#ifndef FILE_IO_H
#define FILE_IO_H

#include "Image.h"

/* Read image from a file 						*/
/* The size of the image needs to be pre-set				*/
/* The memory spaces of the image will be allocated in this function	*/
/* Return values:							*/
/* NULL: fail to load or create an image				*/
/* image: load or create an image successfully				*/
IMAGE *LoadImage(const char *fname);

/* Save a processed image 		*/
/* Return values:			*/
/* 0: successfully saved the image	*/
/* 1: Cannot open the file for writing	*/
/* 2: File error while writing to file	*/
int SaveImage(const char *fname, const IMAGE *image);

#endif

/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
