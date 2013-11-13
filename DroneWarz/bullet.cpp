#include "bullet.h"


Bullet::Bullet(ALLEGRO_BITMAP& bitmap) : AirborneObject(bitmap)
{
	engineStrength = 200.00;
	SPEED_BARRIER_X = 100;
	SPEED_BARRIER_Y = -100;
	direction = 0.0;
	velx = 0;
	vely = 0;
	trailShow = false;
	TERMINAL_VELY = 100.0;
	trailList = NULL;
}

void Bullet::setSourceObject(AirborneObject& origin){
	sourceOfProjectile = origin;
	x = origin.x + (al_get_bitmap_width(origin.bitmapObject)/2);
	y = origin.y + (al_get_bitmap_height(origin.bitmapObject)/2);

}

//void Bullet::setSourceObject(AiGround& origin){
//	sourceOfProjectile = origin;
//	x = origin.getX() + (al_get_bitmap_width(origin.bitmapObject)/2);
//	y = origin.getY() + (al_get_bitmap_height(origin.bitmapObject)/2);
//}

void Bullet::setDirection(float dir){
	direction = dir;
}


Bullet::~Bullet(void)
{
	
}

void Bullet::update(void){
	
	//if(engineStrength > 1.0)
	//	engineStrength -= 1.0;
	//else{
	//	engineStrength = 0;
	//}

	accelx = (engineStrength * cos((direction * PI) / 180.0));
	accely = -(engineStrength * sin((direction * PI) / 180.0)) + GRAVITY;
	/*if(trailShow){
		addTrailMarker();
	}*/
	
	AirborneObject::update();	

}

void Bullet::checkVelocityBarriers(){
	if(velx > SPEED_BARRIER_X) 
		velx = SPEED_BARRIER_X;
	if(vely < SPEED_BARRIER_Y)
		vely = SPEED_BARRIER_Y;

};

