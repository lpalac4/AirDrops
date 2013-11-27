/*
	The Reload class models the reload mechanism in a plane/ship.  Every weapon will have its own 
	reload class to track its projectile output.
	@author Luis Palacios
*/

#ifndef RELOAD_H
#define RELOAD_H

#include <time.h>


class Reload
{
public:
	Reload(void);
	Reload(unsigned int);
	~Reload(void);
	
	void firedShot(void);
	bool checkIfReady(void);

private:
	time_t lastFired;
	time_t currentTime;
	time_t reloadTime;
	bool readyToFire;
};


#endif

