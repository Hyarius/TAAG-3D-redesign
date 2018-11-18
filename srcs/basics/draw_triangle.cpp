#include "template.h"

void			draw_triangle_texture(t_point a, t_point b, t_point c)
{
	GLfloat g_vertex_buffer_data[] = {
		(float)a.x, (float)a.y, 0.0f,
		(float)b.x, (float)b.y, 0.0f,
		(float)c.x, (float)c.y, 0.0f,
	};

	GLfloat g_uv_buffer_data[] = {
		(float)a.r,  (float)a.g,
		(float)b.r,  (float)b.g,
		(float)c.r,  (float)c.g,
	};

	GLfloat g_alpha_buffer_data[] = {
		(float)a.b,
		(float)b.b,
		(float)c.b,
	};

	glBindVertexArray(get_vertex_array());

	glBindBuffer(GL_ARRAY_BUFFER, get_vertex_buffer());
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, get_texture_buffer());
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, get_alpha_buffer());
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_alpha_buffer_data), g_alpha_buffer_data, GL_STATIC_DRAW);

	glUseProgram(get_program_sprite());

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, get_vertex_buffer());
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, get_texture_buffer());
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, get_alpha_buffer());
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 0, NULL);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void			draw_triangle_color(t_point a, t_point b, t_point c)
{
	GLfloat g_vertex_buffer_data[] = {
		(float)a.x, (float)a.y, 0.0f,
		(float)b.x, (float)b.y, 0.0f,
		(float)c.x, (float)c.y, 0.0f,
	};

	GLfloat g_color_buffer_data[] = {
		(float)a.r,  (float)a.g,  (float)a.b, (float)a.a,
		(float)b.r,  (float)b.g,  (float)b.b, (float)b.a,
		(float)c.r,  (float)c.g,  (float)c.b, (float)c.a,
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
