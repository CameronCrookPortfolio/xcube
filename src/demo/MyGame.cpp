#include "MyGame.h"
int ballVelocity = 3;
int ballVelocityX = 0;
bool playedMusic = false;
bool playedBGMusic = false;



MyGame::MyGame() : AbstractGame(), score(0), lives(3), numKeys(0), gameWon(false), satBox2(DEFAULT_WINDOW_WIDTH/2 -50, 500, 90, 25), box2(115, 235, 30, 30), SATbox1(DEFAULT_WINDOW_WIDTH/2,50,25,25), box(420,210,40,40), satBox3(180,40, 35, 35), satBox4(180, 80, 35, 35), satBox5(470,100, 35, 55), satBox6(400,-400, 45, 45), satBox7(380,80, 25,25), satBox8(380,80,30,30), satBox9(600, -400, 40,20){ //x,y,len,width
	TTF_Font * font = ResourceManager::loadFont("res/fonts/arial.ttf", 72);
	
	gfx->useFont(font);
	gfx->setVerticalSync(true);

    for (int i = 0; i < numKeys; i++) {
        std::shared_ptr<GameKey> k = std::make_shared<GameKey>();
        k->isAlive = true;
        k->pos = Point2(getRandom(0, 750), getRandom(0, 550));
        gameKeys.push_back(k);
    }
	//Mix_Chunk* sound1 = Mix_LoadWAV("res/audio/ding.wav");
	//sfx->playSound(sound1);
	
	
	
	
	
	
	
}

MyGame::~MyGame() {
	
	

}

void MyGame::handleKeyEvents() {
	int speed = 3;

	if (eventSystem->isPressed(Key::W)) {
		velocity.y = -speed;
	}

	if (eventSystem->isPressed(Key::S)) {
		velocity.y = speed;
	}

	if (eventSystem->isPressed(Key::A)) {
		velocity.x = -speed;
	}

	if (eventSystem->isPressed(Key::D)) {
		velocity.x = speed;
	}
}

void MyGame::update() {
	Mix_Chunk* dingSound = Mix_LoadWAV("res/audio/ding.wav");
	Mix_Chunk* winSound = Mix_LoadWAV("res/audio/win.wav");
	
	//FINAL DEMO
	Vector2f paddleCentre = mySystem->calculateCentreRect(satBox2);
	if (mySystem->checkAABB(satBox2, SATbox1)) 
	{
		
		sfx->playSound(dingSound);
		std::cout << "CAMERON_CROOK-CI517-2023";
		ballVelocity = -ballVelocity;
		if (paddleCentre.x < SATbox1.x) //to the left of other box
		{
			//ballVelocityX = 1;
			ballVelocityX += 2;
		}
		else {
			//ballVelocityX = -1;
			ballVelocityX -= 2;
		}
		
		
	}
	//'BALL'
	if (SATbox1.y < 0) { //bottom of screen
		SATbox1.y = 0;
		ballVelocity = -ballVelocity;
	}
	if (SATbox1.y > 575) {
		SATbox1.y = 575;
		ballVelocity = -ballVelocity;
	}
	if (SATbox1.x < 0 || SATbox1.x > DEFAULT_WINDOW_WIDTH - SATbox1.w) //gone off scren on x axis
	{ 
		ballVelocityX = -ballVelocityX;
	}
	
	//RED BOX/PADDLE CONTROLS FOR AABB
	satBox2.x += velocity.x;
	if (satBox2.x < 0) 
	{
		satBox2.x = 0;
	}
	if (satBox2.x > 710) 
	{
		satBox2.x = 710;
	}

	if (mySystem->SATcheckCollisionRotated(SATbox1, satBox3, 0, 50))
	{
		sfx->playSound(dingSound);
		std::cout << "collision";
		ballVelocity = -ballVelocity;
		ballVelocityX = -ballVelocityX;
		satBox3.x = 1000;
		score += 100;

	}
	if (mySystem->SATcheckCollisionRotated(SATbox1, satBox4, 0, 50))
	{
		sfx->playSound(dingSound);
		std::cout << "collision";
		ballVelocity = -ballVelocity;
		ballVelocityX = -ballVelocityX;
		satBox4.x = 1000;
		score += 100;
	}
	if (mySystem->SATcheckCollisionRotated(SATbox1, satBox5, 0, 50))
	{
		sfx->playSound(dingSound);
		std::cout << "collision";
		ballVelocity = -ballVelocity;
		ballVelocityX = -ballVelocityX;
		satBox5.x = 1000;
		score += 100;
	}
	if (mySystem->SATcheckCollisionRotated(SATbox1, satBox6, 0, 60))
	{
		sfx->playSound(dingSound);
		std::cout << "collision";
		ballVelocity = -ballVelocity;
		ballVelocityX = -ballVelocityX;
		satBox6.x = 1000;
		score += 100;
	}
	if (mySystem->SATcheckCollisionRotated(SATbox1, satBox7, 0, 50))
	{
		sfx->playSound(dingSound);
		std::cout << "collision";
		ballVelocity = -ballVelocity;
		ballVelocityX = -ballVelocityX;
		satBox7.x = 1000;
		score += 100;
	}
	if (mySystem->SATcheckCollisionRotated(SATbox1, satBox8, 0, 350))
	{
		sfx->playSound(dingSound);
		std::cout << "collision";
		ballVelocity = -ballVelocity;
		ballVelocityX = -ballVelocityX;
		satBox8.x = 1000;
		score += 100;
	}
	if (mySystem->SATcheckCollisionRotated(SATbox1, satBox9, 0, 60))
	{
		sfx->playSound(dingSound);
		std::cout << "collision";
		ballVelocity = -ballVelocity;
		ballVelocityX = -ballVelocityX;
		satBox9.x = 1000;
		score += 100;
	}
	

	//SAT BOX CONTROLS
	//SATbox1.x += velocity.x;
	//SATbox1.y += velocity.y;
	SATbox1.y += ballVelocity;
	SATbox1.x += ballVelocityX;

	//575



	for (auto key : gameKeys) {
		if (key->isAlive && box2.contains(key->pos)) { //only NPC box collides with circle. uses CONTAINS function 
			score += 200;
			key->isAlive = false;
			numKeys--;
		}
	}

	velocity.x = 0;
    velocity.y = 0;

	if (score >= 700 && playedMusic == false) {
		ballVelocity = 0;
		ballVelocityX = 0;
		sfx->playSound(winSound);
		playedMusic = true;
		gameWon = true;
	}
	
}

