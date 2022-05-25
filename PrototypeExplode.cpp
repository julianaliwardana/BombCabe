#include<iostream>
#include<windows.h>
#include<thread>
#include<conio.h>
#include<future>
#include "MyFunction.h"
using namespace std;
#define ENTER 13
#define UP 72
#define DOWN 80
#define LEFT  75
#define RIGHT 77

char map[20][20];
int posX = 1, posY = 1;
short curX = 2, curY = 1;
int range=5;
int bombX,bombY;

//void changeCursorPosition(short x, short y){ //change cursor position
//	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//	COORD pos = {x, y};
//	SetConsoleCursorPosition(hConsole, pos);
//}

void generateMap(){
	for(int i = 0; i < 20; i++){
		if(i == 0 || i == 19) for(int j = 0; j < 20; j++) map[i][j] = '#';
		else{
			for(int j = 0; j < 20; j++){
				if(j == 0 || j == 19) map[i][j] = '#';
				else map[i][j] = ' ';
			}
		}
	}
	map[posY][posX] = '@';
}

void printMap(){
	for(int i = 0; i < 20; i++){
		for(int j = 0; j < 20; j++){
			printf("%c ", map[i][j]);	
		}
		printf("\n");
	}
}

void planABomb(short y, short x, int cY, int cX){
	changeCursorPosition(curX + x, curY + y);
	
	short curBombX=curX+x;
	short curBombY=curY+y;
	setcolor(15);
	printf("%c", 207);
	this_thread::sleep_for(chrono::milliseconds(2000));
	
	changeCursorPosition(curBombX,curBombY);
//	this_thread::sleep_for(chrono::milliseconds(5000));
	
	auto bombUp = [](short curBombX, short curBombY){
		for(int i=1;i<=range;i++){
			changeCursorPosition(curBombX,curBombY-i);
			setcolor(4);
			printf("%c",176);
			this_thread::sleep_for(chrono::milliseconds(114));
		}
	};

//	printf("%u %u",curBombY,curBombX);
	auto bombDown = [](short curBombX, short curBombY){
		this_thread::sleep_for(chrono::milliseconds(16));
		for(int i=1;i<=range;i++){
			changeCursorPosition(curBombX,curBombY+i);
			setcolor(4);
			printf("%c",176);
			this_thread::sleep_for(chrono::milliseconds(115));
		}
	};	
	
	auto bombLeft = [](short curBombX, short curBombY){
		this_thread::sleep_for(chrono::milliseconds(32));
		for(int i=1;i<=range;i++){
			changeCursorPosition(curBombX-i,curBombY);
			setcolor(4);
			printf("%c",176);
			this_thread::sleep_for(chrono::milliseconds(116));
		}
	};	
	
	auto bombRight = [](short curBombX, short curBombY){
		this_thread::sleep_for(chrono::milliseconds(50));
		for(int i=1;i<=range;i++){
			changeCursorPosition(curBombX+i,curBombY);
			setcolor(4);
			printf("%c",176);
			this_thread::sleep_for(chrono::milliseconds(117));
		}
	};	
	thread up(bombUp, curBombX, curBombY);
	thread down(bombDown, curBombX, curBombY);
	thread left(bombLeft, curBombX, curBombY);
	thread right(bombRight, curBombX , curBombY);	
	up.detach();
	down.detach();
	left.detach();
	right.detach();
	
	setcolor(15);
	this_thread::sleep_for(chrono::milliseconds(1000));
	changeCursorPosition(curBombX,curBombY);
	printf("%c",32);
	map[bombY][bombX]=' ';
	auto removebombUp = [](short curBombX, short curBombY){
		for(int i=1;i<=range;i++){
			changeCursorPosition(curBombX,curBombY-i);
			printf("%c",32);
			this_thread::sleep_for(chrono::milliseconds(110));
		}
	};

	auto removebombDown = [](short curBombX, short curBombY){
		this_thread::sleep_for(chrono::milliseconds(16));
		for(int i=1;i<=range;i++){
			changeCursorPosition(curBombX,curBombY+i);
			printf("%c",32);
			this_thread::sleep_for(chrono::milliseconds(111));
		}
	};	
	
	auto removebombLeft = [](short curBombX, short curBombY){
		this_thread::sleep_for(chrono::milliseconds(32));
		for(int i=1;i<=range;i++){
			changeCursorPosition(curBombX-i,curBombY);
			printf("%c",32);
			this_thread::sleep_for(chrono::milliseconds(112));
		}
	};	
	
	auto removebombRight = [](short curBombX, short curBombY){
		this_thread::sleep_for(chrono::milliseconds(50));
		for(int i=1;i<=range;i++){
			changeCursorPosition(curBombX+i,curBombY);
			printf("%c",32);
			this_thread::sleep_for(chrono::milliseconds(113));
		}
	};	
	
	thread reup(removebombUp, curBombX, curBombY);
	thread redown(removebombDown, curBombX, curBombY);
	thread releft(removebombLeft, curBombX, curBombY);
	thread reright(removebombRight, curBombX , curBombY);	
	reup.detach();
	redown.detach();
	releft.detach();
	reright.detach();
	
}

