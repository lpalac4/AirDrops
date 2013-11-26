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

