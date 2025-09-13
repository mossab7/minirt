#include <minirt.h>

t_vec3 add_vec3(t_vec3 a, t_vec3 b)
{
    t_vec3 result;

    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;

    return (result);
}

t_vec3 scale_vec3(t_vec3 a, double scalar)
{
    t_vec3 result;

    result.x = a.x * scalar;
    result.y = a.y * scalar;
    result.z = a.z * scalar;

    return (result);
}

t_color scale_color(t_color a, double scalar)
{
    t_color result;

    result.r = a.r * scalar;
    result.g = a.g * scalar;
    result.b = a.b * scalar;

    return (result);
}

t_vec3 sub_vec3(t_vec3 a, t_vec3 b)
{
    t_vec3 result;

    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;

    return (result);
}
t_vec3 mul_vec3(t_vec3 a, t_vec3 b)
{
    t_vec3 result;

    result.x = a.x * b.x;
    result.y = a.y * b.y;
    result.z = a.z * b.z;

    return (result);
}
t_vec3 div_vec3(t_vec3 a, t_vec3 b)
{
    t_vec3 result;

    result.x = a.x / b.x;
    result.y = a.y / b.y;
    result.z = a.z / b.z;

    return (result);
}
t_vec3 mul_scalar_vec3(t_vec3 a, double scalar)
{
    t_vec3 result;

    result.x = a.x * scalar;
    result.y = a.y * scalar;
    result.z = a.z * scalar;

    return (result);
}
t_vec3 div_scalar_vec3(t_vec3 a, double scalar)
{
    t_vec3 result;

    result.x = a.x / scalar;
    result.y = a.y / scalar;
    result.z = a.z / scalar;

    return (result);
}

double length_vec3(t_vec3 a)
{
    return sqrtf(a.x * a.x + a.y * a.y + a.z * a.z);
}

t_vec3 normalize_vec3(t_vec3 a)
{
    t_vec3 result;
    double length;

    length = length_vec3(a);
    if (length == 0)
        return a;
    result.x = a.x / length;
    result.y = a.y / length;
    result.z = a.z / length;

    return (result);
}

double dot_vec3(t_vec3 a, t_vec3 b)
{
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}


double distance_vec3(t_vec3 a, t_vec3 b)
{
    return sqrtf((a.x - b.x) * (a.x - b.x) +
                 (a.y - b.y) * (a.y - b.y) +
                 (a.z - b.z) * (a.z - b.z));
}

t_vec3 cross_vec3(t_vec3 a, t_vec3 b)
{
    t_vec3 result;

    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.x * b.z;
    result.z = a.x * b.y - a.y * b.x;

    return (result);
}

t_vec3 vec3_negate(t_vec3 vec)
{
    t_vec3 result;

    result.x = -vec.x;
    result.y = -vec.y;
    result.z = -vec.z;

    return (result);
}