#include "template.h"

s_data::s_data()
{
	this->data = NULL;
}

s_data::s_data(void **p_data)
{
	this->data = p_data;
}

void		s_data::operator = (void **p_data)
{
	this->data = p_data;
}
