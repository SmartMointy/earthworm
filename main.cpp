#include <iostream>
#include "Game.h"
#include <Windows.h>

int __stdcall wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    // Init Game
    Game game;

    // Game Loop
    while (game.getWindowIsOpen())
    {
        // Update time
        game.updateDt();

        // Update
        game.update();

        // Render
        game.render();
    }

    // Application end
    return 0;
}