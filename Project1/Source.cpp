#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")  //pokrece program bez konzole

#include "pch.h"

using namespace tinyxml2;
using namespace std;

extern std::vector<bricks> Cigle;
extern std::vector<brick> obliciCigli;

void CollisionDetection();
void BrickBallCoollision();
void DeleteBrick(bricks);
void PaddleReset();

float leftedge;
float rightedge;
float topedge;
float bottomedge;

bool levelCompleted = false;

ALLEGRO_BITMAP *slika = NULL;

void setEstimatedBallEdges();

void paddleCollision(bool);

ALLEGRO_EVENT ev;
ALLEGRO_TIMEOUT timeout;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_FONT* font;

void SetLevelFiles();
std::vector<string> levelfiles;

ball lopta{};
paddle mainpaddle{};

float r = lopta.GetRadius();
int mx = 400;
int my = 250;

bool brickHited;

const float RIGHT_EDGE = 841.0f;

int life = 3;
std::string s_life;

unsigned long score = 0;
std::string countscore;

int level_number = 1;
std::string slevelnumber;

const float kutsektora1 = 0.461799f;
const float kutsektora2 = 0.087266f;

void level1Load();

int main()
{
	al_init();
	al_init_font_addon();
	al_init_primitives_addon();
	al_install_audio();
	al_init_acodec_addon();
	al_init_image_addon();
	al_reserve_samples(5);
	al_install_mouse();
	al_install_keyboard();

	ALLEGRO_DISPLAY* display = al_create_display(1000, 697);
	//al_hide_mouse_cursor(display);
	
	font = al_create_builtin_font();
	
	al_clear_to_color(al_map_rgb(0, 0, 0));

	event_queue = al_create_event_queue();
	if (!event_queue) {
		cout<<"failed to create event_queue!\n";
		al_destroy_display(display);
		return -1;
	}

	// load all xml files in vector
	SetLevelFiles();

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	
	al_draw_filled_rectangle(440, 275, 560, 330, al_map_rgb(205, 205, 255));
	al_draw_filled_rectangle(440, 375, 560, 430, al_map_rgb(205, 205, 255));
	al_draw_text(font, al_map_rgb(255, 255, 255), 500, 300, ALLEGRO_ALIGN_CENTER, "Nova igra!");
	al_draw_text(font, al_map_rgb(255, 255, 255), 500, 400, ALLEGRO_ALIGN_CENTER, "Izlaz!");
	al_flip_display();

	while (1)
	{
		al_wait_for_event(event_queue, &ev);
		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
		if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
			mx = ev.mouse.x;
			my = ev.mouse.y;
			if (mx > 440 && mx < 560 && my > 375 && my < 430)
				break;
			if (mx > 440 && mx < 560 && my > 275 && my < 330)
			{
				level1Load();
				break;
			}
		}
	}

	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	return 0;
}

