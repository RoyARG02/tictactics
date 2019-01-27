#include<iomanip>
#include<windows.h>
#include<time.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<conio.h>
#include<stdbool.h>

using namespace std;

char square[3][3];
char vacant[10];
bool readSuccess;
int vacSpace=10;

int menu();
BOOL gotoxy(const WORD, const WORD);
BOOL windowSetup();
void pausemenu(char);
void menuoutline(const string&,const string&,const string&,const string&,const string&,const string&,const string&,const string&,const string&);
void gameSolo(int);
void gameVersus();
void markwrite(int,char);
int compare(int,int,char);
int cpuaix(int);
char cpuai(int);
int checkwin();
void board(int,int);
void box(int,int*);
int detMARK();
void reset();

BOOL gotoxy(const WORD x,const WORD y)
{
    COORD coordinates;
    coordinates.X=x;
    coordinates.Y=y;
    return SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coordinates);
}

BOOL windowSetup()
{
    srand((unsigned)time(NULL));
    _COORD coord;
    CONSOLE_SCREEN_BUFFER_INFO SBINFO;
    coord.X=80;
    coord.Y=30;
    _SMALL_RECT Rect;
    Rect.Top=0;
    Rect.Bottom=29;
    Rect.Left=0;
    Rect.Right=79;
    SetConsoleTitleA("TICTACTICS");
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE),TRUE,&Rect);
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

class stats
{
    int sologames;
    int solowon;
    int sololost;
    int versusgames;
    int versusplOne;
    int versusplTwo;
    bool cpuex;
    public:
        void dispstatsS()
        {
            menuoutline("SOLO STATISTICS","\0","\0","\0","\0","\0","\0","\0","\0");
            gotoxy(3,11);
            cout<<" Games played ";
            gotoxy(3,13);
            cout<<" Games won ";
            gotoxy(3,15);
            cout<<" Games lost ";
            gotoxy(3,17);
            cout<<" Games drawn ";
            gotoxy(3,19);
            cout<<" Win percentage ";
            gotoxy(30,11);
            cout<<sologames;
            gotoxy(30,13);
            cout<<solowon;
            gotoxy(30,15);
            cout<<sololost;
            gotoxy(30,17);
            cout<<sologames-(solowon+sololost);
            gotoxy(30,19);
            if(sologames==0)
                cout<<"0.00 %";
            else
                cout<<setprecision(3)<<((float)solowon/sologames)*100<<" %";
            gotoxy(3,21);
            cout<<" B  BACK";
            gotoxy(3,28);
        }

        void dispstatsV()
        {
            menuoutline("VERSUS STATISTICS","\0","\0","\0","\0","\0","\0","\0","\0");
            gotoxy(3,11);
            cout<<" Games played ";
            gotoxy(3,13);
            cout<<" Games won by player 1 ";
            gotoxy(3,15);
            cout<<" Win percentage ";
            gotoxy(3,17);
            cout<<" Games won by player 2 ";
            gotoxy(3,19);
            cout<<" Win percentage ";
            gotoxy(3,21);
            cout<<" Games drawn ";
            gotoxy(30,11);
            cout<<versusgames;
            gotoxy(30,13);
            cout<<versusplOne;
            gotoxy(30,15);
            if(versusgames==0)
                cout<<"0.00 %";
            else
                cout<<setprecision(3)<<((float)versusplOne/versusgames)*100<<" %";
            gotoxy(30,17);
            cout<<versusplTwo;
            gotoxy(30,19);
            if(versusgames==0)
                cout<<"0.00 %";
            else
                cout<<setprecision(3)<<((float)versusplTwo/versusgames)*100<<" %";
            gotoxy(30,21);
            cout<<versusgames-(versusplOne+versusplTwo);
            gotoxy(3,23);
            cout<<" B  BACK";
            gotoxy(3,28);
        }
        void updatestats(short int);
        bool toggleEX(bool);
}tttics;

bool stats::toggleEX(bool update=false)
{
    if(update)
        tttics.cpuex=(tttics.cpuex)?false:true;
    return tttics.cpuex;
}

