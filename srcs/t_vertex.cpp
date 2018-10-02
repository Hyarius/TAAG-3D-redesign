#include "template.h"

s_vertex::s_vertex(int p_x, int p_y, int p_z)
{
	this->x = p_x;
	this->y = p_y;
	this->z = p_z;
}

s_vertex::s_vertex()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

s_f_vertex::s_f_vertex(double p_x, double p_y, double p_z)
{
	this->x = p_x;
	this->y = p_y;
	this->z = p_z;
}

s_f_vertex::s_f_vertex()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}
