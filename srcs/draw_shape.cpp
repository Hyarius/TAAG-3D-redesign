#include "template.h"

void			draw_rectangle(t_vect tl, t_vect tr, t_vect dl, t_vect dr, int color_type)
{
	t_point		tl_opengl = screen_to_opengl(tl);
	t_point		tr_opengl = screen_to_opengl(tr);
	t_point		dl_opengl = screen_to_opengl(dl);
	t_point		dr_opengl = screen_to_opengl(dr);

	t_color		color = get_open_color(color_type);

	t_triangle a = t_triangle(t_point(tl_opengl.x, tl_opengl.y, color.r, color.g, color.b), t_point(tr_opengl.x, tr_opengl.y, color.r, color.g, color.b), t_point(dl_opengl.x, dl_opengl.y, color.r, color.g, color.b));
	t_triangle b = t_triangle(t_point(dl_opengl.x, dl_opengl.y, color.r, color.g, color.b), t_point(dr_opengl.x, dr_opengl.y, color.r, color.g, color.b), t_point(tr_opengl.x, tr_opengl.y, color.r, color.g, color.b));

	draw_triangle_color(a, 255);
	draw_triangle_color(b, 255);
}

void			draw_rectangle(t_vect coord, t_vect size, int color_type)
{
	SDL_Surface *s;

	SDL_Color	color = get_color(color_type);

	SDL_Rect rect;

	set_sdl_rect(&rect, 0, 0, size.x, size.y);

	Uint32 rmask, gmask, bmask, amask;

	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		rmask = 0xff000000;
		gmask = 0x00ff0000;
		bmask = 0x0000ff00;
		amask = 0x000000ff;
	#else
		rmask = 0x000000ff;
		gmask = 0x0000ff00;
		bmask = 0x00ff0000;
		amask = 0xff000000;
	#endif

	s = SDL_CreateRGBSurface(0, size.x, size.y, 32, rmask, gmask, bmask, amask);

	SDL_FillRect(s, &rect, SDL_MapRGBA(s->format, color.r, color.g, color.b, 255));

	draw_image(s, coord, size);
}

void			draw_centred_rectangle(t_vect coord, t_vect size, int color_type)
{
	SDL_Surface *s;

	SDL_Color	color = get_color(color_type);

	SDL_Rect rect;

	set_sdl_rect(&rect, 0, 0, size.x, size.y);

	Uint32 rmask, gmask, bmask, amask;

	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		rmask = 0xff000000;
		gmask = 0x00ff0000;
		bmask = 0x0000ff00;
		amask = 0x000000ff;
	#else
		rmask = 0x000000ff;
		gmask = 0x0000ff00;
		bmask = 0x00ff0000;
		amask = 0xff000000;
	#endif

	s = SDL_CreateRGBSurface(0, size.x, size.y, 32, rmask, gmask, bmask, amask);

	SDL_FillRect(s, &rect, SDL_MapRGBA(s->format, color.r, color.g, color.b, 255));

	draw_centred_image(s, coord, size);
}

void			draw_alpha_rectangle(t_vect coord, t_vect size, int color_type, int alpha)
{
	SDL_Surface *s;

	SDL_Color	color = get_color(color_type);

	SDL_Rect rect;

	set_sdl_rect(&rect, 0, 0, size.x, size.y);

	Uint32 rmask, gmask, bmask, amask;

	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		rmask = 0xff000000;
		gmask = 0x00ff0000;
		bmask = 0x0000ff00;
		amask = 0x000000ff;
	#else
		rmask = 0x000000ff;
		gmask = 0x0000ff00;
		bmask = 0x00ff0000;
		amask = 0xff000000;
	#endif

	s = SDL_CreateRGBSurface(0, size.x, size.y, 32, rmask, gmask, bmask, amask);

	SDL_FillRect(s, &rect, SDL_MapRGBA(s->format, color.r, color.g, color.b, alpha));

	draw_image(s, coord, size);

}

void			draw_alpha_centred_rectangle(t_vect coord, t_vect size, int color_type, int alpha)
{
	SDL_Surface *s;

	SDL_Color	color = get_color(color_type);

	SDL_Rect rect;

	set_sdl_rect(&rect, 0, 0, size.x, size.y);

	Uint32 rmask, gmask, bmask, amask;

	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		rmask = 0xff000000;
		gmask = 0x00ff0000;
		bmask = 0x0000ff00;
		amask = 0x000000ff;
	#else
		rmask = 0x000000ff;
		gmask = 0x0000ff00;
		bmask = 0x00ff0000;
		amask = 0xff000000;
	#endif

	s = SDL_CreateRGBSurface(0, size.x, size.y, 32, rmask, gmask, bmask, amask);

	SDL_FillRect(s, &rect, SDL_MapRGBA(s->format, color.r, color.g, color.b, alpha));

	draw_centred_image(s, coord, size);

}

void			draw_border_rectangle(t_vect coord, t_vect size, int color_type, int color_type2)
{
	draw_rectangle(coord, size, color_type);
	draw_rectangle(t_vect(coord.x + BORDER, coord.y + BORDER), t_vect(size.x - BORDER * 2, size.y - BORDER * 2), color_type2);
}

