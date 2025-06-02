#ifndef UTILS_HPP
#define UTILS_HPP

#include "AEEngine.h"

struct Shape
{
	float _x, _y;
	float _width, _height;
	float _r, _g, _b, _a;

	Shape(float x, float y, float width, float height, float r = 1.f, float g = 1.f, float b = 1.f, float a = 1.f);
};

struct Rect : public Shape
{
	int score;

	Rect(float x, float y, float width, float height, float r = 1.f, float g = 1.f, float b = 1.f, float a = 1.f);
};

struct Circle : public Shape
{
	AEVec2 moving_vector;
	float speed;

	Circle(float x, float y, float width, float height, float r = 1.f, float g = 1.f, float b = 1.f, float a = 1.f);
};

void Draw_Shape(float x, float y, float w, float h, float r, float g, float b, float a, AEGfxVertexList* pMesh, AEMtx33& transform, bool Is_Texture_Mode);

void Draw_Shape(Shape& shape, AEGfxVertexList* pMesh, AEMtx33& transform, bool Is_Texture_Mode);

bool Is_Mouse_In_Square(Rect& rect);
 
#endif