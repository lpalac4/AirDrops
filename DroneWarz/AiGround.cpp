#include "AiGround.h"


AiGround::AiGround(ALLEGRO_BITMAP& bitmap) : GameObject(bitmap)
{
	fireKey = NULL;
}


AiGround::~AiGround()
{

}

void AiGround::processUpdate(){
	chooseDirection();
	chooseWeapon();

}

void AiGround::chooseDirection(){

}

void AiGround::chooseWeapon(){
	fireKey = 1;
}

void AiGround::chooseWeapon(int w){
	fireKey = w;
}


