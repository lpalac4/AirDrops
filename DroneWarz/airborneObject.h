#ifndef AIRBORNEOBJECT_H
#define AIRBORNEOBJECT_H


#include "gameobject.h"
#include <math.h>

static const float PI = 3.14159265;
static const float GRAVITY = 0.5;



class AirborneObject : 
	public GameObject
{
public:
	AirborneObject(ALLEGRO_BITMAP&);
	AirborneObject();
	~AirborneObject(void);
	void update(void);
	virtual void checkVelocityBarriers();

//protected:
	float x;
	float y;
	float velx, vely;
	bool flying;
	float accelx, accely;
	float SPEED_BARRIER_X;
	float SPEED_BARRIER_Y;
	float direction;
	float TERMINAL_VELY;
	float MAX_ALTITUDE;
	bool isAi;
	
};

#endif

