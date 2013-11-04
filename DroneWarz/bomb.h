#ifndef BOMB_H
#define BOMB_H

#include "bullet.h"

class Bomb :
	public Bullet
{
public:
	Bomb(ALLEGRO_BITMAP&);
	~Bomb(void);
	
	void setSourceObject(AirborneObject&);
	void setDirection(float);
	void update(void);
	void checkVelocityBarriers(void);
	void startExplosion();


//private:
	AirborneObject sourceOfProjectile;
	float engineStrength;
	bool explode;
};

#endif