#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>

#include "SDL2/SDL.h"
#include "glad/glad.h"

enum boolean { FALSE, TRUE };

//initialize_free.c
void initialize(SDL_Window **window, SDL_GLContext *gl_context, int screen_width, int screen_height, int info);
void free_memory(SDL_Window *window);

//event_inputs.c
void event_inputs(int *running);
void key_events(SDL_Event event, int *running);
void mouse_events(SDL_Event event);

//opengl_setup.c
GLuint compile_shader(GLuint type, const char* source);
GLuint create_shader_program(const char* vertex_shader_source, const char* fragment_shader_source);
void create_graphics_pipeline(GLuint graphics_pipeline_object,
                              const char* vertex_shader_source, const char* fragment_shader_source);
void create_vertex_specs(GLfloat *vertex, int vertex_length, GLint step_size,
                         GLuint vertex_array_object, GLuint vertex_buffer_object);

//draw.c
void predraw(GLuint graphics_pipeline_object, int screen_width, int screen_height);
void draw(GLuint vertex_array_object, GLuint vertex_buffer_object);

#endif
