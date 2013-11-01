/**     
        @author Luis Palacios 2013

        The plane class is a subclass of an AirborneObject which has the capabilities of adjusting its
        acceleration and angle of momemtum.  It also is capable of creating new objects including
        bullets, rockets, cannon shells, and bombs when the ui detects the user pressing the appropriate 
        keys.

**/



#ifndef PLANE_H
#define PLANE_H

#include "airborneobject.h"
#include "bullet.h"
#include <stdio.h>
#include <list>

/** boundaries for the pitch of the plane **/
const float MIN_PITCH = -0.9;  
const float MAX_PITCH = 0.9;
/** limits to the maximum increments the plane can pitch **/
const float PITCH_INCREMENT = 0.1;
const float PITCH_DECREMENT = 1.0;
/** default value for pitch, velocity and stalling vel **/
const float PITCH_CONSTANT = 0.0;
const float SPEED_CONSTANT = 10;
const float STALLING_VELX = 5;
/** default values for throttle, the number of bullets, cannonshells, bombs, rockets the plane holds
	as well as the default health value **/
const int DEFAULT_THROTTLE = 0.9;
const int DEFAULT_BULLETS = 300;
const int DEFAULT_CANNONSHELLS = 50;
const int DEFAULT_ROCKETS = 0;
const int DEFAULT_BOMBS = 0;
const int DEFAULT_HEALTH = 100;
/** bullet Bitmap is declared and defined elsewhere in the project **/
extern ALLEGRO_BITMAP* bulletBitmap;


class Plane :
	public AirborneObject
{
public:
	/** only constructor must pass a bitmap **/
	Plane(ALLEGRO_BITMAP&);
	~Plane(void);
	/** getters and setters FINISH LATER**/
	int getRockets(){ return rockets;}
	int adjustRockets(int delta){ rockets += delta;}
	
	/** update member function **/
	void update(void);
	/** increase/decrease pitch member function
		param bool: true - pitch up 
	**/
	void adjustPitch(bool);
	/** set pitch to zero **/
	void resetPitch(void);
	/** adjust throttle by int amount **/
	void adjustThrottle(int);
	/** level out the plane over time **/
	void stallRoutine(void);
	/** ensure plane velocities are within limits **/
	virtual void checkVelocityBarriers();
	/** fireBullets and add them to the list passed by reference **/
	Bullet* fireBullets();
	

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
