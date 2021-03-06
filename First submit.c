#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

/* bug
会跳过不一样的数和后面一样的数合并
当没有空格但游戏可以继续时炸
两个块从最远处移向一边移动出问题eg：8|2|0|0 》》0|8|0|2
合并数出错  > 后发现不是合并的锅
上面两条在源程序处理时有冲突只能满足其一，改变算法现均可实现

无效动作未处理
在做出动作后才报游戏结束
*/
int run(int(*s)[4]);
char direction();//读取键盘的方向键
void prBoard(int(*s)[4]);
void merge_right(int(*s)[4]);
void move_right(int(*s)[4]);
int judge(int(*s)[4]);
int rand24();
int randBoard(int(*s)[4]);
void merge_left(int(*s)[4]);
void move_left(int(*s)[4]);
void merge_up(int(*s)[4]);
void move_up(int(*s)[4]);
void move_down(int(*s)[4]);
void merge_down(int(*s)[4]);
int judge_down(int(*s)[4]);
int judge_up(int(*s)[4]);
int judge_right(int(*s)[4]);
int judge_left(int(*s)[4]);



int score = 0;
// int board[4][4] = {
// 	{2,0,0,8},  //横向为排标记i，纵向为列标记为j
// 	{0,2,16,4},
// 	{0,0,0,0},
// 	{0,0,0,0}
// 	};//显示存储数据的数组
int board[4][4] = { 0 };
int main() {

	run(board);
	// prBoard(board);
	// merge_left(board);
	// prBoard(board);
	// move_left(board);
	// prBoard(board);



	// getchar();
	return 0;
}

char direction()//读取键盘的方向键
{
	int c1 = _getch(), c2 = _getch();
	if (c2 == 72)return 'u';  //w
	if (c2 == 80)return 'd';  //s
	if (c2 == 75)return 'l';  //a
	if (c2 == 77)return 'r';  //d
	return 'NULL';
}

void prBoard(int(*s)[4]) {  //显示此时的游戏盘
	printf("+----|----|----|----+\n");
	for (int i = 0; i < 4; i++) {
		printf("|");
		for (int j = 0; j < 4; j++) {
			if (s[i][j] == 0)
				printf("    |");
			else
				printf("%4d|", s[i][j]);
		}
		printf("\n|----+----+----+----|\n");
	}
	// printf("|%4d|%4d|%4d|%4d|\n",s[0][0],s[0][1],s[0][2],s[0][3]);
	// printf("|----+----+----+----|\n");
	// printf("|%4d|%4d|%4d|%4d|\n",s[1][0],s[1][1],s[1][2],s[1][3]);
	// printf("|----+----+----+----|\n");
	// printf("|%4d|%4d|%4d|%4d|\n",s[2][0],s[2][1],s[2][2],s[2][3]);
	// printf("|----+----+----+----|\n");
	// printf("|%4d|%4d|%4d|%4d|\n",s[3][0],s[3][1],s[3][2],s[3][3]);
	// printf("+----|----|----|----+\n");
}

void merge_right(int(*s)[4]) {  //向右合并，产生分数
	for (int i = 0; i < 4; i++) {  //i为每一行遍历
		for (int j = 3; j >= 0; j--) {  //j为一行中元素的遍历
			if (s[i][j] == 0)  //为零则跳过
				continue;
			else {
				for (int q = j - 1; q >= 0; q--) {
					if ((s[i][q] != 0) && (s[i][q] != s[i][j]))
						break;
					if (s[i][j] == s[i][q]) {
						s[i][j] += s[i][q];  //加到前面那个变量中
						score += s[i][j];  //累加分数
						s[i][q] = 0;  //清空该元素
						j = q;  //跳过被清空的元素
						printf("\a");
						break;
					}
				}
			}
		}
	}
}

void move_right(int(*s)[4]) {  //向右移,不会产生分数增加
	for (int i = 0; i < 4; i++) {  //i为每一行的遍历
		for (int j = 3; j >= 0; j--) {  //j为一行中每个变量的遍历
			if (s[i][j] == 0) {
				for (int q = j - 1; q >= 0; q--) {
					if (s[i][q] == 0)
						continue;
					else {
						s[i][j] = s[i][q];
						s[i][q] = 0;
						j -= 1;
					}
				}
			}
		}
	}
}