void level1Load()
{
	
	double deltatime = 0.003;
	bool Xpressed = false;
	bool Ypressed = false;
	al_clear_to_color(al_map_rgb(0, 0, 0));

	// load level 1
	level nivo{};
	nivo = level(levelfiles[0].c_str());
	slika = nivo.GetBackgroundTexture();

	al_draw_bitmap_region(slika, 0.0f, 0.0f, RIGHT_EDGE, mainpaddle.GetPositionY() + 9, 0, 0, 0);

	// Postavljanje teksture na ucitane cigle
	for (auto cigla : Cigle)
	{
		al_draw_bitmap(obliciCigli[cigla.getTip()].Texture, (float)cigla.getXPosition(), (float)cigla.getYPosition(), 0);
	}

	al_draw_filled_rectangle(RIGHT_EDGE, 0, RIGHT_EDGE + 9.0f, 697, al_map_rgb(205, 205, 255)); // desni pading
	al_draw_filled_rectangle(mainpaddle.GetPositionX(), mainpaddle.GetPositionY(), mainpaddle.GetPositionX() + 80, mainpaddle.GetPositionY() + 9, al_map_rgb(205, 205, 255)); //prvo iscrtavanje paddle-a
	
	al_draw_text(font, al_map_rgb(255, 255, 255), 925, 100, ALLEGRO_ALIGN_CENTER, "Broj zivota:");
	s_life = std::to_string(life);
	al_draw_text(font, al_map_rgb(255, 255, 255), 925, 120, ALLEGRO_ALIGN_CENTER, s_life.c_str());


	al_draw_text(font, al_map_rgb(255, 255, 255), 925, 250, ALLEGRO_ALIGN_CENTER, "Score:");
	countscore = std::to_string(score);
	al_draw_text(font, al_map_rgb(255, 255, 255), 925, 270, ALLEGRO_ALIGN_CENTER, countscore.c_str());

	al_draw_text(font, al_map_rgb(255, 255, 255), 925, 400, ALLEGRO_ALIGN_CENTER, "Level:");
	slevelnumber = std::to_string(level_number);
	al_draw_text(font, al_map_rgb(255, 255, 255), 925, 420, ALLEGRO_ALIGN_CENTER, slevelnumber.c_str());

	al_flip_display();

	while (life)
	{
		al_init_timeout(&timeout, deltatime);

		bool get_event = al_wait_for_event_until(event_queue, &ev, &timeout);

		if (get_event && ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}

		if (ev.type == ALLEGRO_EVENT_KEY_DOWN || Xpressed || Ypressed)
		{
			if (ev.keyboard.keycode == ALLEGRO_KEY_LEFT)
			{
				Xpressed = true;
				if (mainpaddle.GetPositionX() > 0)
				{
					al_draw_filled_rectangle(mainpaddle.GetPositionX(), mainpaddle.GetPositionY(), mainpaddle.GetPositionX() + 80, mainpaddle.GetPositionY(), al_map_rgb(0, 0, 0));
					mainpaddle.MoveLeft();
					al_draw_filled_rectangle(mainpaddle.GetPositionX(), mainpaddle.GetPositionY(), mainpaddle.GetPositionX() + 80, mainpaddle.GetPositionY(), al_map_rgb(205, 205, 255));
				}
				
			}

			else if (ev.keyboard.keycode == ALLEGRO_KEY_RIGHT)
			{
				Ypressed = true;
				if (mainpaddle.GetPositionX() < 760)
				{
					al_draw_filled_rectangle(mainpaddle.GetPositionX(), mainpaddle.GetPositionY(), mainpaddle.GetPositionX() + 80, mainpaddle.GetPositionY(), al_map_rgb(0, 0, 0));
					mainpaddle.MoveRight();
					al_draw_filled_rectangle(mainpaddle.GetPositionX(), mainpaddle.GetPositionY(), mainpaddle.GetPositionX() + 80, mainpaddle.GetPositionY(), al_map_rgb(205, 205, 255));
				}
				
			}

		}

		if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			if (ev.keyboard.keycode == ALLEGRO_KEY_LEFT)
			{
				Xpressed = false;
			}

			else if (ev.keyboard.keycode == ALLEGRO_KEY_RIGHT)
			{
				Ypressed = false;
			}
		}

		if (Cigle.size() == nivo.GetInpenetrables())
		{
			slevelnumber = std::to_string(level_number);
			al_draw_text(font, al_map_rgb(0, 0, 0), 925, 420, ALLEGRO_ALIGN_CENTER, slevelnumber.c_str());
			++level_number;
			slevelnumber = std::to_string(level_number);
			al_draw_text(font, al_map_rgb(255, 255, 255), 925, 420, ALLEGRO_ALIGN_CENTER, slevelnumber.c_str());

			lopta.Resetball();
			mainpaddle.ResetPosition();

			Cigle.clear();
			obliciCigli.clear();

			nivo = level(levelfiles[level_number - 1].c_str());
			slika = nivo.GetBackgroundTexture();
			al_draw_bitmap_region(slika, 0.0f, 0.0f, RIGHT_EDGE, mainpaddle.GetPositionY() + 9, 0, 0, 0);
			
			for (auto cigla : Cigle)
			{
				al_draw_bitmap(obliciCigli[cigla.getTip()].Texture, (float)cigla.getXPosition(), (float)cigla.getYPosition(), 0);
			}

			al_draw_filled_rectangle(mainpaddle.GetPositionX(), mainpaddle.GetPositionY(), mainpaddle.GetPositionX() + 80, mainpaddle.GetPositionY() + 9, al_map_rgb(205, 205, 255));
			levelCompleted = true;
		}

		al_draw_bitmap_region(slika, lopta.GetPositionX()-5, lopta.GetPositionY()-5, r + r, r + r, lopta.GetPositionX() - 5, lopta.GetPositionY() - 5,0);
		al_draw_bitmap_region(slika, 0, 688, RIGHT_EDGE, 9, 0, 688, 0);
		al_draw_filled_rectangle(mainpaddle.GetPositionX(), mainpaddle.GetPositionY(), mainpaddle.GetPositionX() + 80, mainpaddle.GetPositionY() + 9, al_map_rgb(205, 205, 255));

		setEstimatedBallEdges();
		CollisionDetection();
		BrickBallCoollision();
		
		al_draw_filled_circle(lopta.GetNewX(), lopta.GetNewY(), r, al_map_rgb(205, 205, 255));

		al_set_target_backbuffer(al_get_current_display());
		al_flip_display();
	}
	
}

