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
    int info = FALSE; //setting info = TRUE will print opengl info to the terminal 
    
    //Initializes SDL and openGL 
    initialize(window, gl_context, SCREEN_WIDTH, SCREEN_HEIGHT, FALSE); //function in src/initialize_free.c
    
    int running = TRUE;
    while (running == TRUE)
    {
        SDL_Event event;
        events(event, &running); //function in src/event_inputs.c

        SDL_GL_SwapWindow(window);
    }

    free_memory(window);
    return 0;
}
