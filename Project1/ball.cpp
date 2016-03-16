#include "ball.h"

ball::ball()
{
	x = 400.0f;
	y = 682.0f;
	r = 5.0f;
	srand(time(NULL));
	Putanja((float)((rand() % 200) - 180), (float)((rand() % 100) - 200));
}

ball::~ball()
{}

void ball::Putanja(float koorX, float koorY)
{
	length = sqrt(koorX*koorX + koorY*koorY);
	dx = koorX / length;
	dy = koorY / length;
}

float ball::GetNewX()
{
	x = x + dx * SPEED;
	return x;
}

float ball::GetNewY()
{
	y = y + dy * SPEED;
	return y;
}

float ball::GetPositionX()
{
	return x;
}

float ball::GetPositionY()
{
	return y;
}

float ball::Getdx()
{
	return dx;
}

float ball::Getdy()
{
	return dy;
}

void ball::Setdx(float x)
{
	this->dx = x;
}

void ball::Setdy(float y)
{
	this->dy = y;
}

float ball::GetRadius()
{
	return r;
}

float ball::GetLength()
{
	return length;
}

void ball::Resetball()
{
	this->x = 400.0f;
	this->y = 682.0f;
	Putanja((float)((rand() % 200) - 180), (float)((rand() % 100) - 200));
}

void ball::SetDirection(float BallDirection)
{
	dx = cos(BallDirection);
	dy = -sin(BallDirection);
}
