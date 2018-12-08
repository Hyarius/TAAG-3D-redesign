#include "taag.h"

s_camera::s_camera()
{
	angle = t_vertex(0, 0, 0);
	offset = get_win_size() / 2;
	target = t_vect(0, 0);
	sprite_unit = t_vertex(60, 60, 30);
	zoom = 1;
	calc_axe();
}

s_camera::s_camera(int angle_x, int angle_y, int angle_z)
{
	angle = t_vertex(angle_x, angle_y, angle_z);
	offset = get_win_size() / 2;
	target = t_vect(0, 0);
	sprite_unit = t_vertex(60, 60, 45);
	zoom = 1;
	calc_axe();
}

void				s_camera::calc_axe()
{
	matrice 		rot_mat = matrice(R, angle.x, angle.y, angle.z);
	matrice			sca_matrice = matrice(S, zoom, zoom, zoom);

	axe_x = t_vertex(sprite_unit.x, 0.0, 0.0);
	axe_y = t_vertex(0.0, -sprite_unit.y, 0.0);
	axe_z = t_vertex(0.0, 0.0, sprite_unit.z);

	axe_x = sca_matrice * (rot_mat * axe_x);
	axe_y = sca_matrice * (rot_mat * axe_y);
	axe_z = sca_matrice * (rot_mat * axe_z);
}

void				s_camera::handle_move(int motion_x, int motion_y)
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

void				s_camera::handle_rot(double delta)
{
	int			result;

	if (angle.z + delta > 360)
		angle.z = angle.z + delta - 360;
	else if (angle.z + delta < 0)
		angle.z = angle.z + delta + 360;
	else
		angle.z = (angle.z + delta);

	calc_axe();
}

void				s_camera::handle_vertical_rot(double delta)
{
	int			result;

	if (angle.x + delta < 0)
		angle.x = 0;
	else if (angle.x + delta > 90)
		angle.x = 90;
	else
		angle.x = angle.x + delta;
	calc_axe();
}

void				s_camera::handle_zoom(double modif)
{
	zoom *= modif;

	if (zoom < 0.2)
		zoom = 0.2;
	else if (zoom > 15)
		zoom = 15;

	calc_axe();
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

	result = t_vertex(((source.x - target.x) * axe_x.x) - ((source.y - target.y) * axe_y.x),
					  ((source.x - target.x) * axe_x.y) - ((source.y - target.y) * axe_y.y), source.z);

	matrice tra_matrice = matrice(T, offset.x, offset.y + ((source.z - 1) * axe_z.y), 0.0);

	result = tra_matrice * result;

	return (t_vect((int)result.x, (int)result.y));
}
