#include <stdio.h>
#include <windows.h>
#include <MMsystem.h>
#define SPEED 10000
#define widthMap 50
#define heightMap 50
#define LOCALBEGIN 10110
#define LENGTHBEGIN 5
#define STEPCORE 5

enum state {MENU, INGAME, GAMEOVER,TUTORIAL, HIGHSCORE, SETTING, ABOUT, QUIT} state;
void menu();
void setting();
void ingame();
void gameover();
void infor();
void hideCursor();
void gotoxy(int x, int y);
void tutorial();
void about();
void highscore();
void quit();
void esc();
void inBox();
void createFruit();
void newGame();
void createBigFruit();
int trungBig();
void createBoss();
int checkBoss();
void bossMove();
void boss1Move();
void createBoss1();
int checkBoss1();
void createBigBoss();
void BigBossMove();
void CreateSkillBoss();
void moveSkillBoss();

int direction1=0;
int direction2=0;
int direction=0;
int snake[widthMap*heightMap];
int vx=0,vy=-1;
int length;
int fruit;
int score=0;
int ccc;
int demTutorial=0;
int top1=0;
int top2=0;
int top3=0;
int speed=SPEED;
int fruit1,fruit2,fruit3,fruit4;
int time=0;
int stepscore=STEPCORE;
int sx,sy;
int skill[100];
int coHieu;
int speedSkill=2000;
int boss,boss1;
int countEatFruit=1;
int bigBoss;
int countKillBoss=1;
int skillBoss[10];


int main()
{
	
	hideCursor();
	state=0;
	FILE *f=fopen("Score.txt","rt");
	fscanf(f,"%d",&top1);
	fscanf(f,"%d",&top2);
	fscanf(f,"%d",&top3);
	fclose(f);
	while(1)
	{
		switch(state)
		{
			case MENU:
				menu();
				break;	
			case INGAME: 
				ingame();
				break;
			case GAMEOVER:
				gameover(); 
				break;
			case TUTORIAL:
				tutorial();
				break;	
			case QUIT:
				quit();
				break;
			case ABOUT:
				about();
				break;
			case SETTING:
				setting();
				break;
			case HIGHSCORE:
				highscore();
				break;
		}
		
	}
	
	return 0;
}

void hideCursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);  
}

void gotoxy(int x, int y)
{
    static HANDLE h = NULL;  
    if(!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x, y };  
    SetConsoleCursorPosition(h,c);
}

void inBox()
{
	int i;
	for(i=0;i<widthMap;i++)
		printf("-");
	i=0;
	int j=0;
	for(j;j<heightMap;j++)
	{
		printf("\n");
		i=0;
		for(i;i<widthMap;i++)
			printf((i==0||i==(widthMap-1))?"|":" ");
	}
	printf("\n");
	for(i=0;i<widthMap;i++)
		printf("-");		
}

int trung()
{
	int i;
	for(i=0;i<length;i++)
		if(snake[i]==fruit)
			return 0;
	if(boss==fruit)
		return 0;
	return 1;
}

int trungBig()
{
	int i;
	for(i=0;i<length;i++)
		if(snake[i]==fruit1||snake[i]==fruit2||snake[i]==fruit3||snake[i]==fruit4)
			return 0;
	return 1;
}

void createBigFruit()
{
	while(1)
	{
		fruit1=10001+(1+rand()%(widthMap-3))*100;
		fruit1+=rand()%(heightMap-1);
		fruit2=fruit1+1;
		fruit3=fruit1+100;
		fruit4=fruit1+1+100;
		if(trungBig) 
			break;
	}
		
	gotoxy(getX(fruit4),getY(fruit4));
	printf("X");
	gotoxy(getX(fruit1),getY(fruit1));
	printf("X");
	gotoxy(getX(fruit2),getY(fruit2));
	printf("X");
	gotoxy(getX(fruit3),getY(fruit3));
	printf("X");
	
}

void createFruit()
{
	while(1)
	{
		fruit=10001+(1+rand()%(widthMap-2))*100;
		fruit+=rand()%heightMap;
		if(trung) 
			break;
	}
	gotoxy(getX(fruit),getY(fruit));
	printf("M");
}

