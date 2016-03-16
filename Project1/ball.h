#pragma once

#include <math.h>
#include <time.h>
#include <random>
const float SPEED = 1.5f;

class ball
{
public:
	ball();
	~ball();
	void Putanja(float, float);
	float Getdx();
	float Getdy();
	void Setdx(float);
	void Setdy(float);
	float GetNewX();
	float GetNewY();
	float GetPositionX();
	float GetPositionY();
	float GetRadius();
	float GetLength();
	void SetDirection(float); //postavlja kut pod kojim ce se lopta kretati nakon sudara sa paddleom
	void Resetball();

private:
	float x;
	float y;
	float r;
	float dx;
	float dy;
	float length;
};