/***************************************************************/
/******************Computer Science Project*********************/
/***************TICTACTICS - A Tic-Tac-Toe Game*****************/
/*********************MADE BY ANURAG ROY************************/
/*************************CLASS XIIB****************************/
#include<iomanip.h>
#include<windows.h>
#include<process.h>
#include<stdio.h>
#include<string.h>
#include<fstream.h>
#include<conio.h>
#include<stdlib.h>
#include<ctype.h>

char square[10] = {'0','1','2','3','4','5','6','7','8','9'};
void mainmenu();
void pausemenu(char);
void menuoutline(char[],char,char[],char,char[],char,char[],char,char[],char,char[],char,char[],char,char[]);
void gameplaysolo();
void gameplayversus();
void markwrite(char);
void timedelay();
void warning();
void instructions();
void cpuai();
int checkwin();
void board(char);
char box(int,char);
void vacantSpace();
int z=0;
char mark;
char choice='\0';
char compmark;


fstream statin;
class stats{
int sologames;
int solowon;
int sololost;
int solodraw;
int versusgames;
int versusplOne;
int versusplTwo;
int versusdraw;
public:


void dispstatsS()
{
	menuoutline("STATISTICS",'\0',"",'\0',"",'\0',"",'\0',"",'\0'," ",'\0',"",'\0',"");
	gotoxy(25,10);
	cout<<"SOLO";
	gotoxy(25,12);
	cout<<" Games played ";
	gotoxy(25,13);
	cout<<" Games won ";
	gotoxy(25,14);
	cout<<" Games lost ";
	gotoxy(25,15);
	cout<<" Games drawn ";
	gotoxy(25,16);
	cout<<" Win percentage ";

	gotoxy(50,12);
	cout<<sologames;
	gotoxy(50,13);
	cout<<solowon;
	gotoxy(50,14);
	cout<<sololost;
	gotoxy(50,15);
	cout<<solodraw;
	gotoxy(50,16);
	if(sologames==0)
		cout<<"0.00 %";
	else
		cout<<setprecision(3)<<((float)solowon/sologames)*100<<" %";
	gotoxy(25,25);
	cout<<" B  BACK\n";
}

void dispstatsV()
{
	menuoutline("STATISTICS",'\0',"",'\0',"",'\0',"",'\0',"",'\0'," ",'\0',"",'\0',"");
	gotoxy(25,10);
	cout<<"VERSUS";
	gotoxy(25,12);
	cout<<" Games played ";
	gotoxy(25,14);
	cout<<" Games won by player 1 ";
	gotoxy(25,15);
	cout<<" Win percentage ";
	gotoxy(25,17);
	cout<<" Games won by player 2 ";
	gotoxy(25,18);
	cout<<" Win percentage ";
	gotoxy(25,20);
	cout<<" Games drawn ";

	gotoxy(50,12);
	cout<<versusgames;
	gotoxy(50,14);
	cout<<versusplOne;
	gotoxy(50,15);
	if(versusgames==0)
		cout<<"0.00 %";
	else
		cout<<setprecision(3)<<((float)versusplOne/versusgames)*100<<" %";
	gotoxy(50,17);
	cout<<versusplTwo;
	gotoxy(50,18);
	if(versusgames==0)
		cout<<"0.00 %";
	else
		cout<<setprecision(3)<<((float)versusplTwo/versusgames)*100<<" %";
	gotoxy(50,20);
	cout<<versusdraw;
	gotoxy(25,25);
	cout<<" B  BACK\n";
}


void updatestats(char x);

}tttics;

void stats :: updatestats(char x)
{
	switch(x)
	{
	case 's':
	tttics.sologames++;	break;
	case 'w':
	tttics.solowon++;	 	break;
	case 'l':
	tttics.sololost++;	break;
	case 'd':
	tttics.solodraw++;	break;
	case 'V':
	tttics.versusgames++;	break;
	case 'W':
	tttics.versusplOne++;	break;
	case 'L':
	tttics.versusplTwo++;	break;
	case 'D':
	tttics.versusdraw++;		break;
	default:
	tttics.sologames=tttics.solowon=tttics.sololost=tttics.solodraw=tttics.versusgames=tttics.versusplOne=tttics.versusplTwo=tttics.versusdraw=0;
	}
}


