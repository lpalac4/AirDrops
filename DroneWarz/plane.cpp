#include "plane.h"


Plane::Plane(ALLEGRO_BITMAP& bitmap) : AirborneObject(bitmap)
{
	pitch = PITCH_CONSTANT;
	SPEED_BARRIER_X = 10.0;
	SPEED_BARRIER_Y = -10.0;
	
	health = DEFAULT_HEALTH;
	throttle = DEFAULT_THROTTLE;
	bullets = DEFAULT_BULLETS;
	cannonshells = DEFAULT_CANNONSHELLS;
	bombs = DEFAULT_BOMBS;
	rockets = DEFAULT_ROCKETS;
	noseRotation = 0.0;
	engineStrength = 100.0;
	stalling = false;
}


Plane::~Plane(void)
{ 
	delete this;
}

void Plane::update(void){
	/** calculate accelerations **/
	if(stalling){
		stallRoutine();
		AirborneObject::update();
	}
	noseRotation += pitch;
	if(noseRotation >= 45.0)
		noseRotation = 45.0;
	if(noseRotation < -45.0)
		noseRotation = -45.0;
	if(pitch == 0.0){
		if(noseRotation > 0)
			noseRotation -= 1.0;
		else{
			noseRotation += 1.0;
		}
	}
	
	accelx = (throttle * engineStrength) * cos((noseRotation * PI) / 180.0);
	accely = -((throttle * engineStrength) * sin((noseRotation * PI) / 180.0)) + GRAVITY;

	
	AirborneObject::update();
	//if(velx < STALLING_VELX){
		//stalling = true;
		//stallRoutine();
	//}
}

/**	adjusting pitch given 0,0 is on the top left corner of viewport **/

void Plane::adjustPitch(bool pitchUp){
	if(pitchUp)
		pitch += PITCH_INCREMENT;
	else
		pitch -= PITCH_DECREMENT;

	if(pitch > MAX_PITCH)
		pitch = MAX_PITCH;
	if(pitch < MIN_PITCH)
		pitch = MIN_PITCH;

}

void Plane::resetPitch(void){
	pitch = PITCH_CONSTANT;
}

void Plane::adjustThrottle(int newThrottle){
	if(newThrottle > 100 || newThrottle < 0){
		fprintf(stderr, "throttle is not being bound");
		return;
	}

	throttle = newThrottle;

}

void  Plane::stallRoutine(){
	if(noseRotation > 0.0){
		noseRotation -= 1.0;
	}
	if(noseRotation < 0.0){
		noseRotation += 1.0;
	}

}

void Plane::checkVelocityBarriers(){
	
	if(velx > SPEED_BARRIER_X) 
		velx = SPEED_BARRIER_X;
	if(vely < SPEED_BARRIER_Y)
		vely = SPEED_BARRIER_Y;
}

void Plane::fireBullets(std::list<Projectile*>& allProjectiles){
	Projectile* newBullet = new Projectile((*bulletBitmap));
	newBullet->setSourceObject(self());
	allProjectiles.push_back(newBullet);
}

Plane Plane::self(void){
	return *this;
}
