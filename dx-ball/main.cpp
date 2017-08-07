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
}p,temp,ball;

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
        p.x=x;
        p.y=y;
        b.push_back(p);
    }
    void batlen()
    {
        for(int i=1;i<bat_len;i++)
        {
            p=b.front();
            batpoint(p.x+i);
        }
    }
    void bat_move_left()
    {
        p=b.front();
        p.x=p.x-1;
        if(bound_check_X(p.x))
        {
            b.push_front(p);
            b.pop_back();
        }
    }
    void bat_move_right()
    {
        p=b.back();
        p.x=p.x+1;
        if(bound_check_X(p.x))
        {
            b.pop_front();
            b.push_back(p);
        }
    }
    void show_bat()
    {
        deque<point>::iterator it;
        for (it=b.begin();it!=b.end();it++)
        {
            p=*it;
            gotoxy(p.x,p.y,'=');
        }
    }
};
class brick:public virtual bounds{
public:
    int bricks[bound_X][bound_Y];
    brick()
    {
        for(int i=0;i<5;i++)
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
        for(int i=0;i<5;i++)
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
    int brick_hit(int x,int y)
    {
        //cout<<x<<endl;
        //cout<<y<<endl;
        if(bricks[x][y-1]==1)
        {
            if(bricks[x-1][y]==1)
            {
                delete_brick(x,y-1);
                delete_brick(x-1,y);
                return (1);
            }
            else if(bricks[x+1][y]==1)
            {
                delete_brick(x,y-1);
                delete_brick(x+1,y);
                return (2);
            }
            else
            {
                delete_brick(x,y-1);
                return (3);
            }
        }
        else if(bricks[x-1][y-1]==1)
        {
            delete_brick(x-1,y-1);
            return (4);
        }
        else if(bricks[x+1][y-1]==1)
        {
            delete_brick(x+1,y-1);
            return (5);
        }
        else
        {
            return (0);
        }
    }
};
class dx_ball:public dx_bat,public brick{
public:
    //ball.x;
    //ball.y;
    dx_ball()
    {//gotoxy(27,25,'A');
        ball.x=8;
        ball.y=14;
        movement_left_up();
        temp.x=8;
        temp.y=14;
   }
    void show_ball()
    {
        gotoxy(ball.x,ball.y,'O');
    }
    void collision_walls(point temp)
    {
        if(ball.x-1==0 )
        {
            if(temp.y+1==ball.y)
            {
                movement_right_down();
            }
            else if(temp.y-1==ball.y)
            {
                movement_right_up();
            }
        }
        else if(ball.x+1==bound_X)
        {
            if(temp.y+1==ball.y)
            {
                movement_left_down();
            }
            else if(temp.y-1==ball.y)
            {
                movement_left_up();
            }
        }
        else if(ball.y-1==0)
        {
            if(temp.x+1==ball.x)
            {
                movement_right_down();
            }
            else if(temp.x-1==ball.x)
            {
                movement_left_down();
            }
        }
   }
    bool game_over()
    {
        if(ball.y+1==bound_Y)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    void collision_bat(point temp)
    {
        int flag=0;
        deque<point>::iterator it;
        for (it=b.begin();it!=b.end();it++ )
        {
            p=*it;
            if(ball.x==p.x && ball.y+1==p.y)
            {
                flag=1;
                break;
            }
        }
        if(flag==1)
        {
            if(temp.x-1== ball.x)
            {
                movement_left_up();
            }
            else if(temp.x+1== ball.x)
            {
                movement_right_up();
            }
        }
    }
    void collision_brick(point temp)
    {
        int hit=brick_hit(ball.x,ball.y);
        switch(hit)
        {
        case 1:
            movement_right_down();
            break;
        case 2:
            movement_left_down();
            break;
        case 3:
            if(temp.x+1==ball.x)
            {
                movement_right_down();
            }
            else if(temp.x-1==ball.x)
            {
                movement_left_down();
            }
            break;
        case 4:
            movement_right_down();
            break;
        case 5:
            movement_left_down();
            break;
        case 0:
            break;
        }
    }
    void movement_left_up()
    {//gotoxy(25,25,'y');
        temp.x=ball.x;
        temp.y=ball.y;
        ball.x=ball.x-1;
        ball.y=ball.y-1;
    }
    void movement_right_up()
    {
        temp.x=ball.x;
        temp.y=ball.y;
        ball.x=ball.x+1;
        ball.y=ball.y-1;
    }
    void movement_left_down()
    {
        temp.x=ball.x;
        temp.y=ball.y;
        ball.x=ball.x-1;
        ball.y=ball.y+1;
    }
    void movement_right_down()
    {
        temp.x=ball.x;
        temp.y=ball.y;
        ball.x=ball.x+1;
        ball.y=ball.y+1;
    }
    void movement()
    {
        collision_walls(temp);
        collision_bat(temp);
        collision_brick(temp);
        if(temp.x-1==ball.x && temp.y-1==ball.y)
        {
            movement_left_up();
        }
        else if(temp.x+1==ball.x && temp.y-1==ball.y)
        {
            movement_right_up();
        }
        else if(temp.x-1==ball.x && temp.y+1==ball.y)
        {
            movement_left_down();
        }
        else if(temp.x+1==ball.x && temp.y+1==ball.y)
        {
            movement_right_down();
        }
    }
};
class game:public dx_ball{
public:
    game()
    {
        dx_bat bat;
        dx_ball b;
        batpoint(5);
        batlen();
        //show_bat();
        //show_ball();
    }
    void play()
    {
        char n='n';
        system("cls");
        show_bounds();
        show_bat();
        show_ball();
        show_brick();
        movement();
        start_time=GetTickCount();
        check_time=start_time+700;
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
    while(!startgame.game_over())
    {
        startgame.play();
    }
    system("cls");
    cout<<"GAME OVER ";
    return 0;
}
