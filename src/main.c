#include <stdio.h>

#include "SDL2/SDL.h"
#include "glad/glad.h"

#include "header.h"

int main()
{
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;
    SDL_Window *window = NULL;
    SDL_GLContext gl_context = NULL;
    int info = FALSE; //setting info = TRUE will print opengl info to terminal 
    
    //Initializes SDL and openGL 
    initialize(window, gl_context, SCREEN_WIDTH, SCREEN_HEIGHT, FALSE);

    free_memory(window);
    return 0;
}