int main()
{
	clrscr();
	gotoxy(3,21);
	cout<<"TICTACTICS";
	gotoxy(3,22);
	cout<<"PRESS ANY KEY";
	gotoxy(33,24);
	cout<<"Build 15116 V 3.0\n";
	getch();
	statin.open("gamest.dat",ios::in|ios::out|ios::binary);
	if(!statin)
		tttics.updatestats('?');
	statin.read((char *)&tttics,sizeof(stats));
	timedelay();
	mainmenu();
	return 0;
}


void mainmenu()
{
	char menuoption,mode;
	choice='\0',z=0;

	gamemodeselection:
	menuoutline("GAME MODE SELECTION",'S',"SOLO",'V',"VERSUS",'A',"ABOUT",'Q',"QUIT",' '," ",' '," ",' '," ");
	mode=getch();
	timedelay();
	mode=toupper(mode);
	if(mode=='S')
	{
		mainmenusolo:
		menuoutline("MAIN MENU SOLO",'N',"NEW GAME",'I',"INSTRUCTIONS",'O',"STATISTICS",'B',"BACK",' '," ",' '," ",' '," ");
		menuoption=getch();
		timedelay();
		menuoption=toupper(menuoption);
		if(menuoption=='N')
		{
			markselection:
			menuoutline("GAME MARK SELECTION",'X',"CROSS",'O',"NOUGHT",'B',"BACK",' '," ",' '," ",' '," ",' '," ");
			mark=getch();
			timedelay();
			mark=toupper(mark);
			if(mark=='X'||mark=='O')
				gameplaysolo();
			else if(mark=='B')
				goto mainmenusolo;
			else
			{
				warning();
				goto markselection;
			}
		}
		else if(menuoption=='I')
		{
			instructions:
			instructions();
			menuoption=getch();
			timedelay();
			menuoption=toupper(menuoption);
			if(menuoption=='B')
				goto mainmenusolo;
			else
			{
				warning();
				goto instructions;
			}
		}
		else if(menuoption=='O')
		{
			statsS:
			tttics.dispstatsS();
			menuoption=getch();
			timedelay();
			menuoption=toupper(menuoption);
			if(menuoption=='B')
				goto mainmenusolo;
			else
			{
				warning();
				goto statsS;
			}
		}
		else if(menuoption=='B')
			goto gamemodeselection;
		else
		{
			warning();
			goto mainmenusolo;
		}
	}
	else if(mode=='V')
	{
		mainmenuversus:
		menuoutline("MAIN MENU VERSUS",'N',"NEW GAME",'I',"INSTRUCTIONS",'O',"STATISTICS",'B',"BACK ",' '," ",' '," ",' '," ");
		menuoption=getch();
		timedelay();
		menuoption=toupper(menuoption);
		if(menuoption=='N')
		{
			decideyourselves:
			menuoutline("GAME MARK SELECTION",' ',"DECIDE AMONG YOURSELVES WHICH MARK TO SELECT",' '," ",'C',"CONTINUE",'B',"BACK",' '," ",' '," ",' '," ");
			mark=getch();
			timedelay();
			mark=toupper(mark);
			if(mark=='C')
				gameplayversus();
			else if(mark=='B')
				goto mainmenuversus;
			else
			{
				warning();
				goto decideyourselves;
			}
		}
		else if(menuoption=='I')
		{
			instructions2:
			instructions();
			menuoption=getch();
			timedelay();
			menuoption=toupper(menuoption);
			if(menuoption=='B')
				goto mainmenuversus;
			else
			{
				warning();
				goto instructions2;
			}
		}
		else if(menuoption=='O')
		{
			statsV:
			tttics.dispstatsV();
			menuoption=getch();
			timedelay();
			menuoption=toupper(menuoption);
			if(menuoption=='B')
				goto mainmenuversus;
			else
			{
				warning();
				goto statsV;
			}
		}
		else if(menuoption=='B')
			goto gamemodeselection;
		else
		{
			warning();
			goto mainmenuversus;
		}
	}

	else if(mode=='A')
	{
		about:
		menuoutline("ABOUT",' ',"TicTactics",' ',"Version 3.0.15116",' ',"MADE BY ANURAG ROY ",' ',"CLASS XIIB",' '," ",'B',"BACK",' '," ");
		menuoption=getch();
		timedelay();
		menuoption=toupper(menuoption);
		if(menuoption=='B')
			goto gamemodeselection;
		else
		{
			warning();
			goto about;
		}

	}
	else if(mode=='Q')
	{
		quitgame:
		cout<<"\a";
		menuoutline("QUITTING GAME",' ',"Are you sure you want to quit this game?",' '," ",'Y',"YES",'N',"NO",' '," ",' '," ",' '," ");
		menuoption=getch();
		timedelay();
		menuoption=toupper(menuoption);
		if(menuoption=='Y')
		{
			clrscr();
			statin.seekp(0,ios::beg);
			statin.write((char *)&tttics,sizeof(stats));
			statin.close();
			DestroyWindow(GetActiveWindow());
			exit(0);
		}
		else if(menuoption=='N')
		{
			goto gamemodeselection;
		}
		else
		{
			warning();
			goto quitgame;
		}
	}
	else
	{
		warning();
		goto gamemodeselection;
	}

 return ;
}


