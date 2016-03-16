#include "paddle.h"

paddle::paddle()
{
	x = 380.0f;
	y = 688.0f;
}

paddle::~paddle()
{

}

float paddle::GetPositionX()
{
	return x;
}

float paddle::GetPositionY()
{
	return y;
}

void paddle::ResetPosition()
{
	x = 380.0f;
	y = 688.0f;
}

void paddle::MoveLeft()
{
	x = x - 1.0f;
}

void paddle::MoveRight()
{
	x = x + 1.0f;
}