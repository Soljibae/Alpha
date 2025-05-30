#include "AEEngine.h"
#include "utils.hpp"

Shape::Shape(float x, float y, float width, float height, float r, float g, float b, float a) :_x(x), _y(y), _width(width), _height(height), _r(r), _g(g), _b(b), _a(a) {}

Rect::Rect(float x, float y, float width, float height, float r, float g, float b, float a) : Shape(x, y, width, height, r, g, b, a), score(0) {}

Circle::Circle(float x, float y, float width, float height, float r, float g, float b, float a) : Shape(x, y, width, height, r, g, b, a), speed(600)
{
	AEVec2Zero(&moving_vector);
}

void Draw_Shape(float x, float y, float w, float h, float r, float g, float b, float a, AEGfxVertexList* pMesh, AEMtx33& transform)
{
	Rect shape(x, y, w, h, r, g, b, a);

	Draw_Shape(shape, pMesh, transform);
}

void  Draw_Shape(Shape& shape, AEGfxVertexList* pMesh, AEMtx33& transform)
{
	AEMtx33 scale;
	AEMtx33Scale(&scale, shape._width, shape._height);
	AEMtx33 tran;
	AEMtx33Trans(&tran, shape._x, shape._y);

	AEMtx33Concat(&transform, &tran, &scale);

	AEGfxSetColorToMultiply(0.f, 0.f, 0.f, 0.f);

	AEGfxSetColorToAdd(shape._r, shape._g, shape._b, shape._a);

	AEGfxSetTransform(transform.m);

	AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
}