void pausemenu(char c)
{
	quitsession:
	char pauseopt;
	clrscr();
	if(c=='P')
		menuoutline("GAME PAUSED",'\b',"\b\bEsc RESUME",'R',"RESTART",'Q',"QUIT TO MAIN MENU",'E',"QUIT GAME",' '," ",' '," ",' '," ");
	else if(c=='S')
		menuoutline("GAME WON",'R',"RESTART",'Q',"QUIT TO MAIN MENU",'E',"QUIT GAME",' '," ",' '," ",' '," ",' '," ");
	else if(c=='s')
		menuoutline("GAME LOST",'R',"RESTART",'Q',"QUIT TO MAIN MENU",'E',"QUIT GAME",' '," ",' '," ",' '," ",' '," ");
	else if(c=='V')
		menuoutline("PLAYER 1 WINS!",'R',"RESTART",'Q',"QUIT TO MAIN MENU",'E',"QUIT GAME",' '," ",' '," ",' '," ",' '," ");
	else if(c=='v')
		menuoutline("PLAYER 2 WINS!",'R',"RESTART",'Q',"QUIT TO MAIN MENU",'E',"QUIT GAME",' '," ",' '," ",' '," ",' '," ");
	else if(c=='D')
		menuoutline("GAME DRAW",'R',"RESTART",'Q',"QUIT TO MAIN MENU",'E',"QUIT GAME",' '," ",' '," ",' '," ",' '," ");

	pauseopt=getch();
	pauseopt=toupper(pauseopt);
	if(pauseopt==27&&c=='P')
	{
		choice='0';
		return;
	}
	else if(pauseopt=='Q')
	{
		quitmainmenu:
		menuoutline("QUITTING TO MAIN MENU",' ',"Are you sure you want to quit to main menu?",' '," ",'Y',"YES",'N',"NO",' '," ",' '," ",' '," ");
		pauseopt=getch();
		timedelay();
		pauseopt=toupper(pauseopt);
		if(pauseopt=='Y')
		{
			for(int i=0;i<10;i++)
				square[i] = (48+i);
			mainmenu();
		}
		else if(pauseopt=='N')
			goto quitsession;
		else
		{
			warning();
			goto quitmainmenu;
		}
	}

	else if(pauseopt=='R')
	{
		restart:
		menuoutline("RESTARTING GAME",' ',"Are you sure you want to restart this game?",' '," ",'Y',"YES",'N',"NO",' '," ",' '," ",' '," ");
		pauseopt=getch();
		timedelay();
		pauseopt=toupper(pauseopt);
		if(pauseopt=='Y')
		{
			for(int i=0;i<10;i++)
				square[i] = (48+i);
			return;

		}
		else if(pauseopt=='N')
			goto quitsession;
		else
		{
			warning();
			goto restart;
		}
	}
	else if(pauseopt=='E')
	{
		quitgame:
		cout<<"\a";
		menuoutline("QUITTING GAME",' ',"Are you sure you want to quit this game?",' '," ",'Y',"YES",'N',"NO",' '," ",' '," ",' '," ");
		pauseopt=getch();
		timedelay();
		pauseopt=toupper(pauseopt);
		if(pauseopt=='Y')
		{
			clrscr();
			statin.seekp(0,ios::beg);
			statin.write((char *)&tttics,sizeof(stats));
			statin.close();
			DestroyWindow(GetActiveWindow());
			exit(0);
		}
		else if(pauseopt=='N')
			goto quitsession;
		else
		{
			warning();
			goto quitgame;
		}
	}
	else
	{
		warning();
		goto quitsession;
	}
}


