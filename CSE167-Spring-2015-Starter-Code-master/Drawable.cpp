#include "Drawable.h"
#include "Window.h"
#include "Vector3.h"

Drawable::Drawable()
{
    this->toWorld.identity();
}

Drawable::~Drawable()
{
    //
}

void Drawable::draw(DrawData& data)
{
    std::cout << "Warning: draw() is not implemented" << std::endl;
}

void Drawable::myDraw(DrawData& data)
{
	std::cout << "Warning: draw() is not implemented" << std::endl;
}

void Drawable::myDrawPt(DrawData& data)
{
	std::cout << "Warning: draw() is not implemented" << std::endl;
}

void Drawable::update(UpdateData& data)
{
    std::cout << "Warning: update() is not implemented" << std::endl;
}

void Drawable::left(float space)
{
	Matrix4 moveLeft;
	moveLeft.makeTranslate(-space, 0, 0);

	toWorld = moveLeft * toWorld;
}

void Drawable::right(float space)
{
	Matrix4 moveRight;
	moveRight.makeTranslate(space, 0, 0);

	toWorld = moveRight * toWorld;
}

void Drawable::up(float space)
{
	Matrix4 moveUp;
	moveUp.makeTranslate(0, space, 0);

	toWorld = moveUp * toWorld;
}

void Drawable::down(float space)
{
	Matrix4 moveDown;
	moveDown.makeTranslate(0, -space, 0);

	toWorld = moveDown * toWorld;
}

void Drawable::into(float space)
{
	Matrix4 moveInto;
	moveInto.makeTranslate(0, 0, -space);

	toWorld = moveInto * toWorld;
}

void Drawable::out(float space)
{
	Matrix4 moveOut;
	moveOut.makeTranslate(0, 0, space);

	toWorld = moveOut * toWorld;
}

void Drawable::reset()
{

	toWorld.identity();
}

void Drawable::rotateZ(float degree)
{
	float radians = degree / 180.0 * 3.1415926;
	Matrix4 rotation;
	rotation.makeRotateZ(radians);

	toWorld = rotation * toWorld;
}

void Drawable::reverseZ(float degree)
{
	float radians = degree / 180.0 * 3.1415926;
	Matrix4 rotation;
	rotation.makeRotateZ(-radians);

	toWorld = rotation * toWorld;
}


void Drawable::scale(float sx, float sy, float sz)
{
	Matrix4 size;
	size.makeScale(sx, sy, sz);

	toWorld = toWorld * size;
}

void Drawable::getPosition()
{
	Vector3 v;
	v.set(toWorld.get(3, 0), toWorld.get(3, 1), toWorld.get(3, 2));
	v.print("");

}