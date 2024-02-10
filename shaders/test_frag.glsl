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

struct ff
{
    float upper, lower;
};

ff split(float a)
{
     ff R;
    float scale = 4097.0;

    float p = a * scale;
    R.upper = a - p + p;
    R.lower = a - R.upper;

    return R;
}

ff mul12(ff A, ff B)
{
    ff R;
    float p, q;

    p = A.upper*B.upper;
    q = A.lower*B.upper + A.upper*B.lower;

    R.upper = p + q;
    R.lower = p - R.upper + q + A.lower*B.lower;

    return R;
}

ff ff_add(ff A, ff B)
{
    ff C;

    float R = A.upper + B.upper;
    float r = 0.0;

    if (abs(A.upper) > abs(B.upper))
    {
        r = A.upper - R + B.upper + B.lower + A.lower;
    }
    else
    {
        r = B.upper - R + A.upper + A.lower + B.lower;
    }

    C.upper = R + r;
    C.lower = R - C.upper + r;

    return C;
}

ff ff_sub(ff A, ff B)
{
    ff C;

    float R = A.upper - B.upper;
    float r = 0.0;

    if (abs(A.upper) > abs(B.upper))
    {
        r = A.upper - R - B.upper - B.lower + A.lower;
    }
    else
    {
        r = -B.upper - R + A.upper + A.lower - B.lower;
    }

    C.upper = R + r;
    C.lower = R - C.upper + r;

    return C;

}


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
    
    else if (u_state == 1)
    {
        x_scale = (u_xub - u_xlb) / max_res;
        y_scale = (u_yub - u_ylb) / max_res;

        a = u_xlb + (gl_FragCoord.x * x_scale); 
        b = u_ylb + (gl_FragCoord.y * y_scale); 

        re = a;
        im = b;

        ff ffa = split(a);
        ff ffb = split(b);
        
        ff ffre = split(re); 
        ff ffim = split(im); 
        
        ff ffna, ffnb;
        ff fftwo = {2, 0};
         
        for (i = 0; i < u_iter; i++)
        {
            ffna = ff_sub(mul12(ffa, ffa), mul12(ffb, ffb));      //a*a - b*b;
            ffnb = mul12(fftwo, mul12(ffa, ffb));                      //2*a*b;

            ffa = ff_add(ffna, ffre);       //na + re;
            ffb = ff_add(ffnb, ffim);     //nb + im;
            
            if (ffa.upper*ffa.upper + ffb.upper*ffb.upper >= 4.0)
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
















