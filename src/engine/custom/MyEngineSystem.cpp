#include "MyEngineSystem.h"
#include <iostream>
#include <cmath> //sin, cos
#include <algorithm> //use for std::min_element and std::max_element







void MyEngineSystem::checkAABB(myStruct &obj1,myStruct &obj2, bool &isColliding) 
{
	if (obj1.x < obj2.x + obj2.w &&
		obj1.x + obj1.w > obj2.x &&
		obj1.y < obj2.y + obj2.h &&
		obj1.y + obj1.h > obj2.y)
	{
		isColliding = true;
		std::cout << "colliding.\n";
		
	}
	else {
		isColliding = false;
	}
	

	
}
bool MyEngineSystem::checkAABB(Rectangle2f obj1, Rectangle2f& obj2) //for two rectangles with float values
{
	if (obj1.x < obj2.x + obj2.w &&
		obj1.x + obj1.w > obj2.x &&
		obj1.y < obj2.y + obj2.h &&
		obj1.y + obj1.h > obj2.y)
	{
		return true;
		
	}
	else {
		return false;
	}
}
float MyEngineSystem::dotProduct(const Vector2f& v1, const Vector2f& v2) 
{
	return v1.x * v2.x + v1.y * v2.y;
	
}
float MyEngineSystem::magnitude(const Vector2f& v) 
{
	return std::sqrt(v.x * v.x + v.y * v.y); //pythag
}
Vector2f MyEngineSystem::normalize(const Vector2f& v) 
{
	const float mag = magnitude(v);
	if (mag != 0.0f) {
		return{ v.x / mag, v.y / mag };
	}
	
	return { 0.0f, 0.0f };
	
}
bool MyEngineSystem::overlap(float min1, float max1, float min2, float max2) 
{
	return min1 <= max2 && min2 <= max1;
}
bool MyEngineSystem::SATcheckCollisionAxisAligned(const Rectangle2f& rect1, const Rectangle2f& rect2)
{
	//calculate axes for each rect
	Vector2f axes[4];

	axes[0] = normalize({ rect1.w, 0.0f });
	axes[1] = normalize({ 0.0f, rect1.h });

	axes[2] = normalize({ rect2.w, 0.0f });
	axes[3] = normalize({ 0.0f, rect2.h });
	
	//project each rect onto axis and check overlap
	bool isOverlap = true;
	for (const auto& axis : axes) 
	{
		const float rect1Min = dotProduct({ rect1.x, rect1.y }, axis);
		const float rect1Max = dotProduct({ rect1.x + rect1.w, rect1.y + rect1.h }, axis);
		const float rect2Min = dotProduct({ rect2.x, rect2.y }, axis);
		const float rect2Max = dotProduct({ rect2.x + rect2.w, rect2.y + rect2.h}, axis);
		
		if (!overlap(rect1Min, rect1Max, rect2Min, rect2Max)) {
			isOverlap = false;
			break;
			//return false;
		}
		
	}
	
	//return true;

	if (isOverlap) {
		//std::cout << "Colliding!\n";
		return true;
	}
	else {
		//std::cout << "Not Colliding!\n";
		return false;
	}
}


Vector2f MyEngineSystem::calculateCentreRect(const Rectangle2f& rect) 
{
	//calculates centre of axis-aligned rectangle
	float center_x = rect.x + (rect.w / 2.0f);
	float center_y = rect.y + (rect.h / 2.0f);
	return { center_x, center_y }; 
}
Vector2f MyEngineSystem::calculateCentreRect(const myStruct& rect)
{
	//calculates centre of axis-aligned rectangle
	float center_x = rect.x + (rect.w / 2.0f);
	float center_y = rect.y + (rect.h / 2.0f);
	return { center_x, center_y };
}

Vector2f MyEngineSystem::calculateCentreRotatedRect(const Vector2f& centreXY, float width, float height, float rotation) 
{
	//radian conversion
	float radianRotation = rotation * (3.14159 / 180);
	
	
	float cosAngle = std::cos(radianRotation);
	float sinAngle = std::sin(radianRotation);

	float rotatedCentreX = centreXY.x * cosAngle - centreXY.y * sinAngle;
	float rotatedCentreY = centreXY.x * sinAngle + centreXY.y * cosAngle;

	return{ rotatedCentreX, rotatedCentreY };
}

