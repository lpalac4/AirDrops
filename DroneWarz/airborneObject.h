#ifndef AIRBORNEOBJECT_H
#define AIRBORNEOBJECT_H


#include "gameobject.h"
#include <math.h>

static const float PI = 3.14159265;
static const float GRAVITY = 9.0;

const float TERMINAL_VELY = 10.0;

class AirborneObject : 
	public GameObject
{
public:
	AirborneObject(ALLEGRO_BITMAP& );
	virtual ~AirborneObject(void);
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
	
};

#endif

