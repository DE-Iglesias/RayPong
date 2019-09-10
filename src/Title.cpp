#include "Title.h"
#include "Game.h"
using namespace Game;
namespace Title
{
	int P1C = 1;
	int P2C = 1;
	void TitleUpdate();
	void TitleDraw();

	void TitleUpdate() 
	{
		if (IsKeyPressed(KEY_ENTER))
		{
			currentScreen++;
		}
		if (IsKeyPressed(KEY_A))
		{
			if (P1C > 1)
			{
				P1C--;
			}
			else
			{
				P1C = 3;
			}
		}
		if (IsKeyPressed(KEY_D))
		{
				P1C++;
			if(P1C > 3)
				P1C = 1;
		}
		if (IsKeyPressed(KEY_LEFT))
		{
			if (P2C > 1)
			{
				P2C--;
			}
			else
			{
				P2C = 3;
			}
		}
		if (IsKeyPressed(KEY_RIGHT))
		{
				P2C++;
				if (P2C > 3)
					P2C = 1;
		}
		switch (P1C)
		{
		case 1:
			P2Color = RED;
			break;
		case 2:
			P2Color = PINK;
			break;
		case 3:
			P2Color = ORANGE;
			break;
		}
		switch (P2C)
		{
		case 1:
			P1Color = BLUE;
			break;
		case 2:
			P1Color = SKYBLUE;
			break;
		case 3:
			P1Color = DARKPURPLE;
			break;
		}
	}
	void TitleDraw()
	{
		BeginDrawing();
		ClearBackground(LIGHTGRAY);
		DrawText("Press Enter to Play", (screenWidth / 2) - 200, screenHeight / 4, 40, BLACK);
		DrawText("Pick Player Colors using AD and <- ->", 150, screenHeight / 4 + 50, 40, BLACK);
		DrawText("Player 1", (screenWidth - 700), screenHeight / 2, 30, P2Color);
		DrawText("Player 2", (screenWidth - 400), screenHeight / 2, 30, P1Color);
		EndDrawing();
	}
}