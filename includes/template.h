#ifndef TEMPLATE_H
# define TEMPLATE_H

# include "include.h"
# include "define.h"
# include "structure_template.h"
# include "template_class.h"

using namespace std;

//		Basics functions
int					get_root(int size);
void				error_exit(string msg, int error);
void				set_sdl_rect(SDL_Rect *rect, int x, int y, int w, int h);
void				get_leaks(string msg);
t_vect				get_mouse_coord();
vector<string>		list_files(string path, string extension);

//		Color handler
void				set_color_tab(void);
SDL_Color			get_color(int i);
t_color				get_open_color(int i);

//		Convert
double				degree_to_radius(double angle);
double				radius_to_degree(double radian);
string				convert_double(double i, int n);
string 				convert_int(int i);
t_point				screen_to_opengl(t_vect source);

//		Draw image
void			draw_image(SDL_Surface *surface, t_vect tl, t_vect tr, t_vect dl, t_vect dr);
void			draw_image(SDL_Surface *surface, t_vect coord, t_vect size);
void			draw_image(SDL_Surface *surface, t_vect coord);
void			draw_image(t_vect tl, t_vect tr, t_vect dl, t_vect dr);
void			draw_image(t_vect coord, t_vect size);
void			draw_centred_image(SDL_Surface *surface, t_vect coord, t_vect size);
void			draw_centred_image(SDL_Surface *surface, t_vect coord);

//		Draw shape
void			draw_rectangle(t_vect tl, t_vect tr, t_vect dl, t_vect dr, int color_type);
void			draw_rectangle(t_vect coord, t_vect size, int color_type);
void			draw_centred_rectangle(t_vect coord, t_vect size, int color_type);
void			draw_alpha_rectangle(t_vect coord, t_vect size, int color_type, int alpha);
void			draw_alpha_centred_rectangle(t_vect coord, t_vect size, int color_type, int alpha);
void			draw_border_rectangle(t_vect coord, t_vect size, int color_type, int color_type2);
void			draw_border_centred_rectangle(t_vect coord, t_vect size, int color_type, int color_type2);
void			draw_alpha_border_rectangle(t_vect coord, t_vect size, int color_type, int color_type2, int alpha);
void			draw_alpha_border_centred_rectangle(t_vect coord, t_vect size, int color_type, int color_type2, int alpha);
void			draw_rectangle(t_vect tl, t_vect tr, t_vect dl, t_vect dr, double *color);
void			draw_rectangle(t_vect coord, t_vect size, t_color color);
void			draw_centred_rectangle(t_vect coord, t_vect size, t_color color);
void			draw_alpha_rectangle(t_vect coord, t_vect size, t_color color, int alpha);
void			draw_alpha_centred_rectangle(t_vect coord, t_vect size, t_color color, int alpha);
void			draw_border_rectangle(t_vect coord, t_vect size, t_color color, t_color color2);
void			draw_border_centred_rectangle(t_vect coord, t_vect size, t_color color, t_color color2);
void			draw_alpha_border_rectangle(t_vect coord, t_vect size, t_color color, t_color color2, int alpha);
void			draw_alpha_border_centred_rectangle(t_vect coord, t_vect size, t_color color, t_color color2, int alpha);

//		Draw text
int				draw_text(string text, t_vect coord, int typo, int color_type, TTF_Font *font);
int				draw_text_alpha(string text, t_vect coord, int typo, int color_type, TTF_Font *font, int alpha);
int				draw_centred_text(string text, t_vect coord, int typo, int color_type, TTF_Font *font);
int				draw_centred_alpha_text(string text, t_vect coord, int typo, int color_type, TTF_Font *font, int alpha);
int				calc_buffer_text_len(string text, int typo, int color_type);
int				draw_buffer_text(string text, t_vect coord, int typo, int color_type);
int				draw_centred_buffer_text(string text, t_vect coord, int typo, int color_type);
int				draw_buffer_sized_text(string text, t_vect coord, int size, int typo, int color_type);
int				calc_buffer_sized_text_len(string text, int size, int typo, int color_type);
int				draw_centred_buffer_sized_text(string text, t_vect coord, int size, int typo, int color_type);
int				draw_lined_buffer_text(string text, t_vect coord, int typo, int color_type);
int				draw_lined_buffer_sized_text(string text, t_vect coord, int size, int typo, int color_type);

//		Draw triangle
void			draw_triangle_texture(t_triangle surface);
void			draw_triangle_color(t_triangle surface, int alpha);

//		Draw uv mapping
void			draw_uv_texture(tileset *tile, int sprite, t_vect tl, t_vect tr, t_vect dl, t_vect dr);

//		File handler
vector<string>	strsplit(string input, const string c);
string			get_str(ifstream *myfile);
vector<string>	get_strsplit(ifstream *myfile, const string c, int size);

//		Fps handler
void			set_fps(int i);
void			reset_fps(int i);
int				get_fps(void);
void			check_frame();

//		Screen handler
void				window_initialisation(string window_name);
SDL_GLContext		*get_context(void);
t_vect				get_win_size(void);
SDL_Window			*get_window();
void				prepare_screen();
void				prepare_screen(t_color color);
void				render_screen();
GLuint				get_program_color();
GLuint				get_program_sprite();
GLuint				get_link_texture();
GLuint				get_vertex_array();
GLuint				get_vertex_buffer();
GLuint				get_color_buffer();
GLuint				get_texture_buffer();
GLuint				get_texture_id();

//		Shader
GLuint				LoadShaders(const char * vertex_file_path, const char * fragment_file_path);

//		Text handler
SDL_Surface			*get_char(int size, int style, int p_color, char c);

//		Tileset
tileset				*create_tileset(string path);


#endif
