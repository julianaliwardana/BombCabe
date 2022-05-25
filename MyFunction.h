#include<iostream>
#include<windows.h>
#include<string>
#include<conio.h>
#define PLAYER 153
#define EXPLODE 'X'
#define BOMB 207
#define SPACE 32
#define NOT_IMMORTAL_WALL '#'
#define ENEMY 232
#define MAX 26
#define DOOR 'O'
using namespace std;

//scoreBoard player
struct node{
	char nama[50];
	int score;
	struct node *next,*prev;
}*head[MAX],*tail[MAX];

//appliance
bool playSong = true;
short curX = 2, curY = 1;
int maxPlaceBomb = 1;

//Check cheat is active or not
bool THROUGHTHEWALL = false; //tembus tembok (batal)
bool IMMUNE = false; //kebal (ga mati - mati)
bool INFINITYBOMB = false; //bisa taro bomb banyak (kalo true, maxPlaceBomb = 99)

//Player's stats
int level = 1; //level dungeon (max = 2)
int armor = 0; //armor, biar ga reset (batal)
int live = 2; //nyawa player
int range = 1; //panjang ledakan bomb (range max = 2)
bool squareBomb = false; //meledaknya kotak
int score = 0;
//map
char map[25][25];
char check[25][25];
int posX, posY, mapX, mapY, X, Y;
int notImmortalX[105], notImmortalY[105];
int enemyX[10],enemyY[10];
int curEnemyX[10],curEnemyY[10];
int door;

//END Variable Session

void setcolor(unsigned short color){ //change color
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	
	SetConsoleTextAttribute(hCon,color);
}

void changeCursorPosition(short x, short y){ //change cursor position
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = {x, y};
	SetConsoleCursorPosition(hConsole, pos);
}

string getName(){
	changeCursorPosition(18, 13);
	string temp = "";
	int count = 0;
//	bool check = false;
	char key;
	while(key != 13){
		key = getch();
		if(count < 8){
			if(key >= 'A' && key <= 'Z'){
				printf("%c ", key);
				temp += key;
				count++;
			}else if(key >= 'a' && key <= 'z'){
				printf("%c ", key - 32);
				temp += key;
				count++;
			}else if(key == 8 && count >= 1){
				printf("\b\b  \b\b");
				temp.pop_back();
				count--;
			}
			if(count == 8) printf("\b");
		}else{
			if(key == 8){
				printf("\b  \b\b");
				temp.pop_back();
				count--;
			}
		}
	}
	return temp;
}

void randomWall()
{
	int i, x, y;
	int totalWall = level * 5;
	
	for(i = 0; i < totalWall; i++)
	{
		loop:
		x = rand() % (mapX - 2) + 1;
		y = rand() % (mapY - 2) + 1;
		if(map[y][x] == '0' && y > 2 && x > 2){
			map[y][x] = NOT_IMMORTAL_WALL;
			notImmortalX[i] = x;
			notImmortalY[i] = y;
		} 
		else goto loop;
	}
	door = rand() % totalWall;
}

void randomEnemy(){
	int i,x,y;
	int totalEnemy = 1;
	
	for(i=0;i<totalEnemy;i++){
		loop:
		x=rand()%(mapX-2)+1;
		y=rand()%(mapY-2)+1;
		if(map[y][x]=='0'&&y>2&&x>2){
			map[y][x]=ENEMY;
			enemyX[i]=x;
			enemyY[i]=y;
			curEnemyX[i]=x+5;
			curEnemyY[i]=y+3;
		}else{
			goto loop;
		}
	}
}

