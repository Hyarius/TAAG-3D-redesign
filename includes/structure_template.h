#ifndef STRUCTURE_TEMPLATE_H
# define STRUCTURE_TEMPLATE_H

using namespace std;

enum X_ROTATE { X };
enum Y_ROTATE { Y };
enum Z_ROTATE { Z };
enum ROTATION { R };
enum TRANSLATION { T };
enum SCALE { S };
enum PERSPECTIVE { P };

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
	int				x;
	int				y;
	s_vect();
	s_vect(int x, int y);
	s_vect			operator * (int mult);
	s_vect			operator * (double mult);
	s_vect			operator * (s_vect mult);
	s_vect			operator * (struct s_f_vect mult);
	s_vect			operator + (int add);
	s_vect			operator + (double add);
	s_vect			operator + (s_vect add);
	s_vect			operator + (struct s_f_vect add);
	s_vect			operator / (int div);
	s_vect			operator / (double div);
	s_vect			operator / (s_vect div);
	s_vect			operator / (struct s_f_vect div);
	s_vect			operator - (int min);
	s_vect			operator - (double min);
	s_vect			operator - (s_vect min);
	s_vect			operator - (struct s_f_vect min);
}					t_vect;

typedef struct		s_f_vect
{
	double			x;
	double			y;
	s_f_vect();
	s_f_vect(double x, double y);
	s_f_vect		operator * (int mult);
	s_f_vect		operator * (double mult);
	s_f_vect		operator * (s_vect mult);
	s_f_vect		operator * (struct s_f_vect mult);
	s_f_vect		operator + (int add);
	s_f_vect		operator + (double add);
	s_f_vect		operator + (s_vect add);
	s_f_vect		operator + (struct s_f_vect add);
	s_f_vect		operator / (int div);
	s_f_vect		operator / (double div);
	s_f_vect		operator / (s_vect div);
	s_f_vect		operator / (struct s_f_vect div);
	s_f_vect		operator - (int min);
	s_f_vect		operator - (double min);
	s_f_vect		operator - (s_vect min);
	s_f_vect		operator - (struct s_f_vect min);
}					t_f_vect;

typedef struct		s_vertex
{
	int				x;
	int				y;
	int				z;
	s_vertex(int p_x, int p_y, int p_z);
	s_vertex();
}					t_vertex;

typedef struct		s_f_vertex
{
	double			x;
	double			y;
	double			z;
	s_f_vertex(double p_x, double p_y, double p_z);
	s_f_vertex();
}					t_f_vertex;

typedef struct	s_point
{
	double		x;
	double		y;
	double		a;
	double		b;
	double		c;
				s_point();
				s_point(double p_x, double p_y);
				s_point(double p_x, double p_y, double p_a, double p_b, double p_c);
				s_point(double p_x, double p_y, double p_a, double p_b);
}				t_point;

typedef struct	s_triangle
{
	t_point	a;
	t_point b;
	t_point c;
	s_triangle(t_point p_a, t_point p_b, t_point p_c);
}				t_triangle;

struct matrice
{
	double value[4][4];

	matrice(double a0, double a1, double a2, double a3, double b0, double b1, double b2, double b3, double c0, double c1, double c2, double c3,
					double d0, double d1, double d2, double d3);
	matrice(X_ROTATE, double angle);
	matrice(Y_ROTATE, double angle);
	matrice(Z_ROTATE, double angle);
	matrice(ROTATION, double x, double y, double z);
	matrice(TRANSLATION, double t_x, double t_y, double t_z);
	matrice(SCALE, double t_x, double t_y, double t_z);
	matrice operator * (matrice p_matrice);
	t_f_vertex operator * (t_f_vertex vertex);
	t_f_vertex operator * (t_vertex vertex);
	void print();
};
#endif
