#include<bits/stdc++.h>
#include<conio.h>
#include <windows.h>
using namespace std;

COORD coord={0,0};
DWORD start_time, check_time;

struct point                                                            //structure of point
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
    static const int bound_X=16;                //bounds of game
    static const int bound_Y=16;                //static because due to inheritance diamond problem will occur
    void show_bounds()
    {
        for(int i=0;i<=bound_X;i++)
        {
            gotoxy(i,bound_Y,'~');              //print lower bound
        }
        for(int i=0;i<bound_X;i++)
        {
            gotoxy(bound_X,i,'|');              //print side bound
        }
    }
    bool bound_check_X(int x)                  //check horizontal bound
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
    deque<point>b;              //deque for bat of point type
    dx_bat()
    {
        y=15;                    //vertical coordinate for bat just above vertical bound
        bat_len=5;              //bat length
    }
    void batpoint(int x)
    {
        p.x=x;                  //x here is coordinate for left most part of bat
        p.y=y;                  //y is fixed
        b.push_back(p);         //this point is pushed in deque
    }
    void batlen()
    {
        for(int i=1;i<bat_len;i++)  //runs bat_len-1 times as the left most point is already present in deque
        {
            p=b.front();            //p gets value of front which is left most point of bat
            batpoint(p.x+i);        //function to insert bat_len-1 points in deque
        }
    }
    void bat_move_left()                //move bat left
    {
        p=b.front();
        p.x=p.x-1;
        if(bound_check_X(p.x))          //checking horizontal bounds
        {
            b.push_front(p);            //push next left point
            b.pop_back();               //pop last right point
        }
    }
    void bat_move_right()
    {
        p=b.back();
        p.x=p.x+1;
        if(bound_check_X(p.x))          //checking horizontal bounds
        {
            b.pop_front();              //pop last left point
            b.push_back(p);             //push next right point
        }
    }
    void show_bat()                     //function to display bat
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
    {           // Initializing bricks
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
    /*show brick is used in too ways:-
      1.If brick is present in then brick is printed using gotoxy function and function return true
      2.If no brick is present the function returns false
    */
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
    void delete_brick(int x,int y)              //used to delete a brick
    {
        bricks[x][y]=0;
    }
    int brick_hit(int x,int y,int a,int b)          //to check brick hit conditions
    {  // x and y are balls current coordinates and a b are ball previous coordinates
        if(y==0)                                     //ball going
        {
            if(bricks[x+1][y+1]==1000 && a+1==x)                    //brick right bottom
            {
                return (11);
            }
            else if(bricks[x-1][y+1]==1000 && a-1==x)
            {
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
                return (13);
            }
            else if(bricks[x+1][y+1]==1000)
            {
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
                return (15);
            }
            else if(bricks[x-1][y+1]==1000)
            {
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
                    return (1);
                }
                else if(bricks[x+1][y]==1000 && x==a+1)
                {
                    return (2);
                }
                else
                {
                    return (3);
                }
            }
            else if(bricks[x-1][y-1]==1000 && x==a-1)
            {
                return (4);
            }
            else if(bricks[x+1][y-1]==1000 && x==a+1)
            {
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
                    return (6);
                }
                else if(bricks[x-1][y]==1000 && x==a-1)
                {
                    return (7);
                }
                else
                {
                    return (8);
                }
            }
            else if(bricks[x+1][y+1]==1000 && x==a+1)
            {
                return (9);
            }
            else if(bricks[x-1][y+1]==1000 && x==a-1)
            {
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
    dx_ball()
    {
        ball.x=8;                   //initial coordinates for ball
        ball.y=14;
        movement_left_up();         //initial direction for ball
    }
    void show_ball()                //displays the ball
    {
        gotoxy(ball.x,ball.y,'0');
    }
    bool collision_walls(point temp)
    {
        if(ball.x==0 )                          //left bound check
        {
            if(ball.y==0)                       //corner check
            {
                corner_left_up();
            }
            else if(temp.y+1==ball.y)           //if ball was going down
            {
                movement_right_down();
            }
            else if(temp.y-1==ball.y)           //if ball was going up
            {
                movement_right_up();
            }
            return true;
        }
        else if(ball.x+1==bound_X)              //right bound check
        {
            if(ball.y==0)                       //corner check
            {
                corner_right_up();
            }
            else if(temp.y+1==ball.y)           //if ball was going down
            {
                movement_left_down();
            }
            else if(temp.y-1==ball.y)           //if ball was going up
            {
                movement_left_up();
            }
            return true;
        }
        else if(ball.y==0)                      //upper bound check
        {
            if(temp.x+1==ball.x)                //ball going right
            {
                movement_right_down();
            }
            else if(temp.x-1==ball.x)           //ball going left
            {
                movement_left_down();
            }
            else if(temp.x==ball.x)            //ball going straight down
            {
                movement_down();
            }
            return true;
        }
        else
        {
            return false;                       //if no wall collision occurred
        }

    }
    bool game_over()                //game over condition
    {
        if(ball.y+1==bound_Y)
        {
            system("cls");
            cout<<"GAME OVER ";
            return true;
        }
        else                        //return false if condition not true
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
        if(flag==1)         //The ball will surly hit the bat
        {
            if(i==0 || i ==1)           //left part of bat
            {
                if(ball.x==0)           //check corner condition
                {
                    corner_left_down();
                }
                else
                {
                    movement_left_up();
                }
            }
            else if(i==2)           //middle part of bat
            {
                movement_up();
            }
            else                    //right part of bat
            {
               if(ball.x==bound_X-1)    //check corner condition
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
        else        //return false if ball do not hit bat
        {
            return false;
        }
    }
    bool collision_brick(int hit)
    {
       if(hit)
       {                //if brick is hit
            switch(hit)
            {
                case 1:
                    delete_brick(ball.x,ball.y-1);
                    delete_brick(ball.x-1,ball.y);
                    movement_right_down();//left up 2 check
                    break;
                case 2:
                    delete_brick(ball.x,ball.y-1);
                    delete_brick(ball.x+1,ball.y);
                    movement_left_down();
                    break;
                case 3:
                    delete_brick(ball.x,ball.y-1);
                    if(temp.x+1==ball.x)
                    {
                        movement_right_down();//up move right down check
                    }
                    else if(temp.x-1==ball.x)
                    {
                        movement_left_down();
                    }
                    else
                    {
                        movement_down();//check
                    }
                    break;
                case 4:
                    delete_brick(ball.x-1,ball.y-1);
                    movement_right_down();//left up 1 check
                    break;
                case 5:
                    delete_brick(ball.x+1,ball.y-1);
                    movement_left_down();//right up 1 check
                    break;
                case 6:
                    delete_brick(ball.x,ball.y+1);
                    delete_brick(ball.x+1,ball.y);
                    movement_left_up();//right down 2 check
                    break;
                case 7:
                    delete_brick(ball.x,ball.y+1);
                    delete_brick(ball.x-1,ball.y);
                    movement_right_up();//left down 2 check
                    break;
                case 8:
                    delete_brick(ball.x,ball.y+1);
                    if(temp.x+1==ball.x)
                    {
                        movement_right_up();//down move right up check
                    }
                    else if(temp.x-1==ball.x)
                    {
                        movement_left_up();// down move left up check
                    }
                    else
                    {
                        movement_up();
                    }
                    break;
                case 9:
                    delete_brick(ball.x+1,ball.y+1);
                    movement_left_up();//right down 1 check
                    break;
                case 10:
                    delete_brick(ball.x-1,ball.y+1);
                    movement_right_up();//left down 1 check
                    break;
                case 11:
                    delete_brick(ball.x+1,ball.y+1);
                    movement_left_down();//wall right down 1 check
                    break;
                case 12:
                    delete_brick(ball.x-1,ball.y+1);
                    movement_right_down();// wall left down 1 check
                    break;
                case 13:
                    delete_brick(ball.x+1,ball.y-1);
                    movement_right_down();
                    break;
                case 14:
                    delete_brick(ball.x+1,ball.y+1);
                    movement_right_up();
                    break;
                case 15:
                    delete_brick(ball.x-1,ball.y-1);
                    movement_left_down();
                    break;
                case 16:
                    delete_brick(ball.x-1,ball.y+1);
                    movement_left_up();
                    break;
            }
        }
        else
            return false;
    }
    void movement_left_up()
    {
        if(bricks[ball.x-1][ball.y-1]==1000)            //if brick already exists on left up position
        {//then temp is set in such a way that the ball was moved from previous brick location which was deleted
            temp.x=ball.x+1;
            temp.y=ball.y+1;
        }
        else
        {
            temp.x=ball.x;
            temp.y=ball.y;
            ball.x=ball.x-1;
            ball.y=ball.y-1;
        }
    }
    void movement_right_up()
    {
        if(bricks[ball.x+1][ball.y-1]==1000)            //if brick already exists on right up position
        {
            temp.x=ball.x-1;
            temp.y=ball.y+1;
        }
        else
        {
            temp.x=ball.x;
            temp.y=ball.y;
            ball.x=ball.x+1;
            ball.y=ball.y-1;
        }
    }
    void movement_left_down()
    {
        if(bricks[ball.x-1][ball.y+1]==1000)        //if brick already exists on left down position
        {
            temp.x=ball.x+1;
            temp.y=ball.y-1;
        }
        else
        {
            temp.x=ball.x;
            temp.y=ball.y;
            ball.x=ball.x-1;
            ball.y=ball.y+1;
        }
    }
    void movement_right_down()
    {
        if(bricks[ball.x+1][ball.y+1]==1000)            //if brick already exists on right down position
        {
            temp.x=ball.x-1;
            temp.y=ball.y-1;
        }
        else
        {
            temp.x=ball.x;
            temp.y=ball.y;
            ball.x=ball.x+1;
            ball.y=ball.y+1;
        }
    }
    void corner_right_down()                    //moving ball from left up corner position
    {
        temp.x=ball.x;
        temp.y=ball.y;
        ball.x=ball.x-1;
        ball.y=ball.y-1;
    }
    void corner_left_down()                    //moving ball from right up corner position
    {
        temp.x=ball.x;
        temp.y=ball.y;
        ball.x=ball.x+1;
        ball.y=ball.y-1;
    }
    void corner_left_up()                       //moving ball from right down corner position
    {
        temp.x=ball.x;
        temp.y=ball.y;
        ball.x=ball.x+1;
        ball.y=ball.y+1;
    }
    void corner_right_up()                      //moving ball from left down corner position
    {
        temp.x=ball.x;
        temp.y=ball.y;
        ball.x=ball.x-1;
        ball.y=ball.y+1;
    }
    void movement_up()                          //moving ball up
    {
        temp.x=ball.x;
        temp.y=ball.y;
        ball.y=ball.y-1;
        ball.x=ball.x;
    }
    void movement_down()                        //moving ball down
    {
        temp.x=ball.x;
        temp.y=ball.y;
        ball.y=ball.y+1;
        ball.x=ball.x;
    }
    void movement()
    {                                                                   //temp is previous position of ball
        int hit=brick_hit(ball.x,ball.y,temp.x,temp.y);                 //function to find weather the ball will hit any brick or not
        if(hit)                                                         //if ball hits the brick
        {
            collision_brick(hit);                                       //then collision_brick() function is called which deletes the
                                                                        //particular brick
        }
        else if(collision_bat(temp))                                    //if ball hits bat
        {

        }
        else if(collision_walls(temp))                                 //if ball hits the wall
        {

        }
        else                                                            //if no such cases the movement of ball is unchanged
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
        dx_bat bat;             //object for dx_bat class
        dx_ball b;              //object for dx_ball class
        batpoint(5);            //function to push the left most point of the bat which is 5 in distance horizontally
        batlen();               //function to create bat
    }
    bool game_win()
    {
        if(!show_brick())           //if show_brick() returns false i.e. no brick is left then function returns true
        {                           //show_brick() also prints the bricks
            system("cls");
            cout<<"Level 1 Complete ";
            return true;
        }
        else                        //else return false
        {
            return false;
        }
    }
    void play()
    {
        char n='n';
        show_bat();             //to display bat
        show_ball();            //to display ball
        show_bounds();          //to display bounds
        movement();             //function decides the movement of ball
        start_time=GetTickCount();  //time function to get input from user if any
        check_time=start_time+250; //time limit of input
        while(check_time>GetTickCount())                        //input within time period
        {
            if (kbhit())                //if input then get input in n
            {
				n=getch();
				break;
            }
        }
        switch (n)                                      //movement according key pressed
        {
            case 'a':
                bat_move_left();                        //bat move left
                break;
            case 'd':
                bat_move_right();                       //bat move right
                break;
            case 'n':                                   //n for no movement used in debugging
                break;
        }
        system("cls");                                  //clears the screen
    }
};
int main()
{
    game startgame;                                         //object for class game
    while(!startgame.game_over() && !startgame.game_win())  //check game over and game win condition until then run play function
    {
        startgame.play();                                   //call play function
    }
    return 0;
}

