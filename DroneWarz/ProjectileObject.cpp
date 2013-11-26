#include "ProjectileObject.h"


ProjectileObject::ProjectileObject(ALLEGRO_BITMAP& bitmap) : CharacterObject(bitmap)
{
	engineStrength = 0.5;
	SPEED_BARRIER_X = 10;
	SPEED_BARRIER_Y = -10;
	direction = 0.0;
	velx = 0;
	vely = 0;
	trailShow = false;
	TERMINAL_VELY = 10.0;
	trailList = NULL;
	//playerProjectile = false;
}

void ProjectileObject::setSourceObject(CharacterObject& origin, bool playerOrEnemy){
	sourceOfProjectile = &origin;
	x = origin.x + (al_get_bitmap_width(origin.bitmapObject)/2);
	y = origin.y + (al_get_bitmap_height(origin.bitmapObject)/2);
	playerProjectile = playerOrEnemy;

}

void ProjectileObject::setDirection(float dir){
	direction = dir;
}


ProjectileObject::~ProjectileObject(void)
{
	
}

void ProjectileObject::update(void){

	accelx = (engineStrength * cos((direction * PI) / 180.0));
	accely = -(engineStrength * sin((direction * PI) / 180.0)); //+ GRAVITY;
 
	
	CharacterObject::update();	

}

void ProjectileObject::checkVelocityBarriers(){
	if(velx > SPEED_BARRIER_X) 
		velx = SPEED_BARRIER_X;
	if (velx < -SPEED_BARRIER_X)
		velx = -SPEED_BARRIER_X;
	if(vely < SPEED_BARRIER_Y)
		vely = SPEED_BARRIER_Y;
	if (vely > -SPEED_BARRIER_Y)
		vely = -SPEED_BARRIER_Y;

};

