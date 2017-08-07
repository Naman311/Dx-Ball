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

int main()
{
    for(int i=0;i<5;i++)
        {
            for(int j=i;j<8;j++)
            {
                gotoxy(j,i,'x');
  //              gotoxy(j,i,'z');
            }
            for(int k=8;k<15-i;k++)
            {
                gotoxy(k,i,'x');
//gotoxy(k,i,'z');
            }
        }
    return 0;
}
