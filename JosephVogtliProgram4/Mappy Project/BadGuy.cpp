#include "BadGuy.h"
BadGuy::~BadGuy()
{
	al_destroy_bitmap(image);
}
BadGuy::BadGuy()
{
	image = al_create_bitmap(64,64);   
	if(!image) {
		exit(1);
	}

	al_set_target_bitmap(image);
	al_clear_to_color(al_map_rgb(0, 0, 0));

	x = 0;
	y = 0;

	al_draw_filled_rectangle(25,10,39,54,al_map_rgb(100, 100, 120));
	al_draw_filled_ellipse(32,32,32,16,al_map_rgb(255, 0, 255));
	al_draw_filled_circle(32,32,4,al_map_rgb(255, 255, 255));
	al_draw_filled_circle(16,32,4,al_map_rgb(120, 255, 255));
	al_draw_filled_circle(48,32,4,al_map_rgb(255, 255, 120));
	boundx = al_get_bitmap_width(image)*.75;
	boundy = al_get_bitmap_height(image)*.75;
	live = false;

}
void BadGuy::DrawBadGuy()
{


	if(live)
	{
		al_draw_bitmap(image,x,y,0);
	}

}
void BadGuy::StartBadGuy(int WIDTH, int HEIGHT )
{

	if(!live)
	{
		if(rand() % 500 == 0)
		{
			live = true;
			do{
				x =  rand() % (WIDTH - boundx); 
			}while (x <100);
			do{
				y =  rand() % (HEIGHT - boundy);
			}while (y<100);

		}
	}
	
}

