#include "lib/game.h"
#include "lib/input.h"
#include <curses.h>

class Cursor
{
public:
    Cursor(int _x, int _y) : x(_x), y(_y) 
    {
        tile = grid.GetTiles()[y][x];
        grid.SetTile(x, y, ascii1);
    }

    void Update()
    {
        // move
        int _x = x;
        int _y = y;
        bool moved = true;
        if (userInput == UserInput::Down && y < grid.GetHeight()-1)
            y += 1;
        else if (userInput == UserInput::Up && y > 0)
            y -= 1;
        else if (userInput == UserInput::Left && x > 0)
            x -= 1;
        else if (userInput == UserInput::Right && x < grid.GetWidth()-1)
            x += 1;
        else
            moved = false;

        if (moved)
        {
            grid.SetTile(_x, _y, tile); // draw old tile   
            tile = grid.GetTiles()[y][x];// store new tile
        }
        else 
        {
            // paint
            if (rawInput >= '!' && rawInput <= '~')
                tile = (char)rawInput;
            else if (rawInput == KEY_DC)
                tile = KEY_SPACE;
            else if (rawInput == KEY_HOME)
            {
                tile = KEY_SPACE;
                grid.ClearGrid();
            }
        }

        frameCount++;
        if (frameCount == flip)
        {
            currentAscii = ascii1 == currentAscii ? ascii2 : ascii1;
            frameCount = 0;
        }
        grid.SetTile(x, y, currentAscii);
    }

    char tile;
    int frameCount{0};
    int flip{15};
    char currentAscii = ascii1;
    static constexpr char ascii1 = '-'; 
    static constexpr char ascii2 = 'X'; 
    int x{};
    int y{};
};

class Artist : public Game
{
public:
    Artist(int fps) : Game(fps) {}

protected:
    void Update()
    {
        cursor.Update();
    }

private:
    Cursor cursor{0,0};
};

int main()
{
    constexpr int FPS{30};
    Artist artist{FPS};
    artist.Start();
    return 0;
}