#include<iostream>
#include<windows.h>
#include<thread>
#include<conio.h>
#include<time.h>
#include<algorithm>
#include "MyFunction.h"
#define ENTER 13
#define UP 72
#define DOWN 80
#define LEFT  75
#define RIGHT 77
#define PLAYER 153
#define SPACE 32
#define ESC 27
#define NOT_IMMORTAL_WALL '#'
#define MAX 26
#define DOOR 'O'
using namespace std;

class Main{
	
	public:
		Main(){
			srand(time(NULL));
			setWindowSize("51", "25");
			setFontSize(18, 36, 600);
			SetConsoleTitle("                                                                                                                                       || B O M B C A B E ||");
			mainMenu();
		}
		
		void backMenu(){
			changeCursorPosition(0, 8);
			setcolor(4);
			printf("               >> N E W   G A M E <<              \n");
			printf("                                                  \n"); 
			setcolor(15);
			printf("                 L O A D   G A M E                 \n");
			printf("                                                  \n"); 
			printf("                 H I G H S C O R E                 \n"); 
			printf("                                                  \n"); 
			printf("                  S E T T I N G S                  \n"); 
			printf("                                                  \n"); 
			printf("                    C R E D I T                    \n"); 
			printf("                                                  \n"); 
			printf("                      E X I T                      \n"); 
			printf("                                                  \n"); 
			printf("                                                  \n"); 
			printf("\t\t\t\t\tI N F O");
		}
		
