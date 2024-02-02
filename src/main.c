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

    GLuint vertex_array_object = 0;
    GLuint vertex_buffer_object = 0;
    GLuint graphics_pipeline_object = 0;
    
    GLfloat vertices[] =
    {
        //first triangle
        0.5, 0.5, 0.0,
        -0.5, 0.5, 0.0,
        0.5, -0.5, 0.0,

        //second triangle
        -0.5, 0.5, 0.0,
        -0.5, -0.5, 0.0,
        0.5, -0.5, 0.0
    };
    int vertices_size = sizeof(vertices);

    /*
    const char* vertex_shader_source =
    "#version 460 core\n"
    "in vec4 position;\n"
    "void main()\n"
    "{\n"
    "   gl_position = vec4(position.x, position.y, position.z, position.w);\n"
    "}\n";

    const char* fragment_shader_source =
    "#version 460 core\n"
    "out vec4 color;\n"
    "void main()\n"
    "{\n"
    "   color = vec4(1.0, 0.5, 0.0, 1.0);\n"
    "}\n";
    */
    
    const char *vertex_shader_source = "#version 460 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

    const char *fragment_shader_source = "#version 460 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
    "}\n\0";

    //Initializes SDL and openGL 
    initialize(&window, &gl_context, SCREEN_WIDTH, SCREEN_HEIGHT, info); //function in src/initialize_free.c

    //create_vertex_specs2();
    //create_graphics_pipeline(vertex_shader_source, fragment_shader_source);
    
    create_vertex_specs(vertices, vertices_size, 3, &vertex_array_object, &vertex_buffer_object);
    create_graphics_pipeline(&graphics_pipeline_object, vertex_shader_source, fragment_shader_source);
    
    int running = TRUE;
    while (running == TRUE)
    {
        event_inputs(&running); //function in src/event_inputs.c
        
        predraw(&graphics_pipeline_object, SCREEN_WIDTH, SCREEN_HEIGHT);
        draw(&vertex_array_object, &vertex_buffer_object);

        SDL_GL_SwapWindow(window);
    }

    free_memory(&window, &graphics_pipeline_object, &vertex_array_object, &vertex_buffer_object); //function in src/initialize_free.c
    return 0;
}
