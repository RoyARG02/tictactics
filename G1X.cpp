#include<iomanip>
#include<windows.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>
#include<fstream>
#include<conio.h>
#include<stdbool.h>

using namespace std;

char square[10] = {'0','1','2','3','4','5','6','7','8','9'};
int menu();
void pausemenu(char);
void menuoutline(const string&,const string&,const string&,const string&,const string&,const string&,const string&,const string&,const string&);
void gameSolo();
void gameVersus();
void markwrite(char);
void timedelay();
void warning();
void instructions();
void cpuai();
int checkwin();
void board(char);
char box(int,char);
void vacantSpace();
void reset();
int z=0;
char mark;
char choice='\0';
char compmark;

class stats
{
    int sologames;
    int solowon;
    int sololost;
    int versusgames;
    int versusplOne;
    int versusplTwo;
    public:
        void dispstatsS()
        {
            menuoutline("STATISTICS","\0","\0","\0","\0","\0","\0","\0","\0");
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
            cout<<sologames-(solowon+sololost);
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
            menuoutline("STATISTICS","\0","\0","\0","\0","\0","\0","\0","\0");
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
            cout<<versusgames-(versusplOne+versusplTwo);
            gotoxy(25,25);
            cout<<" B  BACK\n";
        }
        void updatestats(char x);
}tttics;

void stats :: updatestats(short int update)
{
    if(!readSuccess)
        tttics.sologames=tttics.solowon=tttics.sololost=tttics.versusgames=tttics.versusplOne=tttics.versusplTwo=0;
    if(update<2)
    {
        tttics.sologames++;
        if(update==1)
            solowon++;
        else
            sololost++;
    }
    else
    {
        tttics.versusgames++;
        if(update==2)
            tttics.versusplOne++;
        else
            tttics.versusplTwo++;
    }
	fstream writ;
	writ.open("file4",ios::out|ios::binary);
	writ.write((char*)&tttics,sizeof(class stats));
    writ.close();
}

char input(char Low)
{
    return (Low>90)?Low-=32:Low;
}

bool readStats()
{
    fstream data;
    data.open("file4",ios::in|ios::binary);
    if(!data)
        return false;
    data.read((char*)&tttics,sizeof(class stats));
    data.close();
    return true;
}

BOOL gotoxy(const WORD x,const WORD y)
{
    COORD coordinates;
    coordinates.X=x;
    coordinates.Y=y;
    return SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coordinates);
}

void reset()
{
    for(int i=0;i<10;i++)
        square[i] = (48+i);
}

int main()
{
	clrscr();
	/*gotoxy(3,21);
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
	return 0;*/

	int mode;
	while(1)
    {
        readSuccess=readStats();
        mode=menu();
        if(mode==2)
            gameVersus();
        else
            gameSolo(mode);
    }

}


int menu()
{
	char option;
    gamemodeselection:
	menuoutline("GAME MODE SELECTION","S","SOLO","V","VERSUS","Q","QUIT","\0","\0");
	option=input(getch());
	if(option=='S')
	{
		mainmenusolo:
		menuoutline("MAIN MENU SOLO","N","NEW GAME","S","STATISTICS","B","BACK","\0","\0");
		option=input(getch());
		if(option=='N')
		{
			markselection:
			menuoutline("GAME MARK SELECTION","X","CROSS","O","NOUGHT","B","BACK","\0","\0");
			option=input(getch());
			if(option=='X')
				return 1;
            else if(option=='O')
                return -1;
			else if(mark=='B')
				goto mainmenusolo;
			else
				goto markselection;
		}
		else if(menuoption=='S')
		{
			statsS:
			tttics.dispstatsS();
			menuoption=getch();
			if(menuoption=='B')
				goto mainmenusolo;
			else
                goto statsS;
		}
		else if(menuoption=='B')
			goto gamemodeselection;
		else
			goto mainmenusolo;
	}
	else if(mode=='V')
	{
		mainmenuversus:
		menuoutline("MAIN MENU VERSUS","N","NEW GAME","S","STATISTICS","B","BACK","\0","\0");
		option=input(getch());
		if(option=='N')
		{
			decideyourselves:
			menuoutline("GAME MARKS","X","->PLAYER 1","O","->PLAYER 2","C","CONTINUE","B","BACK");
			option=input(getch());
			if(option=='C')
				return 2;
			else if(option=='B')
				goto mainmenuversus;
			else
				goto decideyourselves;
		}
		else if(option=='O')
		{
			statsV:
			tttics.dispstatsV();
			option=input(getch());
			if(option=='B')
				goto mainmenuversus;
			else
				goto statsV;
		}
		else if(menuoption=='B')
			goto gamemodeselection;
		else
			goto mainmenuversus;
	}
	else if(mode=='Q')
	{
		quitgame:
		cout<<"\a";
		menuoutline("QUITTING GAME","Y","CONFIRM","B","BACK","\0","\0","\0","\0");
		option=input(getch());
		if(menuoption=='Y')
            exit(0);
		else if(menuoption=='B')
            goto gamemodeselection;
		else
			goto quitgame;
	}
	else
		goto gamemodeselection;
    return 0;
}