int judge(int(*s)[4]) {  //返回0为不可继续游戏，返回1则可继续游戏
	int n = 0;
	for (int i = 0; i < 4; i++) {  //i为每一行的遍历
		for (int j = 3; j >= 0; j--) {  //j为一行中每个变量的遍历
			if (s[i][j] == 0) {
				return 1;
			}
		}
	}  //又任意一个位置为零即返回1结束函数，若没有零，则进行接下来的检擦
	//从各个方向进行检测是否可以移动
	//只需要横纵检查即可

	//从横向向右移的方式进行检查
	for (int i = 0; i < 4; i++) {  //i为每一行的遍历
		for (int j = 3; j > 0; j--) {  //j为一行中每个变量的遍历
			if (s[i][j] == s[i][j - 1])
				return 1;
		}
	}
	//从纵向向上移的方式进行检擦
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 3; i++) {
			if (s[i][j] == s[i + 1][j])
				return 1;
		}
	}
	//通过以上所有检查方法都没有通过，则不能继续游戏则接下来返回0
	return 0;
}

int rand24() {  //生成2或4的随机数
	srand((unsigned)time(0));
	//return (rand() % 5 + 1);  //输出1-5的随机数
	if ((rand() % 5 + 1) == 1)
		return 4;
	else
		return 2;
}

int randBoard(int(*s)[4]) {  //在随机一个空位置生成2或4。返回值无意义，只是用于结束函数
	int n = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (s[i][j] == 0)
				n++;
		}
	}  //得到有多少个位置为零
	if (n == 0)
		return -1;
	srand((unsigned)time(0));
	int _n = rand() % n + 1;  //从中取一个
	n = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (s[i][j] == 0) {
				n++;
				if (_n == n) {
					s[i][j] = rand24();
					return 0;
				}
			}
		}
	}
}

void merge_left(int(*s)[4]) {  //向左合并，产生分数
	for (int i = 0; i < 4; i++) {  //i为每一行遍历，从上至下
		//int num = 0;
		for (int j = 0; j < 4; j++) {  //j为一行中元素的遍历
			if (s[i][j] == 0)  //为零则跳过
				continue;
			else {
				for (int q = j + 1; q < 4; q++) {
					if ((s[i][q] != 0) && (s[i][q] != s[i][j]))
						break;
					if (s[i][j] == s[i][q]) {
						s[i][j] += s[i][q];  //加到前面那个变量中
						score += s[i][j];  //累加分数
						s[i][q] = 0;  //清空该元素
						j = q;  //跳过被清空的元素
						printf("\a");
						break;
					}
				}
			}
		}
	}
}

void move_left(int(*s)[4]) {  //向左移动
	for (int i = 0; i < 4; i++) {  //i为每一行的遍历

		for (int j = 0; j < 4; j++) {  //j为一行中每个变量的遍历
			if (s[i][j] == 0) {
				for (int q = j + 1; q < 4; q++) {
					if (s[i][q] == 0)
						continue;
					else {
						s[i][j] = s[i][q];
						s[i][q] = 0;
						j += 1;
					}
				}
			}
		}
	}
}

void merge_up(int(*s)[4]) {
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 4; i++) {
			if (s[i][j] == 0)
				continue;
			else {
				for (int q = i + 1; q < 4; q++) {
					if ((s[q][j] != 0) && (s[q][j] != s[i][j]))
						break;
					if (s[i][j] == s[q][j]) {
						s[i][j] += s[q][j];  //加到前面那个变量中
						score += s[i][j];  //累加分数
						s[q][j] = 0;  //清空该元素
						i = q;  //跳过被清空的元素
						printf("\a");
						break;
					}
				}
			}
		}
	}
}

void move_up(int(*s)[4]) {
	for (int j = 0; j < 4; j++) {  //i为每一行的遍历
		for (int i = 0; i < 4; i++) {  //j为一行中每个变量的遍历
			if (s[i][j] == 0) {
				for (int q = i + 1; q < 4; q++) {
					if (s[q][j] == 0)
						continue;
					else {
						s[i][j] = s[q][j];
						s[q][j] = 0;
						i += 1;
					}
				}
			}
		}
	}
}

