#include "PikuSheet.h"

Piku::Piku()
{
	piku=NULL;
	sample = NULL;
}
Piku::~Piku()
{
	al_destroy_bitmap(piku);
	al_destroy_sample(sample);
}
void Piku::InitPiku(int width, int height)
{
	x = 80;
	y = 80;


	maxFrame = 3;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 6;
	frameWidth = 32;
	frameHeight = 32;
	animationColumns = 4;
	animationRows = 1;
	animationDirection = 1;
	jframe;

	piku = al_load_bitmap("piku.png");
	al_convert_mask_to_alpha(piku, al_map_rgb(255,0,255));

	sample = al_load_sample("tap.flac");
	if (!sample) {
		exit(10);
	}
}

void Piku::UpdatePiku(int width, int height, int dir)
{
	int oldx = x;
	int oldy = y;

	if(dir == 1){ //right key
		animationDirection = 1; 
		x+=2; 
		if (++frameCount > frameDelay)
		{
			frameCount=0;
			if (++curFrame > maxFrame)
				curFrame=1;
		}
	}
	else if (dir == 0) { //left key
		animationDirection = 0;
		x -= 2;
		if (++frameCount > frameDelay)
		{
			frameCount = 0;
			if (++curFrame > maxFrame)
				curFrame = 1;
		}
		al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
	}
	else if (dir == 3) { //up key
		animationDirection = 3;
		y -= 2;
		if (++frameCount > frameDelay)
		{
			frameCount = 0;
			if (++curFrame > maxFrame)
				curFrame = 1;
		}
		al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
	}
	else if (dir == 4) { //down key
		animationDirection = 4;
		y += 2;
		if (++frameCount > frameDelay)
		{
			frameCount = 0;
			if (++curFrame > maxFrame)
				curFrame = 1;
		}
		al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
	}
		else //represent that they hit the space bar and that mean direction = 0
			animationDirection = dir;

	//check for collided with foreground tiles
	if (animationDirection==0)
	{ 
		if (collided(x, y + frameHeight)) { //collision detection to the left
			x = oldx; 
			y= oldy;
			al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
		}

	}
	else if (animationDirection ==1)
	{ 
		if (collided(x + frameWidth, y + frameHeight)) { //collision detection to the right
			x = oldx; 
			y= oldy;
			al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
		}
	}
	else if (animationDirection == 3)
	{
		if (collided(x + frameWidth, y)) { //collision detection from the bottom
			x = oldx;
			y = oldy;
			al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
		}
	}
	else if (animationDirection == 4)
	{
		if (collided(x, y + frameHeight)) { //collision detection from the top
			x = oldx;
			y = oldy;
			al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
		}
	}
}

bool Piku::CollisionEndBlock()
{
	if (endValue(x + frameWidth/2, y + frameHeight + 5))
		return true;
	else
		return false;
}

void Piku::DrawPiku(int xoffset, int yoffset)
{
	int fx = (curFrame % animationColumns) * frameWidth;
	int fy = (curFrame / animationColumns) * frameHeight;

	if (animationDirection == 1) {
		al_draw_bitmap_region(piku, fx, fy, frameWidth, frameHeight, x - xoffset, y - yoffset, 0);
	}
	else if (animationDirection == 0) {
		al_draw_bitmap_region(piku, fx, fy, frameWidth, frameHeight, x - xoffset, y - yoffset, ALLEGRO_FLIP_HORIZONTAL);
	}
	else if (animationDirection == 2) {
		al_draw_bitmap_region(piku, 0, 0, frameWidth, frameHeight, x - xoffset, y - yoffset, 0);
	}
	else if (animationDirection == 3) {
		al_draw_bitmap_region(piku, fx, fy, frameWidth, frameHeight, x - xoffset, y - yoffset, 0);
	}
	else if (animationDirection == 4) {
		al_draw_bitmap_region(piku, fx, fy, frameWidth, frameHeight, x - xoffset, y - yoffset, 0);
	}
}