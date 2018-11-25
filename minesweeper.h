#ifndef minesweeper_h
#define minesweeper_h

#define MINE 10	//10表示地雷

void msInit(int mine, int _row, int _col);
void msEnd();
int msSelect(int x,int y);
int msGetMapLength();
int* msGetMap(int *out);
int* msGetDisplayMap(int* out);

#endif