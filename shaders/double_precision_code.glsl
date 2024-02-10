#version 460 core

struct ff
{
    float upper, lower;
};

ff split(float a);


ff mul12(float a, float b)
{
    ff A = split(a);
    ff B = split(b);

    float p = A.upper*B.upper;
    float q = A.lower*B.upper + A.upper*B.lower;

    ff R;

    R.upper = p + q;
    R.lower = p - R.upper + q + A.lower*B.lower;

    return R;
}

ff ff_mul(ff A, ff B)
{
    ff T = mul12(A.upper, B.upper);

    float c = A.upper*B.lower + A.lower*B.upper + T.lower;

    ff R;
    R.upper = T.upper + c;
    R.lower = T.upper - R.upper + c;

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

//not done
ff div(ff A, ff B)
{
    ff C;

    return C;
}

int less_greater(ff A, ff B)
{
    if (A.upper > B.upper)
        return 1;
    else 
        return 0;
}   















