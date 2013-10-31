#include "projectile.h"


Projectile::Projectile(ALLEGRO_BITMAP& bitmap) : AirborneObject(bitmap)
{
	engineStrength = 150.0;
	SPEED_BARRIER_X = 15.0;
	SPEED_BARRIER_Y = -15.0;
	direction = 0.0;
	velx = engineStrength;
	vely = GRAVITY;
}

void Projectile::setSourceObject(AirborneObject& origin){
	sourceOfProjectile = origin;
	x = origin.x + (al_get_bitmap_width(origin.bitmapObject)/2);
	y = origin.y + (al_get_bitmap_height(origin.bitmapObject)/2);
}



Projectile::~Projectile(void)
{
	delete &trailQueue;
	delete this;
}

void Projectile::addTrailMarker(int x, int y){
	TrailPairs newPair;
	newPair.x = x;
	newPair.y = y;

	trailQueue.push(newPair);
	if(trailQueue.size() > 8)
		trailQueue.pop();

}

void Projectile::update(void){
	
	if(engineStrength > 1.0)
		engineStrength -= 1.0;
	else{
		engineStrength = 0;
	}

	accelx = (engineStrength * cos((direction * PI) / 180.0));
	accely = -(engineStrength * sin((direction * PI) / 180.0)) + GRAVITY;

}

void Projectile::checkVelocityBarriers(){
	if(velx > SPEED_BARRIER_X) 
		velx = SPEED_BARRIER_X;
	if(vely < SPEED_BARRIER_Y)
		vely = SPEED_BARRIER_Y;

};

