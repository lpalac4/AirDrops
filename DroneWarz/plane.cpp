/** 	
	@author Luis Palacios 2013

	The plane class is a subclass of an AirborneObject which has the capabilities of adjusting its
	acceleration and angle of momemtum.  It also is capable of creating new objects including
	bullets, rockets, cannon shells, and bombs when the ui detects the user pressing the appropriate 
	keys.

**/

#include "plane.h"

/** constructor requires a bitmap thats passed by reference, will call the base class Airborne constructor with that same bitmap reference **/
Plane::Plane(ALLEGRO_BITMAP& bitmap) : AirborneObject(bitmap)
{
	pitch = PITCH_CONSTANT;
	SPEED_BARRIER_X = 5.0;
	SPEED_BARRIER_Y = -5.0;
	
	health = DEFAULT_HEALTH;
	throttle = DEFAULT_THROTTLE;
	bullets = DEFAULT_BULLETS;
	cannonshells = DEFAULT_CANNONSHELLS;
	bombs = DEFAULT_BOMBS;
	rockets = DEFAULT_ROCKETS;
	noseRotation = 0.0;
	engineStrength = 2.5;
	stalling = false;
}


Plane::~Plane(void)
{ 
	
}
/** update all the important attributes of the plane that change with time(t) **/
void Plane::update(void){
	/** calculate accelerations **/
	if(stalling){
		stallRoutine();
		AirborneObject::update();
	}
	noseRotation += pitch;
	if(noseRotation > 45.0)
		noseRotation = 45.0;
	if(noseRotation < -45.0)
		noseRotation = -45.0;
	
	if(pitch == 0.0){
		if(noseRotation > 0.0)
			noseRotation -= 0.5;
		else{
			noseRotation += 0.5;
		}
	}
	
	accelx = (throttle * engineStrength) * cos(((noseRotation+9.7) * PI) / 180.0);
	accely = -((throttle * engineStrength) * sin(((noseRotation+9.7) * PI) / 180.0)) + GRAVITY;

	
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
/** Resets the flaps to a 0 degree angle **/
void Plane::resetPitch(void){
	pitch = PITCH_CONSTANT;
}

/** adjust the throttle of the plane first checking its bounds **/
void Plane::adjustThrottle(int newThrottle){
	if(newThrottle > 1.0 || newThrottle < 0.0){
		fprintf(stderr, "throttle is not being bound");
		return;
	}

	throttle = newThrottle;

}
/** Levels out the angle rotation of the plane's nose over time **/
void  Plane::stallRoutine(){
	if(noseRotation > 0.0){
		noseRotation -= 1.0;
	}
	if(noseRotation < 0.0){
		noseRotation += 1.0;
	}

}

/** checks to make sure the plane doesnt fly faster than it is capable of **/
void Plane::checkVelocityBarriers(){
	
	if(velx > SPEED_BARRIER_X) 
		velx = SPEED_BARRIER_X;
	if(vely < SPEED_BARRIER_Y)
		vely = SPEED_BARRIER_Y;
}

Bullet* Plane::fireBullets(){
	Bullet* newBullet = new Bullet((*bulletBitmap));
	newBullet->setSourceObject(self());
	newBullet->setDirection(noseRotation);
	return newBullet;
}

Plane Plane::self(void){
	return *this;
}