void gameplaysolo()
{
	start:
	int i,a=0,b=0;
	char p;
	choice='\0',z=0;
	clrscr();

	do
	{
		compmark=(mark=='X')?'O':'X';
		sologameplayon:
		if(mark=='X')
		{
			board('S');
			i=checkwin();
		}
		else if(mark=='O')
		{
			if(choice!='0')
			{
				cpuai();
				square[z]=compmark;
				a++;
			}
			board('S');
			i=checkwin();
		}
		if(i==-1)
		{
			gotoxy(3,20);
			for(int space=0;space<=(21-(strlen("1-9   MARK")));space++)
			cout<<" ";
			cout <<"1-9   MARK";
			gotoxy(3,21);
			for(space=0;space<=(21-(strlen("Esc  PAUSE")));space++)
			cout<<" ";
			cout<<"Esc  PAUSE\n\n";
			choice=getch();
			choice=toupper(choice);
			timedelay();
			if(choice>=49&&choice<=57&&square[(int)choice-48]==choice)
				markwrite(choice);

			else if(choice==27)
			{
				pausemenu('P');
				goto sologameplayon;

			}
			else
			{
				cout<<"\a            INVALID MOVE";
				if(mark=='O')
				{
					a--;
					choice='0';
				}
				getch();
				goto sologameplayon;
			}
			cout<<" WAITING FOR COMPUTER...";
			if(mark=='X')
				a++;
			else if(mark=='O')
				b++;
		}
		i=checkwin();
		if(i==-1&&mark=='X')
		{
			cpuai();
			square[z]=compmark;
			b++;
		}
	}while(i==-1);
	tttics.updatestats('s');
	board('S');
	if((i==1)&&mark=='X')
	{
		if(a>b)
		{
			cout<<"				  	\aCONGRATULATIONS,YOU'VE WON!\n";
			tttics.updatestats('w');
			p='S';
		}
		else
		{
			cout<<"				\aSORRY,YOU LOST THIS GAME.BETTER LUCK NEXT TIME!\n";
			tttics.updatestats('l');
			p='s';
		}
	}

	else if((i==1)&&mark=='O')
	{
		if(a>b)
		{
			cout<<"				\aSORRY,YOU LOST THIS GAME.BETTER LUCK NEXT TIME!\n";
			tttics.updatestats('l');
			p='s';
		}
		else
		{
			cout<<"				  	\aCONGRATULATIONS,YOU'VE WON!\n";
			tttics.updatestats('w');
			p='S';
		}

	}

	else if(i==0)
	{
		cout<<"				                  \aGAME DRAW\n";
		tttics.updatestats('d');
		p='D';
	}
	cout<<"\n PRESS ANY KEY TO CONTINUE\n" ;
	choice=getch();

	timedelay();
	pausemenu(p);
	goto start;

}



void gameplayversus()
{
	start:
	int player=1,i;
	char p;
	choice='\0',z=0;

	do
	{
		versusgameplayon:
		board('V');
		gotoxy(3,20);
		for(int space=0;space<=(21-(strlen("1-9   MARK")));space++)
		cout<<" ";
		cout <<"1-9   MARK";
		gotoxy(3,21);
		for(space=0;space<=(21-(strlen("Esc  PAUSE")));space++)
		cout<<" ";
		cout<<"Esc  PAUSE";
		player=(player%2)?1:2;
		gotoxy(3,23);
		for(space=0;space<=(21-(strlen("Player  's turn")));space++)
		cout<<" ";
		cout << "Player " << player << "'s turn\n\n";
		choice=getch();
		choice=toupper(choice);
		timedelay();
		mark=(player == 1) ? 'X' : 'O';
		if(choice>=49&&choice<=57&&square[(int)choice-48]==choice)
			markwrite(choice);

		else if(choice==27)
		{
			pausemenu('P');
			goto versusgameplayon;
		}
		else
		{
			cout<<"            \aINVALID MOVE ";
			player--;
			getch();

		}
		i=checkwin();
		player++;
	}while(i==-1);
	tttics.updatestats('V');
	board('V');
	if(i==1)
	{
		if(--player==1)
		{
			tttics.updatestats('W');
			p='V';
		}
		else
		{
			tttics.updatestats('L');
			p='v';
		}
		cout<<"				               \aPLAYER "<<player<<" WINS!\n";
	}
	else
	{
		cout<<"				\aGAME DRAW\n";
		tttics.updatestats('D');
		p='D';
	}

	cout<<"\n PRESS ANY KEY TO CONTINUE\n" ;
	mark=getch();
	timedelay();
	pausemenu(p);
	goto start;
}



