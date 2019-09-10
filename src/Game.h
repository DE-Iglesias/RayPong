#ifndef GAME_H
#define GAME_H
#include "raylib.h"
using namespace std;
namespace Game
{
		void Play();
		extern bool winner;
		extern bool gameover;
		extern float playerspeed;
		extern int screenWidth;
		extern int screenHeight;
		extern Vector2 PlayerSize;
		extern int Player1Score;
		extern int Player2Score;
		extern Vector2 Player1Position;
		extern Vector2 Player2Position;
		extern Vector2 ballposition;
		extern Vector2 ballspeed;
		extern int ballradius;
		extern int currentScreen;
		extern Color P1Color;
		extern Color P2Color;
};
#endif