void pausemenu(char call)
{
	quitsession:
	char pauseopt;
	if(call==27)
		menuoutline("GAME PAUSED","Esc","RESUME","R","RESTART","Q","QUIT TO MAIN MENU","\0","\0");
	else if(call=='S')
		menuoutline("CONGRATULATIONS,YOU'VE WON!","R","RESTART","Q","QUIT TO MAIN MENU","\0","\0","\0","\0");
	else if(call=='s')
		menuoutline("BETTER LUCK NEXT TIME!","R","RESTART","Q","QUIT TO MAIN MENU","\0","\0","\0","\0");
	else if(call=='V')
		menuoutline("PLAYER 1 WINS!","R","RESTART","Q","QUIT TO MAIN MENU","\0","\0","\0","\0");
	else if(call=='v')
		menuoutline("PLAYER 2 WINS!","R","RESTART","Q","QUIT TO MAIN MENU","\0","\0","\0","\0");
	else if(call=='D')
		menuoutline("GAME DRAW","R","RESTART","Q","QUIT TO MAIN MENU","\0","\0","\0","\0");
    pauseopt=input(getch());
	if(pauseopt==call)
	{
		choice='0';
		return;
	}
	else if(pauseopt=='Q')
	{
	    reset();
        mainmenu();
    }
    else if(pauseopt=='R')
	{
		reset();
	}
	else
        goto quitmainmenu;
}

