#ifndef AOEPROJECTILE_H
#define AOEPROJECTILE_H

#include "ProjectileObject.h"

class AOEProjectile :
	public ProjectileObject
{
public:
	AOEProjectile(ALLEGRO_BITMAP&);
	~AOEProjectile(void);
	
	//void setSourceObject(CharacterObject&);
	void setDirection(float);
	virtual void update(void);
	virtual void checkVelocityBarriers(void);
	void startExplosion();


//private:
	CharacterObject sourceOfProjectile;
	float engineStrength;
	bool explode;
};

#endif