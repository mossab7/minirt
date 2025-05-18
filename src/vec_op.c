#include <minirt.h>

t_vec4 add_vec4(t_vec4 a, t_vec4 b)
{
    t_vec4 result;

    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    result.w = a.w + b.w;

    return (result);
}
t_vec4 sub_vec4(t_vec4 a, t_vec4 b)
{
    t_vec4 result;

    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    result.w = a.w - b.w;

    return (result);
}
t_vec4 mul_vec4(t_vec4 a, t_vec4 b)
{
    t_vec4 result;

    result.x = a.x * b.x;
    result.y = a.y * b.y;
    result.z = a.z * b.z;
    result.w = a.w * b.w;

    return (result);
}
t_vec4 div_vec4(t_vec4 a, t_vec4 b)
{
    t_vec4 result;

    result.x = a.x / b.x;
    result.y = a.y / b.y;
    result.z = a.z / b.z;
    result.w = a.w / b.w;

    return (result);
}
t_vec4 mul_scalar_vec4(t_vec4 a, float scalar)
{
    t_vec4 result;

    result.x = a.x * scalar;
    result.y = a.y * scalar;
    result.z = a.z * scalar;
    result.w = a.w * scalar;

    return (result);
}
t_vec4 div_scalar_vec4(t_vec4 a, float scalar)
{
    t_vec4 result;

    result.x = a.x / scalar;
    result.y = a.y / scalar;
    result.z = a.z / scalar;
    result.w = a.w / scalar;

    return (result);
}

t_vec4 normalize_vec4(t_vec4 a)
{
    t_vec4 result;
    float length;

    length = sqrtf(a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w);
    if (length == 0)
        return a;
    result.x = a.x / length;
    result.y = a.y / length;
    result.z = a.z / length;
    result.w = a.w / length;

    return (result);
}

float dot_vec4(t_vec4 a, t_vec4 b)
{
    return (a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w);
}

float length_vec4(t_vec4 a)
{
    return sqrtf(a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w);
}

float distance_vec4(t_vec4 a, t_vec4 b)
{
    return sqrtf((a.x - b.x) * (a.x - b.x) +
                 (a.y - b.y) * (a.y - b.y) +
                 (a.z - b.z) * (a.z - b.z) +
                 (a.w - b.w) * (a.w - b.w));
}

t_vec4 cross_vec4(t_vec4 a, t_vec4 b)
{
    t_vec4 result;

    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.x * b.z;
    result.z = a.x * b.y - a.y * b.x;
    result.w = 1.0f;

    return (result);
}
