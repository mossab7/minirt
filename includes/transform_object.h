#ifndef TRANSFORM_OBJECT_H
# define TRANSFORM_OBJECT_H

# include "minirt.h"

void	translate_object(t_object *obj, t_vec3 translation);
void	rotate_object(t_object *obj, t_vec3 rotation_angles);

#endif
