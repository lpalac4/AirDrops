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
	/*bool isEqual(CharacterObject*);*/
	void setSourceObject(CharacterObject&, bool);
	void setDirection(float);
	
//protected:
	bool trailShow;
	bool playerProjectile;
	float engineStrength;
	float direction;
	CharacterObject* sourceOfProjectile;
	std::vector<std::pair<float,float>>* trailList;
	

	
};

#endif
