#include "gameObject.h"

GameObject::GameObject(void){
}

GameObject::GameObject(ALLEGRO_BITMAP& bitmap)
{
	bitmapObject = &bitmap;
}


GameObject::~GameObject(void)
{
	delete this;
}
