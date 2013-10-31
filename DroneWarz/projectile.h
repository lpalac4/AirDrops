#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "airborneobject.h"
#include <queue>
#include <utility>



class Projectile :
	public AirborneObject
{
public:
	Projectile(ALLEGRO_BITMAP&);
	virtual ~Projectile(void);
	void addTrailMarker(int, int);
	void update(void);
	virtual void checkVelocityBarriers();
	void setSourceObject(AirborneObject&);

//protected:
	struct TrailPairs{
		int x,y;
	};
	
	float engineStrength;
	float direction;
	GameObject sourceOfProjectile;
	std::queue<TrailPairs> trailQueue;
	

};

#endif
