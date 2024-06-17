#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <iostream>
#include <string>
#include "SpriteSheet.h"
#include "mappy_A5.h"
using namespace std;

int collided(int x, int y);  //Tile Collision
bool endValue( int x, int y ); //End Block with the User Value = 8
int main(void)
{
	const int WIDTH = 900;
	const int HEIGHT = 480;
	int level = 1;
	bool keys[] = {false, false, false, false, false};
	enum KEYS{UP, DOWN, LEFT, RIGHT, SPACE};
	//variables
	bool done = false;
	bool render = false;
	//Player Variable
	Sprite player;



	//allegro variable
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer;

	//program init
	if(!al_init())										//initialize Allegro
		return -1;

	display = al_create_display(WIDTH, HEIGHT);			//create our display object

	if(!display)										//test display object
		return -1;

	//addon init
	al_install_keyboard();
	al_init_image_addon();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	ALLEGRO_FONT* font = al_load_font("goodtime.ttf", 18, 0);

	player.InitSprites(WIDTH,HEIGHT);

	int xOff = 0;
	int yOff = 0;
	int timeCheck = 0;
	int timeLeft = 60;
	int frame = 0;
	bool timeUp = false;
	if(MapLoad("maze1.FMP", 1))
		exit(0);

	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60);

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_start_timer(timer);
	//draw the background tiles
	MapDrawBG(xOff,yOff, 0, 0, WIDTH-1, HEIGHT-1);

	//draw foreground tiles
	MapDrawFG(xOff,yOff, 0, 0, WIDTH-1, HEIGHT-1, 1);
	player.DrawSprites(0,0);
	al_flip_display();
	al_clear_to_color(al_map_rgb(0,0,0));
	while (!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			// Counts to 30 seconds before shutting the game down
			frame += 1;
			if (frame >= 60) {
				timeCheck = frame / 60;
				if (timeCheck == 60) {
					done = true;
				}
			}
			render = true;
			if (keys[UP])
				player.UpdateSprites(WIDTH, HEIGHT, 3);
			else if (keys[DOWN])
				player.UpdateSprites(WIDTH, HEIGHT, 4);
			else if (keys[LEFT])
				player.UpdateSprites(WIDTH, HEIGHT, 0);
			else if (keys[RIGHT])
				player.UpdateSprites(WIDTH, HEIGHT, 1);
			else
				player.UpdateSprites(WIDTH, HEIGHT, 2);
			if (player.CollisionEndBlock()) {
				timer = 0;
				level++;
				player.InitSprites(WIDTH, HEIGHT);
				if (level == 2) {
					frame = 0;
					if (MapLoad("maze2.FMP", 1))
						exit(0);
				}
				if (level == 3) {
					frame = 0;
					if (MapLoad("maze3.FMP", 1))
						exit(0);
				}
				if (level == 4) {
					done = true;
				}
			}
			render = true;

		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = true;
				break;

			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = false;
				break;
			}
		}
		if (render && al_is_event_queue_empty(event_queue))
		{
			render = false;

			//update the map scroll position
			xOff = player.getX() + player.getWidth() - WIDTH / 2;
			yOff = player.getY() + player.getHeight() - HEIGHT / 2;

			//avoid moving beyond the map edge
			if (xOff < 0) xOff = 0;

			if (xOff > (mapwidth * mapblockwidth - WIDTH))
				xOff = mapwidth * mapblockwidth - WIDTH;
			if (yOff < 0)
				yOff = 0;
			if (yOff > (mapheight * mapblockheight - HEIGHT))
				yOff = mapheight * mapblockheight - HEIGHT;

			//draw the background tiles
			MapDrawBG(xOff, yOff, 0, 0, WIDTH, HEIGHT);

			//draw foreground tiles
			MapDrawFG(xOff, yOff, 0, 0, WIDTH, HEIGHT, 0);
			MapUpdateAnims();
			player.DrawSprites(xOff, yOff);
			if (level == 1) {
				al_draw_text(font, al_map_rgb(255, 255, 255), WIDTH / 2, 0, 0, "LEVEL 1");
			}
			else if (level == 2) {
				al_draw_text(font, al_map_rgb(255, 255, 255), WIDTH / 2, 0, 0, "LEVEL 2");
			}
			else if (level == 3) {
				al_draw_text(font, al_map_rgb(255, 255, 255), WIDTH / 2, 0, 0, "LEVEL 3");
			}
			if (done) {
				al_draw_text(font, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2, 0, "GAME OVER");
			}
			string test = to_string(timeLeft - timeCheck); //timer
			const char* test2 = test.c_str();
			al_draw_text(font, al_map_rgb(255, 255, 255), (WIDTH / 2) - 50, HEIGHT - 40 / 2, 0, "TIME:");
			al_draw_text(font, al_map_rgb(255, 255, 255), (WIDTH / 2) + 20, HEIGHT - 40 / 2, 0, test2);
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
	}
	al_rest(5);
	MapFreeMem();
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);						//destroy our display object

	return 0;
}



int collided(int x, int y)
{
	BLKSTR *blockdata;
	blockdata = MapGetBlock(x/mapblockwidth, y/mapblockheight);
	if (blockdata->user1 == 0  || blockdata->user1 == 8) {
		return 0;
	}
	//Collision block
	else if (blockdata->user1 == 1) {
		return 1;
	}
	else if (blockdata->user1 == 2) {
		return 2;
	}
}

bool endValue( int x, int y )
{

	BLKSTR* data;
	data = MapGetBlock( x/mapblockwidth, y/mapblockheight );

	if( data->user1 == 8 )
	{
		return true;
	}else
		return false;
}