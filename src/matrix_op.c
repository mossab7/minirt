#include <minirt.h>


t_matrix4d matrix4d_translation(t_vec3 translation)
{
    t_matrix4d matrix;

    matrix.data[0][0] = 1.0f;
    matrix.data[0][1] = 0.0f;
    matrix.data[0][2] = 0.0f;
    matrix.data[0][3] = translation.x;
    matrix.data[1][0] = 0.0f;
    matrix.data[1][1] = 1.0f;
    matrix.data[1][2] = 0.0f;
    matrix.data[1][3] = translation.y;
    matrix.data[2][0] = 0.0f;
    matrix.data[2][1] = 0.0f;
    matrix.data[2][2] = 1.0f;
    matrix.data[2][3] = translation.z;
    matrix.data[3][0] = 0.0f;
    matrix.data[3][1] = 0.0f;
    matrix.data[3][2] = 0.0f;
    matrix.data[3][3] = 1.0f;

    return (matrix);
}
t_matrix4d matrix4d_rotation_x(double angle)
{
    t_matrix4d matrix;

    matrix.data[0][0] = 1.0f;
    matrix.data[0][1] = 0.0f;
    matrix.data[0][2] = 0.0f;
    matrix.data[0][3] = 0.0f;
    matrix.data[1][0] = 0.0f;
    matrix.data[1][1] = cos(angle);
    matrix.data[1][2] = -sin(angle);
    matrix.data[1][3] = 0.0f;
    matrix.data[2][0] = 0.0f;
    matrix.data[2][1] = sin(angle);
    matrix.data[2][2] = cos(angle);
    matrix.data[2][3] = 0.0f;
    matrix.data[3][0] = 0.0f;
    matrix.data[3][1] = 0.0f;
    matrix.data[3][2] = 0.0f;
    matrix.data[3][3] = 1.0f;

    return (matrix);
}
t_matrix4d matrix4d_rotation_y(double angle)
{
    t_matrix4d matrix;

    matrix.data[0][0] = cos(angle);
    matrix.data[0][1] = 0.0f;
    matrix.data[0][2] = sin(angle);
    matrix.data[0][3] = 0.0f;
    matrix.data[1][0] = 0.0f;
    matrix.data[1][1] = 1.0f;
    matrix.data[1][2] = 0.0f;
    matrix.data[1][3] = 0.0f;
    matrix.data[2][0] = -sin(angle);
    matrix.data[2][1] = 0.0f;
    matrix.data[2][2] = cos(angle);
    matrix.data[2][3] = 0.0f;
    matrix.data[3][0] = 0.0f;
    matrix.data[3][1] = 0.0f;
    matrix.data[3][2] = 0.0f;
    matrix.data[3][3] = 1.0f;

    return (matrix);
}
t_matrix4d matrix4d_rotation_z(double angle)
{
    t_matrix4d matrix;

    matrix.data[0][0] = cos(angle);
    matrix.data[0][1] = -sin(angle);
    matrix.data[0][2] = 0.0f;
    matrix.data[0][3] = 0.0f;
    matrix.data[1][0] = sin(angle);
    matrix.data[1][1] = cos(angle);
    matrix.data[1][2] = 0.0f;
    matrix.data[1][3] = 0.0f;
    matrix.data[2][0] = 0.0f;
    matrix.data[2][1] = 0.0f;
    matrix.data[2][2] = 1.0f;
    matrix.data[2][3] = 0.0f;
    matrix.data[3][0] = 0.0f;
    matrix.data[3][1] = 0.0f;
    matrix.data[3][2] = 0.0f;
    matrix.data[3][3] = 1.0f;

    return (matrix);
}
t_matrix4d matrix4d_mult(t_matrix4d a, t_matrix4d b)
{
    t_matrix4d result;
    int i, j, k;

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            result.data[i][j] = 0.0f;
            for (k = 0; k < 4; k++)
            {
                result.data[i][j] += a.data[i][k] * b.data[k][j];
            }
        }
    }

    return (result);
}

