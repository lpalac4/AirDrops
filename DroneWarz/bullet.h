#ifndef BULLET_H
#define BULLET_H

#include "airborneObject.h"
//#include "AiGround.h"
#include <vector>
#include <utility>



class Bullet :
	public AirborneObject
{
public:
	Bullet(ALLEGRO_BITMAP&);
	~Bullet(void);
	
	virtual void update(void);
	virtual void checkVelocityBarriers();
	void setSourceObject(AirborneObject&);
//	void setSourceObject(AiGround&);
	void setDirection(float);
	
//protected:
	bool trailShow;
	float engineStrength;
	float direction;
	GameObject sourceOfProjectile;
	std::vector<std::pair<float,float>>* trailList;
	

	
};

#endif
