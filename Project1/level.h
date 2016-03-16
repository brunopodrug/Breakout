#pragma once
#include "pch.h"
#include <string>

#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>

class level
{
	private:
		ALLEGRO_BITMAP * BackgroundTexture;
		
		int RowCount, ColumnCount, RowSpacing, ColumnSpacing;
		int inprenetble;
		
	public:
		level(const char *);
		level();
		~level();

		ALLEGRO_BITMAP * GetBackgroundTexture();
		
		int GetInpenetrables();
};