t_matrix4d matrix4d_rotation(t_vec3 rotation)
{
    t_matrix4d matrix;

    matrix = matrix4d_rotation_x(rotation.x);
    matrix = matrix4d_mult(matrix, matrix4d_rotation_y(rotation.y));
    matrix = matrix4d_mult(matrix, matrix4d_rotation_z(rotation.z));

    return (matrix);
}

t_matrix4d matrix4d_scale(t_vec3 scale)
{
    t_matrix4d matrix;

    matrix.data[0][0] = scale.x;
    matrix.data[0][1] = 0.0f;
    matrix.data[0][2] = 0.0f;
    matrix.data[0][3] = 0.0f;
    matrix.data[1][0] = 0.0f;
    matrix.data[1][1] = scale.y;
    matrix.data[1][2] = 0.0f;
    matrix.data[1][3] = 0.0f;
    matrix.data[2][0] = 0.0f;
    matrix.data[2][1] = 0.0f;
    matrix.data[2][2] = scale.z;
    matrix.data[2][3] = 0.0f;
    matrix.data[3][0] = 0.0f;
    matrix.data[3][1] = 0.0f;
    matrix.data[3][2] = 0.0f;
    matrix.data[3][3] = 1.0f;

    return (matrix);
}
t_matrix4d matrix4d_identity(void)
{
    t_matrix4d matrix;

    matrix.data[0][0] = 1.0f;
    matrix.data[0][1] = 0.0f;
    matrix.data[0][2] = 0.0f;
    matrix.data[0][3] = 0.0f;
    matrix.data[1][0] = 0.0f;
    matrix.data[1][1] = 1.0f;
    matrix.data[1][2] = 0.0f;
    matrix.data[1][3] = 0.0f;
    matrix.data[2][0] = 0.0f;
    matrix.data[2][1] = 0.0f;
    matrix.data[2][2] = 1.0f;
    matrix.data[2][3] = 0.0f;
    matrix.data[3][0] = 0.0f;
    matrix.data[3][1] = 0.0f;
    matrix.data[3][2] = 0.0f;
    matrix.data[3][3] = 1.0f;

    return (matrix);
}
t_matrix4d matrix4d_transpose(t_matrix4d matrix)
{
    t_matrix4d result;
    int i, j;

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            result.data[i][j] = matrix.data[j][i];
        }
    }

    return (result);
}

t_matrix4d matrix4d_inverse(t_matrix4d matrix)
{
    t_matrix4d result;
    double det;

    det = matrix.data[0][0] * (matrix.data[1][1] * matrix.data[2][2] - matrix.data[1][2] * matrix.data[2][1]) -
          matrix.data[0][1] * (matrix.data[1][0] * matrix.data[2][2] - matrix.data[1][2] * matrix.data[2][0]) +
          matrix.data[0][2] * (matrix.data[1][0] * matrix.data[2][1] - matrix.data[1][1] * matrix.data[2][0]);

    if (det == 0.0f)
        return (matrix);

    result.data[0][0] = (matrix.data[1][1] * matrix.data[2][2] - matrix.data[1][2] * matrix.data[2][1]) / det;
    result.data[0][1] = -(matrix.data[0][1] * matrix.data[2][2] - matrix.data[0][2] * matrix.data[2][1]) / det;
    result.data[0][2] = (matrix.data[0][1] * matrix.data[1][2] - matrix.data[0][2] * matrix.data[1][1]) / det;
    
    result.data[1][0] = -(matrix.data[1][0] * matrix.data[2][2] - matrix.data[1][2] * matrix.data[2][0]) / det;
    result.data[1][1] = (matrix.data[0][0] * matrix.data[2][2] - matrix.data[0][2] * matrix.data[2][0]) / det;
    result.data[1][2] = -(matrix.data[0][0] * matrix.data[1][2] - matrix.data[0][2] * matrix.data[1][0]) / det;
    
    result.data[2][0] = (matrix.data[1][0] * matrix.data[2][1] - matrix.data[1][1] * matrix.data[2][0]) / det;
    result.data[2][1] = -(matrix.data[0][0] * matrix.data[2][1] - matrix.data[0][1] * matrix.data[2][0]) / det;
    result.data[2][2] = (matrix.data[0][0] * matrix.data[1][1] - matrix.data[0][1] * matrix.data[1][0]) / det;
    
    result.data[0][3] = -(result.data[0][0] * matrix.data[0][3] + 
                        result.data[0][1] * matrix.data[1][3] + 
                        result.data[0][2] * matrix.data[2][3]);
    
    result.data[1][3] = -(result.data[1][0] * matrix.data[0][3] + 
                        result.data[1][1] * matrix.data[1][3] + 
                        result.data[1][2] * matrix.data[2][3]);
    
    result.data[2][3] = -(result.data[2][0] * matrix.data[0][3] + 
                        result.data[2][1] * matrix.data[1][3] + 
                        result.data[2][2] * matrix.data[2][3]);
    
    result.data[3][0] = 0.0f;
    result.data[3][1] = 0.0f;
    result.data[3][2] = 0.0f;
    result.data[3][3] = 1.0f;
    return (result);
}