void startGame()
{
	//PlaySound(TEXT("naruto.wav"), NULL, SND_ASYNC);
	score=0;
	vx=0,vy=-1;
	countEatFruit=1;
	time=0;
	countKillBoss=1;
	createFruit();
	createBoss();
	createBoss1();
	snake[0]=LOCALBEGIN;
	int t=snake[0];
	gotoxy(getX(snake[0]),getY(snake[0]));
	printf("X");
	length=LENGTHBEGIN;
	int i;
	for(i=1;i<length;i++)
	{
		snake[i]=++t;
		gotoxy(getX(snake[i]),getY(snake[i]));
		printf("o");
	}
	
}

void printScore()
{
	gotoxy(0,heightMap+3);
	printf("SCORE: %d",score);
}

int getX(int a)
{
	return (a-10000)/100;
}

int getY(int a)
{
	return a%100;
}

void menu()
{
	PlaySound(TEXT("doom.wav"), NULL, SND_ASYNC);
	system("cls");
	int yy=heightMap/3;
	int xx=widthMap/2-5;
	int temp=yy;
	int key=0;
	int next=0;
	int solution=0;
	inBox(); 
	gotoxy(xx,yy-2);
	printf("GAME MENU");
	gotoxy(xx,yy);
	printf("New Game");
	gotoxy(xx,yy+1);
	printf("Tutorial");
	gotoxy(xx,yy+2);
	printf("High Score");
	gotoxy(xx,yy+3);
	printf("About");
	gotoxy(xx,yy+4);
	printf("Setting");
	gotoxy(xx-3,yy);
	printf(">");
	while(state==MENU)
	{
		if(kbhit()){
		gotoxy(xx-3,temp);
		printf(" ");
		key=getch();
		switch(key)
		{
			case 80:
				temp+=1;
				break;
			case 72:
				temp-=1;
				break;
			case 13:
				next=1;
				break;
			case 27:
				ccc=0;
				state=QUIT;
				system("cls");
				break;	
		}
		if(temp==yy-1)
			temp+=5;
		if(temp==yy+5)
			temp-=5;
		gotoxy(xx-3,temp);
		printf(">");
		if(next&&temp==yy)
		{
			solution=1;
			break;
		}
		if(next&&temp==yy+1)
		{
			solution=2;
			break;
		}
		if(next&&temp==yy+2)
		{
			solution=3;
			break;
		}
		if(next&&temp==yy+3)
		{
			solution=4;
			break;
		}
		if(next&&temp==yy+4)
		{
			solution=5;
			break;
		}
		next=0;
		}
	}
	switch(solution)
	{
		case 1:
			system("cls");
			inBox();
			state=INGAME;
			break;
		case 2:
			system("cls");
			state=TUTORIAL;
			break;
		case 3:
			system("cls");
			state=HIGHSCORE;
			break;
		case 4:
			system("cls");
			inBox();
			state=ABOUT;
			break;
		case 5:
			system("cls");
			inBox();
			state=SETTING;
			break;
	}
	
}
 
