#include "taag.h"

s_camera::s_camera()
{
	angle = t_vertex(0, 0, 0);
	axe_x = t_vertex(1, 0, 0);
	axe_y = t_vertex(0, 1, 0);
	axe_z = t_vertex(0, 0, 1);
	offset = get_win_size() / 2;
	target = t_vect(0, 0);
	sprite_unit = t_vertex(1, 1, 1);
	zoom = 1;
}

s_camera::s_camera(int angle_x, int angle_y, int angle_z)
{
	angle = t_vertex(angle_x, angle_y, angle_z);
	calc_axe();
	offset = get_win_size() / 2;
	target = t_vect(0, 0);
	sprite_unit = t_vertex(1, 1, 1);
	zoom = 1;
}

void				s_camera::calc_axe()
{
	matrice 		rot_mat = matrice(R, angle.x, angle.y, angle.z);

	axe_x = t_vertex(1, 0, 0);
	axe_y = t_vertex(0, 1, 0);
	axe_z = t_vertex(0, 0, 1);

	axe_x = rot_mat * axe_x;
	axe_y = rot_mat * axe_y;
	axe_z = rot_mat * axe_z;
}

void				s_camera::camera_move_target(int motion_x, int motion_y)
{
	double		x, y;

	double delta = (-axe_x.x) * (axe_y.y) - axe_y.x * (-axe_x.y);

	if (delta != 0)
	{
		x = (motion_x * axe_y.y - axe_y.x * motion_y) / delta;
		y = ((-axe_x.x) * motion_y - motion_x * (-axe_x.y)) / delta;
	}
	else
		error_exit("Error on camera_motion", 15642);

	target.x += x;
	target.y += y;
}


t_vect				s_camera::coord_to_vect(double x, double y, double z)
{
	return (vertex_to_vect(t_vertex(x, y, z)));
}

t_vect				s_camera::coord_to_vect(int x, int y, int z)
{
	return (vertex_to_vect(t_vertex(x, y, z)));
}

t_vect				s_camera::vertex_to_vect(t_vertex source)
{
	t_vertex	result;

	result = t_vertex(((source.x - this->target.x) * this->axe_x.x) - ((source.y - this->target.y) * this->axe_y.x),
						((source.x - this->target.x) * this->axe_x.y) - ((source.y - this->target.y) * this->axe_y.y), source.z);

	matrice tra_matrice = matrice(T, offset.x, offset.y - ((source.z - 1) * (this->sprite_unit.z  * this->zoom)), 0.0);

	result = tra_matrice * result;

	return (t_vect((int)result.x, (int)result.y));
}