t_vec3 matrix4d_mult_vec3(t_matrix4d matrix, t_vec3 vec)
{
    t_vec3 result;

    result.x = matrix.data[0][0] * vec.x + matrix.data[0][1] * vec.y + matrix.data[0][2] * vec.z + matrix.data[0][3];
    result.y = matrix.data[1][0] * vec.x + matrix.data[1][1] * vec.y + matrix.data[1][2] * vec.z + matrix.data[1][3];
    result.z = matrix.data[2][0] * vec.x + matrix.data[2][1] * vec.y + matrix.data[2][2] * vec.z + matrix.data[2][3];
    
    return (result);
}

t_matrix4d matrix4d_shearing(double xy, double xz, double yx, double yz, double zx, double zy)
{
    t_matrix4d matrix;

    matrix.data[0][0] = 1.0f;
    matrix.data[0][1] = xy;
    matrix.data[0][2] = xz;
    matrix.data[0][3] = 0.0f;
    matrix.data[1][0] = yx;
    matrix.data[1][1] = 1.0f;
    matrix.data[1][2] = yz;
    matrix.data[1][3] = 0.0f;
    matrix.data[2][0] = zx;
    matrix.data[2][1] = zy;
    matrix.data[2][2] = 1.0f;
    matrix.data[2][3] = 0.0f;
    matrix.data[3][0] = 0.0f;
    matrix.data[3][1] = 0.0f;
    matrix.data[3][2] = 0.0f;
    matrix.data[3][3] = 1.0f;

    return (matrix);
}

t_matrix4d matrix4d_scaling(t_vec3 scale)
{
    t_matrix4d matrix;

    matrix.data[0][0] = scale.x;
    matrix.data[0][1] = 0.0f;
    matrix.data[0][2] = 0.0f;
    matrix.data[0][3] = 0.0f;
    matrix.data[1][0] = 0.0f;
    matrix.data[1][1] = scale.y;
    matrix.data[1][2] = 0.0f;
    matrix.data[1][3] = 0.0f;
    matrix.data[2][0] = 0.0f;
    matrix.data[2][1] = 0.0f;
    matrix.data[2][2] = scale.z;
    matrix.data[2][3] = 0.0f;
    matrix.data[3][0] = 0.0f;
    matrix.data[3][1] = 0.0f;
    matrix.data[3][2] = 0.0f;
    matrix.data[3][3] = 1.0f;

    return (matrix);
}


t_matrix4d view_matrix(t_vec3 camera_pos, t_vec3 camera_dir)
{
    t_matrix4d translation;
    t_matrix4d rotation;
    t_matrix4d view;
    t_vec3 neg_pos;

    neg_pos = vec3_negate(camera_pos);

    translation = matrix4d_translation(neg_pos);
    
    rotation = matrix4d_rotation(camera_dir);
    
    rotation = matrix4d_transpose(rotation);
    
    view = matrix4d_mult(rotation, translation);

    return (view);
}