#ifndef PLANE_H
#define PLANE_H

#include "airborneobject.h"
#include "projectile.h"
#include <stdio.h>
#include <list>

const float MIN_PITCH = -0.9;  
const float MAX_PITCH = 0.9;

const float PITCH_INCREMENT = 0.1;
const float PITCH_DECREMENT = 1.0;

const float PITCH_CONSTANT = 0.0;
const float SPEED_CONSTANT = 10;
const float STALLING_VELX = 5;

const int DEFAULT_THROTTLE = 0.9;
const int DEFAULT_BULLETS = 300;
const int DEFAULT_CANNONSHELLS = 50;
const int DEFAULT_ROCKETS = 0;
const int DEFAULT_BOMBS = 0;
const int DEFAULT_HEALTH = 100;

extern ALLEGRO_BITMAP* bulletBitmap;


class Plane :
	public AirborneObject
{
public:
	Plane(ALLEGRO_BITMAP&);
	virtual ~Plane(void);
	int getRockets(){ return rockets;}
	void update(void);
	void adjustPitch(bool);
	void resetPitch(void);
	void adjustThrottle(int);
	void stallRoutine(void);
	virtual void checkVelocityBarriers();
	void fireBullets(std::list<Projectile*>&);
	

//private:
	float roll;
	float pitch;
	bool stalling;
	int health;
	float throttle;
	int bullets;
	int cannonshells;
	int bombs;
	int rockets;
	float noseRotation;
	float engineStrength;

	private:
	Plane self(void);



};

#endif
