#include "header.h"

void predraw(GLuint *graphics_pipeline_object, UniformVariables *U)
{
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glViewport(0, 0, U->x_res, U->y_res);
    glClearColor(1.0, 0.0, 0.0, 1.0);

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glUseProgram(*graphics_pipeline_object);

    GLint state_location = glGetUniformLocation(*graphics_pipeline_object, "u_state");
    GLint iter_location = glGetUniformLocation(*graphics_pipeline_object, "u_iter");
    GLint x_res_location = glGetUniformLocation(*graphics_pipeline_object, "u_x_res");
    GLint y_res_location = glGetUniformLocation(*graphics_pipeline_object, "u_y_res");
    GLint xlb_location = glGetUniformLocation(*graphics_pipeline_object, "u_xlb");
    GLint ylb_location = glGetUniformLocation(*graphics_pipeline_object, "u_ylb");
    GLint xub_location = glGetUniformLocation(*graphics_pipeline_object, "u_xub");
    GLint yub_location = glGetUniformLocation(*graphics_pipeline_object, "u_yub");
    GLint julia_x_location = glGetUniformLocation(*graphics_pipeline_object, "u_julia_x");
    GLint julia_y_location = glGetUniformLocation(*graphics_pipeline_object, "u_julia_y");

    U->xlb = U->x_point - U->lx_off;
    U->ylb = U->y_point - U->ly_off;

    U->xub = U->x_point + U->ux_off;
    U->yub = U->y_point + U->uy_off;

    if (state_location >= 0)
    {
        glUniform1i(state_location, U->state);
        glUniform1i(iter_location, U->iter);
        glUniform1i(x_res_location, U->x_res);
        glUniform1i(y_res_location, U->y_res);

        glUniform1f(xlb_location, U->xlb);
        glUniform1f(ylb_location, U->ylb);
        glUniform1f(xub_location, U->xub);
        glUniform1f(yub_location, U->yub);
        glUniform1f(julia_x_location, U->julia_x);
        glUniform1f(julia_y_location, U->julia_y);
    }
    else 
    {
        printf("Unhelpful Error!!!\n");
    }
}

void draw(GLuint *vertex_array_object, GLuint *vertex_buffer_object)
{
    GLCheck( glBindVertexArray(*vertex_array_object); )
    GLCheck( glBindBuffer(GL_ARRAY_BUFFER, *vertex_buffer_object); )

    GLCheck( glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); )
    glUseProgram(0);
}
