#include "AiPilot.h"


AiPilot::AiPilot(ALLEGRO_BITMAP& bitmap) : Plane(bitmap)
{
	x = playerPlane->x + SCREEN_W; 
	y = -(rand() + 200);
	noseRotation = 0.0;
	velx = -1.0;
	vely = -1.0;
	isAi = true;
	throttle = 1.0;
	processUpdate();
	grounded = false;
	inFireRange = true;
}


AiPilot::~AiPilot(void)
{

}

void AiPilot::processUpdate(){
	if(x < (playerPlane->x - SCREEN_W/2)){
		x = playerPlane->x + SCREEN_W;
		y = playerPlane->y;
		velx = -1.0;
		vely = -1.0;
	}
	
	chooseDirection();
	chooseThrottle();
	chooseWeapon();
	//if(grounded){
	//	throttle = 0.0;
	//	y = 0.0;
	//	velx = 0.0;
	//	vely = 0.0;
	//	engineStrength = 0.0;
	//}else{
	throttle = 1.0;
	engineStrength = 0.05;
	//}
	accelx = (throttle * engineStrength) * cos(((noseRotation) * PI) / 180.0);
	accely = -((throttle * engineStrength) * sin(((noseRotation + 10.80) * PI) / 180.0));

	AirborneObject::update();


}
/**
	Ai will start with a nosedive manuever to player until he passes him in the x dimension and then 
	fly away.  Using tan function and then taking the negative of 180 - the resulting angle. 
	this is done so that the drawing functions draw at angles according to standard cartesian plane.
**/
void AiPilot::chooseDirection(){
	if(!grounded && x > playerPlane->x){
		float diffX = x - playerPlane->x;
		float diffY = y - playerPlane->y;
		noseRotation = tan((diffY/diffX));
		noseRotation *= 180/PI;
		noseRotation = (180 - noseRotation);
	}
	else if(!grounded && x < playerPlane->x){
		noseRotation = rand() % -60;
	}
	else if(grounded){
		float diffX = x - playerPlane->x;
		float diffY = y - playerPlane->y;
		if(sqrt(diffX * diffX + diffY * diffY) < FIRE_RANGE){
			inFireRange = true;
		}
	}
}

void AiPilot::chooseThrottle(){
	throttle = DEFAULT_THROTTLE;
}


	
void AiPilot::chooseWeapon(){
	fireKey = 1;
}

void AiPilot::chooseWeapon(int w){
	fireKey = w;
}

void AiPilot::checkVelocityBarriers(){
	if(velx > SPEED_BARRIER_X) 
		velx = SPEED_BARRIER_X;
	if(vely < SPEED_BARRIER_Y)
		vely = SPEED_BARRIER_Y;
}


