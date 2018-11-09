#include "taag.h"
#include "base_value.h"

using namespace glm;

void				menu_map_editor(t_data data)
{
	SDL_Event		event;
	bool			quit = false;

	mat4 projection = perspective(radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);

	mat4 camera       = lookAt( vec3(4,4,4), // camera position in space
								vec3(0.5,0.5,0.5), // camera target
								vec3(0,1,0)  // shouldn't change this
						   		);
	mat4 model      = mat4(1.0f);
	mat4 MVP        = projection * camera * model;

	t_model test = s_model("ressources/assets/model/ground/", "ground.obj");

	while (quit == false)
	{
		prepare_screen(t_color(0.5, 0.5, 0.5));


		render_screen(draw_fps);

		if (SDL_PollEvent(&(event)) == 1)
		{
			if (event.type == SDL_QUIT || (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE))
				quit = true;
		}
	}

	printf("Map editor\n");
}
