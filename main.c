#include "display.h"
#include "minesweeper.h"
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>


int main()
{
	int row=20;
	int col=20;

	//光标位置
	int cursor_x=0;
	int cursor_y=0;

	//初始化游戏 10个地雷
	msInit(10,row,col);
	
	int* map=(int*)malloc(sizeof(int)*row*col);
	while(1)
	{	
		//show(msGetMap(map),row,col);
		showAndCursor(msGetDisplayMap(map),row,col,cursor_x,cursor_y);
		char c=getch();
		if(c=='a'||c=='A')
		{
			if(cursor_x>0)cursor_x--;
		}else if(c=='d'||c=='D'){
			if(cursor_x<col-1)cursor_x++;
		}else if(c=='w'||c=='W'){
			if(cursor_y>0)cursor_y--;
		}else if(c=='s'||c=='S'){
			if(cursor_y<row-1)cursor_y++;
		}else if(c=='j'||c=='J'){
			int state=msSelect(cursor_x,cursor_y);
			if(state==1)
			{
				show(msGetMap(map),row,col);
				puts("GAME OVER");
				break;
			}else if(state==2)
			{
				show(msGetMap(map),row,col);
				puts("GAME WIN");
				break;
			}
			
		}
	}
	
	msEnd();
	system("pause");
	
}