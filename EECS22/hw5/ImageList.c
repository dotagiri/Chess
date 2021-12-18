/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2017                     */
/*                                                                   */
/* Author: Tim Schmidt                                               */
/* Date: 11/09/2017                                                  */
/*                                                                   */
/* ImageList.c: source file for image list manipulations             */
/*                                                                   */
/*********************************************************************/

#include <stdlib.h>
#include <assert.h>
#include "ImageList.h"

/* Create a new image entry */
IENTRY *CreateImageEntry(void)
{	
	IENTRY *e;

	/*allocate memory for IENTRY*/
	e = malloc(sizeof(IENTRY));
	if (! e){
		perror("Out of memory! Aborting...");
		exit(10);
		} /*fi*/

	/*initialize to NULL*/
	e->List = NULL;
	e->Next = NULL;
	e->Prev = NULL;
	e->RGBImage = NULL;
	e->YUVImage = NULL;
	return e;
} /*end of CreateImageEntry*/

/* Delete image entry (and image objects)*/
void DeleteImageEntry(IENTRY *e)
{
	/*assert that entry  exists before deleting anything*/
	assert(e);

	e->List = NULL;
	e->Next = NULL;
	e->Prev = NULL;
	if (e->RGBImage){
		DeleteImage(e->RGBImage);
		e->RGBImage = NULL;
		} /*fi*/
	if (e->YUVImage){
		DeleteYUVImage(e->YUVImage);
		e->YUVImage = NULL;
		} /*fi*/
	free(e);
}

/* Create a new image list */
ILIST *CreateImageList(void)
{
	ILIST *l;
	
	/*allocate memory for ILIST*/
	l = malloc(sizeof(ILIST));
	if (! l){
		perror("Out of memory! Aborting...");
		exit(10);
		} /*fi*/
	l->length = 0;
	l->First = NULL;
	l->Last = NULL;
	return l;	
}/*end of CreateImageList*/

/* Delete an image list (and all entries) */
void DeleteImageList(ILIST *list)
{
	/*add assertions for ImageList structure*/
	assert(list);

	/*declare current and next entries for Image*/
	IENTRY *e, *n;

	e = list->First;
	while(e){
		n = e->Next;
		DeleteImageEntry(e);
		e = n;
		} /*elihw*/
	free(list);	
} /*end of DeleteImageList*/

/* Insert a RGB image to the image list at the end */
void AppendRGBImage(ILIST *list, IMAGE *RGBImage)
{
	/*make sure list and the image exists*/
	assert(list);
	assert(RGBImage);	
	/*call CreateImageEntry to allocate space for new image*/
	IENTRY *e = CreateImageEntry();
	e->RGBImage = RGBImage;
	e->YUVImage = NULL;
	e->List = list;

	/*check the end of list*/
	if (list->Last){
		e->List = list;
		/*since its at the end the Next should point to nothing*/
		e->Next = NULL;

		/*previous is the new last*/
		e->Prev = list->Last;
		list->Last->Next = e;
		list->Last = e;
		} /*fi*/
	else{
		e->List = list;
		e->Next = NULL;
		e->Prev = NULL;
		list->First = e;
		list->Last = e;
		} /*esle*/

	list->length++;
} /*end of AppendRGBImage*/

/* Insert a YUV image to the image list at the end */
void AppendYUVImage(ILIST *list, YUVIMAGE *YUVImage)
{
	/*make sure list and image exists*/
	assert(list);
	assert(YUVImage);
	
	/*allocate memory for new image*/
	IENTRY *e = CreateImageEntry();
	e->RGBImage = NULL;
	e->YUVImage = YUVImage;
	e->List = list;

	/*check end of lsit*/
	if(list->Last){
		e->List = list;
		e->Next = NULL;
		e->Prev = list->Last;
		list->Last->Next = e;
		list->Last = e;
		} /*fi*/
	else{
		e->List = list;
		e->Next = NULL;
		e->Prev = NULL;
		list->First = e;
		list->Last = e;
		} /*esle*/
	list->length++;
} /*end of AppendYUVImage*/

/* Reverse an image list */
void ReverseImageList(ILIST *list)
{
	assert(list);
	/*declare variables for entries and new list*/
	IENTRY *current = NULL;
	IENTRY *nPrevious = NULL;
	IENTRY *nlist = NULL;

	current = list->First;
	while(current!= NULL){ /*while loop to change every entry*/
		nPrevious = current->Prev;
		current-> Prev = current->Next;
		current->Next = nPrevious;
		current = current->Prev;
		} /*elihw*/
	nlist = list->First;
	list->First = list->Last;
	list->Last = nlist;
} /*end of ReverseImageList*/

/* EOF */
