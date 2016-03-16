#include "bricks.h"

using namespace tinyxml2;
using namespace std;



brick::brick(const char* _Id, ALLEGRO_BITMAP * _Texture, int _HitPoints, ALLEGRO_SAMPLE * _HitSound, ALLEGRO_SAMPLE * _BreakSound, int _BreakScore) : Id(_Id),
Texture(_Texture), HitPoints(_HitPoints), HitSound(_HitSound), BreakSound(_BreakSound), BreakScore(_BreakScore)
{
	al_install_audio();
	al_init_acodec_addon();
	al_init_image_addon();
}

bricks::bricks(int _x, int _y, int _hp, int _tip) : hp(_hp), tip(_tip), x(_x), y(_y)
{}


void bricks::setHp()
{
	--hp;
}
int bricks::getXPosition()
{
	return x;
}
int bricks::getYPosition()
{
	return y;
}

int bricks::getTip()
{
	return tip;
}

int bricks::getHp()
{
	return hp;
}

void bricks::DecrementHp()
{
	--hp;
}

bricks::~bricks()
{}