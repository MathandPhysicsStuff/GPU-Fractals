#include "header.h"

void predraw(GLuint graphics_pipeline_object, int screen_width, int screen_height)
{
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glViewport(0, 0, screen_width, screen_height);
    glClearColor(1.0, 1.0, 0.0, 1.0);

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glUseProgram(graphics_pipeline_object);
}

void draw(GLuint vertex_array_object, GLuint vertex_buffer_object)
{
    glBindVertexArray(vertex_array_object);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);

    glDrawArrays(GL_TRIANGLES, 0, 3);
}