void tutorial()
{
	if(!demTutorial) 
		inBox();
	int x=widthMap;
	int y=heightMap;
	gotoxy(x/2-10,2);
	printf("===== HUONG DAN ====");
	gotoxy(x/10,6);
	printf("* <Len, Xuong, Trai, Phai>: dieu khien ran!");
	gotoxy(x/10,8);
	printf("* Space: Tam dung!");
	gotoxy(x/10,10);
	printf("* R: Tro ve!");
	gotoxy(x/10,12);
	printf("* Esc: Thoat game!");
	gotoxy(x/2-15,14);
	printf("-------------------------------");
	gotoxy(x/2-10,16);
	printf("===== TUTORIAL ====");
	gotoxy(x/10,20);
	printf("* <up, down, left, right>: control snake!");
	gotoxy(x/10,22);
	printf("* Space: Stop!");
	gotoxy(x/10,24);
	printf("* R: Undo!");
	gotoxy(x/10,26);
	printf("* Esc: Quit game!");
	ccc=3;
	esc();
}
void setting()
{
	int x=widthMap/3;
	int y=heightMap/3;
	int temp=y+4;
	int next=0;
	int solution;
	char key;
	gotoxy(x,y);
	printf("-SPEED-");
	gotoxy(x,y+4);
	printf("20 cay chuoi tren gio ^-^");
	gotoxy(x,y+6);
	printf("50 cay chuoi tren gio =-=");
	gotoxy(x,y+8);
	printf("100 cay chuoi tren gio o-o");
	gotoxy(x,y+10);
	printf("1000 cay chuoi tren gio /-_-\\");
	gotoxy(x,y+12);
	printf("Toc do ban tho luon |R.I.P| T_T ");
	gotoxy(x-3,temp);
	printf(">");
	while(state==SETTING)
	{
		if(kbhit()){
		gotoxy(x-3,temp);
		printf(" ");
		key=getch();
		switch(key)
		{
			case 80:
				temp+=2;
				break;
			case 72:
				temp-=2;
				break;
			case 13:
				next=1;
				break;
			case 'r':
				system("cls");
				state=MENU;
				break;
			case 'R':
				system("cls");
				state=MENU;
				break;
			case 27:
				ccc=5;
				state=QUIT;
				system("cls");
				break;	
			
		}
		if(temp==y+2)
			temp+=10;
		if(temp==y+14)
			temp-=10;
		gotoxy(x-3,temp);
		printf(">");
		if(next&&temp==y+4)
		{
			solution=1;
			break;
		}
		if(next&&temp==y+6)
		{
			solution=2;
			break;
		}
		if(next&&temp==y+8)
		{
			solution=3;
			break;
		}
		if(next&&temp==y+10)
		{
			solution=4;
			break;
		}
		if(next&&temp==y+12)
		{
			solution=5;
			break;
		}
		next=0;
		}
	}
	switch(solution)
	{
		case 1:
			speed=10000;
			stepscore=STEPCORE;
			speedSkill=2000;
			break;
		case 2:
			speed=8000;
			stepscore=STEPCORE+5;
			speedSkill=1800;
			break;
		case 3:
			speed=6000;
			stepscore=STEPCORE+10;
			speedSkill=1600;
			break;
		case 4:
			speed=4000;
			stepscore=STEPCORE+15;
			speedSkill=1400;
			break;
		case 5:
			speed=500;
			stepscore=STEPCORE+20;
			speedSkill=1000;
			break;
	}
	if(state!=QUIT)
		state=MENU;
}

void highscore()
{
	int x=widthMap/2;
	int y=heightMap/3;
	FILE *f=fopen("Score.txt","wt");
	fprintf(f,"%5d",top1);
	fprintf(f,"%5d",top2);
	fprintf(f,"%5d",top3);
	fclose(f);
	system("cls");
	inBox();
	gotoxy(x,y);
	printf("Top 1: %d", top1);
	gotoxy(x,y+1);
	printf("Top 2: %d", top2);
	gotoxy(x,y+2);
	printf("Top 3: %d", top3);
	
	ccc=4;
	esc();
}

void about()
{
	gotoxy(widthMap/4,heightMap/3);
	printf("-= MADE IN ANGIANG-VIETNAM =+");
	gotoxy(widthMap/4,heightMap/3+2);
	printf("    <SAI GON UNIVERSITY>");
	gotoxy(widthMap/4,heightMap/3+4);
	printf(" $ BY MINH KHUY HANDSOME $");	
	ccc=6;
	esc();
}            

                       
void quit()
{
	int x=widthMap;
	int y=heightMap;
	int temp=y/3+4;
	int key=0;
	int next=0;
	int solution=0;
	system("cls");
	inBox();
	gotoxy(x/3,y/3);
	printf("BAN CO MUON THOAT GAME??");
	gotoxy(x/3+10,y/3+4);
	printf("Yes (-_-)");
	gotoxy(x/3+10,y/3+6);
	printf("No (^-^)");
	gotoxy(x/3+8,y/3+4);
	printf(">");
	
	while(1)
	{
		if(kbhit())
		{
			gotoxy(x/3+8,temp);
			printf(" ");
			key=getch();
			switch(key)
			{
				case 80:
					temp+=2;
					break;
				case 72:
					temp-=2;
					break;
				case 13:
					next=1;
					break;
			}
			if(temp==y/3+2)
				temp+=4;
			if(temp==y/3+8)
				temp-=4;
			gotoxy(x/3+8,temp);
			printf(">");
			if(next&&temp==y/3+4)
			{
				solution=1;
				break;
			}
			if(next&&temp==y/3+6)
			{
				solution=2;
				break;
			}
		}
	}
	if(solution==1)
	{
		system("cls");
		exit(0);
	}
	else 
	{
		system("cls");
		demTutorial++;
		inBox();
		state=ccc;
	}
	
}

