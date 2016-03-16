#include "pch.h"
#include <string>


using namespace tinyxml2;
using namespace std;

std::vector<bricks> Cigle;
std::vector<brick> obliciCigli;


level::level()
{}

level::level(const char * filename)
{
	inprenetble = 0;
	XMLDocument doc;
	doc.LoadFile(filename);
	
	XMLElement* child = doc.FirstChildElement("Level");
	RowCount = std::stoi(child->ToElement()->Attribute("RowCount"));
	ColumnCount = std::stoi(child->ToElement()->Attribute("ColumnCount"));
	RowSpacing = std::stoi(child->ToElement()->Attribute("RowSpacing"));
	ColumnSpacing = std::stoi(child->ToElement()->Attribute("ColumnSpacing"));
	BackgroundTexture = al_load_bitmap(child->ToElement()->Attribute("BackgroundTexture"));

	XMLElement* bricks1 = child->FirstChildElement("Bricks");
	child = child->FirstChildElement("BrickTypes")->FirstChildElement("BrickType");
	do
	{
		obliciCigli.push_back(brick{ child->ToElement()->Attribute("Id"), al_load_bitmap(child->ToElement()->Attribute("Texture")), std::stoi(child->ToElement()->Attribute("HitPoints")), al_load_sample(child->ToElement()->Attribute("HitSound")), al_load_sample(child->ToElement()->Attribute("BreakSound")), std::stoi(child->ToElement()->Attribute("BreakScore")) });
		child = child->NextSiblingElement();
	} 
	while (child != NULL);

		std::string mapa = bricks1->GetText();
		const char* znakovi = mapa.c_str();

		//kreiranje cigli
		int brojac = 0;
		int x_position = 1;
		int y_position = 60;
		while (znakovi[brojac] != 'B')
		{
			if ((znakovi[brojac] != '\n') && (znakovi[brojac] != '\t') && (znakovi[brojac] != ' '))
			{
				if (*(obliciCigli[0].Id) == znakovi[brojac])
				{
					Cigle.push_back(bricks{ x_position, y_position, obliciCigli[0].HitPoints, 0 });
				}

				else if (*(obliciCigli[1].Id) == znakovi[brojac])
				{
					Cigle.push_back(bricks{ x_position, y_position, obliciCigli[1].HitPoints, 1 });
				}

				else if (*(obliciCigli[2].Id) == znakovi[brojac])
				{
					Cigle.push_back(bricks{ x_position, y_position, obliciCigli[2].HitPoints, 2 });
				}

				else if (*(obliciCigli[3].Id) == znakovi[brojac])
				{
					Cigle.push_back(bricks{ x_position, y_position, obliciCigli[3].HitPoints, 3 });
					
				}

				if (Cigle.back().getHp() > 5)
				{
					++inprenetble;
				}
					

				x_position += 42;
				if (!(Cigle.size() % ColumnCount) && Cigle.size()!=0)
				{
					x_position = 1;
					y_position += 12;
				}
				
			}
			brojac++;
		};
}

ALLEGRO_BITMAP * level::GetBackgroundTexture()
{
	return BackgroundTexture;
}

int level::GetInpenetrables()
{
	return inprenetble;
}

level::~level()
{
}