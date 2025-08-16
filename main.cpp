#include<bits/stdc++.h>
#include<conio.h>
#include<windows.h>
using namespace std;

bool gameover;
const int width=40;
const int height=20;
int x,y,fx,fy,score;
enum eDirection {STOP=0, LEFT, RIGHT, UP, DOWN};
eDirection snakeDir;


void spawnFruit()
{
    int minw=2;
    int maxw=width-2;
    int minh=2;
    int maxh=height-2;
    fx=(rand() % (maxw - minw + 1)) + minw;
    fy=(rand() % (maxh - minh + 1)) + minh;
}
void setup()
{
    gameover=0;
    snakeDir=STOP;
    x=width/2;
    y=height/2;

    // fx=1;
    // fy=1;
    spawnFruit();
}

void draw()
{
    system("cls");
    for(int i=0; i<width+1; i++)
    {
        cout<<"#";
    }
    cout<<"\n";

    for(int i=0; i<height; i++)
    {
        for(int j=0; j<=width; j++)
        {
            if(j==0 || j==width)
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

    for(int i=0; i<width+1; i++)
    {
        cout<<"#";
    }
    cout<<"\n";
    cout<<"Score: "<<score<<"\n";
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

    if(x==fx && y==fy)
    {
        score++;
        spawnFruit();
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