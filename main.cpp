#include<bits/stdc++.h>
#include<conio.h>
#include<windows.h>
#include<time.h>
using namespace std;

//game variables
bool gameover,grow;
const int width=40;
const int height=20;
int x,y,fx,fy,score;
enum eDirection {STOP=0, LEFT, RIGHT, UP, DOWN};
eDirection snakeDir;
deque<pair<int,int>> snakeBody;
set<long long> snakeSet;

//menu variables
bool quitgame;
bool showsettings;
int selectedOption;
vector<int> toggleVariable;

void hideCursor() 
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false; // hide cursor
    SetConsoleCursorInfo(out, &cursorInfo);
}

long long encode(int x, int y) 
{
    return ((long long)x << 32) | (unsigned int)y;
}
void setCursorPosition(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void spawnFruit()
{
    int minw=2;
    int maxw=width-2;
    int minh=2;
    int maxh=height-2;
    do{
        fx=(rand() % (maxw - minw + 1)) + minw;
        fy=(rand() % (maxh - minh + 1)) + minh;
    }while(snakeSet.find(encode(fx, fy)) != snakeSet.end());
}
void setup()
{
    gameover=0;
    snakeDir=STOP;
    x=width/2;
    y=height/2;
    spawnFruit();
    snakeBody.clear();
    snakeSet.clear();
    snakeBody.push_back({x,y});
    snakeSet.insert(encode(x,y));
    snakeBody.push_back({x+1,y});
    snakeSet.insert(encode(x+1,y));
}

void draw()
{
    setCursorPosition(0,0);
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
                switch(snakeDir)
                {
                    case UP:
                        cout<<"▲";
                        break;
                    case DOWN:
                        cout<<"▼";
                        break;
                    case LEFT:
                        cout<<"◄";
                        break;
                    case RIGHT:
                        cout<<"►";
                        break;
                    default:
                        cout<<"O";
                        break;
                }
                // cout<<"■";
            }
            else if(snakeSet.find(encode(j,i))!=snakeSet.end())
            {
                cout<<"■";
            }
            else if(i==fy && j==fx)
            {
                cout<<"⬤";
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
    cout<<"Press 'x' to exit game to main menu\n";
}

void input()
{
    if(_kbhit())
    {
        switch(_getch())
        {
            case 'a': 
                if(snakeDir != RIGHT) snakeDir = LEFT; 
                break;
            case 'w': 
                if(snakeDir != DOWN) snakeDir = UP; 
                break;
            case 'd': 
                if(snakeDir != LEFT) snakeDir = RIGHT; 
                break;
            case 's': 
                if(snakeDir != UP) snakeDir = DOWN; 
                break;
            case 'x': 
                gameover = true; 
                break;
        }
    }
}
void moveSnakeBody()
{
    if(!toggleVariable[1] && snakeSet.find(encode(x,y))!=snakeSet.end())
    {
        gameover=1;
    }
    snakeBody.push_front({x,y});
    snakeSet.insert(encode(x,y));
    if(!grow)
    {
        pair<int,int> tail = snakeBody.back();
        snakeBody.pop_back();
        snakeSet.erase(encode(tail.first,tail.second));
    }
}

void logic()
{
    switch(snakeDir)
    {
        case LEFT:
            x--;
            moveSnakeBody();
            break;
        case UP:
            y--;
            moveSnakeBody();
            break;
        case RIGHT:
            x++;
            moveSnakeBody();
            break;
        case DOWN:
            y++;
            moveSnakeBody();
            break;
        default:
            break;
    }
    if(x > width || x<0 || y>height || y<0)
    {
        if(toggleVariable[0])
        {
            if(x<0)
            {
                x=width;
            }
            if(x>width)
            {
                x=0;
            }
            if(y<0)
            {
                y=height;
            }
            if(y>height)
            {
                y=0;
            }
        }
        else
            gameover=1;
    }

    if(x==fx && y==fy)
    {
        score++;
        spawnFruit();
        grow=1;
    }
    else{
        grow=0;
    }
}

void startPlaying()
{
    setup();
    while(!gameover)
    {
        draw();
        input();
        logic();
        int speed = 20*(6-toggleVariable[2]);
        // if(score % 5 == 0 && speed > 30) speed -= 8; // faster every 5 points
        Sleep(speed);
    }
    system("cls");
}

void setupMenu(){
    quitgame=0;
    selectedOption=0;
}

void drawMenu() 
{
    setCursorPosition(0,0);

    cout << "\n\n";
    cout << "  ╔══════════════════════════════════════╗  \n";
    cout << "  ║                                      ║  \n";
    cout << "  ║          S N A K E  G A M E          ║  \n";
    cout << "  ║                                      ║  \n";
    cout << "  ╚══════════════════════════════════════╝  \n\n";

    string options[3] = {"Start Game", "Game Settings", "Quit Game"};

    for (int i = 0; i < 3; i++) 
    {
        if (i == selectedOption) 
        {
            cout << "\t  ► " << options[i] << "\n";   // highlighted option
        } 
        else 
        {
            cout << "\t    " << options[i] << "\n";
        }
    }
}

void drawSettings()
{
    setCursorPosition(0,0);

    cout << "\n\n";
    cout << "  ╔══════════════════════════════════════╗  \n";
    cout << "  ║            O P T I O N S             ║  \n";
    cout << "  ╚══════════════════════════════════════╝  \n\n";

    vector<string> options = {"Loop Walls: ", "Self COllision: ","Speed(0-5): ","Reset to Default", "Back to Main Menu"};

    for (int i = 0; i < options.size()-2; i++) 
    {
        if (i == selectedOption)
        {
            cout << "\t  ► " << options[i] << toggleVariable[i]<< "\n";   // highlighted option
        } 
        else 
        {
            cout << "\t    " << options[i] << toggleVariable[i]<< "\n";
        }
    }
    for (int i = options.size()-2; i < options.size(); i++) 
    {
        if (i == selectedOption)
        {
            cout << "\t  ► " << options[i] << "\n";   // highlighted option
        } 
        else 
        {
            cout << "\t    " << options[i] << "\n";
        }
    }

}

void settingsInput()
{
    if(_kbhit())
    {
        switch(_getch())
        {
            case 'w': 
                selectedOption--;
                if(selectedOption<0)
                {
                    selectedOption=2;
                }
                break;
            case 's': 
                selectedOption++;
                if(selectedOption>4)
                {
                    selectedOption=0;
                }
                break;
            case 13: 
                if(selectedOption==0)
                {
                    toggleVariable[0]=1-toggleVariable[0];
                }
                else if(selectedOption==1)
                {
                    toggleVariable[1]=1-toggleVariable[1];
                }
                else if(selectedOption==2)
                {
                    toggleVariable[2]++;
                    if(toggleVariable[2]>5)
                    {
                        toggleVariable[2]=1;
                    }
                }
                else if(selectedOption==3)
                {
                    toggleVariable={0,0,1};
                }
                else if (selectedOption==4)
                {
                    showsettings=0;
                    selectedOption=0;
                }
                break;
        }
    }
}

void settings()
{
    system("cls");
    showsettings=1;
    while(showsettings)
    {
        drawSettings();
        settingsInput();
    }
    system("cls");
}

void menuInput()
{
    if(_kbhit())
    {
        switch(_getch())
        {
            case 'w': 
                selectedOption--;
                if(selectedOption<0)
                {
                    selectedOption=2;
                }
                break;
            case 's': 
                selectedOption++;
                if(selectedOption>2)
                {
                    selectedOption=0;
                }
                break;
            case 13: 
                if(selectedOption==0)
                {
                    startPlaying();
                }
                else if(selectedOption==1)
                {
                    settings();
                }
                else if(selectedOption==2)
                {
                    quitgame=1;
                }
                break;
        }
    }
}
void menu()
{
    system("cls");
    toggleVariable={0,0,1}; //infinite walls, selfcrossing, speed
    while(!quitgame)
    {
        drawMenu();
        menuInput();
    }
    system("cls");
}
int main()
{
    srand(time(NULL));
    SetConsoleOutputCP(CP_UTF8);
    hideCursor();
    menu();
}