void stats :: updatestats(short int update)
{
    if(!readSuccess)
        tttics.sologames=tttics.solowon=tttics.sololost=tttics.versusgames=tttics.versusplOne=tttics.versusplTwo=tttics.cpuex=0;
    if(update<2)
    {
        tttics.sologames++;
        if(update==1)
            solowon++;
        else if(update==-1)
            sololost++;
    }
    else
    {
        tttics.versusgames++;
        if(update==2)
            tttics.versusplOne++;
        else if(update==3)
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

void reset()
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
            square[i][j] = (48+(3*i)+j+1)
    }
    for(int i=0;i<10;i++)
        vacant[i] = (48+i);
    vacSpace=10;
}

int main()
{
    windowSetup();
	system("cls");
	reset(square);
	reset(vacant);
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
    return 0;
}

int menu()
{
	char option,aggcpu;
    gamemodeselection:
	menuoutline("GAME MODE SELECTION","S","SOLO","V","VERSUS","Q","QUIT","!","BUILD 0124(032)");
	option=input(getch());
	if(option=='S')
	{
		mainmenusolo:
		menuoutline("MAIN MENU SOLO","N","NEW GAME","S","STATISTICS","B","BACK","\0","\0");
		option=input(getch());
		if(option=='N')
		{
			markselection:
            aggcpu=(tttics.toggleEX())?251:' ';
			menuoutline("GAME MARK SELECTION","X","CROSS","O","NOUGHT","\0","\0","B","BACK");
			gotoxy(3,15);
            cout<<" T   _EXTRA_AI_TOGGLE ("<<aggcpu<<")";
            gotoxy(3,28);
			option=input(getch());
			if(option=='X')
				return 1;
            else if(option=='O')
                return -1;
            else if(option=='T')
            {
                tttics.toggleEX(1);
                goto markselection;
            }
			else if(option=='B')
				goto mainmenusolo;
			else
				goto markselection;
		}
		else if(option=='S')
		{
			statsS:
			tttics.dispstatsS();
			option=input(getch());
			if(option=='B')
				goto mainmenusolo;
			else
                goto statsS;
		}
		else if(option=='B')
			goto gamemodeselection;
		else
			goto mainmenusolo;
	}
	else if(option=='V')
	{
		mainmenuversus:
		menuoutline("MAIN MENU VERSUS","N","NEW GAME","S","STATISTICS","B","BACK","\0","\0");
		option=input(getch());
		if(option=='N')
		{
			decideyourselves:
			menuoutline("GAME MARKS","\0"," X -> PLAYER 1","\0"," O -> PLAYER 2","C","CONTINUE","B","BACK");
			option=input(getch());
			if(option=='C')
				return 2;
			else if(option=='B')
				goto mainmenuversus;
			else
				goto decideyourselves;
		}
		else if(option=='S')
		{
			statsV:
			tttics.dispstatsV();
			option=input(getch());
			if(option=='B')
				goto mainmenuversus;
			else
				goto statsV;
		}
		else if(option=='B')
			goto gamemodeselection;
		else
			goto mainmenuversus;
	}
	else if(option=='Q')
	{
		menuoutline("QUITTING GAME","\0","\0","\0","\0","\0","\0","Y","CONFIRM");
		option=input(getch());
		if(option=='Y')
            exit(0);
		else
            goto gamemodeselection;
	}
	else
		goto gamemodeselection;
    return 0;
}

void boardHeader(const string &main, const string &first, const string &second, const string &sel1, const string &op1, const string &sel2, const string &op2, const string &sel3, const string &op3)
{
  gotoxy(3,3);
  cout<<main;
  gotoxy(3,8);
  cout<<setw(21)<<first;
  gotoxy(3,11);
  cout<<setw(21)<<second;
  gotoxy(3,20);
  cout<<setw(10)<<sel1<<" "<<op1;
  gotoxy(3,21);
  cout<<setw(10)<<sel2<<" "<<op2;
  gotoxy(3,22);
  cout<<setw(10)<<sel3<<" "<<op3;
}