void ingame()
{
	startGame();
	char key;
	int dem=0;
	unsigned int ct=0;
	unsigned int vBoss=0;
	int useSkill=1;
	while(state==INGAME)
	{
		if(ct==1000000)
			ct=0;
		if(vBoss==1000000)
			vBoss=0;
		if(kbhit())
		{
			key=getch();
			switch(key)
			{
				case 75://LEFT
				if(vy!=0)
				{
					vx=-1;
					vy=0;
				}
					break;
				case 77:	//RIGHT
				if(vy!=0)
				{
					vx=1;
					vy=0;
				}
					break;
				case 80://down
					if(vx!=0)
					{
						vy=1;
						vx=0;
					}
					break;
				case 72://up
					if(vx!=0)
					{
					vy=-1;
					vx=0;
					}
					break;
				case 'r':
					system("cls");
					state=MENU;
					break;
				case 'R':
					system("cls");
					state=MENU;
					break;
				case 27:
					ccc=1;
					quit();	
					createFruit();	
					break;
				case 32:
					while(1)
					{
						gotoxy(widthMap/2-5,heightMap/2);
						printf("<S-T-O-P>");
						if(kbhit())
						{
							key=getch();
							if(key==32)
							{
								gotoxy(widthMap/2-5,heightMap/2);
								printf("         ");
								break;
							}
						}
					}
					break;
				case 'z':
					if(useSkill==1)
					{
						skill[dem]=snake[0];
						sx=vx;
						sy=vy;
						coHieu=1;
						gotoxy(getX(skill[dem]),getY(skill[dem]));
						printf("+");
					}
					break;
			}
		}
		
		
		if(countKillBoss%5==0)
		{
			createBigBoss();
			CreateSkillBoss();
			countKillBoss++;
		}
		if(vBoss%2000==0)
		{
			if(countKillBoss%6==0)
			{
				//countKillBoss++;
				BigBossMove();
				moveSkillBoss();
			}
		}
		if(vBoss%15000==0)
		{
			bossMove();
			if(boss==fruit)
				createFruit();
			boss1Move();
			if(boss1==fruit)
				createFruit();
			
			
		}
		
		if(coHieu)
		{
			if(ct%speedSkill==0)
			{
				if(skill[dem]==bigBoss)
				{
					score+=stepscore*10;
					gotoxy(getX(bigBoss)-3,getY(bigBoss));
					printf("       ");
					countKillBoss++;
				}
				if(skill[dem]==boss)
				{
					score+=stepscore*2;
					countKillBoss++;
					createBoss();
				}
				if(skill[dem]==boss1)
				{
					score+=stepscore*2;
					countKillBoss++;
					createBoss1();
				}
				if(skill[dem]==fruit)
				{
					score-=stepscore;
					createFruit();
				}
				useSkill=0;
				gotoxy(getX(skill[dem]),getY(skill[dem]));
				printf(" ");
				skill[dem]+=sx*100;
				skill[dem]+=sy;
				gotoxy(getX(skill[dem]),getY(skill[dem]));
				if(sy==0)
				{
					if(getX(skill[dem])%2==0)
					printf("+");
					else
					printf("x");
				}	
				if(sx==0)
				{
					if(getY(skill[dem])%2==0)
					printf("+");
					else
					printf("x");
				}		
				
				if(!getX(skill[dem]))
				{
					gotoxy(getX(skill[dem]),getY(skill[dem]));
					printf("|");
					coHieu=0;
					useSkill=1;
				}
				if(!getY(skill[dem]))
				{
					gotoxy(getX(skill[dem]),getY(skill[dem]));
					printf("-");
					coHieu=0;
					useSkill=1;
				}
				if(getY(skill[dem])==heightMap+1)
				{
					gotoxy(getX(skill[dem]),getY(skill[dem]));
					printf("-");
					coHieu=0;
					useSkill=1;
				}
				if(getX(skill[dem])==widthMap-1)
				{
					gotoxy(getX(skill[dem]),getY(skill[dem]));
					printf("|");
					coHieu=0;
					useSkill=1;
				}
				
			}
			
		}
		
		
		if((ct%2000)==0)
		{	
			gotoxy(getX(snake[length-1]),getY(snake[length-1]));
			printf(" ");
			int i=length-1;
			for(i;i>0;i--)
				snake[i]=snake[i-1];
			snake[0]+=vx*100;
			snake[0]+=vy;
			if(getY(snake[0])==0) snake[0]+=heightMap;
			if(getY(snake[0])==(heightMap+1)) snake[0]-=heightMap;
			if(getX(snake[0])==0) snake[0]+=(widthMap-2)*100;
			if(getX(snake[0])==(widthMap-1)) snake[0]-=(widthMap-2)*100;
			gotoxy(getX(snake[0]),getY(snake[0]));
			printf("X");
			gotoxy(getX(snake[1]),getY(snake[1]));
			printf("o");
			int h=0;
			for(h;h<length;h++)
			{
				if(boss==snake[h]||boss1==snake[h])
				{
				gotoxy(getX(snake[h])-2,getY(snake[h]));
				printf("$$$$$");
				gotoxy(getX(snake[h]),getY(snake[h])-1);
				printf("$");
				gotoxy(getX(snake[h]),getY(snake[h])+1);
				printf("$");
				Sleep(2000);
				state=GAMEOVER;
				}
			}
			if(snake[0]==fruit)
			{
				printf("\a");
				gotoxy(getX(fruit),getY(fruit));
				printf("X");
				length++;
				score+=stepscore; 
				countEatFruit++;
				if(countEatFruit%5==0)
				{
					createBigFruit();
					fruit=0;
					continue;
				}
				createFruit();
			}				
			
			if(countEatFruit%5==0)
			{
				if(time<200)
				{
					gotoxy(20,heightMap+4);
					printf("--------------------");
					gotoxy(20+time/10,heightMap+5);
					printf("#");
				}
				time++;
				if(time==200)
				{
				gotoxy(20,heightMap+4);
				printf("                                 ");
				gotoxy(20,heightMap+5);
				printf("                                 ");
				gotoxy(getX(fruit1),getY(fruit1));
				printf(" ");
				gotoxy(getX(fruit4),getY(fruit4));
				printf(" ");
				gotoxy(getX(fruit2),getY(fruit2));
				printf(" ");
				gotoxy(getX(fruit3),getY(fruit3));
				printf(" ");
				fruit1=0;
				fruit2=0;
				fruit3=0;
				fruit4=0;
				countEatFruit++;
				createFruit();
				}
			}	
			if(countEatFruit%5!=0)
				time=0;
			if(snake[0]==fruit1)
			{
				printf("\a");
				gotoxy(getX(fruit1),getY(fruit1));
				printf("X");
				gotoxy(getX(fruit4),getY(fruit4));
				printf(" ");
				gotoxy(getX(fruit2),getY(fruit2));
				printf(" ");
				gotoxy(getX(fruit3),getY(fruit3));
				printf(" ");
				gotoxy(20,heightMap+4);
				printf("                                    ");
				gotoxy(20,heightMap+5);
				printf("                                     ");
				length++;
				score+=stepscore*3;
				fruit1=0;
				fruit2=0;
				fruit3=0;
				fruit4=0;
				createFruit();	
				countEatFruit++;
			}
				
			if(snake[0]==fruit2)
			{
				printf("\a");
				gotoxy(getX(fruit2),getY(fruit2));
				printf("X");
				gotoxy(getX(fruit4),getY(fruit4));
				printf(" ");
				gotoxy(getX(fruit1),getY(fruit1));
				printf(" ");
				gotoxy(getX(fruit3),getY(fruit3));
				printf(" ");
				gotoxy(20,heightMap+4);
				printf("                                    ");
				gotoxy(20,heightMap+5);
				printf("                                     ");
				length++;
				score+=stepscore*3;
				fruit1=0;
				fruit2=0;
				fruit3=0;
				fruit4=0;
				createFruit();	
				countEatFruit++;
			}
				
			if(snake[0]==fruit3)
			{
				printf("\a");
				gotoxy(getX(fruit3),getY(fruit3));
				printf("X");
				gotoxy(getX(fruit1),getY(fruit1));
				printf(" ");
				gotoxy(getX(fruit2),getY(fruit2));
				printf(" ");
				gotoxy(getX(fruit4),getY(fruit4));
				printf(" ");
				gotoxy(20,heightMap+4);
				printf("                                    ");
				gotoxy(20,heightMap+5);
				printf("                                     ");
				length++;
				score+=stepscore*3;
				fruit1=0;
				fruit2=0;
				fruit3=0;
				fruit4=0;
				createFruit();	
				countEatFruit++;
			}
				
			if(snake[0]==fruit4)
			{
				printf("\a");
				gotoxy(getX(fruit4),getY(fruit4));
				printf("X");
				gotoxy(getX(fruit1),getY(fruit1));
				printf(" ");
				gotoxy(getX(fruit2),getY(fruit2));
				printf(" ");
				gotoxy(getX(fruit3),getY(fruit3));
				printf(" ");
				gotoxy(20,heightMap+4);
				printf("                                    ");
				gotoxy(20,heightMap+5);
				printf("                                     ");
				length++;
				score+=stepscore*3;
				fruit1=0;
				fruit2=0;
				fruit3=0;
				fruit4=0;
				createFruit();	
				countEatFruit++;
			}
			
			printScore();
			for(i=1;i<length;i++)
				if(snake[0]==snake[i])
				{
					gotoxy(getX(snake[0])-2,getY(snake[0]));
					printf("$$$$$");
					gotoxy(getX(snake[0]),getY(snake[0])-1);
					printf("$");
					gotoxy(getX(snake[0]),getY(snake[0])+1);
					printf("$");
					Sleep(1000);
					state=GAMEOVER;
				}
		}
		//Sleep(1/100);
		ct++;
		vBoss++;	
	}
}
void gameover()
{
	PlaySound(TEXT("gameover.wav"), NULL, SND_ASYNC);
	int x=widthMap;
	int y=heightMap;
	int temp=x/3-3;
	int next=0;
	char key;
	int solution=0;
	if(score>top1) 
	{
		top3=top2;
		top2=top1;
		top1=score;
	}
	if(score>top2&&score!=top1)
	{
		top3=top2;
		top2=score;
	}
	if(score>top3&&score!=top1&&score!=top2)
		top3=score;
	
	
	
	system("cls");
	inBox();
		gotoxy(2,10);
		printf("\n\n\n====================GAME OVER===================");
		gotoxy(x/3,y/3);
		printf("NEW GAME???");
		gotoxy(x/3-1,y/3+2);
		printf("Yes");
		gotoxy(x/3+9,y/3+2);
		printf("No");
		gotoxy(temp,y/3+2);
		printf("<>");
	while(1)
	{
		if(kbhit())
		{
			gotoxy(temp,y/3+2);
			printf("  ");
			key=getch();
			switch(key)
			{
				case 75://l
					temp-=10;
					break;
				case 77://r
					temp+=10;
					break;
				case 13:
					next=1;
					break;
			}
			if(temp==x/3-13)
				temp+=20;
			if(temp==x/3+17)
				temp-=20;
			gotoxy(temp,y/3+2);
			printf("<>");
			if(next&&temp==x/3-3)
			{
				solution=1;
				break;
			}
			if(next&&temp==x/3+7)
			{
				solution=2;
				break;
			}
		}
	}
	if(solution==1)
	{
		system("cls");
		inBox();
		state=INGAME;
	}
	else 
	{
		system("cls");
		state=MENU;
	}
}

