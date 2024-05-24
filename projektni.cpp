#include <iostream>
#include <conio.h>
#include <windows.h>

#define WIDTH 20
#define HEIGHT 20
#define INVADER 'X'
#define PLAYER '^'
#define BULLET '|'

void draw(char grid[HEIGHT][WIDTH])
{
    system("CLS");
    for (int i = 0; i < HEIGHT; ++i)
    {
        for (int j = 0; j < WIDTH; ++j)
        {
            std::cout << grid[i][j];
        }
        std::cout << std::endl;
    }
}

int main()
{
    char grid[HEIGHT][WIDTH] = {};
    int playerPos = WIDTH / 2;
    int bulletPos = -1;

    // Initialize the grid
    for (int i = 0; i < HEIGHT; ++i)
    {
        for (int j = 0; j < WIDTH; ++j)
        {
            grid[i][j] = ' ';
        }
    }

    // Place the player
    grid[HEIGHT - 1][playerPos] = PLAYER;

    while (true)
    {
        // Move the bullet
        if (bulletPos != -1)
        {
            for (int i = 0; i < WIDTH; ++i)
            {
                if (grid[bulletPos][i] == BULLET)
                {
                    grid[bulletPos][i] = ' ';
                    if (bulletPos > 0)
                    {
                        grid[--bulletPos][i] = BULLET;
                    }
                    else
                    {
                        bulletPos = -1;
                    }
                }
            }
        }

        // Get the user's input
        if (_kbhit())
        {
            switch (_getch())
            {
            case 'a':
                if (playerPos > 0)
                {
                    grid[HEIGHT - 1][playerPos] = ' ';
                    grid[HEIGHT - 1][--playerPos] = PLAYER;
                }
                break;
            case 'd':
                if (playerPos < WIDTH - 1)
                {
                    grid[HEIGHT - 1][playerPos] = ' ';
                    grid[HEIGHT - 1][++playerPos] = PLAYER;
                }
                break;
            case ' ':
                if (bulletPos == -1)
                {
                    bulletPos = HEIGHT - 2;
                    grid[bulletPos][playerPos] = BULLET;
                }
                break;
            default:
                break;
            }
        }

        draw(grid);
        Sleep(100);
    }

    return 0;
}