void moveEnemy(){
	int move=rand()%4;
	
	if(move==0&&map[enemyY[0]][enemyX[0]+1]==SPACE){
		map[enemyY[0]][enemyX[0]++]=SPACE;
		map[enemyY[0]][enemyX[0]]=ENEMY;
		changeCursorPosition(curEnemyX[0]++, curEnemyY[0]);
		printf(" ");
		changeCursorPosition(curEnemyX[0], curEnemyY[0]);
		printf("%c",ENEMY);
		changeCursorPosition(curEnemyX[0], curEnemyY[0]);	
	}else if(move==1&&map[enemyY[0]][enemyX[0]-1]==SPACE){
		map[enemyY[0]][enemyX[0]--]=SPACE;
		map[enemyY[0]][enemyX[0]]=ENEMY;
		changeCursorPosition(curEnemyX[0]--, curEnemyY[0]);
		printf(" ");
		changeCursorPosition(curEnemyX[0], curEnemyY[0]);
		printf("%c",ENEMY);
		changeCursorPosition(curEnemyX[0], curEnemyY[0]);
	}else if(move==2&&map[enemyY[0]+1][enemyX[0]]==SPACE){
		map[enemyY[0]++][enemyX[0]]=SPACE;
		map[enemyY[0]][enemyX[0]]=ENEMY;
		changeCursorPosition(curEnemyX[0], curEnemyY[0]++);
		printf(" ");
		changeCursorPosition(curEnemyX[0], curEnemyY[0]);
		printf("%c",ENEMY);
		changeCursorPosition(curEnemyX[0], curEnemyY[0]);
	}else if(move==3&&map[enemyY[0]-1][enemyX[0]]==SPACE){
		map[enemyY[0]--][enemyX[0]]=SPACE;
		map[enemyY[0]][enemyX[0]]=ENEMY;
		changeCursorPosition(curEnemyX[0], curEnemyY[0]--);
		printf(" ");
		changeCursorPosition(curEnemyX[0], curEnemyY[0]);
		printf("%c",ENEMY);
		changeCursorPosition(curEnemyX[0], curEnemyY[0]);
	}

}

void scanMap(){
	FILE *op = fopen("Assets/Texture/Map.txt", "r");
	int i = 0;
	while(fscanf(op, "%[^\n]\n", map[i]) != EOF){
		i++;
	}
	fclose(op);
	posX = 1;
	posY = 1;
	mapX = strlen(map[0]) - 1;
	mapY = i;
	map[posY][posX] = PLAYER;
	randomWall();
	randomEnemy();
}

void printMap(){
	changeCursorPosition(0, 3);
	for(int i = 0; i < 21; i++){
		printf("     ");
		for(int j = 0; j < 21; j++){
			if(map[i][j] == '1' || check[i][j] == '1'){
				setcolor(4);
				map[i][j] = 178;
				check[i][j] = '1';
 			}
			else if(map[i][j] == '2' || check[i][j] == '2'){
				setcolor(8);
				map[i][j] = 219;
				check[i][j] = '2';
			}
			else if(map[i][j] == '0'){
				map[i][j] = ' ';
				check[i][j] = '0';
			}
			else
				setcolor(15);
			cout << map[i][j];
		}
		cout << endl;
	}
	changeCursorPosition(6, 4);
}

struct node *createNewNode(char *nama,int score){
			struct node *newNode= new node;
			
			newNode->next=NULL;
			newNode->prev=NULL;
			strcpy(newNode->nama,nama);
			newNode->score=score;			
			
			return newNode;
		}
		
		int getValue(char *nama){
			return nama[0] % 'A';
		}
		
		void insert(char *nama,int score){
			int key=getValue(nama);
			
			struct node *newNode= createNewNode(nama,score);
			
			if(head[key]==NULL){
				head[key]=tail[key]=newNode;
			}else{
				newNode->prev=tail[key];
				tail[key]->next=newNode;
				tail[key]=newNode;
			}
		}

