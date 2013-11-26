#include "BoundaryBox.h"


BoundaryBox::BoundaryBox()
{
}

BoundaryBox::BoundaryBox(float& min_x, float& min_y, float w, float h)
{
	minX = min_x;
	minY = min_y;
	width = w;
	height = h;
	centerX = minY + width / 2;
	centerY = minY + height / 2;
	maxX = min_x + width;
	maxY = min_y + height;
}


BoundaryBox::~BoundaryBox()
{
}

void BoundaryBox::updateBoundaryBox(float a, float b){
	minX = a;
	minY = b;
	centerX = minX + width / 2;
	centerY = minY + height / 2;
	maxX = a + width;
	maxY = b + height;
}

bool BoundaryBox::checkIfOverlap(BoundaryBox& box)
{
	if (minX > box.minX && minX < box.maxX){
		if (minY > box.minY && minY < box.maxY)
			return true;
		if (maxY > box.minY && maxY < box.maxY)
			return true;
	}
	if (maxX > box.minX && maxX < box.maxX){
		if (minY > box.minY && minY < box.maxY)
			return true;
		if (maxY > box.minY && maxY < box.maxY)
			return true;
	}
	 
	return false;
}