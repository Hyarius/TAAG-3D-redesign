#include "taag.h"

s_value::s_value()
{
	this->cur = 0;
	this->max = 0;
}

s_value::s_value(int p_max)
{
	this->cur = p_max;
	this->max = p_max;
}

s_value::s_value(int p_cur, int p_max)
{
	this->cur = p_cur;
	this->max = p_max;
}

void	s_value::operator = (int p_value)
{
	this->cur = p_value;
	this->max = p_value;
}