void esc()
{
	char key;
	while(1)
		if(kbhit())
		{
			key=getch();
			if(key == 27)
			{
				state=QUIT;
				break;
			}
			if(key == 'R' || key=='r')
			{
				system("cls");
				state=MENU;
				break;
			}
		}	
}

void newGame()
{
	char key;
	while(1)
	{
		if(kbhit())
		{
			key=getch();
			if(key==75)
			{
				
			}
			if(key==77)
			{
				
			}
		}
	}
}

void createBoss()
{
	while(1)
	{
		boss=10001+(1+rand()%(widthMap-2))*100;
		boss+=rand()%(heightMap-1);
		if(checkBoss)
			break;
	}
	gotoxy(getX(boss),getY(boss));
	printf("@");
}

int checkBoss()
{
	int i;
	for(i=0;i<length;i++)
		if(snake[i]==boss)
			return 0;
	if(boss==fruit)
		return 0;
	return 1;
}

void bossMove()
{
	gotoxy(getX(boss),getY(boss));
	printf(" ");
	if(getX(boss)==widthMap-2)
		direction=1;
	if(getX(boss)==1)
		direction=0;
	if(direction==0)
		boss+=100;
	if(direction==1)
	 	boss-=100;
	gotoxy(getX(boss),getY(boss));
	printf("@");
}

