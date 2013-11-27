#include "AOEProjectile.h"


AOEProjectile::AOEProjectile(ALLEGRO_BITMAP& bitmap) : ProjectileObject(bitmap)
{
	engineStrength = 0.0;
	SPEED_BARRIER_X = 100;
	SPEED_BARRIER_Y = -100;
	direction = 0;
	velx = engineStrength;
	vely = GRAVITY;
	explode = false;
}

AOEProjectile::~AOEProjectile(void)
{
}

void AOEProjectile::setDirection(float dir){
	direction = dir;
}


void AOEProjectile::update(void){
	
	accelx = (engineStrength * cos((direction * PI) / 180.0));
	accely = -(engineStrength * sin((direction * PI) / 180.0)) + GRAVITY;
	CharacterObject::update();	
	if(grounded){
	/** hit the ground explode **/
		explode = true;
	}

	if(explode)
		startExplosion();

}

void AOEProjectile::checkVelocityBarriers(){
	if(velx > SPEED_BARRIER_X) 
		velx = SPEED_BARRIER_X;
	if(vely < SPEED_BARRIER_Y)
		vely = SPEED_BARRIER_Y;

};

void AOEProjectile::startExplosion(){
	

}

