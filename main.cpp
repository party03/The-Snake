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
int snakeLen;
vector<pair<int,int>> snakeBody;
map<pair<int,int>,bool> bodyMap;

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
    spawnFruit();

    snakeLen=1;
    for(int i=0; i<snakeLen; i++)
    {
        snakeBody.push_back({-1,-1});
    }
}

void draw()
{
    bodyMap.clear();
    for(int k=0; k<snakeLen; k++)
    {
        bodyMap.insert({snakeBody[k],1});
    }

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
            int bodyflag=0;
            if(j==0 || j==width)
            {
                cout<<"#";
            }   
            else if(i==y && j==x)
            {
                cout<<"O";
            }
            else if(bodyflag<snakeLen && bodyMap.find({j,i})!=bodyMap.end())
            {
                cout<<"o";
                bodyflag++;
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
void moveSnakeBody()
{
    for(int i=snakeLen-1; i>=1; i--)
    {
        snakeBody[i]=snakeBody[i-1];
    }
    snakeBody[0]={x,y};
}

void logic()
{
    switch(snakeDir)
    {
        case LEFT:
            moveSnakeBody();
            x--;
            break;
        case UP:
            moveSnakeBody();
            y--;
            break;
        case RIGHT:
            moveSnakeBody();
            x++;
            break;
        case DOWN:
            moveSnakeBody();
            y++;
            break;
        default:
            break;
    }
    if(x > width || x<0 || y>height || y<0)
    {
        gameover=1;
    }
    if(bodyMap.find({x,y})!=bodyMap.end())
    {
        gameover=1;
    }

    if(x==fx && y==fy)
    {
        score++;
        spawnFruit();
        snakeLen++;
        snakeBody.push_back(snakeBody[0]);
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