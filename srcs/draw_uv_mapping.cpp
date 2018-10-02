#include "template.h"

void			draw_uv_texture(tileset *tile, int sprite, t_vect tl, t_vect tr, t_vect dl, t_vect dr)
{
	t_point		tl_opengl = screen_to_opengl(tl);
	t_point		tr_opengl = screen_to_opengl(tr);
	t_point		dl_opengl = screen_to_opengl(dl);
	t_point		dr_opengl = screen_to_opengl(dr);

	SDL_Rect	*img = tile->get_rect(sprite);

	double x1, y1, x2, y2;

	x1 = (img->x) / (double)tile->get_surface()->w;
	y1 = (img->y) / (double)tile->get_surface()->h;
	x2 = (img->x + img->w) / (double)tile->get_surface()->w;
	y2 = (img->y + img->h) / (double)tile->get_surface()->h;

	t_triangle a = t_triangle(t_point(dl_opengl.x, dl_opengl.y, x1, y1),
		t_point(dr_opengl.x, dr_opengl.y, x2, y1),
		t_point(tl_opengl.x, tl_opengl.y, x1, y2));

	t_triangle b = t_triangle(t_point(tl_opengl.x, tl_opengl.y, x1, y2),
		t_point(tr_opengl.x, tr_opengl.y, x2, y2),
		t_point(dr_opengl.x, dr_opengl.y, x2, y1));

	draw_triangle_texture(a);
	draw_triangle_texture(b);
}