std::vector<Vector2f> MyEngineSystem::calculateVerticiesRotatedRect(const Vector2f& rotatedCentre, float width, float height, float rotation)
{
	float halfWidth = width / 2.0f;
	float halfHeight = height / 2.0f;

	//convert to radians
	float radianRotation = rotation * (3.14159 / 180);

	float cosAngle = std::cos(radianRotation);
	float sinAngle = std::sin(radianRotation);

	Vector2f verticies[4]; //for a given rect.

	verticies[0] = { //top left
		rotatedCentre.x + halfWidth * cosAngle - halfHeight * sinAngle,
		rotatedCentre.y + halfWidth * sinAngle + halfHeight * cosAngle
	};
	verticies[1] = { //bottom left
		rotatedCentre.x - halfWidth * cosAngle - halfHeight * sinAngle,
		rotatedCentre.y - halfWidth * sinAngle + halfHeight * cosAngle
	};
	verticies[2] = { //bottom right
		rotatedCentre.x - halfWidth * cosAngle + halfHeight * sinAngle,
		rotatedCentre.y - halfWidth * sinAngle - halfHeight * cosAngle
	};
	verticies[3] = { //top right
		rotatedCentre.x + halfWidth * cosAngle + halfHeight * sinAngle,
		rotatedCentre.y + halfWidth * sinAngle - halfHeight * cosAngle
	};

	std::vector<Vector2f>vertexContainer;
	for (int i = 0; i < 4; i++) {
		vertexContainer.push_back(verticies[i]);
	}

	return vertexContainer;
}

//code to output the vertex container to the console to show coords of all verticies
	/*std::cout << "Vertex container: " << std::endl;
	for (int i = 0; i < vertexContainer.size(); i++) {
		std::cout << "Vertex: " << i << ": (" << vertexContainer[i].x << ", " << vertexContainer[i].y << ")" << std::endl;
	}*/

bool MyEngineSystem::SATcheckCollisionRotated(const Rectangle2f& rect1, const Rectangle2f& rect2, float rect1Rot, float rect2Rot)
{
	//assuming rect1's rotation is 0 degrees.
	//float rect1Rot = 0;
	//assuming rect2's rotation is 50 degrees.
	//float rect2Rot = 50;

	//assuming rotation around origin (0,0).


	//calculate the centers of the rects without rotation
	Vector2f rect1Centre = calculateCentreRect(rect1);
	Vector2f rect2Centre = calculateCentreRect(rect2);
	

	//calculate new centres based on rotation
	Vector2f rect1Rotcentre = calculateCentreRotatedRect(rect1Centre, rect1.w, rect1.h, rect1Rot);
	Vector2f rect2Rotcentre = calculateCentreRotatedRect(rect2Centre, rect2.w, rect2.h, rect2Rot);

	std::vector<Vector2f> rect1verticies = calculateVerticiesRotatedRect(rect1Rotcentre, rect1.w, rect1.h, rect1Rot); //vertex containers of verticies
	std::vector<Vector2f> rect2verticies = calculateVerticiesRotatedRect(rect2Rotcentre, rect2.w, rect2.h, rect2Rot); 

	Vector2f axes[8]; //8 axes for two rects
	//rect 1
	axes[0] = normalize({ rect1.w, 0.0f });
	axes[1] = normalize({ 0.0f, rect1.h });
	axes[2] = normalize({ -rect1.h, rect1.w });
	axes[3] = normalize({ rect1.h, -rect1.w });

	//rect 2
	axes[4] = normalize({ rect2.w, 0.0f });
	axes[5] = normalize({ 0.0f, rect2.h });
	axes[6] = normalize({ -rect2.h, rect2.w });
	axes[7] = normalize({ rect2.h, -rect2.w });

	for (const auto& axis : axes) 
	{
		std::vector<float>rect1Projections;
		std::vector<float>rect2Projections;

		//project rect1 vertices onto current axis
		for (int i = 0; i<4; i++) 
		{
			float projection = dotProduct(rect1verticies[i], axis);
			rect1Projections.push_back(projection);
		}
		for (int i = 0; i<4; i++) 
		{
			float projection = dotProduct(rect2verticies[i], axis);
			rect2Projections.push_back(projection);
		}
		float rect1Min = *std::min_element(rect1Projections.begin(), rect1Projections.end());
		float rect1Max = *std::max_element(rect1Projections.begin(), rect1Projections.end());
		float rect2Min = *std::min_element(rect2Projections.begin(), rect2Projections.end());
		float rect2Max = *std::max_element(rect2Projections.begin(), rect2Projections.end());

		if (rect1Max < rect2Min || rect2Max < rect1Min)
		{
			//no overlap found, rectangles separated
			return false;
		}

	}
	return true; 
}
