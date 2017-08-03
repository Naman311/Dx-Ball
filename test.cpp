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

    gotoxy(0,3,'z');
    return 0;
}
