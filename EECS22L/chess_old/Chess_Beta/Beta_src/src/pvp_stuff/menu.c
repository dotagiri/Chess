#include <stdio.h>

int menu_returned_value (void)
{
	//things that are on the menu are the pvp, pvc, records, the official rules
	//and the ability to exit
	//
	/*
 *		integer values that are returned based on the choices that are made:
 *
 *		for PVP: 1 is returned
 *		
 *		for PVC where player is white and easy mode: 2 is returned
 *		for PVC where player is white and medium mode: 3 is returned
		for PVC where player is white and hard mode: 4 is returned
 
*		for PVC where player is black and easy mode: 5 is returned
*		for PVC where player is black and medium mode: 6 is returned
*		for PVC where player is black and hard mode: 7 is returned
*
*		for official rules of chess: 8 is returned
*		
*		return 0 to exit the game	
 *		
 *
 * 	*/
	
	int value;
	int level;
	int player_color;

	printf("***Main Menu***\n");

	printf("(1)Player vs Player mode\n ");
	printf("(2)Player vs Computer mode\n "); 
	printf("(3)Rules of Chess\n ");
	printf("Enter your option with the numbers provided: ");

	scanf("%d", &value);
	//need to add check so taht the value being read in is a integer in the given range
	switch(value)
	{
		case 1:
	//		printf("returned 1\n");
			return 1;
			break;
		case 2:
			printf("What color do you want to play as?\n");
			printf("(1)White\n(2)Black\nMake your choice: ");
			scanf("%d", &player_color);
			printf("What difficulty do you want the computer to be?\n");
			printf("(1)Easy\n(2)Medium\n(3)Hard\nMake your choice: ");
			scanf("%d",&level);
			if(player_color == 1)
			{
				if(level == 1)
				{
				//	printf("returned 2\n");
					return 2;
				}
				else if(level == 2)
				{
					return 3;
				}
				else if(level == 3)
				{
					return 4;
				}
			}
			else if(player_color == 2)
			{
				if(level == 1)
				{
					return 5;
				}
				else if(level == 2)
				{
					return 6;
				}
				else if(level == 3)
				{
					return 7;
				}
			}
			else
			{
				;
			}
			break;
		case 3:
	//		printf("returned 8\n");	
			return 8;
			break;
		default:
			;
	}
	return 0;

}
