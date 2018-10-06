#include "template.h"

int				draw_text(string text, int text_size, t_vect coord, int typo, int color_type)
{
	t_image			*image;
	size_t			i = 0;
	t_vect			rel_coord;
	int				delta = 0;

	while (i < text.length())
	{
		rel_coord = t_vect(coord.x + delta, coord.y);
		image = get_char(text_size, typo, color_type, text[i]);
		image->draw_self(rel_coord, t_vect(image->surface->w, image->surface->h));
		delta += image->surface->w;
		i++;
	}
	return (delta);
}

int				calc_text_len(string text, int text_size, int typo)
{
	t_image			*image;
	size_t			i = 0;
	int				delta = 0;

	while (i < text.length())
	{
		image = get_char(text_size, typo, BLACK, text[i]);
		delta += image->surface->w;
		i++;
	}
	return (delta);
}

int				calc_text_max_size(string text, int typo, t_vect size)
{
	int i = 1;

	while (calc_text_len(text, i + 1, NORMAL) + BORDER * 4 < size.x &&
			get_char(i, NORMAL, BLACK, 'M')->surface->h < size.y)
		i++;
	return (i);
}

int				draw_centred_text(string text, int text_size, t_vect coord, int typo, int color_type)
{
	int x = calc_text_len(text, text_size, typo);
	int y = get_char(text_size, typo, color_type, 'M')->surface->h;

	return (draw_text(text, text_size, t_vect(coord.x - x / 2, coord.y - y / 2), typo, color_type));
}

int				draw_lined_text(string text, int text_size, t_vect coord, int typo, int color_type)
{
	int y = get_char(text_size, typo, color_type, 'M')->surface->h;

	return (draw_text(text, text_size, coord + t_vect(0, (-y / 2)), typo, color_type));
}
