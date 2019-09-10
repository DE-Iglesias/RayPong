#include "End.h"
#include "Game.h"
using namespace Game;
namespace End
{
	void EndUpdate() 
	{
		if (IsKeyDown(KEY_SPACE))

			currentScreen=0;
			
	}
	void EndDraw()
	{
		BeginDrawing();
		ClearBackground(LIGHTGRAY);
		if (!winner)
		{
			DrawText("Player 1 wins", screenWidth / 3, screenHeight / 4, 30, BLACK);
		}
		if (winner)
		{
			DrawText("Player 2 wins", screenWidth / 3, screenHeight / 4, 30, BLACK);
		}
		DrawText("PRESS SPACE TO GO BACK TO TITLE", screenWidth / 5, screenHeight / 2 + 40, 30, BLACK);
		DrawText("PRESS ESCAPE TO EXIT", screenWidth / 5, screenHeight / 2 + 80, 30, BLACK);
		EndDrawing();
	}
}