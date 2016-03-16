#pragma once
#include "pch.h"
#include <string>

#include <allegro5\allegro.h>				// allegro header
#include <allegro5\allegro_acodec.h>		
#include <allegro5\allegro_audio.h>			
#include <allegro5\allegro_image.h>			
#include <allegro5\allegro_primitives.h>	


 // klasa za ucitavanje iz xml-a
class brick
{
public:
	ALLEGRO_BITMAP *Texture;
	ALLEGRO_SAMPLE *HitSound;
	ALLEGRO_SAMPLE *BreakSound;
	
	int HitPoints;
	int BreakScore;
	const char *Id;

	brick(const char*, ALLEGRO_BITMAP *, int, ALLEGRO_SAMPLE *, ALLEGRO_SAMPLE *, int);
};


// klasa za manipulaciju ucitanih tipova cigli
class bricks
{
private:
	int hp;
	int x;
	int y;
	int tip;

public:
	bricks(int,int,int,int);
	~bricks();
	
	void setHp();
	void DecrementHp();
	
	int getXPosition();
	int getYPosition();
	int getTip();
	int getHp();
};