#include "template.h"

s_image::s_image()
{

}

s_image::s_image(string path)
{
	this->surface = IMG_Load(path.c_str());
	s_image(this->surface);
}

s_image::s_image(SDL_Surface *p_surface)
{
	this->surface = p_surface;
	if (this->surface == NULL)
		error_exit("Can't charge a surface into an image", 245);

	if (this->surface->format->BytesPerPixel == 3)
	{
		this->internal_format = GL_RGB;
		if (this->surface->format->Rmask == 0xff)
			this->format = GL_RGB;
		else
			this->format = GL_BGR;
	}
	else if (this->surface->format->BytesPerPixel == 4)
	{
		this->internal_format = GL_RGBA;
		if (this->surface->format->Rmask == 0xff)
			this->format = GL_RGBA;
		else
			this->format = GL_BGRA;
	}

	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, this->internal_format, this->surface->w, this->surface->h, 0, this->format, GL_UNSIGNED_BYTE, this->surface->pixels);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void				s_image::draw_self(t_vect p_coord, t_vect p_size)
{
	glBindTexture(GL_TEXTURE_2D, texture_id);
	draw_image(p_coord, p_size);
}

void				s_image::draw_self(t_vect tl, t_vect tr, t_vect dl, t_vect dr)
{
	glBindTexture(GL_TEXTURE_2D, texture_id);
	draw_image(tl, tr, dl, dr);
}