//#include "TankShell.h"
//
//
//TankShell::TankShell(ALLEGRO_BITMAP& bitmap) : GameObject(bitmap) 
//{
//	engineStrength = 200.00;
//	SPEED_BARRIER_X = 100.0;
//	SPEED_BARRIER_Y = -100.0;
//	TERMINAL_VELY = 100.0;
//	MAX_ALTITUDE = -5000.0;
//	direction = 0.0;
//	velx = 0;
//	vely = 0;
//	trailShow = true;
//	trailList = new std::vector<std::pair<float,float>>();
//}
//
//void TankShell::setSourceObject(AiGround& origin){
//	sourceOfProjectile = origin;
//	x = origin.x + (al_get_bitmap_width(origin.bitmapObject)/2);
//	y = origin.y + (al_get_bitmap_height(origin.bitmapObject)/2);
//
//}
//
//void TankShell::setDirection(float dir){
//	direction = dir;
//}
//
//
//
//TankShell::~TankShell(void)
//{
//	delete trailList;
//}
//
//void TankShell::addTrailMarker(){
//	std::pair<float, float>* trail = new std::pair<float, float>();
//	trail->first = x;
//	trail->second = y;
//
//	if(trailList && trailList->size() > 3){
//			trailList->erase(trailList->begin());
//		}
//	
//	trailList->push_back(*trail);
//}
//
//void TankShell::update(void){
//	
//	//if(engineStrength > 1.0)
//	//	engineStrength -= 1.0;
//	//else{
//	//	engineStrength = 0;
//	//}
//
//	accelx = (engineStrength * cos((direction * PI) / 180.0));
//	accely = -(engineStrength * sin((direction * PI) / 180.0)) + GRAVITY;
//	if(trailShow){
//		addTrailMarker();
//	}
//	
//	float oldvelx = velx;
//	float oldvely = vely;
//
//	if(y > (0))
//		flying = false;
//	
//	velx += accelx;
//	vely += accely;
//	
//	if(!flying) vely = velx = 0;
//	
//	/** check to make sure object is flying faster than the speed of light lol **/
//	checkVelocityBarriers();
//
//	/** make sure object isnt falling faster than terminal velocity **/
//	if(vely > TERMINAL_VELY) vely = TERMINAL_VELY;
//
//	x += (velx + oldvelx)/2;
//	y += (vely + oldvely)/2;
//
//	/** check for maximum altitude **/
//	if(y < MAX_ALTITUDE)
//		y = MAX_ALTITUDE;
//
//}
