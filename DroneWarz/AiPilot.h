#ifndef AIPILOT_H
#define AIPILOT_H


#include "plane.h"
#include "Reload.h"
#include <math.h>

extern float RADIAN_TO_ANGLE;
extern Plane* playerPlane;
static float FIRE_RANGE = SCREEN_W >> 1;

class AiPilot :
	public Plane
{
public:
	AiPilot(ALLEGRO_BITMAP&);
	~AiPilot(void);
	void processUpdate(void);
	virtual void checkVelocityBarriers();
	Reload* getReload(void);
	Reload* reload;
	bool inFireRange;

//private:

	int fireKey;
	void chooseDirection(void);
	void chooseThrottle(void);
	void chooseWeapon(void);
	void chooseWeapon(int);


};

#endif