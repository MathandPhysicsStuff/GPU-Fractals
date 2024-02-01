#include "header.h"

//initializing sdl2 and opengl
void initialize(SDL_Window **window, SDL_GLContext *gl_context, int screen_width, int screen_height, int info)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL2 video failed to initialize: %s\n", SDL_GetError());
        exit(1);
    }
    else
    {
        printf("System is ready to go!\n");
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    *window = SDL_CreateWindow("GPU Fractals",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              screen_width, screen_height,
                              SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    if (*window == NULL)
    {
        printf("SDL window did not initialize\n");
        exit(1);
    }
    
    *gl_context = SDL_GL_CreateContext(*window);
    if (*gl_context == NULL)
    {
        printf("gl_context did not initialize\n");
        exit(1);
    }
    
    if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
    {
        printf("glad did not initialize\n");
        exit(1);
    }
    
    if (info == TRUE)
    {
        printf("Vender: %s\n", glGetString(GL_VENDOR));
        printf("Renderer: %s\n", glGetString(GL_RENDERER));
        printf("Version: %s\n", glGetString(GL_VERSION));
        printf("Shader Language: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    }
}

void free_memory(SDL_Window **window, GLuint *vertex_array_object, GLuint *vertex_buffer_object, GLuint *graphics_pipeline_object)
{
    glDeleteBuffers(1, vertex_buffer_object);
    glDeleteVertexArrays(1, vertex_array_object);
    glDeleteProgram(*graphics_pipeline_object);
    SDL_DestroyWindow(*window);
    SDL_Quit();
}

























