#include "SpecialAttackObject.h"


SpecialAttackObject::SpecialAttackObject(ALLEGRO_BITMAP& bitmap) : ProjectileObject(bitmap)
{
	engineStrength = 0.5;
	SPEED_BARRIER_X = 100.0;
	SPEED_BARRIER_Y = -100.0;
	direction = 0.0;
	velx = 0;
	vely = 0;
	trailShow = true;
	TERMINAL_VELY = 100.0;
	trailList = new std::vector<std::pair<float,float>>();
}
//
//void SpecialAttackObject::setSourceObject(CharacterObject& origin){
//	sourceOfProjectile = origin;
//	x = origin.x + (al_get_bitmap_width(origin.bitmapObject)/2);
//	y = origin.y + (al_get_bitmap_height(origin.bitmapObject)/2);
//
//}

void SpecialAttackObject::setDirection(float dir){
	direction = dir;
}



SpecialAttackObject::~SpecialAttackObject(void)
{
	delete trailList;
}

void SpecialAttackObject::addTrailMarker(){
	std::pair<float, float>* trail = new std::pair<float, float>();
	trail->first = x;
	trail->second = y;

	if(trailList && trailList->size() > 3){
			trailList->erase(trailList->begin());
		}
	
	trailList->push_back(*trail);
}

void SpecialAttackObject::update(void){
	
	//if(engineStrength > 1.0)
	//	engineStrength -= 1.0;
	//else{
	//	engineStrength = 0;
	//}

	accelx = (engineStrength * cos((direction * PI) / 180.0));
	accely = -(engineStrength * sin((direction * PI) / 180.0)); //+ GRAVITY;
	if(trailShow){
		addTrailMarker();
	}
	
	CharacterObject::update();	

}

void SpecialAttackObject::checkVelocityBarriers(){
	if(velx > SPEED_BARRIER_X) 
		velx = SPEED_BARRIER_X;
	if(vely < SPEED_BARRIER_Y)
		vely = SPEED_BARRIER_Y;

};





