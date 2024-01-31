#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>

#include "SDL2/SDL.h"
#include "glad/glad.h"

enum boolean { FALSE, TRUE };

//initialize_free.c
void initialize(SDL_Window *window, SDL_GLContext gl_context, int screen_width, int screen_height, int info);
void free_memory(SDL_Window *window);

//event_inputs.c
void events(SDL_Event event, int *running);
void key_events(SDL_Event event, int *running);
void mouse_events(SDL_Event event);

#endif
