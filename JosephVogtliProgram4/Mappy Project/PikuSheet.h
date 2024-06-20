#ifndef PIKUSHEETH
#define PIKUSHEETH
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <iostream>
using namespace std;
class Piku
{
	friend int collided(int x, int y);
	friend bool endValue( int x, int y );
public:
	Piku();
	~Piku();
	void InitPiku(int width, int height);
	void UpdatePiku(int width, int height, int dir); //dir 1 = right, 0 = left, 2 = Standing Still
	void DrawPiku(int xoffset, int yoffset);
	bool CollidePiku();
	float getX() {return x;}
	float getY() {return y;}
	int getWidth() {return frameWidth;}
	int getHeight() {return frameHeight;}
	int jumping(int jump, const int JUMPIT);
	bool CollisionEndBlock();

private:
	float x;
	float y;

	int maxFrame;
	int curFrame;
	int frameCount;
	int frameDelay;
	int frameWidth;
	int frameHeight;
	int animationColumns;
	int animationRows;
	int animationDirection;
	int jframe;
	int temp;
	ALLEGRO_BITMAP *piku;
	ALLEGRO_SAMPLE* sample;
};
#endif