// smjer kretanja loptice u odnosu na matematicke kvadrante s centrom sustava u sredini ekrana
void CollisionDetection()
{
	//lopta u smijeru 2-og matematickog kvadranta
	if (lopta.Getdx() <= 0.0f && lopta.Getdy() <= 0.0f)
	{
		if (leftedge <= 0)
		{
			lopta.Setdx(-lopta.Getdx());
		}

		else if (topedge <= 0)
		{
			lopta.Setdy(-lopta.Getdy());
		}
	}

	//lopta u smijeru 3-og matematickog kvadranta odbijanje od lijevi rub
	else if (lopta.Getdx() <= 0.0f && lopta.Getdy() >= 0.0f)
	{
		if (leftedge <= 0)
		{
			lopta.Setdx(-lopta.Getdx());
		}

		else if (bottomedge >= mainpaddle.GetPositionY())
		{
			paddleCollision(true);
		}		
	}

	//4-ti matematicki kvadrant
	else if (lopta.Getdx() >= 0.0f && lopta.Getdy() >= 0.0f)
	{
		if (bottomedge >= mainpaddle.GetPositionY())
		{
			paddleCollision(false);
		}
			
		else if (rightedge >= RIGHT_EDGE)
		{
			lopta.Setdx(-lopta.Getdx());
		}
	}

	// 1. matematicki kvadrant
	else if (lopta.Getdx() >= 0.0f && lopta.Getdy() <= 0.0f)
	{
		if (topedge <= 0.0f)
		{
			lopta.Setdy(-lopta.Getdy());
		}
		else if (rightedge >= RIGHT_EDGE)
		{
			lopta.Setdx(-lopta.Getdx());
		}
		
	}
};

// odbijanje loptice i paddle-a s obzirom na upadni kut
void paddleCollision(bool kvadrant)
{
	
	float alpha = acos(lopta.Getdy());
	float beta = 1.5707963f - alpha;
	float gamma;

	// Detekcija kolizije loptice i paddle-a
	// Ako je doslo do kolizije racuna se kut odbijanja s obzirom na kojem dijelu paddlea je doslo do kolizije
	if (leftedge >= mainpaddle.GetPositionX() && rightedge <= mainpaddle.GetPositionX() + 80)
	{
		if (leftedge > mainpaddle.GetPositionX() + 55.0f && rightedge <= mainpaddle.GetPositionX() + 80.0f)
		{
			if (kvadrant)
			{
				gamma = 1.5707963f + alpha - (beta / 2.0f);
				lopta.SetDirection(gamma);
			}

			else
			{
				gamma = 1.5707963f - alpha - (beta / 2.0f);
				lopta.SetDirection(gamma);
			}
		}

		else if (leftedge >= mainpaddle.GetPositionX() && rightedge <= mainpaddle.GetPositionX() + 25.0f)
		{
			if (kvadrant)
			{
				gamma = 1.5707963f + alpha + (beta / 2.0f);
				lopta.SetDirection(gamma);
			}

			else
			{
				gamma = 1.5707963f - alpha + (beta / 2.0f);
				lopta.SetDirection(gamma);
			}
		}

		else if (leftedge > mainpaddle.GetPositionX() + 15.0f && rightedge <= mainpaddle.GetPositionX() + 45.0f) 
		{
			if (kvadrant)
			{
				gamma = 1.5707963f + alpha + (beta / 4.0f);
				lopta.SetDirection(gamma);
			}

			else
			{
				gamma = 1.5707963f - alpha + (beta / 4.0f);
				lopta.SetDirection(gamma);
			}
		}

		else if (leftedge > mainpaddle.GetPositionX() + 35.0f && rightedge <= mainpaddle.GetPositionX() + 65.0f)
		{
			if (kvadrant)
			{
				gamma = 1.5707963f + alpha - (beta / 4.0f);
				lopta.SetDirection(gamma);
			}

			else
			{
				gamma = 1.5707963f - alpha - (beta / 4.0f);
				lopta.SetDirection(gamma);
			}
		}

	}

	else if (rightedge > mainpaddle.GetPositionX() + 80 && leftedge < mainpaddle.GetPositionX() + 80)
	{
		if (kvadrant)
		{
			gamma = 1.5707963f - alpha;
			lopta.SetDirection(gamma);
		}
		else
		{
			gamma = 1.5707963f - alpha - ((2*beta) / 3.0f);
			lopta.SetDirection(gamma);
		}
	}

	else if (rightedge > mainpaddle.GetPositionX() && leftedge < mainpaddle.GetPositionX())
	{
		if (kvadrant)
		{
			gamma = 1.5707963f + alpha + ((2 * beta) / 3.0f);
			lopta.SetDirection(gamma);
		}

		else
		{
			gamma = 1.5707963f + alpha;
			lopta.SetDirection(gamma);
		}
	}

	// loptica nije udarila u paddle
	else
	{

		s_life = std::to_string(life);
		al_draw_text(font, al_map_rgb(0, 0, 0), 925, 120, ALLEGRO_ALIGN_CENTER, s_life.c_str());
		--life;
		s_life = std::to_string(life);
		al_draw_text(font, al_map_rgb(255, 255, 255), 925, 120, ALLEGRO_ALIGN_CENTER, s_life.c_str());

		mainpaddle.ResetPosition();
		lopta.Resetball();
	}

};

