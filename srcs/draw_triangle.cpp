#include "template.h"

void			draw_triangle_texture(t_triangle surface)
{
	GLfloat g_vertex_buffer_data[] = {
		(float)surface.a.x, (float)surface.a.y, 0.0f,
		(float)surface.b.x, (float)surface.b.y, 0.0f,
		(float)surface.c.x, (float)surface.c.y, 0.0f,
	};

	GLfloat g_uv_buffer_data[] = {
		(float)surface.a.a,  (float)surface.a.b,
		(float)surface.b.a,  (float)surface.b.b,
		(float)surface.c.a,  (float)surface.c.b,
	};

	glBindVertexArray(get_vertex_array());

	glBindBuffer(GL_ARRAY_BUFFER, get_vertex_buffer());
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, get_texture_buffer());
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

	glUseProgram(get_program_sprite());

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, get_vertex_buffer());
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, get_texture_buffer());
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void			draw_triangle_color(t_triangle surface, int alpha)
{
	GLfloat g_vertex_buffer_data[] = {
		(float)surface.a.x, (float)surface.a.y, 0.0f,
		(float)surface.b.x, (float)surface.b.y, 0.0f,
		(float)surface.c.x, (float)surface.c.y, 0.0f,
	};

	GLfloat g_color_buffer_data[] = {
		(float)surface.a.a,  (float)surface.a.b,  (float)surface.a.c, (float)alpha / 255.0f,
		(float)surface.b.a,  (float)surface.b.b,  (float)surface.b.c, (float)alpha / 255.0f,
		(float)surface.c.a,  (float)surface.c.b,  (float)surface.c.c, (float)alpha / 255.0f,
	};

	glBindVertexArray(get_vertex_array());

	glBindBuffer(GL_ARRAY_BUFFER, get_vertex_buffer());
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, get_color_buffer());
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

	glUseProgram(get_program_color());

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, get_vertex_buffer());
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, get_color_buffer());
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}
