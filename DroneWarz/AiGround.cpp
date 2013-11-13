//#include "AiGround.h"
//
//
//AiGround::AiGround(ALLEGRO_BITMAP& bitmap) : GameObject(bitmap)
//{
//	fireKey = NULL;
//	x = playerPlane->x + SCREEN_W;
//	y = 0;//SCREEN_H;
//	firingAngle = 0;
//	reload = new Reload();
//}
//
//
//AiGround::~AiGround()
//{
//	delete reload;
//}
//
//void AiGround::processUpdate(){
//	if(x < playerPlane->x - SCREEN_W/2)
//		x = playerPlane->x + SCREEN_W;
//	chooseDirection();
//	chooseWeapon();
//	
//}
//
//void AiGround::chooseDirection(){
//	float diffX = x - playerPlane->x;
//	float diffY = y - playerPlane->y;
//	firingAngle = tan((diffY/diffX));
//	firingAngle *= 180/PI;
//	firingAngle = (180 - firingAngle);
//}
//
//Bullet* AiGround::firedShots(){
//	reload->firedShot();
//	Bullet* newBullet = new Bullet((*bulletBitmap));
//	newBullet->setDirection(firingAngle);
//	return newBullet;
//}
//
//
//void AiGround::chooseWeapon(){
//	fireKey = 1;
//}
//
//void AiGround::chooseWeapon(int w){
//	fireKey = w;
//}
//
//float AiGround::getX(void){
//	return x;
//}
//
//float AiGround::getY(void){
//	return y;
//}
//
//int AiGround::getWeaponChoice(void){
//	return fireKey;
//}
//
//Reload* AiGround::getReload(void){
//	return reload;
//}
//