void boss1Move()
{
	gotoxy(getX(boss1),getY(boss1));
	printf(" ");
	if(getY(boss1)==heightMap-1)
		direction1=1;
	if(getY(boss1)==1)
		direction1=0;
	if(direction1==0)
		boss1+=1;
	if(direction1==1)
	 	boss1-=1;
	gotoxy(getX(boss1),getY(boss1));
	printf("@");
}

void createBoss1()
{
	while(1)
	{
		boss1=10001+(1+rand()%(widthMap-2))*100;
		boss1+=rand()%(heightMap-1);
		if(checkBoss1)
			break;
	}
	gotoxy(getX(boss1),getY(boss1));
	printf("@");
}

int checkBoss1()
{
	int i;
	for(i=0;i<length;i++)
		if(snake[i]==boss1)
			return 0;
	if(boss1==fruit)
		return 0;
	return 1;
}

void createBigBoss()
{
	bigBoss=10002+(1+rand()%(widthMap-2))*100;
	gotoxy(getX(bigBoss),getY(bigBoss));
	printf("@");
}

void BigBossMove()
{
	gotoxy(getX(bigBoss)-3,getY(bigBoss));
	printf(" ");
	gotoxy(getX(bigBoss)+3,getY(bigBoss));
	printf(" ");
	if(getX(bigBoss)==widthMap-5)
		direction2=1;
	if(getX(bigBoss)==4)
		direction2=0;
	if(direction2==0)
		bigBoss+=100;
	if(direction2==1)
	 	bigBoss-=100;
	gotoxy(getX(bigBoss)-3,getY(bigBoss));
	printf("(((#)))");	
}

