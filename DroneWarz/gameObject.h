#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "allegro5\allegro.h"

extern const int SCREEN_W;
extern const int SCREEN_H;
extern ALLEGRO_BITMAP* explosion;

class GameObject
{
public:
	GameObject(ALLEGRO_BITMAP&);
	GameObject(void);
	~GameObject(void);

//protected:
	ALLEGRO_BITMAP* bitmapObject;

};

#endif

