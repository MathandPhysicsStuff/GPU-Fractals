#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>

#include "SDL2/SDL.h"
#include "glad/glad.h"

//debug macro
#define GLCheck(x) GLClearAllErrors(); x; GLCheckErrorStatus(#x, __LINE__);

enum boolean { FALSE, TRUE };

typedef struct UniformVariables
{
    GLint state;
    int iter;
    int x_res, y_res;
    float zoom;
    float x_point, y_point;
    float lx_off, ux_off;
    float ly_off, uy_off;
    float xlb, ylb, xub, yub;

}UniformVariables;

//initialize_free.c
void initialize(SDL_Window **window, SDL_GLContext *gl_context, int screen_width, int screen_height, int info);
void free_memory(SDL_Window **window,
                 GLuint *vertex_array_object,
                 GLuint *vertex_buffer_object,
                 GLuint *graphics_pipeline_object);

//event_inputs.c
void event_inputs(int *running);
void key_events(SDL_Event event, int *running);
void mouse_events(SDL_Event event);

//opengl_setup.c
char* read_file(char *file_name); //for reading shader and fragment files
GLuint compile_shader(GLuint type, const char* source);
GLuint create_shader_program(const char* vertex_shader_source, const char* fragment_shader_source);
void create_graphics_pipeline(GLuint *graphics_pipeline_object,
                              const char* vertex_shader_source, const char* fragment_shader_source);
void create_vertex_specs(GLfloat *vertices, int vertices_length, GLint step_size,
                         GLuint *vertex_array_object, GLuint *vertex_buffer_object, GLuint *index_buffer_object);
 
//draw.c
void predraw(GLuint *graphics_pipeline_object, UniformVariables *U);
void draw(GLuint *vertex_array_object, GLuint *vertex_buffer_object);

//debug.c
void GLClearAllErrors();
int GLCheckErrorStatus(const char* function, int line);

#endif