		void mainMenu(){
			moveExactCenter();
			char key;
			PlaySound(TEXT("Assets/Songs/mainSong.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			printf("\n");
			int i = 0;
			printf("     %c%c%c", 200, 187, 201); cout << string(35, 205); printf("%c%c%c\n", 187, 201, 188);
			printf("    %c%c%c%c  %c%c%c  %c", 202, 187, 200, 185, 201, 205, 187, 218); setcolor(4); printf("*    *"); setcolor(7); printf("%c     %c%c%c    ", 191, 201, 186, 187); setcolor(4); printf("*"); setcolor(7); printf("%c      %c%c%c%c\n", 191, 204, 188, 201, 202);
			printf("     %c%c%c  %c%c%c %c%c%c %c%c%c %c%c    %c   %c%c%c %c%c %c%c  %c%c%c\n", 206, 205, 185, 204, 205, 185, 201, 202, 187, 201, 203, 187, 204, 187, 186, 201, 205, 187, 204, 187, 201, 187, 204, 205, 206);
			printf("    %c%c%c%c  %c%c%c %c%c%c %c%c%c %c%c    %c%c%c %c%c%c %c%c %c%c  %c%c%c%c\n", 203, 188, 201, 185, 200, 205, 188, 200, 205, 188, 186, 186, 186, 200, 188, 200, 186, 188, 200, 205, 185, 200, 188, 200, 205, 204, 187, 200, 203);
			printf("     %c%c%c", 201, 188, 200); cout << string(35, 205); printf("%c%c%c\n", 188, 200, 187);
			setcolor(4);
			printf("\n\n\t       >> N E W   G A M E <<");
			setcolor(15);
			printf("\n\n\t         L O A D   G A M E"); 
			printf("\n\n\t         H I G H S C O R E"); 
			printf("\n\n\t          S E T T I N G S"); 
			printf("\n\n\t            C R E D I T");
			printf("\n\n\t              E X I T\n\n\n");
			printf("\t\t\t\t\tI N F O");
			chooseMenu:
			int currMenu = 1;
			changeCursorPosition(36, 8);
			key = getch();
			while(key != ENTER){
				if(key == UP){
					if(currMenu == 1){
						changeCursorPosition(15, 8);
						setcolor(15);
						printf("   N E W   G A M E   ");
						changeCursorPosition(37, 21);
						setcolor(4);
						printf(">> I N F O <<");
						currMenu = 7;
						setcolor(15);
					}else if(currMenu == 2){
						changeCursorPosition(14, 10);
						setcolor(15);
						printf("   L O A D   G A M E   ");
						changeCursorPosition(15, 8);
						setcolor(4);
						printf(">> N E W   G A M E <<");
						currMenu--;
						setcolor(15);
					}else if(currMenu == 3){
						changeCursorPosition(14, 12);
						setcolor(15);
						printf("   H I G H S C O R E   ");
						changeCursorPosition(14, 10);
						setcolor(4);
						printf(">> L O A D   G A M E <<");
						currMenu--;
						setcolor(15);
					}else if(currMenu == 4){
						changeCursorPosition(15, 14);
						setcolor(15);
						printf("   S E T T I N G S   ");
						changeCursorPosition(14, 12);
						setcolor(4);
						printf(">> H I G H S C O R E <<");
						currMenu--;
						setcolor(15);
					}else if(currMenu == 5){
						changeCursorPosition(17, 16);
						setcolor(15);
						printf("   C R E D I T   ");
						changeCursorPosition(15, 14);
						setcolor(4);
						printf(">> S E T T I N G S <<");
						currMenu--;
						setcolor(15);
					}else if(currMenu == 6){
						changeCursorPosition(19, 18);
						setcolor(15);
						printf("   E X I T   ");
						changeCursorPosition(17, 16);
						setcolor(4);
						printf(">> C R E D I T <<");
						currMenu--;
						setcolor(15);
					}else{
						changeCursorPosition(37, 21);
						setcolor(15);
						printf("   I N F O   ");
						changeCursorPosition(19, 18);
						setcolor(4);
						printf(">> E X I T <<");
						currMenu--;
						setcolor(15);
					}
				}else if(key == DOWN){
					if(currMenu == 1){
						changeCursorPosition(15, 8);
						setcolor(15);
						printf("   N E W   G A M E   ");
						changeCursorPosition(14, 10);
						setcolor(4);
						printf(">> L O A D   G A M E <<");
						currMenu++;
						setcolor(15);
					}else if(currMenu == 2){
						changeCursorPosition(14, 10);
						setcolor(15);
						printf("   L O A D   G A M E   ");
						changeCursorPosition(14, 12);
						setcolor(4);
						printf(">> H I G H S C O R E <<");
						currMenu++;
						setcolor(15);
					}else if(currMenu == 3){
						changeCursorPosition(14, 12);
						setcolor(15);
						printf("   H I G H S C O R E   ");
						changeCursorPosition(15, 14);
						setcolor(4);
						printf(">> S E T T I N G S <<");
						currMenu++;
						setcolor(15);
					}else if(currMenu == 4){
						changeCursorPosition(15, 14);
						setcolor(15);
						printf("   S E T T I N G S   ");
						changeCursorPosition(17, 16);
						setcolor(4);
						printf(">> C R E D I T <<");
						currMenu++;
						setcolor(15);
					}else if(currMenu == 5){
						changeCursorPosition(17, 16);
						setcolor(15);
						printf("   C R E D I T   ");
						setcolor(4);
						changeCursorPosition(19, 18);
						printf(">> E X I T <<");
						currMenu++;
						setcolor(15);
					}else if(currMenu == 6){
						changeCursorPosition(19, 18);
						setcolor(15);
						printf("   E X I T   ");
						changeCursorPosition(37, 21);
						setcolor(4);
						printf(">> I N F O <<");
						currMenu++;
						setcolor(15);
					}else{
						changeCursorPosition(37, 21);
						setcolor(15);
						printf("   I N F O   ");
						changeCursorPosition(15, 8);
						setcolor(4);
						printf(">> N E W   G A M E <<");
						currMenu = 1;
						setcolor(15);
					}
				}
				key = getch();
			}
			/*
				currMenu
				1 As New Game
				2 As Load Game
				3 As Highscore
				4 As Settings
				5 As Credit
				6 As Exit
				7 As Info
			*/
			switch(currMenu){
				case 1:
					newGame();
					break;
				case 2:
					break;
				case 3:
					scoreBoard();
					break;
				case 4:
					break;
				case 5:
					credit();
					break;
				case 6:
					exitMenu();
					goto chooseMenu;
					break;
				case 7:
					info();
					goto chooseMenu;
					break;
			}
		}
		
		void newGame(){
			changeCursorPosition(15, 8);
			for(int i = 0; i < 22; i++) printf(" ");
			changeCursorPosition(15, 10);
			for(int i = 0; i < 20; i++) printf(" ");
			changeCursorPosition(15, 12);
			for(int i = 0; i < 20; i++) printf(" ");
			changeCursorPosition(15, 14);
			for(int i = 0; i < 20; i++) printf(" ");
			changeCursorPosition(15, 16);
			for(int i = 0; i < 20; i++) printf(" ");
			changeCursorPosition(15, 18);
			for(int i = 0; i < 20; i++) printf(" ");
			changeCursorPosition(35, 21);
			for(int i = 0; i < 15; i++) printf(" ");
			changeCursorPosition(14, 11);
			printf("%c", 201); cout << string(10, 205); printf("%c", 202); cout << string(10, 205); printf("%c\n", 187);
			cout << string(14, 32); printf("%c", 186); cout << string(21, 32); printf("%c\n", 186);
			cout << string(14, 32); printf("%c", 186); cout << string(21, 32); printf("%c\n", 186);
			cout << string(14, 32); printf("%c", 186); cout << string(21, 32); printf("%c\n", 186);
			cout << string(14, 32); printf("%c", 200); cout << string(21, 205); printf("%c\n", 188);
			string name = getName(); 
			transform(name.begin(), name.end(), name.begin(), ::toupper);
			printf("\n\n\n\n"); cout << string(16, 32); printf("Success Create Name");
			printf("\n\n"); cout << string(18, 32);
			string animation = "Creating A Map!";
			int len = animation.size();
			for(int i = 0; i < len; i++){
				cout << animation[i];
				Sleep(200);
			}
			Sleep(500);
			startGame();
		}
		
		void startGame(){
			setWindowSize("31", "35");
			setFontSize(30, 30, 600);
			char key;
			while(live >= 0){
				system("cls");
				changeCursorPosition(12, 1);
				printf("Level %d\n\n", level);
				scanMap();
				printMap();
				changeCursorPosition(11, 24);
				printf("Score : %d", score);
				changeCursorPosition(6, 4);
				posY = 1; posX = 1;
				curX = 6; curY = 4;
				key = getch();
				bool levelUp = false;
				while(!levelUp){
					this_thread::sleep_for(chrono::milliseconds(100));
					key = getch();
					if(key == UP){
						moveEnemy();
						if(map[posY - 1][posX] == SPACE || map[posY - 1][posX] == DOOR|| map[posY-1][posX]==ENEMY){
							if(map[posY-1][posX]==ENEMY){
								return;
							}
							else if(map[posY - 1][posX] == DOOR){
								level++;
								levelUp = true;
							}else{
								map[posY--][posX] = SPACE;
								map[posY][posX] = PLAYER;
								changeCursorPosition(curX, curY--);
								printf(" ");
								changeCursorPosition(curX, curY);
								printf("%c", PLAYER);
								changeCursorPosition(curX, curY);
							}
						}
					}else if(key == DOWN){
						moveEnemy();
						if(map[posY + 1][posX] == SPACE || map[posY + 1][posX] == DOOR|| map[posY+1][posX]==ENEMY){
							if(map[posY+1][posX]==ENEMY) return;
							else if(map[posY + 1][posX] == DOOR){
								level++;
								levelUp = true;
							}else{
								map[posY++][posX] = SPACE;
								map[posY][posX] = PLAYER;
								changeCursorPosition(curX, curY++);
								printf(" ");
								changeCursorPosition(curX, curY);
								printf("%c", PLAYER);
								changeCursorPosition(curX, curY);
							}
						}
					}else if(key == LEFT){
						moveEnemy();
						if(map[posY][posX - 1] == SPACE || map[posY][posX - 1] == DOOR|| map[posY][posX-1]==ENEMY){
							if(map[posY][posX-1]==ENEMY) return;
							else if(map[posY][posX - 1] == DOOR){
								level++;
								levelUp = true;
							}else{
								map[posY][posX--] = SPACE;
								map[posY][posX] = PLAYER;
								changeCursorPosition(curX, curY);
								curX--;
								printf(" ");
								changeCursorPosition(curX, curY);
								printf("%c", PLAYER);
								changeCursorPosition(curX, curY);
							}
						}
					}else if(key == RIGHT){
						moveEnemy();
						if(map[posY][posX + 1] == SPACE || map[posY][posX + 1] == DOOR|| map[posY][posX+1]==ENEMY){
							if(map[posY][posX+1]==ENEMY) return;
							else if(map[posY][posX + 1] == DOOR){
								level++;
								levelUp = true;
							}else{
								map[posY][posX++] = SPACE;
								map[posY][posX] = PLAYER;
								changeCursorPosition(curX, curY);
								curX++;
								printf(" ");
								changeCursorPosition(curX, curY);
								printf("%c", PLAYER);
								changeCursorPosition(curX, curY);
							}
						}
					}else if(key == ESC){ //PAUSE A GAME
						
					}else if(key == SPACE){ //PLACE A BOMB
						if(maxPlaceBomb > 0){
							map[posY][posX]=207;
							maxPlaceBomb--;
							thread plan(planABomb, posY, posX);
							plan.detach();
						}
					}
				}
			}
		}
		
		void scoreBoard(){
			system("cls");
			int player=0;
			
			FILE *file=fopen("Scoreboard/data.txt","r");
			char nama[50];
			int score;
			while(fscanf(file,"%[^#]#%d\n",&nama,&score)!=EOF){
				insert(nama,score);
				player++;
			}
			
			for(int i=0;i<MAX;i++){
				if(head[i]!=NULL){
					struct node *curr=head[i];
					while(curr!=NULL){
						printf("%s %d\n",curr->nama,curr->score);
						curr=curr->next;
					}
				}
			}
			printf("%d",player);
			getch();
		}
		
		void exitMenu(){
			printf("\a");
			char key;
			changeCursorPosition(0, 8);
			setcolor(15);
			printf(" %c", 201); cout << string(47, 205); printf("%c\n", 187);
			printf(" %c                                               %c\n", 186, 186);
			printf(" %c    A R E  Y O U  S U R E                      %c\n", 186, 186);
			printf(" %c       Y O U  W A N T  T O  E X I T            %c\n", 186, 186);
			printf(" %c                        B O M B  C A B E  ?    %c\n", 186, 186);
			printf(" %c                                               %c\n", 186, 186);
			printf(" %c           Y E S              ", 186); setcolor(4); printf(">> N O <<"); setcolor(15); printf("        %c\n", 186); 
			printf(" %c                                               %c\n", 186, 186);
			printf(" %c", 200); cout << string(47, 205); printf("%c\n", 188);
			bool isExit = false;
			key = getch();
			while(key != ENTER){
				if(key == LEFT){
					if(isExit){
						changeCursorPosition(10, 14);
						setcolor(15);
						printf("   Y E S   ");
						changeCursorPosition(32, 14);
						setcolor(4);
						printf(">> N O <<");
						isExit = false;
					}else{
						changeCursorPosition(32, 14);
						setcolor(15);
						printf("   N O   ");
						changeCursorPosition(10, 14);
						setcolor(4);
						printf(">> Y E S <<");
						isExit = true;
					}
				}else if(key == RIGHT){
					if(!isExit){
						changeCursorPosition(32, 14);
						setcolor(15);
						printf("   N O   ");
						changeCursorPosition(10, 14);
						setcolor(4);
						printf(">> Y E S <<");
						isExit = true;
					}else{
						changeCursorPosition(10, 14);
						setcolor(15);
						printf("   Y E S   ");
						changeCursorPosition(32, 14);
						setcolor(4);
						printf(">> N O <<");
						isExit = false;
						
					}
				}
				key = getch();
			}
			switch(isExit){
				case true:
					exit(0);
				case false:
					break;
			}
			backMenu();
		}
		
		void credit(){
			system("cls");
			printf("\n\t\t     BOMB CABE\n\n");
			printf("\n\t\t   -- CREDITS --\n\n");
			printf("\tCODE\t        MAP    \t    GAMEPLAY\n");
			printf("\t    \t      DESIGNS   \n");
			printf("         by \t        by    \t       by  \n");
			printf("        Juan \t       Juan \t      Juan \n");
			printf("  \nMusic by  Toby Fox - Megalovania -  \n");
			
			printf("\n\n");
			printf("\n\n");
			
			system("pause");
			system("cls");
			mainMenu();
		}
		
		void info(){
			char key=LEFT;
			changeCursorPosition(15, 8);
			for(int i = 0; i < 22; i++) printf(" ");
			changeCursorPosition(15, 10);
			for(int i = 0; i < 20; i++) printf(" ");
			changeCursorPosition(15, 12);
			for(int i = 0; i < 20; i++) printf(" ");
			changeCursorPosition(15, 14);
			for(int i = 0; i < 20; i++) printf(" ");
			changeCursorPosition(15, 16);
			for(int i = 0; i < 20; i++) printf(" ");
			changeCursorPosition(15, 18);
			for(int i = 0; i < 20; i++) printf(" ");
			changeCursorPosition(35, 21);
			for(int i = 0; i < 15; i++) printf(" ");
			while (key != ENTER){
				if(key == RIGHT){
					changeCursorPosition(20, 6);
					for(int i = 0; i < 11; i++) printf(" ");
					changeCursorPosition(21, 8);
					for(int i = 0; i < 1; i++) printf(" ");
					changeCursorPosition(5, 9);
					for(int i = 0; i < 19; i++) printf(" ");
					changeCursorPosition(5, 12);
					for(int i = 0; i < 32; i++) printf(" ");
					changeCursorPosition(5, 15);
					for(int i = 0; i < 30; i++) printf(" ");
					changeCursorPosition(43, 19);
					for(int i = 0; i < 6; i++) printf(" ");
					
					changeCursorPosition(21, 6);
					printf("GAME INFO\n\n");
					printf("     1. The game consist of THREE levels\n");
					printf("\n\n");
					printf("     2. Destroy the walls (#) to find the portal\n");
					printf("\n\n");
					printf("     3. Each wall you destroyed, give you scores\n");
					printf("\n\n");
					printf("     4. Avoid the ghost to stay alive\n");
					printf("\n\n");
					changeCursorPosition(2, 19);
					printf("%c PREV",17);
					
				}else if(key == LEFT){
					changeCursorPosition(21, 6);
					for(int i = 0; i < 9; i++) printf(" ");
					changeCursorPosition(5, 8);
					for(int i = 0; i < 35; i++) printf(" ");
					changeCursorPosition(5, 11);
					for(int i = 0; i < 43; i++) printf(" ");
					changeCursorPosition(5, 14);
					for(int i = 0; i < 43; i++) printf(" ");
					changeCursorPosition(5, 17);
					for(int i = 0; i < 32; i++) printf(" ");
					changeCursorPosition(2, 19);
					for(int i = 0; i < 6; i++) printf(" ");
		
					changeCursorPosition(20, 6);			
					printf("HOW TO PLAY\n");
					changeCursorPosition(21, 8);
					printf("%c\n", 30);
					printf("     1. Move with  %c %c %c\n", 17, 31, 16);
					printf("\n\n");
					printf("     2. Press SPACE to place the bomb\n");
					printf("\n\n");
					printf("     3. Press Esc to pause the game\n");
					printf("\n\n");
					changeCursorPosition(43, 19);
					printf("NEXT %c",16);
				}
				key = getch();//ganti getch key right
				if(key==ENTER){
					break;
				}
			}
			changeCursorPosition(20, 6);
			for(int i = 0; i < 11; i++) printf(" ");
			changeCursorPosition(2, 19);
			for(int i = 0; i < 47; i++) printf(" ");
		backMenu();
		}
		
		//Not Finish
		void settings(){
			char key;
			key = getch();
			do{
				if(key == 32){
					if(playSong){
						playSong = false;
						PlaySound(NULL, 0, 0);
					}else{
						playSong = true;
						PlaySound(TEXT("Assets/mainSong.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
					}
				}
				key = getch();
			}while(true);
		}
	
};

int main(){
	new Main();
	return 0;
}
