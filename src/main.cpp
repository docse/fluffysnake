#ifdef _WIN32
    #include <windows.h>

    void sleep(unsigned milliseconds)
    {
        Sleep(milliseconds);
    }

    void clear()
    {
        system("cls");
    }
#else
    #include <unistd.h>
    
    void sleep(unsigned milliseconds)
    {
        usleep(milliseconds * 1000); // takes microseconds
    }
    
    void clear()
    {
        system("clear");
    }
#endif
#include <iostream>
#include <conio.h>

bool run;
bool win;

const int width = 16*3;
const int height = 16;

int playerX, playerY;
int body_length;
char bodyX[50];
char bodyY[50];
enum EDirection {stop = 0, dup, ddown, dleft, dright};
EDirection direction; // 0 - not moving 1 - up 2 - down 3 - left 4 - right

int appleX, appleY;
int score;

using namespace std;
void Start()
{
    run = true;
    win = false;
    score = 0;
    body_length = 0;
    direction = stop;
    playerX = width/2;
    playerY = height/2;
    appleX = rand() % width;
    appleY = rand() % height;
}

void Render()
{
    clear();
    for(int top = 0; top < width+2; top++)
        cout << "#";
    cout << endl;

    for(int middleY = 0; middleY < height; middleY++)
    {
        for(int middleX = 0; middleX < width; middleX++)
        {
            if(middleX == 0)
                cout << "#";
            if(middleX == playerX && middleY == playerY)
                cout << "O";
            else if(middleX == appleX && middleY == appleY)
                cout << "A";
            else
            {
                bool added_o = false;
                for(int bl = 0; bl < body_length; bl++)
                {
                    if(bodyX[bl] == middleX && bodyY[bl] == middleY)
                    {
                        cout << "o";
                        added_o = true;
                    }
                } 
                if(!added_o)
                    cout << " ";
            }
            if(middleX == width-1)
                cout << "#";
        }
        cout << endl;
    }

    for(int bottom = 0; bottom < width+2; bottom++)
        cout << "#";
    cout << endl;
    cout << endl;
    cout << "Score: " << score;
}

void Input()
{
    if(_kbhit())
    {
        switch(_getch())
        {
            case 'w':
                direction = dup;
                break;
            case 'a':
                direction = dleft;
                break;
            case 's':
                direction = ddown;
                break;
            case 'd':
                direction = dright;
                break;
            case 'r':
                run = false;
                break;
        }
    }
}

void Logic()
{
    int prevX = bodyX[0];
    int prevY = bodyY[0];
    int prevX2, prevY2;
    bodyX[0] = playerX;
    bodyY[0] = playerY;
    for(int bl = 1; bl < body_length; bl++)
    {
        prevX2 = bodyX[bl];
        prevY2 = bodyY[bl];
        bodyX[bl] = prevX;
        bodyY[bl] = prevY;
        prevX = prevX2;
        prevY = prevY2;
    }
    if(direction == dup)
        playerY--;
    if(direction == dleft)
        playerX--;
    if(direction == ddown)
        playerY++;
    if(direction == dright)
        playerX++;
    if(score == 50)
    {
        run = false;
        win = true;
    }
    for(int bc = 0; bc < body_length; bc++)
    {
        cout << bodyX[bc];
    }
    // apple collision
    if(playerX == appleX && playerY == appleY)
    {
        appleX = rand() % width;
        appleY = rand() % height;
        score++;
        body_length++;
    }
    if(playerX >= width)
        playerX -= width;
    if(playerY >= height)
        playerY -= height;
    if(playerX <= -2)
        playerX += width;
    if(playerY <= -2)
        playerY += height;

}

int main()
{
    Start();
    while(run)
    {
        Render();
        Input();
        Logic();
        sleep(50);
    }
        clear();
    if(win)
        cout << "YOU WON!";
    else
        cout << "GAME OVER";

    return 0;
}