void			draw_border_centred_rectangle(t_vect coord, t_vect size, int color_type, int color_type2)
{
	draw_centred_rectangle(coord, size, color_type);
	draw_centred_rectangle(coord, t_vect(size.x - BORDER * 2, size.y - BORDER * 2), color_type2);
}

void			draw_alpha_border_rectangle(t_vect coord, t_vect size, int color_type, int color_type2, int alpha)
{
	draw_alpha_rectangle(coord, size, color_type, alpha);
	draw_alpha_rectangle(t_vect(coord.x + BORDER, coord.y + BORDER), t_vect(size.x - BORDER * 2, size.y - BORDER * 2), color_type2, alpha);
}

void			draw_alpha_border_centred_rectangle(t_vect coord, t_vect size, int color_type, int color_type2, int alpha)
{
	draw_alpha_centred_rectangle(coord, size, color_type, alpha);
	draw_alpha_centred_rectangle(coord, t_vect(size.x - BORDER * 2, size.y - BORDER * 2), color_type2, alpha);
}

void			draw_rectangle(t_vect tl, t_vect tr, t_vect dl, t_vect dr, t_color color)
{
	t_point		tl_opengl = screen_to_opengl(tl);
	t_point		tr_opengl = screen_to_opengl(tr);
	t_point		dl_opengl = screen_to_opengl(dl);
	t_point		dr_opengl = screen_to_opengl(dr);

	t_triangle a = t_triangle(t_point(tl_opengl.x, tl_opengl.y, color.r, color.g, color.b), t_point(tr_opengl.x, tr_opengl.y, color.r, color.g, color.b), t_point(dl_opengl.x, dl_opengl.y, color.r, color.g, color.b));
	t_triangle b = t_triangle(t_point(dl_opengl.x, dl_opengl.y, color.r, color.g, color.b), t_point(dr_opengl.x, dr_opengl.y, color.r, color.g, color.b), t_point(tr_opengl.x, tr_opengl.y, color.r, color.g, color.b));

	draw_triangle_color(a, 255);
	draw_triangle_color(b, 255);
}

void			draw_rectangle(t_vect coord, t_vect size, t_color color)
{
	draw_rectangle(t_vect(coord.x, coord.y), t_vect(coord.x + size.x, coord.y), t_vect(coord.x, coord.y + size.y), t_vect(coord.x + size.x, coord.y + size.y), color);
}

void			draw_centred_rectangle(t_vect coord, t_vect size, t_color color)
{
	draw_rectangle(t_vect(coord.x - size.x / 2, coord.y - size.y / 2), t_vect(coord.x + size.x / 2, coord.y - size.y / 2), t_vect(coord.x - size.x / 2, coord.y + size.y / 2), t_vect(coord.x + size.x / 2, coord.y + size.y / 2), color);
}

void			draw_alpha_rectangle(t_vect coord, t_vect size, t_color color, int alpha)
{
	SDL_Surface *s;

	SDL_Rect rect;

	set_sdl_rect(&rect, 0, 0, size.x, size.y);

	Uint32 rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif

	s = SDL_CreateRGBSurface(0, size.x, size.y, 32, rmask, gmask, bmask, amask);

	SDL_FillRect(s, &rect, SDL_MapRGBA(s->format, (Uint8)color.r * 255, (Uint8)color.g * 255, (Uint8)color.b * 255, (Uint8)alpha));

	draw_image(s, coord, size);

}

void			draw_alpha_centred_rectangle(t_vect coord, t_vect size, t_color color, int alpha)
{
	SDL_Surface *s;

	SDL_Rect rect;

	set_sdl_rect(&rect, 0, 0, size.x, size.y);

	Uint32 rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif

	s = SDL_CreateRGBSurface(0, size.x, size.y, 32, rmask, gmask, bmask, amask);


	SDL_FillRect(s, &rect, SDL_MapRGBA(s->format, (Uint8)color.r * 255, (Uint8)color.g * 255, (Uint8)color.b * 255, (Uint8)alpha));

	draw_centred_image(s, coord, size);

}

void			draw_border_rectangle(t_vect coord, t_vect size, t_color color, t_color color2)
{
	draw_rectangle(coord, size, color);
	draw_rectangle(t_vect(coord.x + BORDER, coord.y + BORDER), t_vect(size.x - BORDER * 2, size.y - BORDER * 2), color2);
}

void			draw_border_centred_rectangle(t_vect coord, t_vect size, t_color color, t_color color2)
{
	draw_centred_rectangle(coord, size, color);
	draw_centred_rectangle(coord, t_vect(size.x - BORDER * 2, size.y - BORDER * 2), color2);
}

void			draw_alpha_border_rectangle(t_vect coord, t_vect size, t_color color, t_color color2, int alpha)
{
	draw_alpha_rectangle(coord, size, color, alpha);
	draw_alpha_rectangle(t_vect(coord.x + BORDER, coord.y + BORDER), t_vect(size.x - BORDER * 2, size.y - BORDER * 2), color2, alpha);
}

void			draw_alpha_border_centred_rectangle(t_vect coord, t_vect size, t_color color, t_color color2, int alpha)
{
	draw_alpha_centred_rectangle(coord, size, color, alpha);
	draw_alpha_centred_rectangle(coord, t_vect(size.x - BORDER * 2, size.y - BORDER * 2), color2, alpha);
}
