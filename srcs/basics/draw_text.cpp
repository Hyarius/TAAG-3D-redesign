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

	while (calc_text_len(text, i + 1, NORMAL) < size.x &&
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

static bool			verify_paragraphe_size(vector<string> line, t_vect size, int text_size, int typo)
{
	t_vect	tmp = t_vect(0, 0);
	size_t	i = 0;

	while (i < line.size())
	{
		if (calc_text_len(line[i] + " ", text_size, typo) > size.x)
			return (false);
		if (tmp.y + get_char(text_size, typo, BLACK, 'M')->surface->h > size.y)
			return (false);
		if (tmp.x + calc_text_len(line[i] + " ", text_size, typo) >= size.x)
		{
			tmp.x = 0;
			tmp.y = tmp.y + get_char(text_size, typo, BLACK, 'M')->surface->h;
			if (tmp.y + get_char(text_size, typo, BLACK, 'M')->surface->h > size.y)
				return (false);
		}
		tmp.x += calc_text_len(line[i] + " ", text_size, typo);
		i++;
	}
	return (true);
}

int					calc_paragraphe_size(string text, t_vect size, int typo)
{
	int				i = 1;
	vector<string>	line;

	line = strsplit(text, " ");
	while (verify_paragraphe_size(line, size, i + 100, typo) == true)
		i += 100;
	while (verify_paragraphe_size(line, size, i + 50, typo) == true)
		i += 50;
	while (verify_paragraphe_size(line, size, i + 25, typo) == true)
		i += 25;
	while (verify_paragraphe_size(line, size, i + 10, typo) == true)
		i += 10;
	while (verify_paragraphe_size(line, size, i + 1, typo) == true)
		i += 1;

	return (i);
}

void				draw_paragraphe(string text, t_vect coord, t_vect size, int typo, int color_type)
{
	int		delta;
	size_t i = 0;
	vector<string>	line;
	line = strsplit(text, " ");
	t_vect	tmp = t_vect(0, 0);
	size_t text_size = calc_paragraphe_size(text, size, typo);

	printf("text_size = %d\n", text_size);

	while (i < line.size())
	{
		if (tmp.x + calc_text_len(line[i], text_size, typo) > size.x)
		{
			tmp.x = 0;
			tmp.y = tmp.y + get_char(text_size, typo, BLACK, 'M')->surface->h;
		}
		tmp.x += draw_text(line[i] + " ", text_size, tmp + coord, typo, color_type);
		i++;
	}
}
