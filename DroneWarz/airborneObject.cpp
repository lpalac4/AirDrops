#include "airborneObject.h"


AirborneObject::AirborneObject(ALLEGRO_BITMAP& bitmap) : GameObject(bitmap)
{
	x = SCREEN_W / 2.5 - al_get_bitmap_width(bitmapObject) / 2.0;
	y = SCREEN_H / 2.5 - al_get_bitmap_height(bitmapObject) / 2.0;
		
	velx = vely = 0;
	flying = true;
	accelx = accely = 0;
}


AirborneObject::~AirborneObject(void)
{
	delete this;
}

void AirborneObject::update(void)
{
	float oldvelx = velx;
	float oldvely = vely;

	if(y > (SCREEN_H))
		flying = false;
	
	velx += accelx;
	vely += accely;
	
	if(!flying) vely = velx = 0;
	
	/** check to make sure object is flying faster than the speed of light lol **/
	checkVelocityBarriers();

	/** make sure object isnt falling faster than terminal velocity **/
	if(vely > TERMINAL_VELY) vely = TERMINAL_VELY;

	x += (velx + oldvelx)/2;
	y += (vely + oldvely)/2;

}

void AirborneObject::checkVelocityBarriers(){
	/** handled by subclass **/
}
