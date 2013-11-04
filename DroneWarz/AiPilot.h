#ifndef AIPILOT_H
#define AIPILOT_H


#include "plane.h"

extern float RADIAN_TO_ANGLE;
extern Plane* playerPlane;

class AiPilot :
	public Plane
{
public:
	AiPilot(ALLEGRO_BITMAP&);
	~AiPilot(void);
	void processUpdate();
	virtual void checkVelocityBarriers();
	
private:

	int fireKey;
	void chooseDirection(void);
	void chooseThrottle(void);
	void chooseWeapon(void);
	void chooseWeapon(int);


};

#endif