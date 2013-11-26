#ifndef SPECIALATTACKOBJECT_H
#define SPECIALATTACKOBJECT_H


#include "ProjectileObject.h"
#include <vector>


class SpecialAttackObject :
	public ProjectileObject
{
public:
	SpecialAttackObject(ALLEGRO_BITMAP&);
	~SpecialAttackObject(void);

	void addTrailMarker();
	virtual void update(void);
	virtual void checkVelocityBarriers();
	
	void setDirection(float);

//protected:
	
	float engineStrength;
	float direction;
	GameObject sourceOfProjectile;
	
};

#endif