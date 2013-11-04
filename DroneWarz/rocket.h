#ifndef ROCKET_H
#define ROCKET_H


#include "bullet.h"
#include <vector>


class Rocket :
	public Bullet
{
public:
	Rocket(ALLEGRO_BITMAP&);
	~Rocket(void);

	void addTrailMarker();
	virtual void update(void);
	virtual void checkVelocityBarriers();
	void setSourceObject(AirborneObject&);
	void setDirection(float);

//protected:
	
	float engineStrength;
	float direction;
	GameObject sourceOfProjectile;
	//std::vector<std::pair<float,float>>* trailList;
	
};

#endif