int checkwin()
{
	if (square[1] == square[2] && square[2] == square[3])
		return 1;
	else if (square[4] == square[5] && square[5] == square[6])
		return 1;
	else if (square[7] == square[8] && square[8] == square[9])
		return 1;
	else if (square[1] == square[4] && square[4] == square[7])
		return 1;
	else if (square[2] == square[5] && square[5] == square[8])
		return 1;
	else if (square[3] == square[6] && square[6] == square[9])
		return 1;
	else if (square[1] == square[5] && square[5] == square[9])
		return 1;
	else if (square[3] == square[5] && square[5] == square[7])
		return 1;
	else if (square[1] != '1' && square[2] != '2' && square[3] != '3' &&
				square[4] != '4' && square[5] != '5' && square[6] != '6' &&
				square[7] != '7' && square[8] != '8' && square[9] != '9')
		return 0;
	else
		return -1;
}


void cpuai()
{
	char check=compmark;
	int flag=0;
	do
	{
		if(square[1]==square[2]&&square[1]==check&&square[3]=='3')
			{
				z=3;
				break;
			}
		else if(square[2]==square[3]&&square[2]==check&&square[1]=='1')
			{
				z=1;
				break;
			}
		else if(square[1]==square[3]&&square[1]==check&&square[2]=='2')
			{
				z=2;
				break;
			}

		else if(square[4]==square[5]&&square[4]==check&&square[6]=='6')
			{
				z=6;
				break;
			}
		else if(square[5]==square[6]&&square[5]==check&&square[4]=='4')
			{
				z=4;
				break;
			}
		else if(square[4]==square[6]&&square[4]==check&&square[5]=='5')
			{
				z=5;
				break;
			}

		else if(square[7]==square[8]&&square[7]==check&&square[9]=='9')
			{
				z=9;
				break;
			}
		else if(square[8]==square[9]&&square[8]==check&&square[7]=='7')
			{
				z=7;
				break;
			}
		else if(square[7]==square[9]&&square[7]==check&&square[8]=='8')
			{
				z=8;
				break;
			}

		else if(square[1]==square[4]&&square[1]==check&&square[7]=='7')
			{
				z=7;
				break;
			}
		else if(square[4]==square[7]&&square[4]==check&&square[1]=='1')
			{
				z=1;
				break;
			}
		else if(square[1]==square[7]&&square[1]==check&&square[4]=='4')
			{
				z=4;
				break;
			}

		else if(square[2]==square[5]&&square[2]==check&&square[8]=='8')
			{
				z=8;
				break;
			}
		else if(square[5]==square[8]&&square[5]==check&&square[2]=='2')
			{
				z=2;
				break;
			}
		else if(square[2]==square[8]&&square[2]==check&&square[5]=='5')
			{
				z=5;
				break;
			}

		else if(square[3]==square[6]&&square[3]==check&&square[9]=='9')
			{
				z=9;
				break;
			}
		else if(square[6]==square[9]&&square[6]==check&&square[3]=='3')
			{
				z=3;
				break;
			}
		else if(square[3]==square[9]&&square[3]==check&&square[6]=='6')
			{
				z=6;
				break;
			}

		else if(square[1]==square[5]&&square[1]==check&&square[9]=='9')
			{
				z=9;
				break;
			}
		else if(square[5]==square[9]&&square[5]==check&&square[1]=='1')
			{
				z=1;
				break;
			}
		else if(square[1]==square[9]&&square[1]==check&&square[5]=='5')
			{
				z=5;
				break;
			}

		else if(square[3]==square[5]&&square[3]==check&&square[7]=='7')
			{
				z=7;
				break;
			}
		else if(square[3]==square[7]&&square[3]==check&&square[5]=='5')
			{
				z=5;
				break;
			}
		else if(square[5]==square[7]&&square[5]==check&&square[3]=='3')
			{
				z=3;
				break;
			}
		else
			{
				flag++;
				check=mark;
			}
	}while(flag!=2);


	if(flag==2)
		vacantSpace();

}



