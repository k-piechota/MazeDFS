#include "Cell.h"

Cell::Cell(int x, int y)
{
	this->x = x;
	this->y = y;
}

int Cell::get_x()
{
	return this->x;
}

int Cell::get_y()
{
	return this->y;
}