int main(){
	generateMap();
	printMap();
	char key;
	int lastTurn = -1;
	while(key != ENTER){

		key=getch();
		setcolor(15);
		if(key == UP){
			if(map[posY - 1][posX] == ' '){
				map[posY--][posX] = ' ';
				map[posY][posX] = '@';
				changeCursorPosition(curX, curY--);
				printf(" ");
				changeCursorPosition(curX, curY);
				printf("@");
				lastTurn = 8;
			}
		}else if(key == DOWN){
			if(map[posY + 1][posX] == ' '){
				map[posY++][posX] = ' ';
				map[posY][posX] = '@';
				changeCursorPosition(curX, curY++);
				printf(" ");
				changeCursorPosition(curX, curY);
				printf("@");
				lastTurn = 2;
			}
		}else if(key == LEFT){
			if(map[posY][posX - 1] == ' '){
				map[posY][posX--] = ' ';
				map[posY][posX] = '@';
				changeCursorPosition(curX, curY);
				curX -= 2;
				printf(" ");
				changeCursorPosition(curX, curY);
				printf("@");
				lastTurn = 4;
			}
		}else if(key == RIGHT){
			if(map[posY][posX + 1] == ' '){
				map[posY][posX++] = ' ';
				map[posY][posX] = '@';
				changeCursorPosition(curX, curY);
				curX += 2;
				printf(" ");
				changeCursorPosition(curX, curY);
				printf("@");
				lastTurn = 6;
			}
		}else if(key == 32){
			if(lastTurn == 8){
				if(map[posY - 1][posX] == ' '){
					map[posY-1][posX]=207;
					thread plan(planABomb, -1, 0, -1, 0);
					plan.detach();
					bombX=posX;
					bombY=posY-1;
				}
			}else if(lastTurn == 2){
				if(map[posY + 1][posX] == ' '){
					map[posY+1][posX]=207;
					thread plan(planABomb, 1, 0, 1, 0);
					plan.detach();
					bombX=posX;
					bombY=posY+1;
				}
			}else if(lastTurn == 4){
				if(map[posY][posX - 1] == ' '){
					map[posY][posX-1]=207;
					thread plan(planABomb, 0, -2, 0, -1);
					plan.detach();
					bombX=posX-1;
					bombY=posY;
				}
			}else if(lastTurn == 6){
				if(map[posY][posX + 1] == ' '){
					map[posY][posX+1]=207;
					thread plan(planABomb, 0, 2, 0, 1);
					plan.detach();
					bombX=posX+1;
					bombY=posY;
				}
			}
		}
	}
	return 0;
}
