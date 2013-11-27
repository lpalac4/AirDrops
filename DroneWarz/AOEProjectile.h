/*
	The AOEProjectile class represents a weapon that does aoe damage ie.Bomb and derives from the Projectile class
	necessary functions.
	@author Luis Palacios.
*/

#ifndef AOEPROJECTILE_H
#define AOEPROJECTILE_H

#include "ProjectileObject.h"

class AOEProjectile :
	public ProjectileObject
{
public:
	AOEProjectile(ALLEGRO_BITMAP&);
	~AOEProjectile(void);
	
	void setDirection(float);
	virtual void update(void);
	virtual void checkVelocityBarriers(void);
	void startExplosion();

	CharacterObject sourceOfProjectile;
	float engineStrength;
	bool explode;
};

#endif