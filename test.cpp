#include<bits/stdc++.h>
#include<conio.h>
#include <windows.h>

using namespace std;

COORD coord={0,0};

void gotoxy(int x,int y,char c)                                        //gotoxy Function definition.
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
    cout<<c;
}
    static const int bound_X=16;
    static const int bound_Y=16;

int main()
{
    int bricks[bound_X][bound_Y];
        for(int i=0;i<bound_Y/2;i++)
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
        for(int i=0;i<bound_Y;i++)
        {
            for(int j=0;j<bound_X;j++)
            {
                if(bricks[j][i]==1)
                {
                    gotoxy(j,i,'z');
                }
            }
        }
    return 0;
}
