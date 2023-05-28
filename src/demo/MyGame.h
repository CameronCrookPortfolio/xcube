#ifndef __TEST_GAME_H__
#define __TEST_GAME_H__

#include "../engine/AbstractGame.h"
#include "../engine/AudioEngine.h"


struct GameKey {
	Point2 pos;
	bool isAlive;
};

class MyGame : public AbstractGame {
	private:
		Rect box;
		Rect box2; // new cube cc

		Rectangle2f SATbox1; //new SAT boxes/rects
		Rectangle2f satBox2;//player paddle rect

		Rectangle2f satBox3;
		Rectangle2f satBox4;
		Rectangle2f satBox5;
		Rectangle2f satBox6;
		Rectangle2f satBox7;
		Rectangle2f satBox8;
		Rectangle2f satBox9;
		

	

		Vector2i velocity;
		std::vector<std::shared_ptr<GameKey>> gameKeys;

		/* GAMEPLAY */
		int score, numKeys, lives;
		bool gameWon;

		void handleKeyEvents();
		void update();
		void render();
		void renderUI();
	public:
        MyGame();
		~MyGame();
		bool isColliding = false;
		Mix_Chunk* sound1;
		
};

#endif