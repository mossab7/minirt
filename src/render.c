#include <minirt.h>

bool		is_in_shadow(t_scene *scene, t_hit_info *hit_info);

t_vec3	cross_product(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}

t_vec3	screen_to_world(int x, int y)
{
	t_vec3	result;

	result.x = ((2.0 * x) / WIN_WIDTH) - 1.0;
	result.y = ((2.0 * y) / WIN_HEIGHT) - 1.0;
	result.z = 0.0;
	return (result);
}

t_ray	shoot_ray(t_scene *scene, t_vec3 screen_pos)
{
	t_ray	ray;
	t_vec3	direction;
	t_vec3	vertical;
	t_vec3	horizontal;

	vertical = scale_vec3(scene->camera.up, screen_pos.y
			* scene->camera.height);
	horizontal = scale_vec3(scene->camera.right, screen_pos.x
			* scene->camera.width);
	direction = scene->camera.direction;
	direction = add_vec3(direction, horizontal);
	direction = add_vec3(direction, vertical);
	ray.origin = scene->camera.position;
	ray.direction = normalize_vec3(direction);
	return (ray);
}

t_hit_info	intersect_sphere(t_ray *ray, t_sphere *sphere)
{
	t_hit_info	hit_info;
	t_vec3		oc;
	double		a;
	double		b;
	double		c;
	double		discriminant;
	double		t1;
	double		t2;

	hit_info.distance = -1.0;
	hit_info.hit = false;
	oc = sub_vec3(ray->origin, sphere->center);
	a = dot_vec3(ray->direction, ray->direction);
	b = 2.0 * dot_vec3(oc, ray->direction);
	c = dot_vec3(oc, oc) - (sphere->diameter * sphere->diameter) / 4.0;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
	{
		return (hit_info);
	}
	t1 = (-b - sqrt(discriminant)) / (2.0 * a);
	t2 = (-b + sqrt(discriminant)) / (2.0 * a);
	if (t1 > 0.001)
		hit_info.distance = t1;
	else if (t2 > 0.001)
		hit_info.distance = t2;
	else
		return (hit_info);
	hit_info.point = add_vec3(ray->origin,
			scale_vec3(ray->direction, hit_info.distance));
	hit_info.normal = normalize_vec3(sub_vec3(hit_info.point,
			sphere->center));
	hit_info.color = sphere->color;
	hit_info.hit = true;
	return (hit_info);
}

t_hit_info	intersect_cylinder_side(t_ray *ray, t_cylinder *cylinder)
{
	t_hit_info	hit_info;
	t_vec3		axis;
	t_vec3		oc;
	double		rd_dot_axis;
	double		oc_dot_axis;
	double		a;
	double		b;
	double		c;
	double		discriminant;
	double		t1;
	double		t2;
	double		t;
	t_vec3		hit_point;
	t_vec3		center_to_hit;
	double		projection;
	t_vec3		axis_point;

	hit_info.distance = -1.0;
	hit_info.hit = false;
	axis = normalize_vec3(cylinder->axis);
	oc = sub_vec3(ray->origin, cylinder->center);
	rd_dot_axis = dot_vec3(ray->direction, axis);
	oc_dot_axis = dot_vec3(oc, axis);
	a = dot_vec3(ray->direction, ray->direction) - pow(rd_dot_axis, 2);
	b = 2 * (dot_vec3(ray->direction, oc) - rd_dot_axis * oc_dot_axis);
	c = dot_vec3(oc, oc) - pow(oc_dot_axis, 2)
		- pow(cylinder->diameter / 2, 2);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (hit_info);
	t1 = (-b - sqrt(discriminant)) / (2 * a);
	t2 = (-b + sqrt(discriminant)) / (2 * a);
	t = t1 > 0.001 ? t1 : t2;
	if (t < 0.001)
		return (hit_info);
	hit_point = add_vec3(ray->origin, scale_vec3(ray->direction, t));
	center_to_hit = sub_vec3(hit_point, cylinder->center);
	projection = dot_vec3(center_to_hit, axis);
	if (fabs(projection) > cylinder->height / 2)
		return (hit_info);
	hit_info.distance = t;
	hit_info.point = hit_point;
	axis_point = add_vec3(cylinder->center,
			scale_vec3(axis, projection));
	hit_info.normal = normalize_vec3(sub_vec3(hit_point, axis_point));
	hit_info.color = cylinder->color;
	hit_info.hit = true;
	return (hit_info);
}

