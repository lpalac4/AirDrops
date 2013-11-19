#include "airborneObject.h"


AirborneObject::AirborneObject(ALLEGRO_BITMAP& bitmap) : GameObject(bitmap)
{
	TERMINAL_VELY = 3.0;
	MAX_ALTITUDE = -5000.0;
	x = 0; //SCREEN_W / 2.5 - al_get_bitmap_width(bitmapObject) / 2.0;
	y = -300; //SCREEN_H / 2.5 - al_get_bitmap_height(bitmapObject) / 2.0;
		
	velx = vely = 0;
	grounded = false;
	accelx = accely = 0;
	direction = 0;
	isAi = false;
}

AirborneObject::AirborneObject(){

}

AirborneObject::~AirborneObject(void)
{
	
}

void AirborneObject::update(void)
{
	float oldvelx = velx;
	float oldvely = vely;

	if(y > (0))
		grounded = true;
	
	velx += accelx;
	vely += accely;
	
	if(grounded){
		y = 0;
		accelx = 0;
		accely = 0;
		vely = 0;
		velx = 0;
	}
	
	/** check to make sure object is flying faster than the speed of light lol **/
	checkVelocityBarriers();

	/** make sure object isnt falling faster than terminal velocity **/
	if(vely > TERMINAL_VELY) vely = TERMINAL_VELY;

	x += (velx + oldvelx)/2;
	y += (vely + oldvely)/2;

	/** check for maximum altitude **/
	if(y < MAX_ALTITUDE)
		y = MAX_ALTITUDE;

}

void AirborneObject::checkVelocityBarriers(){
	/** handled by subclass **/
}

void AirborneObject::setIsGrounded(bool isGround){
	grounded = isGround;
}

bool AirborneObject::getIsGrounded(){
	return grounded;
}

