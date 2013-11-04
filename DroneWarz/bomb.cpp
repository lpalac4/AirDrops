#include "bomb.h"


Bomb::Bomb(ALLEGRO_BITMAP& bitmap) : Bullet(bitmap)
{
	engineStrength = 0.0;
	SPEED_BARRIER_X = 100;
	SPEED_BARRIER_Y = -100;
	direction = 0;
	velx = engineStrength;
	vely = GRAVITY;
	//TERMINAL_VELY = GRAVITY * 3;
	explode = false;
}

Bomb::~Bomb(void)
{
}

void Bomb::setSourceObject(AirborneObject& origin){
	sourceOfProjectile = origin;
	x = origin.x + (al_get_bitmap_width(origin.bitmapObject)/2);
	y = origin.y + (al_get_bitmap_height(origin.bitmapObject)/2);

}

void Bomb::setDirection(float dir){
	direction = dir;
	
}


void Bomb::update(void){
	
	accelx = (engineStrength * cos((direction * PI) / 180.0));
	accely = -(engineStrength * sin((direction * PI) / 180.0)) + GRAVITY;
	AirborneObject::update();	
	if(!flying){
	/** hit the ground explode **/
		explode = true;
	}

	if(explode)
		startExplosion();

}

void Bomb::checkVelocityBarriers(){
	if(velx > SPEED_BARRIER_X) 
		velx = SPEED_BARRIER_X;
	if(vely < SPEED_BARRIER_Y)
		vely = SPEED_BARRIER_Y;

};

void Bomb::startExplosion(){
	

}

