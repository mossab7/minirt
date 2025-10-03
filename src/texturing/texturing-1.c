/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturing-1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 20:58:40 by zbengued          #+#    #+#             */
/*   Updated: 2025/09/16 20:59:06 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

static void	calculate_sphere(double *u, double *v, t_hit_info *hit_info)
{
	*u = 0.5 + atan2(hit_info->normal.z, hit_info->normal.x) / (2 * M_PI);
	*v = 0.5 - asin(hit_info->normal.y) / M_PI;
}

static void	calculate_plane(double *u, double *v, t_hit_info *hit_info)
{
	*u = hit_info->point.x;
	*v = hit_info->point.z;
}

static void	calculate_cylinder(double *u, double *v, t_hit_info *hit_info)
{
	*u = atan2(hit_info->normal.x, hit_info->normal.z) / (2 * M_PI);
	*v = hit_info->point.y;
}

static void	calculate_cone(double *u, double *v, t_hit_info *hit_info)
{
	*u = atan2(hit_info->normal.x, hit_info->normal.z) / (2 * M_PI);
	*v = dot_vec3(sub_vec3(hit_info->point,
				hit_info->object->u_obj.cone.center),
			normalize_vec3(hit_info->object->u_obj.cone.axis));
}

t_color	apply_checkerboard_pattern(t_hit_info *hit_info, t_pattern *pattern)
{
	double (u), v = 0;
	int (checker_u), checker_v;
	if (hit_info->object_type == SPHERE)
		calculate_sphere(&u, &v, hit_info);
	else if (hit_info->object_type == PLANE)
		calculate_plane(&u, &v, hit_info);
	else if (hit_info->object_type == CYLINDER)
		calculate_cylinder(&u, &v, hit_info);
	else if (hit_info->object_type == CONE)
		calculate_cone(&u, &v, hit_info);
	else
	{
		u = 0;
		v = 0;
	}
	checker_u = (int)floor(u * pattern->scale);
	checker_v = (int)floor(v * pattern->scale);
	if ((checker_u + checker_v) % 2 == 0)
		return (pattern->color1);
	return (pattern->color2);
}
