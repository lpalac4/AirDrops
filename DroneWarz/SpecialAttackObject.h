/*
	The SpecialAttack class represents a weapon much more dramatic then a standard projectile
	in that it maintains a trail of its most recent positions, and should also allow for more 
	implementations of other such 'effects'.
	@author Luis Palacios
*/

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

	float engineStrength;
	float direction;
	GameObject sourceOfProjectile;
	
};

#endif