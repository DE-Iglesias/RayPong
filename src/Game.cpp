#include "Game.h"
#include "Title.h"
#include "End.h"
namespace Game 
{
	bool gameover = false;
	float playerspeed = 420.0f;
	int screenWidth = 1000;
	int screenHeight = 600;	
	int currentScreen = 0;
	int ballradius = 7;
	Vector2 PUPSize = {30,30};
	Vector2 PUPPosition;
	bool PUPType;
	bool PUPSpawn = false;
	Vector2 PlayerSize = { 15,100 };	
	Vector2 ballspeed = {0,0};
	Vector2 ballposition;	
	Vector2 Player1Position;
	Vector2 Player2Position;
	int Player1Score;
	int Player2Score;
	void Play(void);
	Color ballcolor;
	static void GameUpdate(Vector2&, Vector2&, Vector2&, Vector2&, Color&, int&, int&);
	static void Init();
	static void GameDraw(void);
	static void IsGameOver();
	Color P1Color;
	Color P2Color;
	bool isPaused;
	bool winner = false;
	Rectangle rec1;
	Rectangle rec2;
	Rectangle PUP;
	bool ventanaOn = false;
	static void GameUpdate(Vector2&, Vector2&, Vector2&, Vector2&, Color&, int&, int&)
	{
		if (!isPaused)
		{
			if (ballspeed.x > 0) ballcolor = P2Color;
			if (ballspeed.x < 0) ballcolor = P1Color;
			if (IsKeyDown(KEY_UP) && Game::Player1Position.y > 0) Player1Position.y -= playerspeed * GetFrameTime();
			if (IsKeyDown(KEY_DOWN) && Player1Position.y < screenHeight - PlayerSize.y) Player1Position.y += playerspeed * GetFrameTime();
			if (IsKeyDown(KEY_W) && Player2Position.y > 0) Player2Position.y -= playerspeed * GetFrameTime();
			if (IsKeyDown(KEY_S) && Player2Position.y < screenHeight - PlayerSize.y) Player2Position.y += playerspeed * GetFrameTime();
			ballposition = { ballposition.x + (ballspeed.x * GetFrameTime()), ballposition.y + (ballspeed.y * GetFrameTime()) };
			if ((ballposition.y - ballradius) < 0 || (ballposition.y + ballradius) > (screenHeight - ballradius))
			{
				ballspeed.y = -ballspeed.y;
			}
			if (!PUPSpawn)
			{
				PUPPosition.x = GetRandomValue(200, screenWidth - 200 );
				PUPPosition.y = GetRandomValue(100, screenHeight - 100);
				PUPType = GetRandomValue(0, 1);
				PUP.height = PUPSize.y;
				PUP.width = PUPSize.x;
				PUP.x = PUPPosition.x;
				PUP.y = PUPPosition.y;
				PUPSpawn = true;
			}
			if (ballposition.x - ballradius < 0)
			{
				Player2Score++;
				ballposition = { (float)screenWidth / 2, (float)screenHeight / 2 };
				ballspeed.x = -ballspeed.x;
				ballspeed.y = 0;
				ballcolor = P2Color;
			}
			if (ballposition.x + ballradius > screenWidth)
			{
				Player1Score++;
				ballposition = { (float)screenWidth / 2, (float)screenHeight / 2 };
				ballspeed.x = -ballspeed.x;
				ballspeed.y = 0;
				ballcolor = P1Color;
			}
			if (IsKeyPressed(KEY_ENTER))
					isPaused = true;
			rec1.width = PlayerSize.x;
			rec1.height = PlayerSize.y;
			rec1.x = Player1Position.x;
			rec1.y = Player1Position.y;
			rec2.width = PlayerSize.x;
			rec2.height = PlayerSize.y;
			rec2.x = Player2Position.x;
			rec2.y = Player2Position.y;
			if (CheckCollisionCircleRec(ballposition, ballradius, rec1))
			{
				ballspeed.x = -ballspeed.x;
				ballspeed.y = GetRandomValue(-500, 500);
				ballcolor = P1Color;
			}
			if (CheckCollisionCircleRec(ballposition, ballradius, rec2))
			{
				ballspeed.x = -ballspeed.x;
				ballspeed.y = ballspeed.y + GetRandomValue(-500, 500);
				ballcolor = P2Color;
			}
			if (CheckCollisionCircleRec(ballposition, ballradius, PUP))
			{
				PUPSpawn = false;
			}
			IsGameOver();
		}
		else
		{
			if (IsKeyPressed(KEY_ENTER))
			isPaused = false;
		}
	}

	static void Init()
	{
		
		isPaused = false;
		int randValue = GetRandomValue(0, 1);
		if (randValue == 0)
		{
			ballspeed = { 800 , 0 };
			ballcolor = P2Color;
		}
		else
		{
			ballspeed = {-800 , 0 };
			ballcolor = P1Color;
		}
		ballposition = {(float)screenWidth/2, (float)screenHeight/2};
		if (!ventanaOn)
		{
			InitWindow(screenWidth, screenHeight, "Pong v1.0");
			ventanaOn = true;
		}
		Player1Position = { (float)screenWidth - (PlayerSize.x * 3), (float)screenHeight - (PlayerSize.y + screenHeight / 3) };
		Player2Position = { (PlayerSize.x * 2), (PlayerSize.y + screenHeight / 3) };
		int Player1Score = 0;
		int Player2Score = 0;
	}
	static void GameDraw()
	{
		BeginDrawing();
		ClearBackground(LIGHTGRAY);
			if (!isPaused)
			{
				DrawCircleV(ballposition, ballradius, ballcolor);
				DrawRectangleV(Player1Position, PlayerSize, P1Color);
				DrawRectangleV(Player2Position, PlayerSize, P2Color);
				if (PUPSpawn) 
				{
					if (PUPType)
						DrawRectangleV(PUPPosition, PUPSize, GREEN);
					else
						DrawRectangleV(PUPPosition, PUPSize, BLUE);
				}
				DrawText(FormatText("%i", Player1Score), 15, 15, 20, P2Color);
				DrawText(FormatText("%i", Player2Score), (screenWidth - 30), 15, 20, P1Color);
			}
			else
			{
				DrawText("PAUSE: PRESS ENTER TO RESUME", (screenWidth / 2) - 200, screenHeight / 2, 30, BLACK);
			}
		EndDrawing();
		
	}
	void IsGameOver()
	{
		if (Player2Score >= 10 || Player1Score >= 10)
		{
			currentScreen++;
			if (Player2Score >= 10)
			{
				winner = true;
			}
			else
			{
				winner = false;
			}
		}
	}
	void Play()
	{
		Init();

		while (!WindowShouldClose())
		{
			switch (currentScreen)
			{
			case 0:
				Title::TitleUpdate();
				Title::TitleDraw();
				break;
			case 1:
				GameUpdate(Player1Position, Player2Position, ballspeed, ballposition, ballcolor, Player1Score, Player2Score);
				GameDraw();
				break;
			case 2:
				End::EndUpdate();
				End::EndDraw();
				Init();
				Player1Score = 0;
				Player2Score = 0;
				break;
			}
			if(gameover == true)
				CloseWindow();
		}
		CloseWindow();	
	}
}