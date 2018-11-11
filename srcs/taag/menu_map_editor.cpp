#include "taag.h"
#include "base_value.h"

using namespace glm;

mat4 computeMatricesFromInputs(SDL_Event *event);

void				menu_map_editor(t_data data)
{
	SDL_Event		event;
	bool			quit = false;

	SDL_WarpMouseInWindow(get_window(), ((int)(get_win_size().x)) / 2, ((int)(get_win_size().y)) / 2);

	mat4 Projection = perspective(radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);

	mat4 View = lookAt(
		vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
		vec3(0, 0, 0), // and looks at the origin
		vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);

	mat4 Model = glm::mat4(1.0f);

	mat4 MVP = Projection * View * Model;

	t_model test = s_model("ressources/assets/model/", "cube.obj");

	while (quit == false)
	{

		prepare_screen(t_color(0.5, 0.5, 0.5));

		test.draw_model( MVP);

		render_screen(draw_fps);

		if (SDL_PollEvent(&(event)) == 1)
		{
			if (event.type == SDL_QUIT || (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE))
				quit = true;
		}
		SDL_FlushEvents(SDL_MOUSEMOTION, SDL_MOUSEWHEEL);

	}

	printf("Map editor\n");
}
