#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "airborneObject.h"
#include <list>
#include <utility>



class Bullet :
	public AirborneObject
{
public:
	Bullet(ALLEGRO_BITMAP&);
	~Bullet(void);
	void addTrailMarker();
	void update(void);
	virtual void checkVelocityBarriers();
	void setSourceObject(AirborneObject&);
	void setDirection(float);

//protected:
	struct TrailPairs{
		int x,y;
	};
	
	float engineStrength;
	float direction;
	GameObject sourceOfProjectile;
	std::list<TrailPairs> trailQueue;
	bool trailShow;
	
};

#endif
