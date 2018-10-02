#include "template.h"

s_vect::s_vect()
{
	this->x = 0;
	this->y = 0;
}

s_vect::s_vect(int p_x, int p_y)
{
	this->x = p_x;
	this->y = p_y;
}

s_f_vect::s_f_vect()
{
	this->x = 0;
	this->y = 0;
}

s_f_vect::s_f_vect(double p_x, double p_y)
{
	this->x = p_x;
	this->y = p_y;
}

s_vect			s_vect::operator * (int mult)
{
	t_vect result = t_vect(this->x * mult, this->y * mult);
	return (result);
}

s_vect			s_vect::operator * (double mult)
{
	t_vect result = t_vect(this->x * mult, this->y * mult);
	return (result);
}

s_vect			s_vect::operator * (s_vect mult)
{
	t_vect result = t_vect(this->x * mult.x, this->y * mult.y);
	return (result);
}

s_vect			s_vect::operator * (s_f_vect mult)
{
	t_vect result = t_vect(this->x * mult.x, this->y * mult.y);
	return (result);
}

s_vect			s_vect::operator + (int add)
{
	t_vect result = t_vect(this->x + add, this->y + add);
	return (result);
}

s_vect			s_vect::operator + (double add)
{
	t_vect result = t_vect(this->x + add, this->y + add);
	return (result);
}

s_vect			s_vect::operator + (s_vect add)
{
	t_vect result = t_vect(this->x + add.x, this->y + add.y);
	return (result);
}

s_vect			s_vect::operator + (struct s_f_vect add)
{
	t_vect result = t_vect(this->x + add.x, this->y + add.y);
	return (result);
}

s_vect			s_vect::operator / (int div)
{
	t_vect result = t_vect(this->x / div, this->y / div);
	return (result);
}

s_vect			s_vect::operator / (double div)
{
	t_vect result = t_vect(this->x / div, this->y / div);
	return (result);
}

s_vect			s_vect::operator / (s_vect div)
{
	t_vect result = t_vect(this->x / div.x, this->y / div.y);
	return (result);
}

s_vect			s_vect::operator / (struct s_f_vect div)
{
	t_vect result = t_vect(this->x / div.x, this->y / div.y);
	return (result);
}

s_vect			s_vect::operator - (int min)
{
	t_vect result = t_vect(this->x - min, this->y - min);
	return (result);
}

s_vect			s_vect::operator - (double min)
{
	t_vect result = t_vect(this->x - min, this->y - min);
	return (result);
}

s_vect			s_vect::operator - (s_vect min)
{
	t_vect result = t_vect(this->x - min.x, this->y - min.y);
	return (result);
}

s_vect			s_vect::operator - (struct s_f_vect min)
{
	t_vect result = t_vect(this->x - min.x, this->y - min.y);
	return (result);
}

s_f_vect			s_f_vect::operator * (int mult)
{
	s_f_vect result = t_f_vect(this->x * mult, this->y * mult);
	return (result);
}

s_f_vect			s_f_vect::operator * (double mult)
{
	s_f_vect result = t_f_vect(this->x * mult, this->y * mult);
	return (result);
}

s_f_vect			s_f_vect::operator * (s_vect mult)
{
	s_f_vect result = t_f_vect(this->x * mult.x, this->y * mult.y);
	return (result);
}

s_f_vect			s_f_vect::operator * (s_f_vect mult)
{
	s_f_vect result = t_f_vect(this->x * mult.x, this->y * mult.y);
	return (result);
}

s_f_vect			s_f_vect::operator + (int add)
{
	s_f_vect result = t_f_vect(this->x + add, this->y + add);
	return (result);
}

s_f_vect			s_f_vect::operator + (double add)
{
	s_f_vect result = t_f_vect(this->x + add, this->y + add);
	return (result);
}

s_f_vect			s_f_vect::operator + (s_vect add)
{
	s_f_vect result = t_f_vect(this->x + add.x, this->y + add.y);
	return (result);
}

s_f_vect			s_f_vect::operator + (struct s_f_vect add)
{
	s_f_vect result = t_f_vect(this->x + add.x, this->y + add.y);
	return (result);
}

s_f_vect			s_f_vect::operator / (int div)
{
	s_f_vect result = t_f_vect(this->x / div, this->y / div);
	return (result);
}

s_f_vect			s_f_vect::operator / (double div)
{
	s_f_vect result = t_f_vect(this->x / div, this->y / div);
	return (result);
}

s_f_vect			s_f_vect::operator / (s_vect div)
{
	s_f_vect result = t_f_vect(this->x / div.x, this->y / div.y);
	return (result);
}

s_f_vect			s_f_vect::operator / (struct s_f_vect div)
{
	s_f_vect result = t_f_vect(this->x / div.x, this->y / div.y);
	return (result);
}

s_f_vect			s_f_vect::operator - (int min)
{
	s_f_vect result = t_f_vect(this->x - min, this->y - min);
	return (result);
}

s_f_vect			s_f_vect::operator - (double min)
{
	s_f_vect result = t_f_vect(this->x - min, this->y - min);
	return (result);
}

s_f_vect			s_f_vect::operator - (s_vect min)
{
	s_f_vect result = t_f_vect(this->x - min.x, this->y - min.y);
	return (result);
}

s_f_vect			s_f_vect::operator - (struct s_f_vect min)
{
	s_f_vect result = t_f_vect(this->x - min.x, this->y - min.y);
	return (result);
}