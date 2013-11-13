///**
//	AIGround class is the ai controller for ground troops that will modify the ground data models 
//	Derived from the GameObject base class 
//	
//**/
//
//#ifndef AIGROUND_H
//#define AIGROUND_H
//
//#include "plane.h"
//#include "gameobject.h"
//#include "Reload.h"
//
//extern Plane* playerPlane;
//extern float RADIAN_TO_ANGLE;
//
//class AiGround :
//	public GameObject
//{
//public:
//	AiGround(ALLEGRO_BITMAP&);
//	~AiGround(void);
//	void processUpdate(void);
//	float getX(void);
//	float getY(void);
//	int getWeaponChoice(void);
//	Reload* getReload(void);
//	Bullet* firedShots(void);
//
//private:
//	void chooseDirection(void);
//	void chooseWeapon(void);
//	void chooseWeapon(int);
//	
//	int fireKey;
//	float firingAngle;
//	float x, y;
//	Reload* reload;
//};
//
//
//#endif
//
