Author: Daisuke Otagiri
Date: 3/15/2020
=========================================================================
The goal of this program is to produce a movie from an image or filter. 
Given the frames, start, end, and step size, the program will create a 
movie with the specified amount of frames. The available filters are:
Black and White, HueRotate, and Reverse. Filters can be applied using
-bw, -hue, or -reverse in the command line. 

MovieLab.c is responsible for the command line arguments and print 
statements after the program is ran. Each conditional is activated by
using strcmp to see if the user inputted the specific command. After
going through each command, the program will leave flags up so the proper
print statements can go off after the for loop. For loading movie, since
frameNum, width and height aren't defined yet until after the loop, 
LoadMovie must be called in the importFlag so the proper movie can be 
loaded. Same for Reverse, ReverseImageList requires the movie from LoadMovie
so it must be called after the movie is loaded. This requires a separate flag
for the print statement "Operation Reverse is done".

Movie.c allocates, deallocates and converts RGB to YUV or YUV to RGB.
MovieHeight and MovieWidth can also be accessed from Movie.c mainly used
for the for loops in other files. RGV to YUV and vice versa uses a function
called clip that makes RGB values stay in the bound 0-255. I defined this function
before the RGB2YUV and YUV2RGB functions. 

DIPs.c contains the filters Black and White and HueRotate. Black and White
turns the Movie into black and white given the percentage over frames of the 
movie. 100% implies completely black and white and 0% is the original image.
Black and White is applied by dividing the sum of RGB values by 3, subtracting
this value by the original RGB and finally multiplying it by percent and adding 
it back to the RGB values. 

HueRotate changes the color of a RGB pixel gradually given the percentage. 
Both Black and White and HueRotate converts int percent to floating percent
in order to calculate the new RGB values.

Reverse filter reverses the movie from an inpute movie. This method is simply done
by reversing every entry in the ImageList by using pointers, setting previous 
values to next values, next to previous, first to last and last to first. I
swapped the pointers by delcaring a temporary pointers that stored the original
addresses they were pointing to. This way the addresses are not lost and can be 
properly modified so everything is in reverse order. 

IterativeFilter.c creates a movie using the image by copying it depending on the range of
start to end (specific by user in command line). For each frame, an image must be stored and
applied with the appropriate filter. This image is then appended so the next image can be 
processed. Lastly RGB2YUVMovie is called to convert the RGB images into YUV so a movie can
be finally created with YUV values. 

ImageList.c uses a double-linked list to store frames of the movie in the correct order. 
The entries contain Prev (previous), and Next (next). Using the structures of ImageEntry and List, 
ImageList.c creates, deletes, and append RGB or YUV Images by using pointers from theses 
structures defined in ImageList.h. ReverseImageList reverses the order of the entries so 
an outputted movie will be in reverse order because of the reverrsed ImageList.

===========================================================================================
EOF 
