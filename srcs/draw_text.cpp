#include "template.h"

int				draw_text(string text, t_vect coord, int typo, int color_type, TTF_Font *font)
{
	SDL_Color		color;
	SDL_Surface		*surface;
	int				delta;

	TTF_SetFontStyle(font, typo);
	color = get_color(color_type);
	surface = TTF_RenderText_Blended(font, text.c_str(), color);
	draw_image(surface, coord);
	delta = surface->w;
	SDL_FreeSurface(surface);
	return (delta);
}

int				draw_text_alpha(string text, t_vect coord, int typo, int color_type, TTF_Font *font, int alpha)
{
	SDL_Color		color;
	SDL_Surface		*surface;
	int				delta;

	TTF_SetFontStyle(font, typo);
	color = get_color(color_type);
	surface = TTF_RenderText_Blended(font, text.c_str(), color);
	SDL_SetSurfaceAlphaMod(surface, alpha);
	draw_image(surface, coord);
	delta = surface->w;
	SDL_FreeSurface(surface);
	return (delta);
}

int				draw_centred_text(string text, t_vect coord, int typo, int color_type, TTF_Font *font)
{
	SDL_Color		color;
	SDL_Surface		*surface;
	int				delta;

	TTF_SetFontStyle(font, typo);
	color = get_color(color_type);
	surface = TTF_RenderText_Blended(font, text.c_str(), color);
	draw_image(surface, t_vect(coord.x - surface->w / 2, coord.y - surface->h / 2));
	delta = surface->w;
	SDL_FreeSurface(surface);
	return (delta);
}

int				draw_centred_alpha_text(string text, t_vect coord, int typo, int color_type, TTF_Font *font, int alpha)
{
	SDL_Color		color;
	SDL_Surface		*surface;
	int				delta;

	TTF_SetFontStyle(font, typo);
	color = get_color(color_type);
	surface = TTF_RenderText_Blended(font, text.c_str(), color);
	SDL_SetSurfaceAlphaMod(surface, alpha);
	draw_image(surface, t_vect(coord.x - surface->w / 2, coord.y - surface->h / 2));
	delta = surface->w;
	SDL_FreeSurface(surface);
	return (delta);
}

int				draw_buffer_text(string text, t_vect coord, int typo, int color_type)
{
	SDL_Surface		*surface;
	size_t			i;
	t_vect			rel_coord;
	int				delta;

	i = 0;
	delta = 0;
	while (i < text.length())
	{
		surface = get_char(12, typo, color_type, text[i]);
		rel_coord = t_vect(coord.x + delta, coord.y);
		draw_image(surface, rel_coord);
		delta += surface->w;
		i++;
	}
	return (delta);
}

int				calc_buffer_text_len(string text, int typo, int color_type)
{
	SDL_Surface		*surface;
	size_t			i;
	int				delta;

	i = 0;
	delta = 0;
	while (i < text.length())
	{
		surface = get_char(12, typo, color_type, text[i]);
		delta += surface->w;
		i++;
	}
	return (delta);
}

int				draw_centred_buffer_text(string text, t_vect coord, int typo, int color_type)
{
	int x = calc_buffer_text_len(text, typo, color_type);
	int y = get_char(1, typo, color_type, text[0])->h;
	return (draw_buffer_text(text, t_vect(coord.x - x / 2, coord.y - y / 2), typo, color_type));
}

int				draw_buffer_sized_text(string text, t_vect coord, int size, int typo, int color_type)
{
	SDL_Surface		*surface;
	size_t			i;
	t_vect			rel_coord;
	t_vect			rel_size;
	int				delta;

	i = 0;
	delta = 0;
	while (i < text.length())
	{
		surface = get_char(size, typo, color_type, text[i]);
		rel_coord = t_vect(coord.x + delta, coord.y);
		draw_image(surface, rel_coord);
		delta += surface->w;
		i++;
	}
	return (delta);
}

int				calc_buffer_sized_text_len(string text, int size, int typo, int color_type)
{
	SDL_Surface		*surface;
	size_t			i;
	t_vect			rel_size;
	int				delta;

	i = 0;
	delta = 0;
	while (i < text.length())
	{
		surface = get_char(size, typo, color_type, text[i]);
		rel_size = t_vect(surface->w, surface->h);
		delta += rel_size.x;
		i++;
	}
	return (delta);
}

int				draw_centred_buffer_sized_text(string text, t_vect coord, int size, int typo, int color_type)
{
	int x = calc_buffer_sized_text_len(text, size, typo, color_type);
	int y = get_char(size, typo, color_type, '0')->h;
	return (draw_buffer_sized_text(text, t_vect(coord.x - x / 2, coord.y - y / 2), size, typo, color_type));
}

int				draw_lined_buffer_text(string text, t_vect coord, int typo, int color_type)
{
	int x = calc_buffer_sized_text_len(text, 1, typo, color_type);
	int y = get_char(1, typo, color_type, '0')->h;
	return (draw_buffer_sized_text(text, coord + t_vect(0, (-y / 2)), 1, typo, color_type));
}

int				draw_lined_buffer_sized_text(string text, t_vect coord, int size, int typo, int color_type)
{
	int x = calc_buffer_sized_text_len(text, size, typo, color_type);
	int y = get_char(size, typo, color_type, '0')->h;
	return (draw_buffer_sized_text(text, coord + t_vect(0, (-y / 2)), size, typo, color_type));
}
