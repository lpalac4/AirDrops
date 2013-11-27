#include "PlayerObject.h"

/** constructor requires a bitmap thats passed by reference, will call the base class Airborne constructor with that same bitmap reference **/
PlayerObject::PlayerObject(ALLEGRO_BITMAP& bitmap) : CharacterObject(bitmap)
{
	pitch = PITCH_CONSTANT;
	SPEED_BARRIER_X = 2.0;
	SPEED_BARRIER_Y = -2.0;
	reloadSpecialAttack = new Reload();
	reloadBomb = new Reload();
	reloadBullet = new Reload();
	health = DEFAULT_HEALTH;
	throttle = DEFAULT_THROTTLE;
	bullets = DEFAULT_BULLETS;
	cannonshells = DEFAULT_CANNONSHELLS;
	bombs = DEFAULT_BOMBS;
	rockets = DEFAULT_ROCKETS;
	noseRotation = 0.0;
	engineStrength = 2.5;
	stalling = false;
	showTrail = true;
	trailList = new std::vector<std::pair<float, float>>;
	
}

PlayerObject::PlayerObject(ALLEGRO_BITMAP& bitmap, PlayerType playerType) : CharacterObject(bitmap)
{
	pitch = PITCH_CONSTANT;
	SPEED_BARRIER_X = 2.0;
	SPEED_BARRIER_Y = -2.0;
	health = DEFAULT_HEALTH;
	throttle = DEFAULT_THROTTLE;
	bullets = DEFAULT_BULLETS;
	cannonshells = DEFAULT_CANNONSHELLS;
	bombs = DEFAULT_BOMBS;
	rockets = DEFAULT_ROCKETS;
	noseRotation = 0.0;
	engineStrength = 2.5;
	stalling = false;
	showTrail = true;
	trailList = new std::vector<std::pair<float, float>>;
	reloadSpecialAttack = new Reload(2);
	reloadBomb = new Reload(3);
	reloadBullet = new Reload(1);

}


PlayerObject::~PlayerObject(void)
{ 
	//delete trailList;
}
/** update all the important attributes of the plane that change with time(t) **/
void PlayerObject::update(void){
	/** calculate accelerations **/
	if(stalling){
		stallRoutine();
		CharacterObject::update();
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
	
	accelx = (throttle * engineStrength) * cos(((noseRotation) * PI) / 180.0);
	accely = -((throttle * engineStrength) * sin(((noseRotation + 10.80) * PI) / 180.0)) + GRAVITY;

	
	CharacterObject::update();

	if(showTrail){
		std::pair<float, float>* trail = new std::pair<float, float>();
		trail->first = x;
		trail->second = y;

		if(trailList && trailList->size() > 8){
			trailList->erase(trailList->begin());
		}
		trailList->push_back(*trail);
	}
}

/**	adjusting pitch given 0,0 is on the top left corner of viewport **/

void PlayerObject::adjustPitch(bool pitchUp){
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
void PlayerObject::resetPitch(void){
	pitch = PITCH_CONSTANT;
}

/** adjust the throttle of the plane first checking its bounds **/
void PlayerObject::adjustThrottle(int newThrottle){
	if(newThrottle > 1.0 || newThrottle < 0.0){
		fprintf(stderr, "throttle is not being bound");
		return;
	}

	throttle = newThrottle;

}
/** Levels out the angle rotation of the plane's nose over time **/
void  PlayerObject::stallRoutine(){
	if(noseRotation > 0.0){
		noseRotation -= 1.0;
	}
	if(noseRotation < 0.0){
		noseRotation += 1.0;
	}

}

/** checks to make sure the plane doesnt fly faster than it is capable of **/
void PlayerObject::checkVelocityBarriers(){
	
	if(velx > SPEED_BARRIER_X) 
		velx = SPEED_BARRIER_X;
	if(vely < SPEED_BARRIER_Y)
		vely = SPEED_BARRIER_Y;
}

ProjectileObject* PlayerObject::fireBullets(){
	ProjectileObject* newBullet = new ProjectileObject((*bulletBitmap));
	//newBullet->setSourceObject(self());
	newBullet->setDirection(noseRotation);
	reloadBullet->firedShot();
	return newBullet;
}

SpecialAttackObject* PlayerObject::fireRockets(){
	SpecialAttackObject* newRocket = new SpecialAttackObject(*rocketBitmap);
	//newRocket->setSourceObject(self());
	newRocket->setDirection(noseRotation);
	reloadSpecialAttack->firedShot();
	return newRocket;
}

AOEProjectile* PlayerObject::dropBombs(){
	AOEProjectile* newBomb = new AOEProjectile(*bombBitmap);
	//newBomb->setSourceObject(self());
	newBomb->setDirection(270);
	reloadBomb->firedShot();
	return newBomb;
}

PlayerObject PlayerObject::self(void){
	return *this;
}