void pausemenu(char call,int mode)
{
	quitsession:
	char pauseopt;
	if(call==27)                            //Escape restart is bugged
		boardHeader("GAME PAUSED","\0","\0","Esc","RESUME","R","RESTART","Q","QUIT TO MAIN MENU");
	else if(call=='X'||call=='O')
		boardHeader("CONGRATULATIONS,YOU'VE WON!","\0","\0","R","RESTART","Q","QUIT TO MAIN MENU","\0","\0");
	else if(call=='s'||call=='S')
		boardHeader("BETTER LUCK NEXT TIME!","\0","\0","R","RESTART","Q","QUIT TO MAIN MENU","\0","\0");
	else if(call=='V')
		boardHeader("PLAYER 1 WINS!","\0","\0","R","RESTART","Q","QUIT TO MAIN MENU","\0","\0");
	else if(call=='v')
		boardHeader("PLAYER 2 WINS!","\0","\0","R","RESTART","Q","QUIT TO MAIN MENU","\0","\0");
	else if(call=='D'||call=='x'||call=='o')
		boardHeader("GAME DRAW","\0","\0","R","RESTART","Q","QUIT TO MAIN MENU","\0","\0");
    gotoxy(3,28);
    pauseopt=input(getch());
	if(pauseopt==call)
		return;
	else if(pauseopt=='Q')
	{
	    reset(square);
	    reset(vacant);
        main();
    }
    else if(pauseopt=='R')
	{
		reset(square);
	    reset(vacant);
	    if(call=='V'||call=='v'||call=='D')
            gameVersus();
        else
        {
            if(call=='X'||call=='x'||call=='S')
                gameSolo(1);
            else
                gameSolo(-1);
        }
	}
	else
        goto quitsession;
}

void gameSolo(int sym)
{
	char mark='X',choice='\0';
	int prev=0;
    do
    {

		board(sym,prev);
        if( (sym==1&&mark=='X') || (sym==-1&&mark=='O') )
        {
            gotoxy(3,28);
            choice=input(getch());
        }
        else
            choice=cpuai(sym);
        if(choice>=49&&choice<=57&&square[(int)(choice-49)/3][(int)(choice-49)%3]==choice)

        {
            prev=(int)choice-48;
            markwrite(prev,mark);
            mark=(mark == 'X') ? 'O' : 'X';
        }
        if(choice==27)
        {
            pausemenu(choice,1);
            choice='0';
        }
	}while(checkwin()==-1);
	board(0,checkwin());
	if(checkwin())
	{
		if((sym==1&&mark=='O') || (sym==-1&&mark=='X'))
		{
			tttics.updatestats(1);
			choice=(sym==1)?'X':'O';
		}
		else
		{
			tttics.updatestats(-1);
			choice=(sym==1)?'S':'s';
		}
	}
	else
	{
		tttics.updatestats(0);
		choice=(sym==1)?'x':'o';
	}
	pausemenu(choice);
}

void gameVersus()
{
	char mark='X',choice='\0';
	int prev=0;
	do
	{

		board(mark,prev);
		gotoxy(3,28);
		choice=input(getch());
        if(choice>=49&&choice<=57&&square[(int)(choice-49)/3][(int)(choice-49)%3]==choice)
        {
            prev=(int)choice-48;
            markwrite(prev,mark);
            mark=(mark == 'X') ? 'O' : 'X';
        }
        if(choice==27)
        {
            pausemenu(choice);
            choice='0';
        }
	}while(checkwin()==-1);
	board(0,checkwin());
	if(checkwin())
	{
		if(mark=='O')
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

int compare(int x, int y, char mark=square[x][y])
{
    if(x==y)
    {
        if(square[(x+1)%3][(y+1)%3]==square[(x+2)%3][(y+2)%3])
        {
            if(square[(x+1)%3][(y+1)%3]==mark)
            return 1;
        }
    }
    else if(x+y==2)
    {
        else if(square[(x+1)%3][(y-1)%3]==square[(x+2)%3][(y-2)%3])
        {
            if(square[(x+1)%3][(y-1)%3]==mark)
            return 1;
        }
    }

    if(square[x][(y+1)%3]==square[x][(y+2)%3])
    {
        if(square[x][(y+1)%3]==mark)
        return 1;
    }
    else if(square[(x+1)%3][y]==square[(x+2)%3][y])
    {
        if(square[(x+1)%3][y]==mark)
        return 1;
    }
    return 0;
}

int cpuaix(int sym)
{
    if(sym==1)
    {
        if(square[5]=='5')
            return 5;
        int place=rand()%4;
        return (place*3)+ (place%2)*(-1)+1;        // if even add 1
    }
    else
    {
        if(square[5]=='5'&&)
            return (rand()%2)*8 + 1
        else if(square[5]=='O')
            return 2;
        else;

    }
}

char cpuai(int sym)
{
	char check=(sym==1)?'O':'X';
	do
	{
	    for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                if(square[i][j]==49+(3*i+j))
                {
                    if(compare(i,j,check))
                        return square[i][j];
                }
            }
        }
        check=(check=='X')?'O':'X';
	}while((check=='X'&&sym==1)||(check=='O'&&sym==-1));
	if(tttics.toggleEX())
        return square[cpuaix(sym)];
    else
        return vacant[detMARK()];
}

