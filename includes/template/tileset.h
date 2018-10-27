#ifndef TILESET_H
# define TILESET_H

#include "template_structure.h"

typedef struct		s_tileset
{
	SDL_Surface		*surface;
	GLenum			format;
	GLint			internal_format;
	GLuint			texture_id;
	t_vect			size;
	vector<t_vect>	sprite_list;
					s_tileset();
					s_tileset(string p_path, t_vect p_size);
	void			draw_self(t_vect p_tl, t_vect p_tr, t_vect p_dl, t_vect p_dr, int sprite, double p_alpha);
	void 			draw_self(t_vect p_coord, t_vect p_size, int p_sprite, double p_alpha);
	void 			draw_self(t_vect p_coord, t_vect p_size, int p_sprite);
}					t_tileset;

#endif