void MyGame::render() {

	//REGULAR RECTANGLES
	//gfx->setDrawColor(SDL_COLOR_RED);
	//gfx->drawRect(box);
	////drawing second box to collide with
	//gfx->setDrawColor(SDL_COLOR_BLUE);
	//gfx->drawRect(box2);
	//gfx->setDrawColor(SDL_COLOR_YELLOW);
	//gfx->drawRectf(SATbox1); //draw rect f works with floats
	//gfx->setDrawColor(SDL_COLOR_PURPLE);
	//gfx->drawRectf(satBox2); //draw rect f works with floats


	////ROTATED RECT
	////___________________________
	//Vector2f centre2 = mySystem->calculateCentreRect(satBox2); //based on x,y,w,h. Will change if rect moves
	//Vector2f rotatedCentre2 = mySystem->calculateCentreRotatedRect(centre2, satBox2.w, satBox2.h, 50);
	//std::vector<Vector2f> box2Verts = mySystem->calculateVerticiesRotatedRect(rotatedCentre2, satBox2.w, satBox2.h, 50);
	//Vector2f bx2TL = box2Verts[0];
	//Vector2f bx2BL = box2Verts[1];
	//Vector2f bx2BR = box2Verts[2];
	//Vector2f bx2TR = box2Verts[3];

	//gfx->setDrawColor(SDL_COLOR_RED);
	//gfx->drawLinef({ bx2TL.x, bx2TL.y }, { bx2TR.x, bx2TR.y }); //TL to TR
	//gfx->drawLinef({ bx2TR.x, bx2TR.y }, { bx2BR.x, bx2BR.y }); //TR to BR
	//gfx->drawLinef({ bx2BR.x, bx2BR.y }, { bx2BL.x, bx2BL.y }); //BR to BL
	//gfx->drawLinef({ bx2BL.x, bx2BL.y }, { bx2TL.x, bx2TL.y }); //BL to TL
	////_____________________________________________


	//FULL GAME DEMO
	//PADDLE
	gfx->setDrawColor(SDL_COLOR_RED);
	gfx->drawRectf(satBox2); //satBox2 = player controlled paddle
	//'BALL'
	gfx->setDrawColor(SDL_COLOR_YELLOW);
	gfx->drawRectf(SATbox1);

	//ROTATED RECTS
	//1
	gfx->setDrawColor(SDL_COLOR_PINK);
	//gfx->drawRectf(satBox3);
	Vector2f centre = mySystem->calculateCentreRect(satBox3); //based on x,y,w,h. Will change if rect moves
	Vector2f rotatedCentre2 = mySystem->calculateCentreRotatedRect(centre, satBox3.w, satBox3.h, 50);
	std::vector<Vector2f> verts = mySystem->calculateVerticiesRotatedRect(rotatedCentre2, satBox3.w, satBox3.h, 50);
	Vector2f TL = verts[0];
	Vector2f BL = verts[1];
	Vector2f BR = verts[2];
	Vector2f TR = verts[3];
	gfx->drawLinef({ TL.x, TL.y }, { TR.x, TR.y }); //TL to TR
	gfx->drawLinef({ TR.x, TR.y }, { BR.x, BR.y }); //TR to BR
	gfx->drawLinef({ BR.x, BR.y }, { BL.x, BL.y }); //BR to BL
	gfx->drawLinef({ BL.x, BL.y }, { TL.x, TL.y }); //BL to TL
	//2
	gfx->setDrawColor(SDL_COLOR_ORANGE);
	Vector2f centre2 = mySystem->calculateCentreRect(satBox4); //based on x,y,w,h. Will change if rect moves
	Vector2f rotatedCentre3 = mySystem->calculateCentreRotatedRect(centre2, satBox4.w, satBox4.h, 50);
	std::vector<Vector2f> verts2 = mySystem->calculateVerticiesRotatedRect(rotatedCentre3, satBox4.w, satBox4.h, 50);
	Vector2f TL2 = verts2[0];
	Vector2f BL2 = verts2[1];
	Vector2f BR2 = verts2[2];
	Vector2f TR2 = verts2[3];
	gfx->drawLinef({ TL2.x, TL2.y }, { TR2.x, TR2.y }); //TL to TR
	gfx->drawLinef({ TR2.x, TR2.y }, { BR2.x, BR2.y }); //TR to BR
	gfx->drawLinef({ BR2.x, BR2.y }, { BL2.x, BL2.y }); //BR to BL
	gfx->drawLinef({ BL2.x, BL2.y }, { TL2.x, TL2.y }); //BL to TL
	//3
	gfx->setDrawColor(SDL_COLOR_GREEN);
	Vector2f centre3 = mySystem->calculateCentreRect(satBox5); //based on x,y,w,h. Will change if rect moves
	Vector2f rotatedCentre4 = mySystem->calculateCentreRotatedRect(centre3, satBox5.w, satBox5.h, 50);
	std::vector<Vector2f> verts3 = mySystem->calculateVerticiesRotatedRect(rotatedCentre4, satBox5.w, satBox5.h, 50);
	Vector2f TL3 = verts3[0];
	Vector2f BL3 = verts3[1];
	Vector2f BR3 = verts3[2];
	Vector2f TR3 = verts3[3];
	gfx->drawLinef({ TL3.x, TL3.y }, { TR3.x, TR3.y }); //TL to TR
	gfx->drawLinef({ TR3.x, TR3.y }, { BR3.x, BR3.y }); //TR to BR
	gfx->drawLinef({ BR3.x, BR3.y }, { BL3.x, BL3.y }); //BR to BL
	gfx->drawLinef({ BL3.x, BL3.y }, { TL3.x, TL3.y }); //BL to TL
	//4
	gfx->setDrawColor(SDL_COLOR_PURPLE);
	gfx->drawRectf(satBox6);
	Vector2f centre4 = mySystem->calculateCentreRect(satBox6); //based on x,y,w,h. Will change if rect moves
	Vector2f rotatedCentre5 = mySystem->calculateCentreRotatedRect(centre4, satBox6.w, satBox6.h, 60);
	std::vector<Vector2f> verts4 = mySystem->calculateVerticiesRotatedRect(rotatedCentre5, satBox6.w, satBox6.h, 60);
	Vector2f TL4 = verts4[0];
	Vector2f BL4 = verts4[1];
	Vector2f BR4 = verts4[2];
	Vector2f TR4 = verts4[3];
	gfx->drawLinef({ TL4.x, TL4.y }, { TR4.x, TR4.y }); //TL to TR
	gfx->drawLinef({ TR4.x, TR4.y }, { BR4.x, BR4.y }); //TR to BR
	gfx->drawLinef({ BR4.x, BR4.y }, { BL4.x, BL4.y }); //BR to BL
	gfx->drawLinef({ BL4.x, BL4.y }, { TL4.x, TL4.y }); //BL to TL
	//5
	gfx->setDrawColor(SDL_COLOR_BLUE);
	Vector2f centre5 = mySystem->calculateCentreRect(satBox7); //based on x,y,w,h. Will change if rect moves
	Vector2f rotatedCentre6 = mySystem->calculateCentreRotatedRect(centre5, satBox7.w, satBox7.h, 50);
	std::vector<Vector2f> verts5 = mySystem->calculateVerticiesRotatedRect(rotatedCentre6, satBox7.w, satBox7.h, 50);
	Vector2f TL5 = verts5[0];
	Vector2f BL5 = verts5[1];
	Vector2f BR5 = verts5[2];
	Vector2f TR5 = verts5[3];
	gfx->drawLinef({ TL5.x, TL5.y }, { TR5.x, TR5.y }); //TL to TR
	gfx->drawLinef({ TR5.x, TR5.y }, { BR5.x, BR5.y }); //TR to BR
	gfx->drawLinef({ BR5.x, BR5.y }, { BL5.x, BL5.y }); //BR to BL
	gfx->drawLinef({ BL5.x, BL5.y }, { TL5.x, TL5.y }); //BL to TL
	//6
	gfx->setDrawColor(SDL_COLOR_AQUA);
	Vector2f centre6 = mySystem->calculateCentreRect(satBox8); //based on x,y,w,h. Will change if rect moves
	Vector2f rotatedCentre7 = mySystem->calculateCentreRotatedRect(centre6, satBox8.w, satBox8.h, 350);
	std::vector<Vector2f> verts6 = mySystem->calculateVerticiesRotatedRect(rotatedCentre7, satBox8.w, satBox8.h, 350);
	Vector2f TL6 = verts6[0];
	Vector2f BL6 = verts6[1];
	Vector2f BR6 = verts6[2];
	Vector2f TR6 = verts6[3];
	gfx->drawLinef({ TL6.x, TL6.y }, { TR6.x, TR6.y }); //TL to TR
	gfx->drawLinef({ TR6.x, TR6.y }, { BR6.x, BR6.y }); //TR to BR
	gfx->drawLinef({ BR6.x, BR6.y }, { BL6.x, BL6.y }); //BR to BL
	gfx->drawLinef({ BL6.x, BL6.y }, { TL6.x, TL6.y }); //BL to TL
	//7
	gfx->setDrawColor(SDL_COLOR_WHITE);
	Vector2f centre7 = mySystem->calculateCentreRect(satBox9); //based on x,y,w,h. Will change if rect moves
	Vector2f rotatedCentre8 = mySystem->calculateCentreRotatedRect(centre7, satBox9.w, satBox9.h, 60);
	std::vector<Vector2f> verts7 = mySystem->calculateVerticiesRotatedRect(rotatedCentre8, satBox9.w, satBox9.h, 60);
	Vector2f TL7 = verts7[0];
	Vector2f BL7 = verts7[1];
	Vector2f BR7 = verts7[2];
	Vector2f TR7 = verts7[3];
	gfx->drawLinef({ TL7.x, TL7.y }, { TR7.x, TR7.y }); //TL to TR
	gfx->drawLinef({ TR7.x, TR7.y }, { BR7.x, BR7.y }); //TR to BR
	gfx->drawLinef({ BR7.x, BR7.y }, { BL7.x, BL7.y }); //BR to BL
	gfx->drawLinef({ BL7.x, BL7.y }, { TL7.x, TL7.y }); //BL to TL






	


	gfx->setDrawColor(SDL_COLOR_YELLOW);
	for (auto key : gameKeys)
        if (key->isAlive)
		    gfx->drawCircle(key->pos, 5);
}

void MyGame::renderUI() {
	gfx->setDrawColor(SDL_COLOR_AQUA);
	std::string scoreStr = std::to_string(score);
	gfx->drawText(scoreStr, 780 - scoreStr.length() * 50, 25);

	if (gameWon)
		gfx->drawText("YOU WON", 250, 500);
}