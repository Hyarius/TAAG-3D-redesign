#include "taag.h"

using namespace glm;


glm::vec3 position = glm::vec3(0, 0, 5);
float horizontalAngle = 3.14f;
float verticalAngle = 0.0f;
float initialFoV = 45.0f;

float speed = 3.0f;
float mouseSpeed = 0.005f;



mat4 computeMatricesFromInputs(SDL_Event *event) {

	// glfwGetTime is called only once, the first time this function is called
	static double lastTime = SDL_GetTicks() / 1000;

	// Compute time difference between current and last frame
	double currentTime = SDL_GetTicks() / 1000;
	float deltaTime = float(currentTime - lastTime);

	// Get mouse position
	int xpos, ypos;
	SDL_GetMouseState(&xpos, &ypos);

	// Reset mouse position for next frame
	SDL_WarpMouseInWindow(get_window(), (int)(get_win_size().x / 2), (int)(get_win_size().y) / 2);

	// Compute new orientation
	horizontalAngle += mouseSpeed * float((int)(get_win_size().x / 2) - xpos);
	verticalAngle += mouseSpeed * float((int)(get_win_size().y / 2) - ypos);

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	// Right vector
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f / 2.0f)
	);

	// Up vector
	glm::vec3 up = glm::cross(right, direction);

	// Move forward
	if (event->type == SDL_KEYUP && event->key.keysym.sym == SDLK_UP) {
		position += direction * deltaTime * speed;
	}
	// Move backward
	if (event->type == SDL_KEYUP && event->key.keysym.sym == SDLK_DOWN) {
		position -= direction * deltaTime * speed;
	}
	// Strafe right
	if (event->type == SDL_KEYUP && event->key.keysym.sym == SDLK_RIGHT) {
		position += right * deltaTime * speed;
	}
	// Strafe left
	if (event->type == SDL_KEYUP && event->key.keysym.sym == SDLK_LEFT) {
		position -= right * deltaTime * speed;
	}

	float FoV = initialFoV;

	mat4 projection = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);

	mat4 camera = glm::lookAt(
		position,           // Camera is here
		position + direction, // and looks here : at the same position, plus "direction"
		vec3(0, 1, 0)                  // Head is up (set to 0,-1,0 to look upside-down)
	);

	mat4 model = mat4(1.0f);

	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;

	return (projection * camera * model);
}