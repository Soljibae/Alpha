#include <crtdbg.h> // To check for memory leaks
#include "AEEngine.h"
#include "gamemanager.hpp"

int APIENTRY wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    //_crtBreakAlloc = 392;

    AESysInit(hInstance, nCmdShow, 1600, 900, 1, 60, true, NULL);

    AESysSetWindowTitle("Pong");
    
    GameState gameState;

    gameState.Running_game();

    AESysExit();

}