void board(char mode)
{
	clrscr();
	gotoxy(3,3);
	cout << "TICTACTICS";
	if(mode=='S')
	{
		gotoxy(3,8);
		for(int space=0;space<=(21-(strlen("YOU[ ]")));space++)
			cout<<" ";
		cout<<"YOU["<<mark<<"]";
		gotoxy(3,11);
		for(space=0;space<=(21-(strlen("COMPUTER[ ]")));space++)
			cout<<" ";
		cout<<"COMPUTER["<<compmark<<"]";
	}
	else
	{
		gotoxy(3,8);
		for(int space=0;space<=(21-(strlen("PLAYER 1[X]")));space++)
			cout<<" ";
		cout<<"PLAYER 1[X]";
		gotoxy(3,11);
		for(space=0;space<=(21-(strlen("PLAYER 2[O]")));space++)
			cout<<" ";
		cout<<"PLAYER 2[O]";
	}

	gotoxy(47,8);
	cout <<box(1,'+')<<box(1,'-')<<box(1,'-')<<box(1,'-')<<box(1,'+')<<"|"<<box(2,'+')<<box(2,'-')<<box(2,'-')<<box(2,'-')<<box(2,'+')<<"|"<<box(3,'+')<<box(3,'-')<<box(3,'-')<<box(3,'-')<<box(3,'+');
	gotoxy(47,9);
	cout <<box(1,'|')<< " " << square[1] << " "<<box(1,'|')<<"|"<<box(2,'|')<<" " << square[2] << " "<<box(2,'|')<<"|"<<box(3,'|')<<" " << square[3]<<" "<<box(3,'|');
	gotoxy(47,10);
	cout <<box(1,'+')<<box(1,'-')<<box(1,'-')<<box(1,'-')<<box(1,'+')<<"|"<<box(2,'+')<<box(2,'-')<<box(2,'-')<<box(2,'-')<<box(2,'+')<<"|"<<box(3,'+')<<box(3,'-')<<box(3,'-')<<box(3,'-')<<box(3,'+');
	gotoxy(47,11);
	cout << "-----+-----+-----" ;
	gotoxy(47,12);
	cout <<box(4,'+')<<box(4,'-')<<box(4,'-')<<box(4,'-')<<box(4,'+')<<"|"<<box(5,'+')<<box(5,'-')<<box(5,'-')<<box(5,'-')<<box(5,'+')<<"|"<<box(6,'+')<<box(6,'-')<<box(6,'-')<<box(6,'-')<<box(6,'+');
	gotoxy(47,13);
	cout <<box(4,'|')<< " " << square[4] << " "<<box(4,'|')<<"|"<<box(5,'|')<<" " << square[5] << " "<<box(5,'|')<<"|"<<box(6,'|')<<" " << square[6]<<" "<<box(6,'|');
	gotoxy(47,14);
	cout <<box(4,'+')<<box(4,'-')<<box(4,'-')<<box(4,'-')<<box(4,'+')<<"|"<<box(5,'+')<<box(5,'-')<<box(5,'-')<<box(5,'-')<<box(5,'+')<<"|"<<box(6,'+')<<box(6,'-')<<box(6,'-')<<box(6,'-')<<box(6,'+');
	gotoxy(47,15);
	cout << "-----+-----+-----" ;
	gotoxy(47,16);
	cout <<box(7,'+')<<box(7,'-')<<box(7,'-')<<box(7,'-')<<box(7,'+')<<"|"<<box(8,'+')<<box(8,'-')<<box(8,'-')<<box(8,'-')<<box(8,'+')<<"|"<<box(9,'+')<<box(9,'-')<<box(9,'-')<<box(9,'-')<<box(9,'+');
	gotoxy(47,17);
	cout <<box(7,'|')<< " " << square[7] << " "<<box(7,'|')<<"|"<<box(8,'|')<<" " << square[8] << " "<<box(8,'|')<<"|"<<box(9,'|')<<" " << square[9]<<" "<<box(9,'|');
	gotoxy(47,18);
	cout <<box(7,'+')<<box(7,'-')<<box(7,'-')<<box(7,'-')<<box(7,'+')<<"|"<<box(8,'+')<<box(8,'-')<<box(8,'-')<<box(8,'-')<<box(8,'+')<<"|"<<box(9,'+')<<box(9,'-')<<box(9,'-')<<box(9,'-')<<box(9,'+')<< endl << endl;

}


void timedelay()
{
	for(long int time=1;time<=240000000;time++);
	return;
}


