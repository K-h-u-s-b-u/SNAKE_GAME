#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>  // Include this for seeding the random number generator

using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitx, fruity, score; 
int tailx[100], taily[100];
int nTail;
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirecton dir;

void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    srand(time(0));  // Seed for random number generation
    fruitx = rand() % width;
    fruity = rand() % height;
    score = 0;
} 

void Draw()
{
    system("cls");  
    for (int i = 0; i < width + 2; i++)
        cout << "_";
    cout << endl;

    for (int i = 0; i < height; i++) 
    {
        for (int j = 0; j < width; j++) 
        {
            if (j == 0) 
                cout << "|";
            if (i == y && j == x)
                cout << "0";
            else if (i == fruity && j == fruitx)
                cout << "F";
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailx[k] == j && taily[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }

            if (j == width - 1)
                cout << "|";
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << "-";
    cout << endl;
    cout << "Score: " << score << endl;
}

void Input()
{
    if (_kbhit())
    {
        switch (getch())
        {
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;  // Corrected
                break;
            case 'w':
                dir = UP; 
                break;
            case 's':
                dir = DOWN;
                break;
            case 'x':
                gameOver = true;
                break;
        }
    }
}

void Logic()
{
    int prevx = tailx[0];
    int prevy = taily[0];
    int prev2X, prev2Y;
    tailx[0] = x;
    taily[0] = y;   
    for (int i = 1; i < nTail; i++) 
    {
        prev2X = tailx[i];
        prev2Y = taily[i];
        tailx[i] = prevx;
        taily[i] = prevy;
        prevx = prev2X;
        prevy = prev2Y;
    }
    switch (dir)    
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    if (x >= width) x = 0; 
    else if (x < 0) x = width - 1; 

    if (y >= height) y = 0; 
    else if (y < 0) y = height - 1;

    for (int i = 0; i < nTail; i++)
    {
        if (tailx[i] == x && taily[i] == y)
            gameOver = true;
    }

    if (x == fruitx && y == fruity) 
    {
        score += 10;
        fruitx = rand() % width;
        fruity = rand() % height;
        nTail++;
    }
} 

int main()
{
    Setup();
    cout << endl << "Press a for LEFT" << endl <<  "Press d for RIGHT" << endl << "Press s for DOWN" << endl << "Press w for UP" << endl;
    int n=50;
    cout <<  "Select mode: " << "EASY = 1000" << endl << "MEDIUM = 100" << endl << "HARD = 50" << endl;
    cin >> n;
    while (!gameOver)
    {
        Draw();
        Input(); 
        Logic(); // You missed calling the Logic function
        Sleep(n); // sleep time
    }
    
    return 0;
}
