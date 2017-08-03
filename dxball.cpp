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
class bounds{
public:
    static const int bound_X=16;
    static const int bound_Y=16;
    void show_bounds()
    {
        for(int i=0;i<=bound_X;i++)
        {
            gotoxy(i,bound_Y,'~');
        }
        for(int i=0;i<bound_X;i++)
        {
            gotoxy(bound_X,i,'|');
        }
    }
    bool bound_check_X(int x)
    {
        if(x<0 || x>bound_X-1)
        {
            return false;
        }
        else
            return true;
    }
};

class dx_bat:public virtual bounds{
public:
    int x,y;
    int bat_len;
    deque<point>b;
    dx_bat()
    {
        y=15;
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
        for(int i=1;i<bat_len;i++)
        {
            temp=b.front();
            batpoint(temp.x+i);
        }
    }
    void bat_move_left()
    {
        temp=b.front();
        temp.x=temp.x-1;
        if(bound_check_X(temp.x))
        {
            b.push_front(temp);
            b.pop_back();
        }
    }
    void bat_move_right()
    {
        temp=b.back();
        temp.x=temp.x+1;
        if(bound_check_X(temp.x))
        {
            b.pop_front();
            b.push_back(temp);
        }
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
class brick:public virtual bounds{
public:
    int bricks[bound_X][bound_Y/2];
    brick()
    {
        for(int i=0;i<(bound_Y/2);i++)
        {
            for(int j=i;j<(bound_X/2);j++)
            {
                bricks[j][i]=1;
            }
            for(int k=bound_X/2;k<(bound_X-i);k++)
            {
                 bricks[k][i]=1;
            }
        }
    }
    void show_brick()
    {
        for(int i=0;i<(bound_Y/2);i++)
        {
            for(int j=0;j<bound_X;j++)
            {
                if(bricks[j][i]==1)
                {
                    gotoxy(j,i,'z');
                }
            }
        }
    }
    void delete_brick(int x,int y)
    {
        bricks[x][y]=0;
    }
    void brick_hit(int x,int y)
    {
        if(bricks[x][y-1]==1)
        {
            if(bricks[x-1][y]==1)
            {
                delete_brick(x,y-1);
                delete_brick(x-1,y);
            }
            else if(bricks[x+1][y]==1)
            {
                delete_brick(x,y-1);
                delete_brick(x+1,y);
            }
            else
            {
                delete_brick(x,y-1);
            }
        }
        else if(bricks[x-1][y-1]==1)
        {
            delete_brick(x-1,y-1);
        }
        else if(bricks[x+1][y-1]==1)
        {
            delete_brick(x+1,y-1);
        }
    }
};
class ball{
public:
    //ball()




};
class game:public dx_bat,public brick{
public:
    game()
    {
        dx_bat bat;
        batpoint(5);
        batlen();
        show_bat();
    }
    void play()
    {
        char n='n';
        system("cls");
        show_bounds();
        show_bat();
        show_brick();
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
            case 'n':
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
