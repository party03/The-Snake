#include<bits/stdc++.h>
#include<conio.h>
#include<windows.h>
using namespace std;

bool gameover;
const int width=20;
const int height=20;
int x,y,fx,fy,score;
enum eDirection {STOP=0, LEFT, RIGHT, UP, DOWN};
eDirection snakeDir;
void setup()
{
    gameover=0;
    snakeDir=STOP;
    x=width/2;
    y=height/2;

    fx=rand()%width;
    fy=rand()%height;
}

void draw()
{
    system("cls");
    for(int i=0; i<width; i++)
    {
        cout<<"#";
    }
    cout<<"\n";

    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
            if(j==0 || j==width-1)
            {
                cout<<"#";
            }   
            else if(i==y && j==x)
            {
                cout<<"O";
            }
            else if(i==fy && j==fx)
            {
                cout<<"F";
            }
            else{
                cout<<" ";
            }
        }
        cout<<"\n";
    }

    for(int i=0; i<width; i++)
    {
        cout<<"#";
    }
}

void input()
{
    if(_kbhit())
    {
        switch(_getch())
        {
            case 'a':
                snakeDir=LEFT;
                break;
            case 'w':
                snakeDir=UP;
                break;
            case 'd':
                snakeDir=RIGHT;
                break;
            case 's':
                snakeDir=DOWN;
                break;
            case 'x':
                gameover=true;
                break;
        }
    }
}

void logic()
{
    switch(snakeDir)
    {
        case LEFT:
            x--;
            break;
        case UP:
            y--;
            break;
        case RIGHT:
            x++;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;
    }
    if(x > width || x<0 || y>height || y<0)
    {
        gameover=1;
    }
}

int main()
{
    setup();
    while(!gameover)
    {
        draw();
        input();
        logic();
        Sleep(100);
    }
}