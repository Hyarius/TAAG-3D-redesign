#include "template.h"

void			draw_image(SDL_Surface *surface, t_vect tl, t_vect tr, t_vect dl, t_vect dr)
{
	t_point		tl_opengl = screen_to_opengl(tl);
	t_point		tr_opengl = screen_to_opengl(tr);
	t_point		dl_opengl = screen_to_opengl(dl);
	t_point		dr_opengl = screen_to_opengl(dr);

	glBindTexture(GL_TEXTURE_2D, get_texture_id());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);

	t_triangle a = t_triangle(t_point(tl_opengl.x, tl_opengl.y, 0.0, 0.0),
		t_point(tr_opengl.x, tr_opengl.y, 1.0, 0.0),
		t_point(dl_opengl.x, dl_opengl.y, 0.0, 1.0));

	t_triangle b = t_triangle(t_point(dl_opengl.x, dl_opengl.y, 0.0, 1.0),
		t_point(dr_opengl.x, dr_opengl.y, 1.0, 1.0),
		t_point(tr_opengl.x, tr_opengl.y, 1.0, 0.0));

	draw_triangle_texture(a);
	draw_triangle_texture(b);
}

void			draw_image(SDL_Surface *surface, t_vect coord, t_vect size)
{
	draw_image(surface, t_vect(coord.x, coord.y), t_vect(coord.x + size.x, coord.y), t_vect(coord.x, coord.y + size.y), t_vect(coord.x + size.x, coord.y + size.y));
}

void			draw_image(SDL_Surface *surface, t_vect coord)
{
	draw_image(surface, t_vect(coord.x, coord.y), t_vect(coord.x + surface->w, coord.y), t_vect(coord.x, coord.y + surface->h), t_vect(coord.x + surface->w, coord.y + surface->h));
}

void			draw_image(t_vect tl, t_vect tr, t_vect dl, t_vect dr)
{
	t_point		tl_opengl = screen_to_opengl(tl);
	t_point		tr_opengl = screen_to_opengl(tr);
	t_point		dl_opengl = screen_to_opengl(dl);
	t_point		dr_opengl = screen_to_opengl(dr);

	t_triangle a = t_triangle(t_point(tl_opengl.x, tl_opengl.y, 0.0, 0.0),
		t_point(tr_opengl.x, tr_opengl.y, 1.0, 0.0),
		t_point(dl_opengl.x, dl_opengl.y, 0.0, 1.0));

	t_triangle b = t_triangle(t_point(dl_opengl.x, dl_opengl.y, 0.0, 1.0),
		t_point(dr_opengl.x, dr_opengl.y, 1.0, 1.0),
		t_point(tr_opengl.x, tr_opengl.y, 1.0, 0.0));

	draw_triangle_texture(a);
	draw_triangle_texture(b);
}

void			draw_image(t_vect coord, t_vect size)
{
	draw_image(t_vect(coord.x, coord.y), t_vect(coord.x + size.x, coord.y), t_vect(coord.x, coord.y + size.y), t_vect(coord.x + size.x, coord.y + size.y));
}

void			draw_centred_image(SDL_Surface *surface, t_vect coord, t_vect size)
{
	draw_image(surface, t_vect(coord.x - size.x / 2, coord.y - size.y / 2), size);
}

void			draw_centred_image(SDL_Surface *surface, t_vect coord)
{
	draw_image(surface, t_vect(coord.x - surface->w / 2, coord.y - surface->h / 2));
}