void CreateSkillBoss()
{
	int i=0;
	for(i;i<4;i++)
	{
		skillBoss[i]=10004+(1+rand()%(widthMap-2))*100;
		gotoxy(getX(skillBoss[i]),getY(skillBoss[i]));
		printf("|");
	}
	/*
	skillBoss[0]=10004+(1+rand()%(widthMap-2))*100;
	gotoxy(getX(skillBoss[0]),getY(skillBoss[0]));
	printf("v");
	while(1)
	{
		skillBoss[1]=10004+(1+rand()%(widthMap-2))*100;
		gotoxy(getX(skillBoss[1]),getY(skillBoss[1]));
		printf("|");
		if(skillBoss[0]!=skillBoss[1])
			break;	
	}
	*/
	
}

void moveSkillBoss()
{
	
	int i;
	int j;
	for(i=0;i<length;i++)
		for(j=0;j<4;j++)
			if(skillBoss[j]==snake[i])
				state=GAMEOVER;
	
	for(i=0;i<4;i++)
	{
		gotoxy(getX(skillBoss[i]), getY(skillBoss[i]));
		printf(" ");
		skillBoss[i]+=1;
		gotoxy(getX(skillBoss[i]), getY(skillBoss[i]));
		printf("|");
		if(getY(skillBoss[0])==heightMap-1)
		{
			for(j=0;j<4;j++)
			{
				gotoxy(getX(skillBoss[j]), getY(skillBoss[j]));
				printf(" ");
			}
			CreateSkillBoss();
			break;
		}
	}
	/*
	gotoxy(getX(skillBoss[0]), getY(skillBoss[0]));
	printf(" ");
	skillBoss[0]+=1;
	gotoxy(getX(skillBoss[0]), getY(skillBoss[0]));
	printf("v");
	gotoxy(getX(skillBoss[1]), getY(skillBoss[1]));
	printf(" ");
	skillBoss[1]+=1;
	gotoxy(getX(skillBoss[1]), getY(skillBoss[1]));
	printf("|");
	if(getY(skillBoss[0])==heightMap-1||getY(skillBoss[1])==heightMap-1)
	{
		gotoxy(getX(skillBoss[0]), getY(skillBoss[0]));
		printf(" ");
		gotoxy(getX(skillBoss[1]), getY(skillBoss[1]));
		printf(" ");
		CreateSkillBoss();
	}
	*/
	
}



