#ifndef BOUNDARYBOX_H
#define BOUNDARYBOX_H


#include <tuple>
#include <cmath>

class BoundaryBox
{
public:
	BoundaryBox(void);
	BoundaryBox(float&,float&,float,float);
	~BoundaryBox(void);

	float minX, minY, maxX, maxY, width, height, centerX, centerY;
	void updateBoundaryBox(float, float);
	
	bool checkIfOverlap(BoundaryBox&);

};

#endif