t_hit_info	intersect_cylinder_cap(t_ray *ray, t_cylinder *cylinder,
		int cap_side)
{
	t_hit_info	hit_info;
	t_vec3		axis;
	t_vec3		cap_center;
	t_vec3		cap_normal;
	double		denom;
	double		t;
	t_vec3		hit_point;
	t_vec3		to_center;
	t_vec3		radial_component;
	double		radius;

	hit_info.distance = -1.0;
	hit_info.hit = false;
	axis = normalize_vec3(cylinder->axis);
	cap_center = add_vec3(cylinder->center,
			scale_vec3(axis, cap_side * (cylinder->height / 2)));
	cap_normal = scale_vec3(axis, cap_side);
	denom = dot_vec3(cap_normal, ray->direction);
	if (fabs(denom) < EPSILON)
		return (hit_info);
	t = dot_vec3(sub_vec3(cap_center, ray->origin), cap_normal) / denom;
	if (t < 0.001)
		return (hit_info);
	hit_point = add_vec3(ray->origin, scale_vec3(ray->direction, t));
	to_center = sub_vec3(hit_point, cap_center);
	radial_component = sub_vec3(to_center,
			scale_vec3(axis, dot_vec3(to_center, axis)));
	radius = cylinder->diameter / 2;
	if (length_vec3(radial_component) > radius)
		return (hit_info);
	hit_info.distance = t;
	hit_info.point = hit_point;
	hit_info.normal = cap_normal;
	hit_info.color = cylinder->color;
	hit_info.hit = true;
	return (hit_info);
}

t_hit_info	intersect_cylinder(t_ray *ray, t_cylinder *cylinder)
{
	t_hit_info	hit_info;
	t_hit_info	side_hit;
	t_hit_info	top_cap_hit;
	t_hit_info	bottom_cap_hit;

	hit_info.distance = -1.0;
	hit_info.hit = false;
	side_hit = intersect_cylinder_side(ray, cylinder);
	top_cap_hit = intersect_cylinder_cap(ray, cylinder, 1);
	bottom_cap_hit = intersect_cylinder_cap(ray, cylinder, -1);
	if (side_hit.hit && (!top_cap_hit.hit
			|| side_hit.distance < top_cap_hit.distance)
		&& (!bottom_cap_hit.hit
			|| side_hit.distance < bottom_cap_hit.distance))
		hit_info = side_hit;
	else if (top_cap_hit.hit && (!bottom_cap_hit.hit
			|| top_cap_hit.distance < bottom_cap_hit.distance))
		hit_info = top_cap_hit;
	else if (bottom_cap_hit.hit)
		hit_info = bottom_cap_hit;
	return (hit_info);
}

t_hit_info	intersect_plane(t_ray *ray, t_plane *plane)
{
	t_hit_info	hit_info;
	double		denom;
	double		t;

	hit_info.distance = -1.0;
	hit_info.hit = false;
	denom = dot_vec3(plane->normal, ray->direction);
	if (fabs(denom) < EPSILON)
		return (hit_info);
	t = dot_vec3(sub_vec3(plane->center, ray->origin), plane->normal) / denom;
	if (t < 0.001)
		return (hit_info);
	hit_info.distance = t;
	hit_info.point = add_vec3(ray->origin,
			scale_vec3(ray->direction, hit_info.distance));
	hit_info.normal = plane->normal;
	hit_info.color = plane->color;
	hit_info.hit = true;
	return (hit_info);
}

static t_pattern	*get_object_pattern(t_hit_info *hit_info)
{
	t_pattern	*pattern;

	pattern = NULL;
	if (!hit_info->object)
		return (NULL);
	if (hit_info->object_type == SPHERE)
		pattern = &hit_info->object->obj.sphere.pattern;
	else if (hit_info->object_type == PLANE)
		pattern = &hit_info->object->obj.plane.pattern;
	else if (hit_info->object_type == CYLINDER)
		pattern = &hit_info->object->obj.cylinder.pattern;
	return (pattern);
}

