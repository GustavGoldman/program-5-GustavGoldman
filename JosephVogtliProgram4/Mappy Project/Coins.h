#include "PikuSheet.h"
class coin
{
public:
	coin();
	~coin();
	void drawCoin();
	void updateCoin(int WIDTH, int HEIGHT, char direction);
	void collideCoin(Piku piku);
	void placeCoin(int x, int y);
private:
	int x;
	int y;
	int boundx;
	int boundy;
	bool live;
	bool yMove;
	int speed;
	float angle;
	ALLEGRO_BITMAP* image;
};