#ifndef TEMPLATE_STRUCTURE_H
# define TEMPLATE_STRUCTURE_H

using namespace std;

enum X_ROTATE { X };
enum Y_ROTATE { Y };
enum Z_ROTATE { Z };
enum ROTATION { R };
enum TRANSLATION { T };
enum SCALE { S };
enum PERSPECTIVE { P };
enum IDENTITY { I };

typedef struct		s_color
{
	double r;
	double g;
	double b;
	double a;
	s_color();
	s_color(double p_r, double p_g, double p_b);
	s_color(double p_r, double p_g, double p_b, double p_a);
}					t_color;

typedef struct		s_vect
{
	double			x;
	double			y;
					s_vect();
					s_vect(int x, int y);
					s_vect(double x, double y);
					s_vect(int x, double y);
					s_vect(double x, int y);
	s_vect			operator * (int mult);
	s_vect			operator * (double mult);
	s_vect			operator * (s_vect mult);
	s_vect			operator + (int add);
	s_vect			operator + (double add);
	s_vect			operator + (s_vect add);
	s_vect			operator / (int div);
	s_vect			operator / (double div);
	s_vect			operator / (s_vect div);
	s_vect			operator - (int min);
	s_vect			operator - (double min);
	s_vect			operator - (s_vect min);
	bool			operator < (s_vect delta);
	bool			operator > (s_vect delta);
}					t_vect;

typedef struct		s_vertex
{
	double			x;
	double			y;
	double			z;
	s_vertex(int p_x, int p_y, int p_z);
	s_vertex(double p_x, double p_y, double p_z);
	s_vertex();
}					t_vertex;

typedef struct	s_point
{
	double		x;
	double		y;
	double		r;
	double		g;
	double		b;
	double		a;
				s_point();
				s_point(double p_x, double p_y);
				s_point(double p_x, double p_y, double p_a, double p_b);
				s_point(double p_x, double p_y, double p_r, double p_g, double p_b);
				s_point(double p_x, double p_y, double p_r, double p_g, double p_b, double p_a);
}				t_point;

typedef struct		s_image
{
	SDL_Surface		*surface;
	GLenum			format;
	GLint			internal_format;
	GLuint			texture_id;
					s_image();
					s_image(string path);
					s_image(t_color p_color);
					s_image(SDL_Surface *p_surface);
	void			draw_self(t_vect p_coordd, t_vect p_size);
	void			draw_self(t_vect tl, t_vect tr, t_vect dl, t_vect dr);
}					t_image;

typedef struct		s_angle
{
	double x;
	double y;
	double z;
					s_angle();
					s_angle(double x, double y, double z);
}					t_angle;

#endif