t_color	calculate_lighting(t_scene *scene, t_hit_info *hit_info)
{
	t_color		base_color;
	t_color		final_color;
	t_vec3		light_dir;
	t_vec3		surface_normal;
	double		light_intensity;
	double		diffuse;
	t_pattern	*pattern;
	t_material	material;
	t_vec3		view_dir;
	t_vec3		reflect_dir;
	double		specular_factor;
	double		specular_intensity;

	material.specular = 0.5;
	material.diffuse = 0.9;
	material.shininess = 32.0;

	base_color = get_pattern_color(hit_info, &hit_info->object->obj);
	pattern = get_object_pattern(hit_info);
	if (pattern && pattern->type == PATTERN_BUMP_MAP)
		surface_normal = apply_bump_mapping(hit_info, pattern);
	else
		surface_normal = hit_info->normal;
	light_dir = normalize_vec3(sub_vec3(scene->light.position,
			hit_info->point));
	light_intensity = fmax(0.0, dot_vec3(surface_normal, light_dir));
	if (is_in_shadow(scene, hit_info))
		light_intensity = 0.0;
	diffuse = scene->amb_light.ratio + light_intensity * material.diffuse;

	view_dir = normalize_vec3(sub_vec3(scene->camera.position, hit_info->point));
	reflect_dir = sub_vec3(scale_vec3(surface_normal, 2 * dot_vec3(light_dir, surface_normal)), light_dir);
	specular_factor = pow(fmax(0.0, dot_vec3(view_dir, reflect_dir)), material.shininess);
	specular_intensity = material.specular * specular_factor * light_intensity;

	final_color.r = base_color.r * diffuse + specular_intensity * scene->light.color.r;
	final_color.g = base_color.g * diffuse + specular_intensity * scene->light.color.g;
	final_color.b = base_color.b * diffuse + specular_intensity * scene->light.color.b;

	return (final_color);
}

t_hit_info	find_closest_intersection(t_container *objects, t_ray *ray)
{
	t_object	*object;
	double		closest_distance;
	size_t		i;
	t_hit_info	hit_info;
	t_hit_info	closest_hit;

	closest_distance = -1.0;
	closest_hit.distance = -1.0;
	closest_hit.hit = false;
	for (i = 0; i < objects->size; i++)
	{
		object = get_object(objects, i);
		if (object->type == SPHERE)
			hit_info = intersect_sphere(ray, &object->obj.sphere);
		else if (object->type == PLANE)
			hit_info = intersect_plane(ray, &object->obj.plane);
		else if (object->type == CYLINDER)
			hit_info = intersect_cylinder(ray, &object->obj.cylinder);
		else
			continue ;
		if (hit_info.hit && hit_info.distance > 0
			&& (closest_distance < 0
				|| hit_info.distance < closest_distance))
		{
			closest_distance = hit_info.distance;
			closest_hit = hit_info;
			closest_hit.object_type = object->type;
			closest_hit.object = object;
		}
	}
	return (closest_hit);
}

bool	is_in_shadow(t_scene *scene, t_hit_info *hit_info)
{
	t_ray		shadow_ray;
	t_hit_info	shadow_hit;
	double		light_distance;

	shadow_ray.origin = hit_info->point;
	shadow_ray.direction = normalize_vec3(sub_vec3(scene->light.position,
			hit_info->point));
	shadow_ray.origin = add_vec3(shadow_ray.origin,
			scale_vec3(shadow_ray.direction, 0.001));
	light_distance = length_vec3(sub_vec3(scene->light.position,
			hit_info->point));
	shadow_hit = find_closest_intersection(scene->objects, &shadow_ray);
	return (shadow_hit.hit && shadow_hit.distance > 0
		&& shadow_hit.distance < light_distance);
}

t_color	trace_ray(t_scene *scene, t_ray *ray)
{
	t_hit_info	hit_info;
	t_color		color;

	hit_info = find_closest_intersection(scene->objects, ray);
	if (!hit_info.hit || hit_info.distance < 0)
	{
		return (scene->amb_light.color);
	}
	color = calculate_lighting(scene, &hit_info);
	return (color);
}

void	put_pixel_to_image(t_canvas *canvas, int x, int y,
		t_color color)
{
	char	*dst;
	int		int_color;
	int		r;
	int		g;
	int		b;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	r = (int)(fmin(1.0, fmax(0.0, color.r)) * 255);
	g = (int)(fmin(1.0, fmax(0.0, color.g)) * 255);
	b = (int)(fmin(1.0, fmax(0.0, color.b)) * 255);
	int_color = (r << 16) | (g << 8) | b;
	dst = canvas->addr + (y * canvas->line_length
			+ x * (canvas->bpp / 8));
	*(unsigned int *)dst = int_color;
}

int	render_scene(t_program *program)
{
	pthread_mutex_lock(&program->main_mutex);
	program->render_flag = true;
	program->worker_finish_count = 0;
	pthread_cond_broadcast(&program->render_cond);
	pthread_mutex_unlock(&program->main_mutex);

	pthread_mutex_lock(&program->main_mutex);
	while (program->worker_finish_count < program->num_workers)
	{
		pthread_cond_wait(&program->completion_cond, &program->main_mutex);
	}
	program->render_flag = false;
	mlx_put_image_to_window(program->mlx->mlx_ptr,
	program->mlx->win_ptr, program->mlx->canvas->img_ptr, 0, 0);
	pthread_mutex_unlock(&program->main_mutex);
	return (0);
}
