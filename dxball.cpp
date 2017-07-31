#include<bits/stdc++.h>
#include<conio.h>
#include <windows.h>
using namespace std;

COORD coord={0,0};
DWORD start_time, check_time;

struct point
{
    int x;
    int y;
}p,temp;

void gotoxy(int x,int y,char c)                                        //gotoxy Function definition.
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
    cout<<c;
}

class dx_bat{
public:
    int x,y;
    int bat_len;
    deque<point>b;
    dx_bat()
    {
        y=10;
        bat_len=5;
    }
    void batpoint(int x)
    {
        temp.x=x;
        temp.y=y;
        b.push_back(temp);
    }
    void batlen()
    {
        for(int i=0;i<bat_len;i++)
        {
            temp=b.front();
            batpoint(temp.x+i);
        }
    }
    void bat_move_left()
    {
        temp=b.front();
        temp.x=temp.x-1;
        b.push_front(temp);
        b.pop_back();
    }
    void bat_move_right()
    {
        temp=b.back();
        temp.x=temp.x+1;
        b.push_back(temp);
        b.pop_front();
    }
    void show_bat()
    {
        deque<point>::iterator it;
        for (it=b.begin();it!=b.end();it++)
        {
            temp=*it;
            gotoxy(temp.x,temp.y,'=');
        }
    }
};

class game:public dx_bat{
public:
    game()
    {
        dx_bat bat;
        batpoint(10);
        batlen();
        show_bat();
    }
    char n;
    void play()
    {
        system("cls");
        show_bat();
        start_time=GetTickCount();
        check_time=start_time+1000;
        while(check_time>GetTickCount())                        //input within time period
        {
            if (kbhit())
            {
				n=getch();
                break;
            }
        }
        switch (n)                                      //movement according key pressed
        {
            case 'a':
                bat_move_left();
                break;
            case 'd':
                bat_move_right();
                break;
        }
    }
};
int main()
{
    game startgame;
    for(;;)
    {
        startgame.play();
    }
    return 0;
}
