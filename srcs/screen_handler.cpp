#include "template.h"

SDL_GLContext		g_context;
SDL_Window			*g_window;
t_vect				g_window_size;
GLuint				program_color;
GLuint				program_sprite;
GLuint				vertex_array;
GLuint				vertex_buffer;
GLuint				color_buffer;
GLuint				link_texture;
GLuint				texture_buffer;
GLenum				texture_format;

t_f_vect			screen_size = t_f_vect(SCREEN_RATIO_X, SCREEN_RATIO_Y);

GLuint				textureID;

void				window_initialisation(string window_name)
{
	SDL_DisplayMode current;
	int				win_x;
	int				win_y;

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GetDesktopDisplayMode(0, &current);
	g_window = SDL_CreateWindow(window_name.c_str(),
						SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
						(int)(current.w * screen_size.x), (int)(current.h * screen_size.y),
						SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	SDL_GetWindowSize(g_window, &win_x, &win_y);
	g_window_size = t_vect(win_x, win_y);
	g_context = SDL_GL_CreateContext(g_window);

	#ifndef __APPLE__
	glewInit();
	#endif

	SDL_WarpMouseInWindow(g_window, g_window_size.x / 2, g_window_size.y / 2);
	SDL_SetWindowGrab(g_window, SDL_FALSE);
	SDL_ShowCursor(1);

	t_color color = get_open_color(BLACK);

	glClearColor((GLclampf)color.r, (GLclampf)color.g, (GLclampf)color.b, 0.0f);

	glGenVertexArrays(1, &vertex_array);
	glBindVertexArray(vertex_array);

	glGenBuffers(1, &vertex_buffer);
	glGenBuffers(1, &color_buffer);
	glGenBuffers(1, &texture_buffer);

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	program_color = LoadShaders(	"ressources/shader/colorshader.vertexshader",	"ressources/shader/colorshader.fragmentshader");
	program_sprite = LoadShaders(	"ressources/shader/textureshader.vertexshader", "ressources/shader/textureshader.fragmentshader");

	link_texture = glGetUniformLocation(program_sprite, "myTextureSampler");

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	texture_format = GL_RGBA;

	set_color_tab();
	TTF_Init();
}

SDL_GLContext		*get_context(void)
{
	return (&g_context);
}

t_vect				get_win_size(void)
{
	return (g_window_size);
}

SDL_Window			*get_window()
{
	return (g_window);
}

void				prepare_screen()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void				prepare_screen(t_color color)
{
	glClearColor((GLclampf)color.r, (GLclampf)color.g, (GLclampf)color.b, 0.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	color = get_open_color(BLACK);
	glClearColor((GLclampf)color.r, (GLclampf)color.g, (GLclampf)color.b, 0.0f);
}


void				render_screen()
{
	check_frame();
	SDL_GL_SwapWindow(g_window);
}


GLuint				get_program_color()
{
	return (program_color);
}

GLuint				get_program_sprite()
{
	return (program_sprite);
}

GLuint				get_link_texture()
{
	return (link_texture);
}

GLuint				get_vertex_array()
{
	return (vertex_array);
}

GLuint				get_vertex_buffer()
{
	return (vertex_buffer);
}

GLuint				get_color_buffer()
{
	return (color_buffer);
}

GLuint				get_texture_buffer()
{
	return (texture_buffer);
}

GLuint				get_texture_id()
{
	return (textureID);
}