void planABomb(int y, int x){
	changeCursorPosition(curX, curY);
	
	//koordinat si bom di cmd
	short curBombX = curX;
	short curBombY = curY;
	
	map[y][x] = BOMB;
	
	setcolor(15);
	this_thread::sleep_for(chrono::milliseconds(2000));
	changeCursorPosition(curBombX, curBombY);
	
	auto bombUp = [=](short curBombX, short curBombY){
		int start = 7;
		for(int i=1;i<=range;i++){
			if((y - i > 0) && (map[y - i][x] == SPACE || map[y - i][x] == NOT_IMMORTAL_WALL)){
				changeCursorPosition(curBombX, curBombY - i);
				if(y - i == notImmortalY[door] && x == notImmortalX[door]){
					setcolor(12);
					score++;
					printf("%c", DOOR);
					map[y - i][x] = DOOR;
					setcolor(15);
					break;	
				}else{
					setcolor(4);
					printf("%c", EXPLODE);	
				}
				setcolor(15);
				if(map[y - i][x] == NOT_IMMORTAL_WALL){
					map[y - i][x] = EXPLODE;
					score++;
					break;
				}
				map[y - i][x] = EXPLODE;
				this_thread::sleep_for(chrono::milliseconds(start % 100));
			}else break;
			start += (start / 2 + pow(start, 3));
		}
	};

	auto bombDown = [=](short curBombX, short curBombY){
		this_thread::sleep_for(chrono::milliseconds(13));
		int start = 13;
		for(int i=1;i<=range;i++){
			if((y + i < mapY) && (map[y + i][x] == SPACE || map[y + i][x] == NOT_IMMORTAL_WALL)){
				changeCursorPosition(curBombX, curBombY + i);
				if(y + i == notImmortalY[door] && x == notImmortalX[door]){
					setcolor(12);
					printf("%c", DOOR);	
					score++;
					map[y + i][x] = DOOR;
					setcolor(15);
					break;
				}else{
					setcolor(4);
					printf("%c",EXPLODE);	
				}
				setcolor(15);
				if(map[y + i][x] == NOT_IMMORTAL_WALL){
					map[y + i][x] = EXPLODE;
					score++;	
					break;
				}
				map[y + i][x] = EXPLODE;
				this_thread::sleep_for(chrono::milliseconds(start % 100));
			}else break;
			start += (start / 2 + pow(start, 3));
		}
	};	
	
	auto bombLeft = [=](short curBombX, short curBombY){
		this_thread::sleep_for(chrono::milliseconds(23));
		int start = 23;
		for(int i=1;i<=range;i++){
			if((x - i > 0) && (map[y][x - i]== SPACE || map[y][x - i] == NOT_IMMORTAL_WALL)){
				changeCursorPosition(curBombX-i,curBombY);
				if(y == notImmortalY[door] && x - i == notImmortalX[door]){
					setcolor(12);
					printf("%c", DOOR);	
					map[y][x - i] = DOOR;
					score++;
					setcolor(15);
					break;
				}else{
					setcolor(4);
					printf("%c",EXPLODE);
				}	
				if(map[y][x - i] == NOT_IMMORTAL_WALL){
					map[y][x - i]=EXPLODE;
					score++;
					break;
				}
				map[y][x - i]=EXPLODE;
				setcolor(15);
				this_thread::sleep_for(chrono::milliseconds(start % 100));
			}else break;
			start += (start / 2 + pow(start, 3));
		}
	};	
	
	auto bombRight = [=](short curBombX, short curBombY){
		this_thread::sleep_for(chrono::milliseconds(27));
		int start = 27;
		for(int i=1;i<=range;i++){
			if((x + i < mapX) && (map[y][x + i] == SPACE || map[y][x + i] == NOT_IMMORTAL_WALL)){
				changeCursorPosition(curBombX + i, curBombY);
				if(y == notImmortalY[door] && x + i == notImmortalX[door]){
					setcolor(12);
					score++;
					printf("%c", DOOR);
					map[y][x + i] = DOOR;
					setcolor(15);
					break;
				}else{
					setcolor(4);
					printf("%c", EXPLODE);	
				}
				setcolor(15);
				if(map[y][x + i] == NOT_IMMORTAL_WALL){
					map[y][x + i] = EXPLODE;
					score++;
					break;
				}
				map[y][x + i] = EXPLODE;
				this_thread::sleep_for(chrono::milliseconds(start % 100));
			}else break;
			start += (start / 2 + pow(start, 3));
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
	this_thread::sleep_for(chrono::milliseconds(2000));
	changeCursorPosition(curBombX,curBombY);
	printf("%c",SPACE);
	map[y][x] = SPACE;
	
	
	auto removebombUp = [=](short curBombX, short curBombY){
		int start = 3;
		for(int i=1;i<=range;i++){
			if(map[y - i][x] == EXPLODE){
				changeCursorPosition(curBombX,curBombY - i);
				printf("%c", SPACE);
				map[y - i][x] = SPACE;
				this_thread::sleep_for(chrono::milliseconds(20));
			}
			start += (start / 2 + pow(start, 3));
		}
	};

	auto removebombDown = [=](short curBombX, short curBombY){
		this_thread::sleep_for(chrono::milliseconds(11));
		int start = 11;
		for(int i=1;i<=range;i++){
			if(map[y+i][x]==EXPLODE){
				changeCursorPosition(curBombX,curBombY+i);
				printf("%c",SPACE);
				map[y+i][x] = SPACE;
				this_thread::sleep_for(chrono::milliseconds(start % 100));
			}
			start += (start / 2 + pow(start, 3));
		}
	};	
	
	auto removebombLeft = [=](short curBombX, short curBombY){
		this_thread::sleep_for(chrono::milliseconds(23));
		int start = 23;
		for(int i=1;i<=range;i++){
			if(map[y][x-i]==EXPLODE){
				changeCursorPosition(curBombX-i,curBombY);
				printf("%c",SPACE);
				map[y][x-i] = SPACE;
				this_thread::sleep_for(chrono::milliseconds(start % 100));
			}
			start += (start / 2 + pow(start, 3));
		}
	};	
	
	auto removebombRight = [=](short curBombX, short curBombY){
		this_thread::sleep_for(chrono::milliseconds(37));
		int start = 37;
		for(int i=1;i<=range;i++){
			if(map[y][x+i]==EXPLODE){
				changeCursorPosition(curBombX+i,curBombY);
				printf("%c",SPACE);
				map[y][x+i] = SPACE;
				this_thread::sleep_for(chrono::milliseconds(start % 100));
			}
			start += (start / 2 + pow(start, 3));
		}
		changeCursorPosition(curX,curY);
		maxPlaceBomb++;
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

void setWindowSize(string x, string y){ //set windows size with parameter
	string cmd = "mode ";
	cmd += x;
	cmd += ", ";
	cmd += y;
	const char *cmds = cmd.c_str();
	system(cmds);
	SMALL_RECT WinRect = {0, 0, (short)stoi(x, nullptr, 10), (short)stoi(x, nullptr, 10)};
	SMALL_RECT* WinSize = &WinRect;
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), true, WinSize);
}

void setFontSize(int x, int y, int weight){ //change font size
    CONSOLE_FONT_INFOEX fontInfo;
    fontInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    fontInfo.dwFontSize.X = x;
    fontInfo.dwFontSize.Y = y;
    fontInfo.FontWeight = weight;
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), false, &fontInfo);
}

void moveExactCenter(){ //make window in center
    RECT rectClient, rectWindow;
    HWND hWnd = GetConsoleWindow();
    GetClientRect(hWnd, &rectClient);
    GetWindowRect(hWnd, &rectWindow);
    int posx, posy;
    posx = GetSystemMetrics(SM_CXSCREEN) / 2 - (rectWindow.right - rectWindow.left) / 2,
    posy = GetSystemMetrics(SM_CYSCREEN) / 2 - (rectWindow.bottom - rectWindow.top) / 2,
    
    SetWindowPos(hWnd, 0, posx, posy, rectClient.right - rectClient.left, rectClient.bottom - rectClient.top, SWP_NOSIZE | SWP_NOZORDER );
}
