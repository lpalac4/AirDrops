/*
	ProjectileObject inherits from CharacterObject all necessary functions and members to create 
	a 2D object but also maintains data on the origin of the projectile.
	@author Luis Palacios
*/

#ifndef PROJECTILEOBJECT_H
#define PROJECTILEOBJECT_H

#include "CharacterObject.h"
#include <vector>
#include <utility>

class ProjectileObject :
	public CharacterObject
{
public:
	ProjectileObject(ALLEGRO_BITMAP&);
	~ProjectileObject(void);
	
	virtual void update(void);
	virtual void checkVelocityBarriers();
	void setSourceObject(CharacterObject&, bool);
	void setDirection(float);
	
	bool trailShow;
	bool playerProjectile;
	float engineStrength;
	float direction;
	CharacterObject* sourceOfProjectile;
	std::vector<std::pair<float,float>>* trailList;
	

	
};

#endif