void gameSolo(int mark)
{
	start:
	int i,a=0,b=0;
	char p;
	choice='\0',z=0;
	clrscr();
    do
	{
		compmark=(mark==1)?'O':'X';
		sologameplayon:
        board(mark,choice);
		/*if(mark=='X')
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
		}*/
		if(i==-1)
		{
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

void gameVersus()
{
	int player=1;
	char mark,choice='\0';
	do
	{
		board(2,choice);
		player=(player%2)?1:2;
		gotoxy(3,23);
		cout <<setw(21)<<"Player "<<player<<"'s turn";
		choice=input(getch());
		mark=(player == 1) ? 'X' : 'O';
		if(choice>=49&&choice<=57&&square[(int)choice-48]==choice)
			markwrite(choice,mark);
        else if(choice==27)
		{
			pausemenu(choice);
			player--;
		}
		player++;
	}while(checkwin()==-1);
	board(checkwin(),'0');
	if(checkwin())
	{
		if(--player==1)
		{
			tttics.updatestats(2);
			choice='V';
		}
		else
		{
			tttics.updatestats(3);
			choice='v';
		}
	}
	else
	{
		tttics.updatestats(4);
		choice='D';
	}
	pausemenu(choice);
}



int checkwin()
{
	if (square[1] == square[2] && square[2] == square[3])
		return 123;
	else if (square[4] == square[5] && square[5] == square[6])
		return 456;
	else if (square[7] == square[8] && square[8] == square[9])
		return 789;
	else if (square[1] == square[4] && square[4] == square[7])
		return 147;
	else if (square[2] == square[5] && square[5] == square[8])
		return 256;
	else if (square[3] == square[6] && square[6] == square[9])
		return 369;
	else if (square[1] == square[5] && square[5] == square[9])
		return 159;
	else if (square[3] == square[5] && square[5] == square[7])
		return 357;
	else if (square[1] != '1' && square[2] != '2' && square[3] != '3' &&square[4] != '4' && square[5] != '5' && square[6] != '6' && square[7] != '7' && square[8] != '8' && square[9] != '9')
		return 0;
	else
		return -1;
}


int cpuai(char check)
{
	int flag=0;
	do
	{
	    if(square[1]=='1')
        {
            if((square[2]==square[3]==check)||(square[4]==square[7]==check)||(square[5]==square[9]==check))
                return 1;
        }
        else if(square[2]=='2')
        {
            if((square[1]==square[3]==check)||(square[5]==square[8]==check))
                return 2;
        }
        else if(square[3]=='3')
        {
            if((square[1]==square[2]==check)||(square[4]==square[7]==check)||(square[5]==square[9]==check))
                return 1;
        }
		if(square[1]==square[2]&&square[1]==check&&square[3]=='3')
			return 3;
		else if(square[2]==square[3]&&square[2]==check&&square[1]=='1')
			return 1;
		else if(square[1]==square[3]&&square[1]==check&&square[2]=='2')
			return 2;
		else if(square[4]==square[5]&&square[4]==check&&square[6]=='6')
			return 6;
		else if(square[5]==square[6]&&square[5]==check&&square[4]=='4')
			return 4;
		else if(square[4]==square[6]&&square[4]==check&&square[5]=='5')
			return 5;
		else if(square[7]==square[8]&&square[7]==check&&square[9]=='9')
			return 9;
		else if(square[8]==square[9]&&square[8]==check&&square[7]=='7')
			return 7;
		else if(square[7]==square[9]&&square[7]==check&&square[8]=='8')
			return 8;
		else if(square[1]==square[4]&&square[1]==check&&square[7]=='7')
			return 7;
		else if(square[4]==square[7]&&square[4]==check&&square[1]=='1')
			return 1;
		else if(square[1]==square[7]&&square[1]==check&&square[4]=='4')
			return 4;
        else if(square[2]==square[5]&&square[2]==check&&square[8]=='8')
			return 8;
		else if(square[5]==square[8]&&square[5]==check&&square[2]=='2')
			return 2;
		else if(square[2]==square[8]&&square[2]==check&&square[5]=='5')
			return 5;
        else if(square[3]==square[6]&&square[3]==check&&square[9]=='9')
			return 9;
		else if(square[6]==square[9]&&square[6]==check&&square[3]=='3')
			return 3;
		else if(square[3]==square[9]&&square[3]==check&&square[6]=='6')
			return 6;
		else if(square[1]==square[5]&&square[1]==check&&square[9]=='9')
			return 9;
		else if(square[5]==square[9]&&square[5]==check&&square[1]=='1')
			return 1;
		else if(square[1]==square[9]&&square[1]==check&&square[5]=='5')
			return 5;
		else if(square[3]==square[5]&&square[3]==check&&square[7]=='7')
			return 7;
		else if(square[3]==square[7]&&square[3]==check&&square[5]=='5')
			return 5;
		else if(square[5]==square[7]&&square[5]==check&&square[3]=='3')
			return 3;
		else
            flag++;
	}while(flag!=2);
    return vacantSpace();
}

void boardHeader(const string &main, const string &first, const string &second)
{
  gotoxy(3,3);
  cout<<main;
  gotoxy(3,8);
  cout<<setw(21)<<first;
  gotoxy(3,11);
  cout<<setw(21)<<second;
  gotoxy(3,20);
  cout<<setw(21)<<"1-9\tMARK";
  gotoxy(3,21);
  cout<<setw(21)<<"Esc\tPAUSE";
}

void board(int mode,char write)  //write is the current mark by player/cpu
{
	clrscr();
	gotoxy(3,3);
	if(mode==1)
        boardHeader("SOLO","YOU[X]","COMPUTER[O]");
    else if(mode==-1)
        boardHeader("SOLO","YOU[O]","COMPUTER[X]");
	else if(mode==2)
        boardHeader("VERSUS","PLAYER 1[X]","PLAYER 2[O]");
    else
        write=mode/100;
    int verPos=8,horPOS=1;
    while(verPos<19)
    {
        gotoxy(47,verPos);
        if(verPos==11||verPos==15);
        {
            cout << "-----+-----+-----" ;
            verPos++;
        }
        else
        {
            cout <<box(horPOS,write)<<"|"<<box(horPOS+1,write)<<"|"<<box(horPOS+2,write);       //-1^verPos
            gotoxy(47,++verPos);
            cout <<box(-horPOS,write)<<"|"<<box(-horPOS-1,write)<<"|"<<box(-horPOS-2,write);
            gotoxy(47,++verPos);
            cout <<box(horPOS,write)<<"|"<<box(horPOS+1,write)<<"|"<<box(horPOS+2,write);
            gotoxy(47,++verPos);
            horPOS+=3;
        }
    }/*
	gotoxy(47,8);
	cout <<box(1,'+')<<box(1,'-')<<box(1,'-')<<box(1,'-')<<box(1,'+')<<"|"<<box(2,'+')<<box(2,'-')<<box(2,'-')<<box(2,'-')<<box(2,'+')<<"|"<<box(3,'+')<<box(3,'-')<<box(3,'-')<<box(3,'-')<<box(3,'+');
	gotoxy(47,9);
	cout <<box(1,'|')<< " " << square[1] << " "<<box(1,'|')<<"|"<<box(2,'|')<<" " << square[2] << " "<<box(2,'|')<<"|"<<box(3,'|')<<" " << square[3]<<" "<<box(3,'|');
	gotoxy(47,10);
	cout <<box(1,'+')<<box(1,'-')<<box(1,'-')<<box(1,'-')<<box(1,'+')<<"|"<<box(2,'+')<<box(2,'-')<<box(2,'-')<<box(2,'-')<<box(2,'+')<<"|"<<box(3,'+')<<box(3,'-')<<box(3,'-')<<box(3,'-')<<box(3,'+');
	gotoxy(47,11);
	cout << "-----+-----+-----" ;*/
}

void menuoutline(const string &main,const string &sel1,const string &opt1,const string &sel2,const string &opt2,const string &sel3,const string &opt3,const string &sel4,const string &opt4)
{
	clrscr();
	gotoxy(3,3);
	cout << "TICTACTICS";
	gotoxy(3,8);
	cout<<setw(21)<<main;
	gotoxy(25,11);
	cout<<" "<<sel1<<"   ";cout.write(opt1,strlen(opt1));
	gotoxy(25,13);
	cout<<" "<<sel2<<"   ";cout.write(opt2,strlen(opt2));
	gotoxy(25,15);
	cout<<" "<<sel3<<"   ";cout.write(opt3,strlen(opt3));
	gotoxy(25,17);
	cout<<" "<<sel4<<"   ";cout.write(opt4,strlen(opt4));
	return;
}

void markwrite(char x,char MARK)
{
	if (x == '1' && square[1] == '1')
		square[1] = MARK;
	else if (x == '2' && square[2] == '2')
		square[2] = MARK;
	else if (x == '3' && square[3] == '3')
		square[3] = MARK;
	else if (x == '4' && square[4] == '4')
		square[4] = MARK;
	else if (x == '5' && square[5] == '5')
		square[5] = MARK;
	else if (x == '6' && square[6] == '6')
		square[6] = MARK;
	else if (x == '7' && square[7] == '7')
		square[7] = MARK;
	else if (x == '8' && square[8] == '8')
		square[8] = MARK;
	else if (x == '9' && square[9] == '9')
		square[9] = MARK;
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

char box(int check,char curr)
{
    if(check+48==curr)
        cout<<"+---+";
    else if(-check+48==curr)
        cout<<"| "<<square[-check]<<" |";
    else if(check<0)
        cout<<"  "<<square[-check]<<"  ";
    else
        cout<<"     ";
    /*
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
		return ' ';*/
}
