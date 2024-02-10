#include <stdio.h>
#include <stdlib.h>

#include "SDL2/SDL.h"
#include "glad/glad.h"

#include "header.h"

int main()
{
    const int SCREEN_WIDTH = 640; //1280;
    const int SCREEN_HEIGHT = 640; //720;
    SDL_Window *window = NULL;
    SDL_GLContext gl_context = NULL;
    int info = FALSE; //setting info = TRUE will print opengl info to the terminal 

    GLuint vertex_array_object = 0;
    GLuint vertex_buffer_object = 0;
    GLuint index_buffer_object = 0;
    GLuint graphics_pipeline_object = 0;

    char* vertex_shader_file = "./shaders/shader.glsl";
    char* fragment_shader_file = "./shaders/fragment.glsl";
    char* test_file = "./shaders/test_frag.glsl";

    GLfloat vertices[] =
    {
        //top right 0
        1.0, 1.0, 0.0,
        
        //top left 1
        -1.0, 1.0, 0.0,
 
        //bottom left 2
        -1.0, -1.0, 0.0,     

        //bottom right 3
        1.0, -1.0, 0.0

        //triangle one -> 0 1 3
        //triangle two -> 1 2 3
    };
    int vertices_size = sizeof(vertices);

    UniformVariables U =
    {
        .state = 0,
        .iter = 512,
        .zoom_level = 0,
        .x_res = SCREEN_WIDTH,
        .y_res = SCREEN_HEIGHT,
        .x_point = 0, .y_point = 0,
        .lx_off = 2, .ly_off = 2,
        .ux_off = 2, .uy_off = 2,
        .step = 0.07,
    };

    char *vertex_shader_source = read_file(vertex_shader_file);
    char *fragment_shader_source = read_file(fragment_shader_file);

    if (vertex_shader_source == NULL)
        printf("Error reading vertex_shader_source\n");

    if (fragment_shader_source == NULL)
        printf("Error reading fragment_shader_source\n");

    //Initializes SDL and openGL 
    initialize(&window, &gl_context, SCREEN_WIDTH, SCREEN_HEIGHT, info); //function in src/initialize_free.c
    
    create_vertex_specs(vertices, vertices_size, 3, &vertex_array_object, &vertex_buffer_object, &index_buffer_object);
    create_graphics_pipeline(&graphics_pipeline_object, vertex_shader_source, fragment_shader_source);
 
    free(vertex_shader_source);
    free(fragment_shader_source);
   
    int running = TRUE;
    while (running == TRUE)
    {
        event_inputs(&running, &U); //function in src/event_inputs.c
        
        predraw(&graphics_pipeline_object, &U);
        draw(&vertex_array_object, &vertex_buffer_object);

        SDL_GL_SwapWindow(window);
    }

    free_memory(&window, &graphics_pipeline_object, &vertex_array_object, &vertex_buffer_object); //function in src/initialize_free.c
    return 0;
}
