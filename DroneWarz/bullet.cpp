#include "bullet.h"


Bullet::Bullet(ALLEGRO_BITMAP& bitmap) : AirborneObject(bitmap)
{
	engineStrength = 280.0;
	SPEED_BARRIER_X = 280.0;
	SPEED_BARRIER_Y = -280.0;
	direction = 0.0;
	velx = engineStrength;
	vely = GRAVITY;
	trailShow = false;
	TERMINAL_VELY = 280;
}

void Bullet::setSourceObject(AirborneObject& origin){
	sourceOfProjectile = origin;
	x = origin.x + (al_get_bitmap_width(origin.bitmapObject)/2);
	y = origin.y + (al_get_bitmap_height(origin.bitmapObject)/2);

}

void Bullet::setDirection(float dir){
	direction = dir;
}


Bullet::~Bullet(void)
{
	delete[] &trailQueue;
}

void Bullet::addTrailMarker(){
	TrailPairs* newPair = new TrailPairs;
	newPair->x = x;
	newPair->y = y;

	trailQueue.push_back(*newPair);

	if(trailQueue.size() > 8){
		TrailPairs* tmpPtr = &(trailQueue.front());
		trailQueue.pop_front();
		delete tmpPtr;
	}
}

void Bullet::update(void){
	
	//if(engineStrength > 1.0)
	//	engineStrength -= 1.0;
	//else{
	//	engineStrength = 0;
	//}

	accelx = (engineStrength * cos((direction * PI) / 180.0));
	accely = -(engineStrength * sin((direction * PI) / 180.0)) + GRAVITY;
	if(trailShow){
		addTrailMarker();
	}
	
	AirborneObject::update();	

}

void Bullet::checkVelocityBarriers(){
	if(velx > SPEED_BARRIER_X) 
		velx = SPEED_BARRIER_X;
	if(vely < SPEED_BARRIER_Y)
		vely = SPEED_BARRIER_Y;

};

