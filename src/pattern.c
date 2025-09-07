/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deepseeko <deepseeko@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 19:02:35 by deepseeko         #+#    #+#             */
/*   Updated: 2025/07/12 19:02:36 by deepseeko        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>
#include <stdbool.h>

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

t_color	apply_checkerboard_pattern(t_hit_info *hit_info, t_pattern *pattern)
{
	double	u, v;
	int		checker_u, checker_v;

	if (hit_info->object_type == SPHERE)
	{
		u = 0.5 + atan2(hit_info->normal.z, hit_info->normal.x) / (2 * M_PI);
		v = 0.5 - asin(hit_info->normal.y) / M_PI;
	}
	else if (hit_info->object_type == PLANE)
	{
		u = hit_info->point.x;
		v = hit_info->point.z;
	}
	else if (hit_info->object_type == CYLINDER)
	{
		u = atan2(hit_info->normal.x, hit_info->normal.z) / (2 * M_PI);
		v = hit_info->point.y;
	}
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

static const int p[] = {
    151,160,137,91,90,15,131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,
    142,8,99,37,240,21,10,23,190,6,148,247,120,234,75,0,26,197,62,94,252,219,
    203,117,35,11,32,57,177,33,88,237,149,56,87,174,20,125,136,171,168,68,175,
    74,165,71,134,139,48,27,166,77,146,158,231,83,111,229,122,60,211,133,230,
    220,105,92,41,55,46,245,40,244,102,143,54,65,25,63,161,1,216,80,73,209,76,
    132,187,208,89,18,169,200,196,135,130,116,188,159,86,164,100,109,198,173,
    186,3,64,52,217,226,250,124,123,5,202,38,147,118,126,255,82,85,212,207,
    206,59,227,47,16,58,17,182,189,28,42,223,183,170,213,119,248,152,2,44,154,
    163,70,221,153,101,155,167,43,172,9,129,22,39,253,19,98,108,110,79,113,224,
    232,178,185,112,104,218,246,97,228,251,34,242,193,238,210,144,12,191,179,
    162,241,81,51,145,235,249,14,239,107,49,192,214,31,181,199,106,157,184,84,
    204,176,115,121,50,45,127,4,150,254,138,236,205,93,222,114,67,29,24,72,243,
    141,128,195,78,66,215,61,156,180
};

static int perm[512];

static void init_permutation_table()
{
    int i;
    static bool initialized = false;

    if (initialized)
        return;
    i = 0;
    while (i < 256)
    {
        perm[i] = p[i];
        perm[i + 256] = p[i];
        i++;
    }
    initialized = true;
}

static double fade(double t)
{
    return t * t * t * (t * (t * 6 - 15) + 10);
}

static double lerp(double t, double a, double b)
{
    return a + t * (b - a);
}

static double grad(int hash, double x, double y)
{
    int h = hash & 7;
    double u = h < 4 ? x : y;
    double v = h < 4 ? y : x;
    return ((h & 1) != 0 ? -u : u) + ((h & 2) != 0 ? -v : v);
}

double	noise_function(double x, double y)
{
    int xi, yi;
    double xf, yf, u, v, g00, g01, g10, g11;

    init_permutation_table();
    xi = (int)floor(x) & 255;
    yi = (int)floor(y) & 255;
    xf = x - floor(x);
    yf = y - floor(y);
    u = fade(xf);
    v = fade(yf);
    
    g00 = grad(perm[perm[xi] + yi], xf, yf);
    g01 = grad(perm[perm[xi] + yi + 1], xf, yf - 1);
    g10 = grad(perm[perm[xi + 1] + yi], xf - 1, yf);
    g11 = grad(perm[perm[xi + 1] + yi + 1], xf - 1, yf - 1);
    
    return lerp(v, lerp(u, g00, g10), lerp(u, g01, g11));
}

t_vec3	calculate_bump_normal(t_hit_info *hit_info, t_pattern *pattern)
{
	double	u, v, bump_u, bump_v, delta;
	t_vec3	tangent, bitangent, perturbed_normal;

	if (hit_info->object_type == SPHERE)
	{
		u = 0.5 + atan2(hit_info->normal.z, hit_info->normal.x) / (2 * M_PI);
		v = 0.5 - asin(hit_info->normal.y) / M_PI;
		u *= pattern->scale;
		v *= pattern->scale;
	}
	else if (hit_info->object_type == PLANE)
	{
		u = hit_info->point.x * pattern->scale;
		v = hit_info->point.z * pattern->scale;
	}
	else if (hit_info->object_type == CYLINDER)
	{
		u = atan2(hit_info->normal.x, hit_info->normal.z) / (2 * M_PI);
		v = hit_info->point.y * pattern->scale;
	}
	else
		return (hit_info->normal);
	delta = 0.001;
	bump_u = noise_function(u + delta, v) - noise_function(u - delta, v);
	bump_v = noise_function(u, v + delta) - noise_function(u, v - delta);
	if (hit_info->object_type == SPHERE)
	{
		tangent = (t_vec3){-hit_info->normal.z, 0, hit_info->normal.x};
		if (length_vec3(tangent) < 0.001)
			tangent = (t_vec3){1, 0, 0};
		tangent = normalize_vec3(tangent);
		bitangent = normalize_vec3(cross_vec3(hit_info->normal, tangent));
	}
	else
	{
		tangent = (t_vec3){1, 0, 0};
		bitangent = (t_vec3){0, 0, 1};
	}
	perturbed_normal = hit_info->normal;
	perturbed_normal = add_vec3(perturbed_normal,
		scale_vec3(tangent, bump_u * pattern->bump_strength));
	perturbed_normal = add_vec3(perturbed_normal,
		scale_vec3(bitangent, bump_v * pattern->bump_strength));
	return (normalize_vec3(perturbed_normal));
}

t_vec3	apply_bump_mapping(t_hit_info *hit_info, t_pattern *pattern)
{
	if (pattern->type == PATTERN_BUMP_MAP)
		return (calculate_bump_normal(hit_info, pattern));
	return (hit_info->normal);
}

t_color	get_pattern_color(t_hit_info *hit_info, void *object)
{
	t_pattern	*pattern;

	pattern = NULL;
	if (hit_info->object_type == SPHERE)
	{
		pattern = &((t_sphere *)object)->pattern;
		if (pattern && pattern->type == PATTERN_CHECKERBOARD)
			return (apply_checkerboard_pattern(hit_info, pattern));
		return (((t_sphere *)object)->color);
	}
	else if (hit_info->object_type == PLANE)
	{
		pattern = &((t_plane *)object)->pattern;
		if (pattern && pattern->type == PATTERN_CHECKERBOARD)
			return (apply_checkerboard_pattern(hit_info, pattern));
		return (((t_plane *)object)->color);
	}
	else if (hit_info->object_type == CYLINDER)
	{
		pattern = &((t_cylinder *)object)->pattern;
		if (pattern && pattern->type == PATTERN_CHECKERBOARD)
			return (apply_checkerboard_pattern(hit_info, pattern));
		return (((t_cylinder *)object)->color);
	}
	return ((t_color){0, 0, 0});
}