void merge_down(int(*s)[4]) {
	for (int j = 0; j < 4; j++) {  //i为每一行遍历
		for (int i = 3; i >= 0; i--) {  //j为一行中元素的遍历
			if (s[i][j] == 0)  //为零则跳过
				continue;
			else {
				for (int q = i - 1; q >= 0; q--) {
					if ((s[q][j] != 0) && (s[q][j] != s[i][j]))
						break;
					if (s[i][j] == s[q][j]) {
						s[i][j] += s[q][j];  //加到前面那个变量中
						score += s[i][j];  //累加分数
						s[q][j] = 0;  //清空该元素
						i = q;  //跳过被清空的元素
						printf("\a");
						break;
					}
				}
			}
		}
	}
}

void move_down(int(*s)[4]) {
	for (int j = 0; j < 4; j++) {  //i为每一行的遍历
		for (int i = 3; i >= 0; i--) {  //j为一行中每个变量的遍历
			if (s[i][j] == 0) {
				for (int q = i - 1; q >= 0; q--) {
					if (s[q][j] == 0)
						continue;
					else {
						s[i][j] = s[q][j];
						s[q][j] = 0;
						i -= 1;
					}
				}
			}
		}
	}
}

int run(int(*s)[4]) {
	do { //每次游戏结束后再是否重复游戏
		board[4][4] = { 0 };
		system("cls");
		//printf("  2048game\n");
		randBoard(board);
		randBoard(board);
		while (judge(board)) {  //判断后再执行操作
			//randBoard(board);
			system("cls");

			printf("      2048game\n");
			printf("      score:%d\n", score);
			prBoard(board);
			switch (direction()) {
			case 'u':
				if (judge_up(board))
					continue;
				merge_up(board);
				move_up(board);
				break;
			case 'd':
				if (judge_down(board))
					continue;
				merge_down(board);
				move_down(board);
				break;
			case 'l':
				if (judge_left(board))
					continue;
				merge_left(board);
				move_left(board);
				break;
			case 'r':
				if (judge_right(board))
					continue;
				merge_right(board);
				move_right(board);
				break;
			case 'NULL':
				return 0;
			}
			randBoard(board);
			//system("cls");

		}
		system("cls");
		int single = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (s[i][j] == 2048)
					single = 1;
			}
		}
		if (single == 1)
			printf("UNBELIEVABLE!!!\nYOU WIN!!!");
		else
			printf("      GAMEOVER!!!\n");

		printf("Do you wanna play again?\n(enter'y'or'n'):");

	} while (getchar() == 'y');
	//prBoard(board);

	//getchar();
}

int judge_left(int(*s)[4]) {  //向左移动
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			if (((s[i][j] == s[i][j + 1]) && (s[i][j] != 0)) || ((s[i][j] == 0) && (s[i][j + 1]) != 0))
				return 0;
		}
	}
	return 1;
}

int judge_right(int(*s)[4]) {  //向右移动
	for (int i = 0; i < 4; i++) {
		for (int j = 3; j > 0; j--) {
			if (((s[i][j] == s[i][j - 1]) && (s[i][j] != 0)) || ((s[i][j] == 0) && (s[i][j - 1]) != 0))
				return 0;
		}
	}
	return 1;
}

int judge_up(int(*s)[4]) { //向上移动
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 3; i++) {
			if (((s[i][j] == s[i + 1][j]) && (s[i][j] != 0)) || ((s[i][j] == 0) && (s[i + 1][j]) != 0))
				return 0;
		}
	}
	return 1;
}

int judge_down(int(*s)[4]) { //向下移动
	for (int j = 0; j < 4; j++) {
		for (int i = 3; i > 0; i--) {
			if (((s[i][j] == s[i - 1][j]) && (s[i][j] != 0)) || ((s[i][j] == 0) && (s[i - 1][j] != 0)))
				return 0;
		}
	}
	return 1;
}
