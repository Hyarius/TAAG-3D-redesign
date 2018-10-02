#include "template.h"

image::image(string path)
{
	this->surface = IMG_Load(path.c_str());
	if (this->surface == NULL)
		error_exit("Can't open a image : " + path, 245);

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
	this->coord = t_vect(0, 0);
	this->size = t_vect(0, 0);

	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, this->internal_format, this->surface->w, this->surface->h, 0, this->format, GL_UNSIGNED_BYTE, this->surface->pixels);

	glBindTexture(GL_TEXTURE_2D, 0);
}

image::image(string path, t_vect p_coord, t_vect p_size)
{
	this->surface = IMG_Load(path.c_str());
	if (this->surface == NULL)
		error_exit("Can't open a image : " + path, 245);

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
	this->coord = p_coord;
	this->size = p_size;

	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, this->internal_format, this->surface->w, this->surface->h, 0, this->format, GL_UNSIGNED_BYTE, this->surface->pixels);

	glBindTexture(GL_TEXTURE_2D, 0);

}

void				image::draw_self()
{
	glBindTexture(GL_TEXTURE_2D, texture_id);
	draw_image(this->coord, this->size);
}

void				image::draw_self(t_vect tl, t_vect tr, t_vect dl, t_vect dr)
{
	glBindTexture(GL_TEXTURE_2D, texture_id);
	draw_image(tl, tr, dl, dr);
}

SDL_Surface			*image::get_surface()
{
	return (this->surface);
}

GLuint				image::get_texture_id()
{
	return (this->texture_id);
}

GLuint				image::get_texture_info()
{
	return (this->texture_info);
}

GLenum				image::get_format()
{
	return (this->format);
}

GLint				image::get_internal_format()
{
	return (this->internal_format);
}