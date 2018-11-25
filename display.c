#define display_c

#include "display.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "config.h"

static char* getDisplayCharByIndex(int index);

void show(int* map,int row,int col)
{
	//清屏
	system("cls");
	char str[2000] = "";
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			strcat(str, getDisplayCharByIndex(map[i * col + j]));
		}
		strcat(str, "\n");
	}
	puts(str);
}


void showAndCursor(int* map,int row,int col,int c_x,int c_y)
{
	//清屏
	system("cls");
	char str[2000] = "";
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if(j==c_x&&i==c_y)
			{
				strcat(str,(char*)C_CURSOR);
			}
			else
			{
				strcat(str, getDisplayCharByIndex(map[i * col + j]));
			}
			
		}
		strcat(str, "\n");
	}
	puts(str);
}

static char *getDisplayCharByIndex(int index)
{
	//char *c = (char*)C_BACK;
	char *c = "  ";
	switch (index)
	{	
		case -1:c =(char*)C_BACK;break;
		case 0:c=(char*)C_SPACE;break;
		case 1:c=" 1";break;
		case 2:c=" 2";break;
		case 3:c=" 3";break;
		case 4:c=" 4";break;
		case 5:c=" 5";break;
		case 6:c=" 6";break;
		case 7:c=" 7";break;
		case 8:c=" 8";break;
		case 10:c = (char*)C_MINE;
		break;
	}
	return c;
}
