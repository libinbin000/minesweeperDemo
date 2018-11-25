#define minesweeper_c

#include "minesweeper.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define random(x) (rand() % x)
//#define pos(x,y) (y*col)+(x) //通过x y获取地图数组的位置

static int* getMineList(int* ,int num,int max);	//获取n个不重复随机数
static void openAround(int x,int y);


int row; //行数
int col; //列数
int mapLength;//地图数组长度
int mineNum; //炸弹数
int *map;
int *mask;

static int pos(int x, int y) { return (y * col) + (x); }
static int getx(int index) { return index % col; }
static int gety(int index) { return index / col; }

void msInit(int mine, int _row, int _col)
{
	int len = _row * _col;

	row = _row;
	col = _col;
	mapLength = len;
	mineNum = mine;

	//初始化map
	map = (int *)malloc(sizeof(int) * row * col);
	
	for (int i = 0; i < len; i++)
	{
		map[i] = 0;
	}

	//生成地雷
	int *mineList = (int *)malloc(sizeof(int) * len);
	getMineList(mineList, mine, len);
	for(int i=0;i<mine;i++)
	{
		int minePos=mineList[i];
		map[minePos]=MINE;
	}

	//遍历各个格子获取计算数字
	for (int i = 0; i < len; i++)
	{
		if (map[i] == MINE) continue;

		int aroundMineNum = 0;
		int x = getx(i);
		int y = gety(i);

		if (y > 0 && map[pos(x, y - 1)] == MINE) aroundMineNum++;							//上
		if (y > 0 && x < col - 1 && map[pos(x + 1, y - 1)] == MINE) aroundMineNum++; 		//右上
		if (y > 0 && x > 0 && map[pos(x - 1, y - 1)] == MINE) aroundMineNum++; 				//左上
		if (x > 0 && map[pos(x - 1, y)] == MINE) aroundMineNum++; 							//左
		if (x < col - 1 && map[pos(x + 1, y)] == MINE) aroundMineNum++; 					//左
		if (y < row - 1 && map[pos(x, y + 1)] == MINE) aroundMineNum++; 					//下
		if (y < row - 1 && x > 0 && map[pos(x - 1, y + 1)] == MINE) aroundMineNum++; 		//左下
		if (y < row - 1 && x < col - 1 && map[pos(x + 1, y + 1)] == MINE) aroundMineNum++; 	//右下

		map[i]=aroundMineNum;

		// if (i >= col && map[i - col] == MINE) aroundMineNum++; 					//上
		// if (i >= col + 1 && map[i - col - 1] == MINE) aroundMineNum++; 			//右上
		// if (i >= col - 1 && map[i - col + 1] == MINE) aroundMineNum++; 			//左上
		// if (i >= 1 && map[i - 1] == MINE) aroundMineNum++; 						//左
		// if (i <= len - 1 - 1 && map[i + 1] == MINE) aroundMineNum++; 				//左
		// if (i <= len - 1 - col && map[i + col] == MINE) aroundMineNum++; 			//下
		// if (i <= len - 1 - col + 1 && map[i + col - 1] == MINE) aroundMineNum++;	//左下
		// if (i <= len - 1 - col - 1 && map[i + col + 1] == MINE) aroundMineNum++;	//右下
		
	}

	//初始化mask
	mask = (int *)malloc(sizeof(int) * len);

	for (int i = 0; i < len; i++)
	{
		mask[i] = 1;
	}

}

void msEnd()
{
	if (NULL != map) free(map);
	if (NULL != mask) free(mask);
}

int msGetMapLength()
{
	return mapLength;
}

int* msGetMap(int* out)
{
	return map;
}

int* msGetDisplayMap(int* out)
{
	for (int i = 0; i < mapLength; i++)
	{
		if (mask[i] == 1)
		{
			out[i] = -1;
		}
		else
		{
			out[i] = map[i];
		}
	}
	return out;
}

//返回1代表死了 返回0就没事
int msSelect(int x,int y)
{
	if (map[pos(x, y)] == MINE)
	{
		return 1;
	}
	else if (map[pos(x, y)] == 0)
	{
		openAround(x, y);
	}
	else
	{
		mask[pos(x, y)] = 0;
	}

	//检查是否胜利
	int openNum=0;
	for(int i=0;i<mapLength;i++)
	{
		if(mask[i]==0)openNum++;
	}

	if(openNum >=mapLength - mineNum)
	{
		return 2;
	}

	return 0;
}

//显示附近的空的格子
static void openAround(int x,int y)
{
	int index = pos(x, y);
	if (mask[index] == 0)return;

	mask[index] = 0;

	if(map[index]!=0)return;

	if (y - 1 >= 0)
		openAround(x, y - 1); //上
	if (y + 1 < row)
		openAround(x, y + 1); //下
	if (x - 1 >= 0)
		openAround(x - 1, y); //左
	if (x + 1 < col)
		openAround(x + 1, y); //右
}

static int* getMineList(int* list,int num, int max) 
{
	int* arr = (int *)malloc(sizeof(int) * max);

	//设置1~max
	for (int i = 0; i < max; i++)
	{
		arr[i] = i;
	}

	//打乱顺序
	srand((int)time(0));
	for (int i = 0; i < max; i++)
	{
		int rnd = random(max - 1);
		int temp = arr[i];
		arr[i] = arr[rnd];
		arr[rnd] = temp;
	}


	//获取前num个
	for (int i=0;i<num;i++)
	{
		list[i] = arr[i];
	}

	free(arr);

	return list;
}

// void test(){
// 	int* test=(int *)malloc(sizeof(int) * 60);
// 	getMineList(test,60,255);
// 	for (int i=0;i<60;i++)
// 	{
// 		printf("%d\n",test[i]);
// 	}
// }