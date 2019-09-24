#include "Game.h"
#include "Title.h"
#include "End.h"
using namespace std;
namespace Game 
{	
//public variables/functions
	int screenWidth = 1000;
	int screenHeight = 600;	
	int currentScreen = 0;	
	void Play(void);
	Color p2Color;
	Color p1Color;
	bool winner = false;
//gameplay variables
	static bool gameover = false;
	static bool isPaused;
	static bool ventanaOn = false;
	static int lastTouch = 0;
	static bool pupSpawn = false;
//ball variables
	static int ballradius = 7;
	static Vector2 ballspeed = {0,0};
	static Vector2 ballposition;	
	static Color ballcolor;	
//player variables
	static Rectangle rec1;
	static Rectangle rec2;
	static Vector2 playerSize = { 15,100 };
	static float playerspeed = 420.0f;
	static Vector2 player1Position;
	static Vector2 player2Position;
	static int player1Score;
	static int player2Score;
	static int sizepup1 = 0;
	static int sizepup2 = 0;
	static int speedpup1 = 0;
	static int speedPUP2 = 0;
//power-up variables
	static Rectangle PUP;
	static Vector2 pupSize = {30,30};
	static Vector2 pupPosition;
	static bool pupType;
//gameplay functions
	static void GameUpdate(Vector2&, Vector2&, Vector2&, Vector2&, Color&, int&, int&);
	static void Init();
	static void GameDraw(void);
	static void IsGameOver();


	static void GameUpdate(Vector2&, Vector2&, Vector2&, Vector2&, Color&, int&, int&)
	{
		if (!isPaused)
		{
			if (ballspeed.x > 0) ballcolor = p1Color;
			if (ballspeed.x < 0) ballcolor = p2Color;
			ballposition = { ballposition.x + (ballspeed.x * GetFrameTime()), ballposition.y + (ballspeed.y * GetFrameTime()) };

			if (IsKeyDown(KEY_UP) && Game::player1Position.y > 0) player1Position.y -= (playerspeed+speedpup1) * GetFrameTime();
			if (IsKeyDown(KEY_DOWN) && player1Position.y < screenHeight - (playerSize.y + sizepup1)) player1Position.y += (playerspeed+speedpup1) * GetFrameTime();
			if (IsKeyDown(KEY_W) && player2Position.y > 0) player2Position.y -= (playerspeed+speedPUP2) * GetFrameTime();
			if (IsKeyDown(KEY_S) && player2Position.y < screenHeight - (playerSize.y + sizepup2)) player2Position.y += (playerspeed + speedPUP2) * GetFrameTime();

			if ((ballposition.y - ballradius) < 0 || (ballposition.y + ballradius) > (screenHeight - ballradius))
			{
				ballspeed.y = -ballspeed.y;
			}

			if (!pupSpawn)
			{
				pupPosition.x = GetRandomValue(200, screenWidth - 200 );
				pupPosition.y = GetRandomValue(100, screenHeight - 100);
				pupType = GetRandomValue(0, 1);
				PUP.height = pupSize.y;
				PUP.width = pupSize.x;
				PUP.x = pupPosition.x;
				PUP.y = pupPosition.y;
				pupSpawn = true;
			}

			if (ballposition.x - ballradius < 0)
			{
				player2Score++;
				ballposition = { (float)screenWidth / 2, (float)screenHeight / 2 };
				ballspeed.x = -ballspeed.x;
				ballspeed.y = 0;
				ballcolor = p1Color;
			}

			if (ballposition.x + ballradius > screenWidth)
			{
				player1Score++;
				ballposition = { (float)screenWidth / 2, (float)screenHeight / 2 };
				ballspeed.x = -ballspeed.x;
				ballspeed.y = 0;
				ballcolor = p2Color;
			}

			if (IsKeyPressed(KEY_ENTER))
					isPaused = true;

			rec1.width = playerSize.x;
			rec1.height = playerSize.y + sizepup1;
			rec1.x = player1Position.x;
			rec1.y = player1Position.y;
			rec2.width = playerSize.x;
			rec2.height = playerSize.y + sizepup2;
			rec2.x = player2Position.x;
			rec2.y = player2Position.y;

			if (CheckCollisionCircleRec(ballposition, ballradius, rec1))
			{
				ballspeed.x = -ballspeed.x;
				ballspeed.y = GetRandomValue(-500, 500);
				ballcolor = p2Color;
				lastTouch = 1;
			}

			if (CheckCollisionCircleRec(ballposition, ballradius, rec2))
			{
				ballspeed.x = -ballspeed.x;
				ballspeed.y = ballspeed.y + GetRandomValue(-500, 500);
				ballcolor = p1Color;
				lastTouch = 2;
			}

			if (CheckCollisionCircleRec(ballposition, ballradius, PUP))
			{
				if (lastTouch == 1)
				{
					if (pupType == 0)
					{
						sizepup1 += 10;
					}
					if (pupType == 1)
					{
						speedpup1 += 40;
					}
				}
				if (lastTouch == 2)
				{
					if (pupType == 0)
					{
						sizepup2 += 10;
					}
					if (pupType == 1)
					{
						speedPUP2 += 40;
					}
				}
				pupSpawn = false;
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
			ballcolor = p1Color;
		}

		else
		{
			ballspeed = {-800 , 0 };
			ballcolor = p2Color;
		}
		ballposition = {(float)screenWidth/2, (float)screenHeight/2};
		if (!ventanaOn)
		{
			InitWindow(screenWidth, screenHeight, "Pong v1.0");
			ventanaOn = true;
		}
		player1Position = { (float)screenWidth - (playerSize.x * 3), (float)screenHeight - (playerSize.y + screenHeight / 3) };
		player2Position = { (playerSize.x * 2), (playerSize.y + screenHeight / 3) };
		player1Score = 0;
		player2Score = 0;
	}
	static void GameDraw()
	{
		BeginDrawing();
		ClearBackground(LIGHTGRAY);
			if (!isPaused)
			{
				DrawCircleV(ballposition, ballradius, ballcolor);
				DrawRectangle(player1Position.x, player1Position.y, playerSize.x, playerSize.y + sizepup1, p2Color);
				DrawRectangle(player2Position.x, player2Position.y, playerSize.x, playerSize.y + sizepup2, p1Color);
				if (pupSpawn) 
				{
					if (pupType)
						DrawRectangleV(pupPosition, pupSize, GREEN);
					else
						DrawRectangleV(pupPosition, pupSize, MAGENTA);
				}
				DrawText(FormatText("%i", player1Score), 15, 15, 20, p1Color);
				DrawText(FormatText("%i", player2Score), (screenWidth - 30), 15, 20, p2Color);
			}
			else
			{
				DrawText("PAUSE: PRESS ENTER TO RESUME", (screenWidth / 2) - 200, screenHeight / 2, 30, BLACK);
			}
		EndDrawing();
		
	}
	void IsGameOver()
	{
		if (player2Score >= 10 || player1Score >= 10)
		{
			currentScreen++;
			if (player2Score >= 10)
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
				GameUpdate(player1Position, player2Position, ballspeed, ballposition, ballcolor, player1Score, player2Score);
				GameDraw();
				break;
			case 2:
				End::EndUpdate();
				End::EndDraw();
				Init();
				break;
			}
			if(gameover == true)
				CloseWindow();
		}
		CloseWindow();	
	}
}