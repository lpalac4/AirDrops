#ifndef CHARACTEROBJECT_H
#define CHARACTEROBJECT_H


#include "GameObject.h"
#include "BoundaryBox.h"
#include <math.h>

static const float PI = 3.14159265;
static const float GRAVITY = 0.5;



class CharacterObject : 
	public GameObject
{
public:
	CharacterObject(ALLEGRO_BITMAP&);
	CharacterObject();
	~CharacterObject(void);
	virtual void update(void);
	virtual void checkVelocityBarriers();
	bool checkForCollision(CharacterObject&);
	void explode(void);
	static bool comparator(CharacterObject*, CharacterObject*);

	float x;
	float y;
	float velx, vely;
	float accelx, accely;
	float SPEED_BARRIER_X;
	float SPEED_BARRIER_Y;
	float direction;
	float TERMINAL_VELY;
	float MAX_ALTITUDE;
	bool isAi;
	void setIsGrounded(bool);
	bool getIsGrounded(void);
	bool hasExploded;
	bool isEqual(CharacterObject&);
	BoundaryBox* boundaryBox;

	bool grounded;
	
};

#endif

