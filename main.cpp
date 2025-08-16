#include<bits/stdc++.h>
#include<conio.h>
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

}

void logic(){

}

int main()
{
    setup();
    while(!gameover)
    {
        draw();
        input();
        logic();
        // sleep(10);
    }
}