// Udarac cigle i loptice
void  BrickBallCoollision()
{
	brickHited = false;
	auto it = std::begin(Cigle);
	while (it != std::end(Cigle))
	{
		if (rightedge >= it->getXPosition() && leftedge <= (it->getXPosition() + 40.0f) && bottomedge >= it->getYPosition() && topedge <= (it->getYPosition() + 10.0f)) //udarena cigla ili s lijeva ili s desna
		{
			if ((rightedge + (-lopta.Getdx()*SPEED) >= it->getXPosition() && leftedge + (-lopta.Getdx()*SPEED) <= (it->getXPosition() + 40.0f)))
			{

				if (!brickHited)
				{
					lopta.Setdy(-lopta.Getdy());
				}
				
			}

			else
			{
				if (!brickHited)
				{
					lopta.Setdx(-lopta.Getdx());
				}
					
			}
			
			brickHited = true;
			levelCompleted = true;

			it->DecrementHp();

			if (it->getHp() == 0)
			{
				al_play_sample(obliciCigli[it->getTip()].BreakSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

				countscore = std::to_string(score);
				al_draw_text(font, al_map_rgb(0, 0, 0), 925, 270, ALLEGRO_ALIGN_CENTER, countscore.c_str());
				score += obliciCigli[it->getTip()].BreakScore;
				countscore = std::to_string(score);
				al_draw_text(font, al_map_rgb(255, 255, 255), 925, 270, ALLEGRO_ALIGN_CENTER, countscore.c_str());

				DeleteBrick(*it);
				it = Cigle.erase(it);
			}
			else
			{
				al_play_sample(obliciCigli[it->getTip()].HitSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			}
		}
		if (std::end(Cigle) != it)
		{
			++it;
		}
			
	}
}

// Precrtavanje unistene cigle
void DeleteBrick(bricks cigla)
{
	float _x = cigla.getXPosition();
	float _y = cigla.getYPosition();
	al_draw_filled_rectangle(_x, _y, _x + 40.0f, _y + 10.0f, al_map_rgb(0, 0, 0));
	al_draw_bitmap_region(slika, _x, _y, 40.0f, 10.0f, _x, _y, 0);
}

// Rubovi kugle
void setEstimatedBallEdges()
{
	leftedge = lopta.Getdx()*SPEED + lopta.GetPositionX() - r;
	rightedge = lopta.Getdx()*SPEED + lopta.GetPositionX() + r;
	topedge = lopta.Getdy()*SPEED + lopta.GetPositionY() - r;
	bottomedge = lopta.Getdy()*SPEED + lopta.GetPositionY() + r;
}


void SetLevelFiles()
{
	levelfiles.push_back("Level1.xml");
	levelfiles.push_back("Level2.xml");
	levelfiles.push_back("Level3.xml");
}