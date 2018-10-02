#include "template.h"

int					get_root(int size)
{
	int		i;

	i = 1;
	while ((i + 1) * (i + 1) <= size)
		i++;
	return (i);
}

void				error_exit(string msg, int error)
{
	printf("Error %d : %s\n", error, msg.c_str());
	getchar();
	exit(error);
}

void				set_sdl_rect(SDL_Rect *rect, int x, int y, int w, int h)
{
	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;
}

void				get_leaks(string msg)
{
	//system("clear");
	system("leaks TAAG 2>/dev/null | grep 'total leaked bytes'");
	cout << msg << "\n\n\n"<< endl;
	//getchar();
}

t_vect				get_mouse_coord()
{
	t_vect mouse;

	SDL_GetMouseState(&mouse.x, &mouse.y);
	return(mouse);
}

int					return_zero()
{
	return (0);
}

int					return_plus()
{
	return (1);
}

int					return_minus()
{
	return (-1);
}