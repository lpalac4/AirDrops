#ifndef AIGROUND_H
#define AIGROUND_H



#include "gameobject.h"

class AiGround :
	public GameObject
{
public:
	AiGround(ALLEGRO_BITMAP&);
	~AiGround(void);
	void processUpdate(void);

private:
	void chooseDirection(void);
	void chooseWeapon(void);
	void chooseWeapon(int);
	int fireKey;
};


#endif

