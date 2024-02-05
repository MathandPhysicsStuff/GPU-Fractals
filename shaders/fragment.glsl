#version 460 core
    
in vec4 gl_FragCoord;

out vec4 FragColor;

uniform int u_state;
uniform int u_iter;
uniform int u_x_res;
uniform int u_y_res;

uniform float u_xlb;
uniform float u_ylb;
uniform float u_xub;
uniform float u_yub;
  
int i; 
float red = 0, green = 0, blue = 0;
float x_scale, y_scale;
float a, b, na, nb, re, im;
float max_res = max(u_x_res, u_y_res);
float min_res = min(u_x_res, u_y_res);

void main()
{
    if (u_state == 0)
    {
        x_scale = (u_xub - u_xlb) / max_res;
        y_scale = (u_yub - u_ylb) / max_res;

        a = u_xlb + (gl_FragCoord.x * x_scale); 
        b = u_ylb + (gl_FragCoord.y * y_scale); 
        
        re = a;
        im = b;
        
        for (i = 0; i < u_iter; i++)
        {
            na = a*a - b*b;
            nb = 2*a*b;

            a = na + re;
            b = nb + im;

            if (a*a + b*b > 4)
            {
                break;
            }
        }
        
        red = float(i % 256) / 256;
        green = float(i % 256) / 256;
        blue = float(i % 256) / 256;

        FragColor = vec4(red, green, blue, 1.0);
    }

    else
    {
        FragColor = vec4(0.0, 0.0, 1.0, 1.0);
    }
}

