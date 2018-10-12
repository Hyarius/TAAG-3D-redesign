#include "template.h"

#ifndef M_PI
   #define M_PI 3.14159265358979323846
#endif

using namespace std;

double				degree_to_radius(double angle)
{
	return ((double)(((double)angle) * M_PI / (double)180));
}

double				radius_to_degree(double radian)
{
	return ((double)((double)(radian * 180) / M_PI));
}

string				convert_double(double i, int n)
{
	ostringstream out;

	if (i > 0 || i < -1)
		n++;
    out << setprecision(n) << i;
    return out.str();
}

string 				convert_int(int i)
{
	ostringstream out;

    out << i;
    return out.str();
}

t_point				screen_to_opengl(t_vect source)
{
	matrice		tra_matrice = matrice(T, -1.0, -1.0, 0);
	t_vertex	result = t_vertex((double)source.x / ((double)get_win_size().x / 2), (double)source.y / ((double)get_win_size().y / 2), 0.0);

	result = tra_matrice * result;

	return (t_point(result.x, -result.y));
}