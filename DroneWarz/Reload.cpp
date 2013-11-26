#include "Reload.h"

Reload::Reload(void)
{
	lastFired;
	currentTime;
	reloadTime = 2;
	readyToFire = true;
};

Reload::Reload(unsigned int duration){
	reloadTime = duration;
	readyToFire = true;

}

Reload::~Reload(void)
{

}

bool Reload::checkIfReady(void){
	time(&currentTime);
	if(readyToFire || difftime(currentTime, lastFired) > 2.0){
		readyToFire = true;
		return true;
	}
	
	return false;
}

void Reload::firedShot(void){
	if(readyToFire){
		readyToFire = false;
		time(&lastFired);
	
	}

	return;
}
