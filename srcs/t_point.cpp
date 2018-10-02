#include "template.h"

s_point::s_point()
{
	x = 0;
	y = 0;
}

s_point::s_point(double p_x, double p_y, double p_a, double p_b, double p_c)
{
	this->x = p_x;
	this->y = p_y;
	this->a = p_a;
	this->b = p_b;
	this->c = p_c;
}

s_point::s_point(double p_x, double p_y, double p_a, double p_b)
{
	this->x = p_x;
	this->y = p_y;
	this->a = p_a;
	this->b = p_b;
	this->c = 0;
}

s_point::s_point(double p_x, double p_y)
{
	this->x = p_x;
	this->y = p_y;
	this->a = 0;
	this->b = 0;
	this->c = 0;
}