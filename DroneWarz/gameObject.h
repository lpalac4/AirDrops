/*
	GameObject was created in an effort to encapsulate all Allegro bitmap variables, which may 
	turn out to be not necessary in the end, but that's what learning a new library is about.
	@author Luis Palacios
*/
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

	ALLEGRO_BITMAP* bitmapObject;

};

#endif

