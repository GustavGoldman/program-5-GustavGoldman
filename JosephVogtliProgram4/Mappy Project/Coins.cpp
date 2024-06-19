#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include "Coins.h"

coin::~coin()
{
	al_destroy_bitmap(image);
}
coin::coin() 
{
	image = al_load_bitmap("coin.png");
	x = 0;
	y = 0;
	live = false;

}
void coin::drawCoin()
{
	if (live) {
		al_draw_bitmap(image, 32,32, 0);
	}
}
void coin::collideCoin(Piku piku)
{
	if (live)
	{

		if (x > (piku.getX() - 32) &&
			x < (piku.getX() + 32) &&
			y >(piku.getY() - 32) &&
			y < (piku.getY() + 32))
		{
			live = false;
		}
	}
}
void coin::placeCoin(int mapX, int mapY)
{
	x = mapX;
	y = mapY;
	live = true;
}