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

	accelx = (engineStrength * cos((direction * PI) / 180.0));
	accely = -(engineStrength * sin((direction * PI) / 180.0)); 
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





