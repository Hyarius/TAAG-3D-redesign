#include "template.h"

s_data::s_data()
{

}

s_data::s_data(vector<void *> p_data)
{
	this->data = p_data;
}

s_data::s_data(int nb_param, ...)
{
	va_list list_param;
    va_start(list_param, nb_param);
	int i = 0;

	while (i < nb_param)
	{
		this->data.push_back(va_arg(list_param, void *));
		i++;
	}
	va_end(list_param);
}

void		s_data::operator = (vector<void *> p_data)
{
	this->data = p_data;
}

void		s_data::operator = (void *p_data)
{
	this->data.clear();
	this->data.push_back(p_data);
}

void		s_data::operator + (vector<void *> p_data)
{
	size_t i = 0;

	i = 0;
	while (i < p_data.size())
	{
		this->data.push_back(p_data[i]);
		i++;
	}
}

void		s_data::operator + (void *p_ptr)
{
	this->data.push_back(p_ptr);
}