int detMARK()
{
    return ((rand()%(vacSpace-1))+1);
}

int checkwin()
{
	if (compare(0,0))
		return 321;
	else if (compare(1,0,square[1][2]))
		return 654;
	else if (compare(2,0,square[2][2]))
		return 987;
	else if (compare(1,4,square[7]))
		return 741;
	else if (compare(2,5,square[8]))
		return 852;
	else if (compare(3,6,square[9]))
		return 963;
	else if (compare(1,5,square[9]))
		return 951;
	else if (compare(3,5,square[7]))
		return 753;
	else if (square[0][0] != '1' && square[0][1] != '2' && square[0][2] != '3' && square[1][0] != '4'
          && square[1][1] != '5' && square[1][2] != '6' && square[2][0] != '7' && square[2][1] != '8'
          && square[2][2] != '9')
		return 0;
	else
		return -1;
}

void board(int mode,int WRITE)  //write is the current mark by player/cpu
{
	system("cls");
	int write=WRITE;
	if(mode==1)
        boardHeader("SOLO","YOU[X]","COMPUTER[O]","Esc","PAUSE","1-9","MARK","X","TURN");
    else if(mode==-1)
        boardHeader("SOLO","YOU[O]","COMPUTER[X]","Esc","PAUSE","1-9","MARK","O","TURN");
	else if(mode==88)
        boardHeader("VERSUS","PLAYER 1[X]","PLAYER 2[O]","Esc","PAUSE","1-9","MARK","X","TURN");
    else if(mode==79)
        boardHeader("VERSUS","PLAYER 1[X]","PLAYER 2[O]","Esc","PAUSE","1-9","MARK","O","TURN");
    int verPos=8,element=1;
    while(verPos<19)
    {
        gotoxy(45,verPos);
        if(verPos==11||verPos==15)
        {
            cout << "-----+-----+-----" ;
            verPos++;
            if(write<WRITE)
                WRITE=WRITE/10;
        }
        else
        {
            box(element,&write);cout<<"|";box(element+1,&write);cout<<"|";box(element+2,&write);
            gotoxy(45,++verPos);write=WRITE;
            box(-element,&write);cout <<"|";box(-element-1,&write);cout<<"|";box(-element-2,&write);
            gotoxy(45,++verPos);write=WRITE;
            box(element,&write);cout<<"|";box(element+1,&write);cout<<"|";box(element+2,&write);
            gotoxy(45,++verPos);
            element+=3;
        }
    }
}

void menuoutline(const string &main,const string &sel1,const string &opt1,const string &sel2,const string &opt2,const string &sel3,const string &opt3,const string &sel4,const string &opt4)
{
	system("cls");
	gotoxy(3,3);
	cout <<main;
	gotoxy(3,11);
	cout<<" "<<sel1<<"   "<<opt1;
	gotoxy(3,13);
	cout<<" "<<sel2<<"   "<<opt2;
	gotoxy(3,15);
	cout<<" "<<sel3<<"   "<<opt3;
	gotoxy(3,17);
	cout<<" "<<sel4<<"   "<<opt4;
	gotoxy(3,28);
	return;
}

void markwrite(int x,char MARK)
{
    square[(int)(x-1)/3][(int)(x-1)%3] = MARK;
    int index=0;
    for(;vacant[index]-48<x;index++);
    while(index<vacSpace)
    {
        vacant[index]=vacant[index+1];
        index++;
    }
    vacSpace--;
}

void box(int check,int *writ)
{
    int curr=(*writ)%10;
    if(check==curr)
        cout<<"+---+";
    else if((-check)==curr)
        cout<<"| "<<square[-check]<<" |";
    else if(check<0)
    {
        cout<<"  "<<square[-check]<<"  ";
        return;
    }
    else
    {
        cout<<"     ";
        return;
    }
    *writ=(*writ)/10;
}