void warning()
{
	cout<<"\a";
	menuoutline("WARNING",' ',"Wrong button pressed.",' ',"Press any key to try again.",' '," ",' '," ",' '," ",' '," ",' '," ");
	getch();
	timedelay();
	return;
}

void instructions()
{
	menuoutline("INSTRUCTIONS",'\b',"The objective of TicTactics is to get 3, horizontally",'\b',"/vertically/diagonally, on a 3X3 board. Select your",'\b',"mark(X/O)according to your choice. Place Xs/Os on the",'\b',"board alternately until either opponent has 3 in a",'\b',"row or all 9 squares are filled. X always goes first,",'\b',"and if no one has three in a row the game goes draw.",'B',"BACK");
	return;
}

void menuoutline(char main[],char sel1,char opt1[],char sel2,char opt2[],char sel3,char opt3[],char sel4,char opt4[],char sel5,char opt5[],char sel6,char opt6[],char sel7,char opt7[])
{
	clrscr();
	gotoxy(3,3);
	cout << "TICTACTICS";
	gotoxy(3,8);
	for(int space=0;space<=(21-(strlen(main)));space++)
		cout<<" ";
	puts(main);
	gotoxy(25,11);
	cout<<" "<<sel1<<"   ";cout.write(opt1,strlen(opt1));cout<<"\n";
	gotoxy(25,13);
	cout<<" "<<sel2<<"   ";cout.write(opt2,strlen(opt2));cout<<"\n";
	gotoxy(25,15);
	cout<<" "<<sel3<<"   ";cout.write(opt3,strlen(opt3));cout<<"\n";
	gotoxy(25,17);
	cout<<" "<<sel4<<"   ";cout.write(opt4,strlen(opt4));cout<<"\n";
	gotoxy(25,19);
	cout<<" "<<sel5<<"   ";cout.write(opt5,strlen(opt5));cout<<"\n";
	gotoxy(25,21);
	cout<<" "<<sel6<<"   ";cout.write(opt6,strlen(opt6));cout<<"\n";
	gotoxy(25,23);
	cout<<" "<<sel7<<"   ";cout.write(opt7,strlen(opt7));cout<<"\n  ";

	return;
}

void markwrite(char x)
{
	if (x == '1' && square[1] == '1')
		square[1] = mark;
	else if (x == '2' && square[2] == '2')
		square[2] = mark;
	else if (x == '3' && square[3] == '3')
		square[3] = mark;
	else if (x == '4' && square[4] == '4')
		square[4] = mark;
	else if (x == '5' && square[5] == '5')
		square[5] = mark;
	else if (x == '6' && square[6] == '6')
		square[6] = mark;
	else if (x == '7' && square[7] == '7')
		square[7] = mark;
	else if (x == '8' && square[8] == '8')
		square[8] = mark;
	else if (x == '9' && square[9] == '9')
		square[9] = mark;

}

void vacantSpace()
{
	int size=0,i,j;
	for(i=1;i<=9;i++)
	{
		if(((int)square[i]-48)==i)
			size++;
	}

	char *space=new char[size];
	for(i=1,j=0;i<=9,j<size;i++)
	{
		if(((int)square[i]-48)==i)
		{
			space[j]=square[i];
			j++;
		}
	}
	randomize();
	i=random(size);
	z=(int)space[i]-48;
	delete[size]space;
}

char box(int n,char c)
{
	if((n==z || n==((int)choice-48))&&checkwin()==-1)
		return c;
	else if (square[1] == square[2] && square[2] == square[3])
	{
		if(n==1||n==2||n==3)
			return c;
	}
	else if (square[4] == square[5] && square[5] == square[6])
	{
		if(n==4||n==5||n==6)
			return c;
	}
	else if (square[7] == square[8] && square[8] == square[9])
	{
		if(n==7||n==8||n==9)
			return c;
	}
	else if (square[1] == square[4] && square[4] == square[7])
	{
		if(n==1||n==4||n==7)
			return c;
	}
	else if (square[2] == square[5] && square[5] == square[8])
		{
		if(n==2||n==5||n==8)
			return c;
	}
	else if (square[3] == square[6] && square[6] == square[9])
	{
		if(n==3||n==6||n==9)
			return c;
	}
	else if (square[1] == square[5] && square[5] == square[9])
	{
		if(n==1||n==5||n==9)
			return c;
	}
	else if (square[3] == square[5] && square[5] == square[7])
	{
		if(n==3||n==5||n==7)
			return c;
	}
	else
		return ' ';
}
