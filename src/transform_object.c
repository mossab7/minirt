#include "../includes/transform_object.h"

void	translate_object(t_object *obj, t_vec3 translation)
{
	if (!obj)
		return ;
	switch (obj->type)
	{
		case SPHERE:
			obj->obj.sphere.center = add_vec3(obj->obj.sphere.center, translation);
			break ;
		case PLANE:
			obj->obj.plane.center = add_vec3(obj->obj.plane.center, translation);
			break ;
		case CYLINDER:
			obj->obj.cylinder.center = add_vec3(obj->obj.cylinder.center, translation);
			break ;
		case HYPERBOLDOID:
			obj->obj.hyperboloid.center = add_vec3(obj->obj.hyperboloid.center, translation);
			break ;
		case PARABOLOID:
			obj->obj.paraboloid.center = add_vec3(obj->obj.paraboloid.center, translation);
			break ;
	}
}

void	rotate_object(t_object *obj, t_vec3 rotation_angles)
{
	t_matrix4d	rot_x;
	t_matrix4d	rot_y;
	t_matrix4d	rot_z;
	t_matrix4d	rot_matrix;
	t_vec3		*axis;

	if (!obj)
		return ;
	rot_x = matrix4d_rotation_x(rotation_angles.x);
	rot_y = matrix4d_rotation_y(rotation_angles.y);
	rot_z = matrix4d_rotation_z(rotation_angles.z);
	rot_matrix = matrix4d_mult(rot_z, matrix4d_mult(rot_y, rot_x));
	axis = NULL;
	switch (obj->type)
	{
		case PLANE:
			axis = &obj->obj.plane.normal;
			break ;
		case CYLINDER:
			axis = &obj->obj.cylinder.axis;
			break ;
		case HYPERBOLDOID:
			axis = &obj->obj.hyperboloid.axis;
			break ;
		case PARABOLOID:
			axis = &obj->obj.paraboloid.axis;
			break ;
		case SPHERE:
			break ;
	}
	if (axis)
	{
		*axis = matrix4d_mult_vec3(rot_matrix, *axis);
		*axis = normalize_vec3(*axis);
	}
}
