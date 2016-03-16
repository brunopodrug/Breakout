#pragma once

class paddle
{
	public:
		paddle();
		~paddle();
		float GetPositionX();
		float GetPositionY();
		void ResetPosition();
		void MoveLeft();
		void MoveRight();
		float SetNewX(float);
		float SetNewY(float);
	
	private:
		float x;
		float y;	
};