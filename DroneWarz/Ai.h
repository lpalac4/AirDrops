/**
	AI class represents an enemy plane/ship on screen and will have member function/variables to take 
	down the player's plane very similar to the player's attacks with more restrictions.
	@author Luis Palacios
**/ 

#ifndef AI_H
#define AI_H

#include "PlayerObject.h"
#include <math.h>

extern float RADIAN_TO_DEGREE;
extern PlayerObject* playerPlane;
static float FIRE_RANGE = SCREEN_W >> 1;

class Ai :
	public PlayerObject
{
public:
	Ai(ALLEGRO_BITMAP&);
	~Ai(void);
	virtual void update(void);
	virtual void checkVelocityBarriers(void);
	bool inFireRange;
	bool canFire(int);
	void setIsGround(void);
	bool groundUnit;

	int fireKey;
	void chooseDirection(void);
	void chooseThrottle(void);
	void chooseWeapon(void);
	void chooseWeapon(int);


};

#endif