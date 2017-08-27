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
            gotoxy(p.x,p.y,'~');
        }
    }
};
class brick:public virtual bounds{
public:
    int bricks[bound_X][bound_Y];
    brick()
    {
        for(int i=0;i<bound_Y/2;i++)
        {
            for(int j=i;j<(bound_X/2);j++)
            {
                bricks[j][i]=1000;
            }
            for(int k=bound_X/2;k<(bound_X-i);k++)
            {
                 bricks[k][i]=1000;
            }
        }
    }
    bool show_brick()
    {
        int flag=0;
        for(int i=0;i<bound_Y/2;i++)
        {
            for(int j=0;j<bound_X;j++)
            {
                if(bricks[j][i]==1000)
                {
                    gotoxy(j,i,'z');
                    flag=1;
                }
            }
        }
        if(flag==1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    void delete_brick(int x,int y)
    {
        bricks[x][y]=0;
    }
    int brick_hit(int x,int y,int a,int b)
    {  // cout<<x<<" "<<y<<" "<<a<<" "<<b<<" ";
        if(y==0)                                     //ball going
        {
            if(bricks[x+1][y+1]==1000 && a+1==x)                    //brick right bottom
            {
                delete_brick(x+1,y+1);
                return (11);
            }
            else if(bricks[x-1][y-1]==1000 && a-1==x)
            {
                delete_brick(x-1,y-1);
                return (12);
            }
            else
            {
                return (0);
            }
        }
        else if(x==0)
        {
            if(bricks[x+1][y-1]==1000)
            {
                delete_brick(x+1,y-1);
                return (13);
            }
            else if(bricks[x+1][y+1]==1000)
            {
                delete_brick(x+1,y+1);
                return (14);
            }
            else
            {
                return (0);
            }
        }
        else if(x==bound_X-1)
        {
            if(bricks[x-1][y-1]==1000)
            {
                delete_brick(x-1,y-1);
                return (15);
            }
            else if(bricks[x-1][y+1]==1000)
            {
                delete_brick(x-1,y+1);
                return (16);
            }
            else
            {
                return (0);
            }
        }
        else if(y==b-1)
        {                                               // ball moving up
            if(bricks[x][y-1]==1000)
            {
                if(bricks[x-1][y]==1000 && x==a-1)
                {
                    delete_brick(x,y-1);
                    delete_brick(x-1,y);
                    return (1);
                }
                else if(bricks[x+1][y]==1000 && x==a+1)
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
            else if(bricks[x-1][y-1]==1000 && x==a-1)
            {
                delete_brick(x-1,y-1);
                return (4);
            }
            else if(bricks[x+1][y-1]==1000 && x==a+1)
            {
                delete_brick(x+1,y-1);
                return (5);
            }
            else
            {
                return (0);
            }
        }
        else if(y==b+1)
        {                                              // ball moving down
            if(bricks[x][y+1]==1000)                   //brick is at bottom
            {
                if(bricks[x+1][y]==1000 && x==a+1)
                {
                    delete_brick(x,y+1);
                    delete_brick(x+1,y);
                    return (6);
                }
                else if(bricks[x-1][y]==1000 && x==a-1)
                {
                    delete_brick(x,y+1);
                    delete_brick(x-1,y);
                    return (7);
                }
                else
                {
                    delete_brick(x,y+1);
                    return (8);
                }
            }
            else if(bricks[x+1][y+1]==1000 && x==a+1)
            {
                delete_brick(x+1,y+1);
                return (9);
            }
            else if(bricks[x-1][y+1]==1000 && x==a-1)
            {
                delete_brick(x-1,y+1);
                return (10);
            }
            else
            {
                return (0);
            }
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
        gotoxy(ball.x,ball.y,'0');
    }
    bool collision_walls(point temp)
    {
        if(ball.x==0 )
        {
            if(ball.y==0)
            {
                corner_left_up();
            }
            else if(temp.y+1==ball.y/* && !(collision_brick(temp))*/)
            {
                movement_right_down();
            }
            else if(temp.y-1==ball.y /*&& !(collision_brick(temp))*/)
            {
                movement_right_up();
            }
            return true;
        }
        else if(ball.x+1==bound_X)
        {
            if(ball.y==0)
            {
                corner_right_up();
            }
            else if(temp.y+1==ball.y/* && !(collision_brick(temp))*/)
            {
                movement_left_down();
            }
            else if(temp.y-1==ball.y/* && !(collision_brick(temp))*/)
            {
                movement_left_up();
            }
            return true;
        }
        else if(ball.y==0)
        {
            if(temp.x+1==ball.x/* && !(collision_brick(temp))*/)
            {
                movement_right_down();
            }
            else if(temp.x-1==ball.x/* && !(collision_brick(temp))*/)
            {
                movement_left_down();
            }
            else if(temp.x==ball.x)
            {
                movement_down();
            }
            return true;
        }
        else
        {
            return false;
        }

    }
    bool game_over()
    {
        if(ball.y+1==bound_Y)
        {
            system("cls");
            cout<<"GAME OVER ";
            return true;
        }
        else
        {
            return false;
        }
    }
    bool collision_bat(point temp)
    {
        int flag=0,i=0;
        deque<point>::iterator it;
        for (it=b.begin();it!=b.end();it++,i++)
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
            if(i==0 || i ==1)
            {
                if(ball.x==0)
                {
                    corner_left_down();
                }
                else
                {
                    movement_left_up();
                }
            }
            else if(i==2)
            {
                movement_up();
            }
            else
            {
               if(ball.x==bound_X-1)
                {
                    corner_right_down();
                }
                else
                {
                    movement_right_up();
                }
            }
            return true;
        }
        else
        {
            return false;
        }
       /* if(flag==1)
        {
            if(temp.x-1== ball.x)
            {
                if(ball.x==0)
                {
                    corner_left_down();
                }
                else
                {
                    movement_left_up();
                }
                return true;
            }
            else if(temp.x+1== ball.x)
            {
                if(ball.x==bound_X-1)
                {
                    corner_right_down();
                }
                else
                {
                    movement_right_up();
                }
                return true;
            }
        }
        else
        {
            return false;
        }*/
    }
    bool collision_brick(point temp)
    {
        int hit=brick_hit(ball.x,ball.y,temp.x,temp.y);
/*        if(hit!=0)
        {
            cout<<"hit = "<<hit;
            cout<<" ";
        }*/
        switch(hit)
        {
        case 0:
            return false;
        case 1:
            movement_right_down();
            return true;
        case 2:
            movement_left_down();
            return true;
        case 3:
            if(temp.x+1==ball.x)
            {
                movement_right_down();
            }
            else if(temp.x-1==ball.x)
            {
                movement_left_down();
            }
            else
            {
                movement_down();
            }
            return true;
        case 4:
            movement_right_down();
            return true;
        case 5:
            movement_left_down();
            return true;
        case 6:
            movement_left_up();
            return true;
        case 7:
            movement_right_up();
            return true;
        case 8:
            if(temp.x+1==ball.x)
            {
                movement_right_up();
            }
            else if(temp.x-1==ball.x)
            {
                movement_left_up();
            }
            else
            {
                movement_up();
            }
            return true;
        case 9:
            movement_left_up();
            return true;
        case 10:
            movement_right_up();
            return true;
        case 11:
            movement_left_down();
            return true;
        case 12:
            movement_right_down();
            return true;
        case 13:
            movement_right_down();
            return true;
        case 14:
            movement_right_up();
            return true;
        case 15:
            movement_left_down();
            return true;
        case 16:
            movement_left_up();
            return true;
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
    void corner_right_down()
    {
        temp.x=ball.x;
        temp.y=ball.y;
        ball.x=ball.x-1;
        ball.y=ball.y-1;
    }
    void corner_left_down()
    {
        temp.x=ball.x;
        temp.y=ball.y;
        ball.x=ball.x+1;
        ball.y=ball.y-1;
    }
    void corner_left_up()
    {
        temp.x=ball.x;
        temp.y=ball.y;
        ball.x=ball.x+1;
        ball.y=ball.y+1;
    }
    void corner_right_up()
    {
        temp.x=ball.x;
        temp.y=ball.y;
        ball.x=ball.x-1;
        ball.y=ball.y+1;
    }
    void movement_up()
    {
        temp.x=ball.x;
        temp.y=ball.y;
        ball.y=ball.y-1;
        ball.x=ball.x;
    }
    void movement_down()
    {
        temp.x=ball.x;
        temp.y=ball.y;
        ball.y=ball.y+1;
        ball.x=ball.x;
    }
    void movement()
    {
        if(collision_brick(temp))
        {

        }
        else if(collision_bat(temp))
        {

        }
        else if(collision_walls(temp))
        {

        }
        else
        {
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
            else if(temp.y+1==ball.y && temp.x==ball.x)
            {
                movement_down();
            }
            else if(temp.y-1==ball.y && temp.x==ball.x)
            {
                movement_up();
            }
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
    bool game_win()
    {
        if(!show_brick())
        {
            system("cls");
            cout<<"Level 1 Complete ";
            return true;
        }
        else
        {
            return false;
        }
    }
    void play()
    {
        char n='n';
        show_bat();
        show_ball();
        //show_brick();
        show_bounds();
        movement();
        start_time=GetTickCount();
        check_time=start_time+250;
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
        system("cls");
    }
};
int main()
{
    game startgame;
    while(!startgame.game_over() && !startgame.game_win())
    {
        startgame.play();
    }
    /*system("cls");
    cout<<"GAME OVER ";*/
    return 0;
}
/* things to do:-
*/
