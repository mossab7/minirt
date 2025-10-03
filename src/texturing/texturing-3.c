/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturing-3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 21:03:55 by zbengued          #+#    #+#             */
/*   Updated: 2025/09/16 22:01:46 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static double	grad(int hash, double x, double y)
{
	int	h;

	h = hash & 3;
	if (h == 0)
		return (x + y);
	else if (h == 1)
		return (-x + y);
	else if (h == 2)
		return (x - y);
	else
		return (-x - y);
}

double	noise_function(double x, double y)
{
	int (xi), yi;
	double (xf), yf, u, v, g00, g01, g10, g11;
	init_permutation_table();
	xi = (int)floor(x) & 255;
	yi = (int)floor(y) & 255;
	xf = x - floor(x);
	yf = y - floor(y);
	u = fade(xf);
	v = fade(yf);
	g00 = grad(get_perm()[get_perm()[xi] + yi], xf, yf);
	g01 = grad(get_perm()[get_perm()[xi] + yi + 1], xf, yf - 1);
	g10 = grad(get_perm()[get_perm()[xi + 1] + yi], xf - 1, yf);
	g11 = grad(get_perm()[get_perm()[xi + 1] + yi + 1], xf - 1, yf - 1);
	return (lerp(v, lerp(u, g00, g10), lerp(u, g01, g11)));
}

static void	fil_uv(t_hit_info *hit_info, double *u, double *v,
		t_pattern *pattern)
{
	if (hit_info->object_type == SPHERE)
	{
		*u = (0.5 + atan2(hit_info->normal.z, hit_info->normal.x) / (2 * M_PI))
			* pattern->scale;
		*v = (0.5 - asin(hit_info->normal.y) / M_PI) * pattern->scale;
	}
	else if (hit_info->object_type == PLANE)
	{
		*u = hit_info->point.x * pattern->scale;
		*v = hit_info->point.z * pattern->scale;
	}
	else if (hit_info->object_type == CYLINDER)
	{
		*u = atan2(hit_info->normal.x, hit_info->normal.z) / (2 * M_PI);
		*v = hit_info->point.y * pattern->scale;
	}
	else if (hit_info->object_type == CONE)
	{
		*u = atan2(hit_info->normal.x, hit_info->normal.z) / (2 * M_PI);
		*v = dot_vec3(sub_vec3(hit_info->point,
					hit_info->object->u_obj.cone.center),
				normalize_vec3(hit_info->object->u_obj.cone.axis));
		*u *= pattern->scale;
		*v *= pattern->scale;
	}
}

static void	calc_tang(t_hit_info *hit_info, t_vec3 *tangent, t_vec3 *bitangent)
{
	if (hit_info->object_type == SPHERE)
	{
		*tangent = (t_vec3){-hit_info->normal.z, 0, hit_info->normal.x};
		if (length_vec3(*tangent) < 0.001)
			*tangent = (t_vec3){1, 0, 0};
		*tangent = normalize_vec3(*tangent);
		*bitangent = normalize_vec3(cross_vec3(hit_info->normal, *tangent));
	}
	else
	{
		*tangent = (t_vec3){1, 0, 0};
		*bitangent = (t_vec3){0, 0, 1};
	}
}

t_vec3	calculate_bump_normal(t_hit_info *hit_info, t_pattern *pattern)
{
	t_vec3	tangent;
	t_vec3	bitangent;
	t_vec3	perturbed_normal;

	double (u), v, bump_u, bump_v, delta;
	if (hit_info->object_type == SPHERE || hit_info->object_type == PLANE
		|| hit_info->object_type == CYLINDER || hit_info->object_type == CONE)
		fil_uv(hit_info, &u, &v, pattern);
	else
		return (hit_info->normal);
	delta = 0.001;
	bump_u = noise_function(u + delta, v) - noise_function(u - delta, v);
	bump_v = noise_function(u, v + delta) - noise_function(u, v - delta);
	calc_tang(hit_info, &tangent, &bitangent);
	perturbed_normal = hit_info->normal;
	perturbed_normal = add_vec3(perturbed_normal, scale_vec3(tangent, bump_u
				* pattern->bump_strength));
	perturbed_normal = add_vec3(perturbed_normal, scale_vec3(bitangent, bump_v
				* pattern->bump_strength));
	return (normalize_vec3(perturbed_normal));
}
