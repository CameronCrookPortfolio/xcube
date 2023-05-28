#ifndef __MY_ENGINE_H__
#define __MY_ENGINE_H__

#include "../EngineCommon.h"
#include "../GameMath.h"
#include "../GraphicsEngine.h"
#include "../AudioEngine.h"
#include <vector> //std::vector


class MyEngineSystem {
	friend class XCube2Engine;
	private:

	public:
		struct myStruct { int x; int y; int w; int h; };
		//struct myVector2f { float x; float y; };
		struct Verticies { Vector2f v1; Vector2f v2; Vector2f v3; Vector2f v4; };
		//struct rect1Verticies { Vector2f v1; Vector2f v2; Vector2f v3; Vector2f v4; };
		//struct rect2Verticies { Vector2f v1; Vector2f v2; Vector2f v3; Vector2f v4; };
		//struct Vector2f { float x; float y; };
		//struct Rectangle { Vector2f position; Vector2f size; }; using Rectangle 2 instead - found in game math
		void checkAABB(myStruct& obj1, myStruct& obj2, bool &isColliding); //return true or false depending on collision detection.
		bool checkAABB(Rectangle2f obj1, Rectangle2f& obj2); //return true or false depending on collision detection.
		float dotProduct(const Vector2f& v1, const Vector2f& v2);
		float magnitude(const Vector2f& v);
		Vector2f normalize(const Vector2f& v);
		bool overlap(float min1, float max1, float min2, float max2);
		bool SATcheckCollisionAxisAligned(const Rectangle2f& rect1, const Rectangle2f& rect2);
		Vector2f calculateCentreRect(const Rectangle2f& rect);
		Vector2f calculateCentreRect(const myStruct& rect);
		Vector2f calculateCentreRotatedRect(const Vector2f& centreXY, float width, float height, float rotation);
		std::vector<Vector2f> calculateVerticiesRotatedRect(const Vector2f& rotatedCentre, float width, float height, float rotation);
		bool SATcheckCollisionRotated(const Rectangle2f& rect1, const Rectangle2f& rect2, float rect1Rot, float rect2Rot);
		//std::vector<Vector2f> rect1verticiesdraw;

};

#endif