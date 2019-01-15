#include<iomanip>
#include<windows.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<conio.h>
#include<stdbool.h>

using namespace std;

char square[10] = {'0','1','2','3','4','5','6','7','8','9'};
bool readSuccess;

int menu();
BOOL gotoxy(const WORD, const WORD);
void pausemenu(char);
void menuoutline(const string&,const string&,const string&,const string&,const string&,const string&,const string&,const string&,const string&);
void gameSolo();
void gameVersus();
void markwrite(int,char);
void cpuai();
int checkwin();
void board(int,int);
void box(int,int*);
void vacantSpace();
void reset();

BOOL gotoxy(const WORD x,const WORD y)
{
    COORD coordinates;
    coordinates.X=x;
    coordinates.Y=y;
    return SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coordinates);
}

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

void reset()
{
    for(int i=0;i<10;i++)
        square[i] = (48+i);
}

int main()
{
    system("cls");
	gotoxy(3,21);
	cout<<"TICTACTICS";
	gotoxy(3,22);
	cout<<"PRESS ANY KEY";
	gotoxy(3,1);
	cout<<"Build 0115M V 3.2";
	gotoxy(0,28);
	getch();
	system("cls");
	int mode;
	while(1)
    {
        readSuccess=readStats();
        mode=menu();
        if(mode==2)
            gameVersus();
        else
            //gameSolo(mode)
            ;
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
			else if(option=='B')
				goto mainmenusolo;
			else
				goto markselection;
		}
		else if(option=='S')
		{
			statsS:
			tttics.dispstatsS();
			option=getch();
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

void pausemenu(char call)
{
	quitsession:
	char pauseopt;
	if(call==27)
		boardHeader("GAME PAUSED","\0","\0","Esc","RESUME","R","RESTART","Q","QUIT TO MAIN MENU");
	else if(call=='S')
		boardHeader("CONGRATULATIONS,YOU'VE WON!","\0","\0","R","RESTART","Q","QUIT TO MAIN MENU","\0","\0");
	else if(call=='s')
		boardHeader("BETTER LUCK NEXT TIME!","\0","\0","R","RESTART","Q","QUIT TO MAIN MENU","\0","\0");
	else if(call=='V')
		boardHeader("PLAYER 1 WINS!","\0","\0","R","RESTART","Q","QUIT TO MAIN MENU","\0","\0");
	else if(call=='v')
		boardHeader("PLAYER 2 WINS!","\0","\0","R","RESTART","Q","QUIT TO MAIN MENU","\0","\0");
	else if(call=='D')
		boardHeader("GAME DRAW","\0","\0","R","RESTART","Q","QUIT TO MAIN MENU","\0","\0");
    gotoxy(3,28);
    pauseopt=input(getch());
	if(pauseopt==call)
		return;
	else if(pauseopt=='Q')
	{
	    reset();
        menu();
    }
    else if(pauseopt=='R')
	{
		reset();
		gameVersus();
	}
	else
        goto quitsession;
}

void gameVersus()
{
	int player=1;
	char mark,choice='\0';
	int prev=0;
	do
	{

		board(2,prev);
        player=(player%2)?1:2;
		gotoxy(3,22);
		cout <<setw(18)<<"Player "<<player<<"'s turn";
		gotoxy(3,28);
		choice=input(getch());
		mark=(player == 1) ? 'X' : 'O';
		if(choice>=49&&choice<=57&&square[(int)choice-48]==choice)
        {
            prev=(int)choice-48;
            markwrite(prev,mark);
        }
        else
            player--;
        if(choice==27)
        {
            pausemenu(choice);
            choice='0';
        }
		player++;
	}while(checkwin()==-1);
	board(0,checkwin());
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
		return 321;
	else if (square[4] == square[5] && square[5] == square[6])
		return 654;
	else if (square[7] == square[8] && square[8] == square[9])
		return 987;
	else if (square[1] == square[4] && square[4] == square[7])
		return 741;
	else if (square[2] == square[5] && square[5] == square[8])
		return 652;
	else if (square[3] == square[6] && square[6] == square[9])
		return 963;
	else if (square[1] == square[5] && square[5] == square[9])
		return 951;
	else if (square[3] == square[5] && square[5] == square[7])
		return 753;
	else if (square[1] != '1' && square[2] != '2' && square[3] != '3' &&square[4] != '4' && square[5] != '5' && square[6] != '6' && square[7] != '7' && square[8] != '8' && square[9] != '9')
		return 0;
	else
		return -1;
}

void board(int mode,int WRITE)  //write is the current mark by player/cpu
{
	system("cls");
	int write=WRITE;
	if(mode==1)
        boardHeader("SOLO","YOU[X]","COMPUTER[O]","Esc","PAUSE","1-9","MARK","\0","\0");
    else if(mode==-1)
        boardHeader("SOLO","YOU[O]","COMPUTER[X]","Esc","PAUSE","1-9","MARK","\0","\0");
	else if(mode==2)
        boardHeader("VERSUS","PLAYER 1[X]","PLAYER 2[O]","Esc","PAUSE","1-9","MARK","\0","\0");
    int verPos=8,element=1;
    while(verPos<19)
    {
        gotoxy(55,verPos);
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
            gotoxy(55,++verPos);write=WRITE;
            box(-element,&write);cout <<"|";box(-element-1,&write);cout<<"|";box(-element-2,&write);
            gotoxy(55,++verPos);write=WRITE;
            box(element,&write);cout<<"|";box(element+1,&write);cout<<"|";box(element+2,&write);
            gotoxy(55,++verPos);
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
	if (square[x] == '1')
		square[1] = MARK;
	else if (square[x] == '2')
		square[2] = MARK;
	else if (square[x] == '3')
		square[3] = MARK;
	else if (square[x] == '4')
		square[4] = MARK;
	else if (square[x] == '5')
		square[5] = MARK;
	else if (square[x] == '6')
		square[6] = MARK;
	else if (square[x] == '7')
		square[7] = MARK;
	else if (square[x] == '8')
		square[8] = MARK;
	else if (square[x] == '9')
		square[9] = MARK;
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
