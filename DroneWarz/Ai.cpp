#include "Ai.h"


Ai::Ai(ALLEGRO_BITMAP& bitmap) : PlayerObject(bitmap)
{
	x = playerPlane->x + SCREEN_W + (rand()%600); 
	y = -(rand() % 500 + 20);
	noseRotation = 0.0;
	velx = -1.0;
	vely = -1.0;
	isAi = true;
	throttle = 1.0;
	update();
	grounded = false;
	groundUnit = false;
	inFireRange = false;
	hasExploded = false;
}


Ai::~Ai(void)
{

}

void Ai::update(){
	if((x + al_get_bitmap_width(bitmapObject)) < (playerPlane->x - SCREEN_W/2)){
		x = playerPlane->x + SCREEN_W;
		y = -(rand() % 500 + 20);
		velx = -1.0;
		vely = -1.0;
		hasExploded = false;
	}

	if (groundUnit){
		y = -40;
		vely = 0;
		velx = 0;
		accely = 0;
		accelx = 0;
		return;
	}

	chooseDirection();
	chooseThrottle();
	chooseWeapon(); 
	throttle = 1.0;
	engineStrength = 0.0;

	accelx = (throttle * engineStrength) * cos(((noseRotation) * PI) / 180.0);
	accely = -((throttle * engineStrength) * sin(((noseRotation + 10.80) * PI) / 180.0));

	CharacterObject::update();


}
/**
	Ai will start with a nosedive manuever to player until he passes him in the x dimension and then 
	fly away.  Using tan function and then taking the negative of 180 - the resulting angle. 
	this is done so that the drawing functions draw at angles according to standard cartesian plane.
**/
void Ai::chooseDirection(){
	float diffX = x - playerPlane->x;
	float diffY = y - playerPlane->y;

	if(!grounded && x > playerPlane->x){
		noseRotation = tan((diffY/diffX));
		noseRotation *= 180/PI;
		noseRotation = (180 - noseRotation);
		if (sqrt(diffX * diffX + diffY * diffY) < FIRE_RANGE){
			inFireRange = true;
		}
	}
	else if(!grounded && x < playerPlane->x){
		noseRotation = rand() % -60;
		inFireRange = false;
	}
	else if(grounded){
		if(sqrt(diffX * diffX + diffY * diffY) < FIRE_RANGE){
			inFireRange = true;
		}
		
		noseRotation = tan((diffY / diffX));
		noseRotation *= 180 / PI;
		noseRotation = (180 - noseRotation);
	}
	if (sqrt(diffX * diffX + diffY * diffY) > FIRE_RANGE){
		inFireRange = false;
	}
}

void Ai::chooseThrottle(){
	throttle = DEFAULT_THROTTLE;
}


	
void Ai::chooseWeapon(){
	fireKey = 1;
}

void Ai::chooseWeapon(int w){
	fireKey = w;
}

void Ai::checkVelocityBarriers(){
	if(velx > SPEED_BARRIER_X) 
		velx = SPEED_BARRIER_X;
	if(vely < SPEED_BARRIER_Y)
		vely = SPEED_BARRIER_Y;
}

bool Ai::canFire(int type){
	switch (type){
	case 1:
		return reloadBullet->checkIfReady();
		break;
	case 2:
		return false;
		break;
	case 3:
		return reloadSpecialAttack->checkIfReady();
		break;
	case 4:
		return reloadBomb->checkIfReady();
		break;
	default:
		return false;
		break;
	}

}

void Ai::setIsGround(){
	groundUnit = true;
}
