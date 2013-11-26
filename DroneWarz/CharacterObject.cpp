#include "CharacterObject.h"


CharacterObject::CharacterObject(ALLEGRO_BITMAP& bitmap) : GameObject(bitmap)
{
	TERMINAL_VELY = 3.0;
	MAX_ALTITUDE = -5000.0;
	x = 0; 
	y = -300;
	velx = vely = 0;
	grounded = false;
	accelx = accely = 0;
	direction = 0;
	isAi = false;
	boundaryBox = new BoundaryBox(x, y, al_get_bitmap_width(&bitmap), al_get_bitmap_height(&bitmap));
	hasExploded = false;
}

CharacterObject::CharacterObject(){

}

CharacterObject::~CharacterObject(void)
{
	
}

void CharacterObject::update(void)
{
	float oldvelx = velx;
	float oldvely = vely;

	if(y > 5)
		grounded = true;
	
	velx += accelx;
	vely += accely;
	
	if(grounded){
		y = 5;
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

	boundaryBox->updateBoundaryBox(x, y);

}

void CharacterObject::checkVelocityBarriers(){
	/** handled by subclass **/
}

void CharacterObject::setIsGrounded(bool isGround){
	grounded = isGround;
}

bool CharacterObject::getIsGrounded(){
	return grounded;
}

bool CharacterObject::checkForCollision(CharacterObject& otherOb)
{
	return boundaryBox->checkIfOverlap(*(otherOb.boundaryBox));
}

void CharacterObject::explode()
{
	bitmapObject = explosion;
	hasExploded = true;
}

bool CharacterObject::comparator(CharacterObject* a, CharacterObject* b)
{
	return a->x > b->x;
}

bool CharacterObject::isEqual(CharacterObject& otherOb)
{
	if (this == NULL)
		return false;
	if (otherOb.x == x && otherOb.y == y){
		return true;
	}

	return false;
}


