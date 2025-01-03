#include "game.h"

Game::Game(int fps) : frame(fps) {}

Game::~Game()
{
    console.printMiddle(endText);
    frame = {1};
    frame.limit();
    frame.limit();
    frame.limit();
    frame.limit();
}

void Game::Start()
{
    console.printMiddle("Use end to quit and home to clear the grid");
    Frame intro{1};
    intro.limit();
    intro.limit();
    intro.limit();
    intro.limit();
    grid.ClearGrid();

    while (!gameOver)
    {
        frame.limit();
        userInput = input.Read();
        if (userInput == UserInput::Quit)
        {
            console.printMiddle("Quitting...");
            break;
        };
        Update();
        render.Draw(grid.GetTiles());
    }
}

void Game::End(const string&& _endText)
{
    gameOver = true;
    endText = _endText;
}