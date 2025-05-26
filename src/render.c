#include <minirt.h>

bool is_in_shadow(t_scene *scene, t_hit_info *hit_info);

t_vec3 cross_product(t_vec3 a, t_vec3 b)
{
    t_vec3 result;
    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.x * b.z;
    result.z = a.x * b.y - a.y * b.x;
    return (result);
}


t_vec3 screen_to_world(int x, int y)
{
    t_vec3 result;

    result.x = ((2.0 * x) / WIN_WIDTH) - 1.0;
    result.y = ((2.0 * y) / WIN_HEIGHT) - 1.0;
    result.z = 0.0;
    return (result);
}

t_ray shoot_ray(t_scene *scene, t_vec3 screen_pos)
{
    t_ray ray;
    t_vec3 direction;
    t_vec3 vertical;
    t_vec3 horizontal;

    vertical = scale_vec3(scene->camera.up, screen_pos.y * scene->camera.height);
    horizontal = scale_vec3(scene->camera.right, screen_pos.x * scene->camera.width);
    direction = scene->camera.direction;
    direction = add_vec3(direction, horizontal);
    direction = add_vec3(direction, vertical);
    
    ray.origin = scene->camera.position;
    ray.direction = normalize_vec3(direction);
    return (ray);
}

t_hit_info intersect_sphere(t_ray *ray, t_sphere *sphere)
{
    t_hit_info hit_info;
    t_vec3 oc;
    double a, b, c, discriminant, t1, t2;
    
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
    
    hit_info.point = add_vec3(ray->origin, scale_vec3(ray->direction, hit_info.distance));
    hit_info.normal = normalize_vec3(sub_vec3(hit_info.point, sphere->center));
    hit_info.color = sphere->color;
    hit_info.hit = true;
    
    return (hit_info);
}


t_hit_info intersect_cylinder_side(t_ray *ray, t_cylinder *cylinder)
{
    t_hit_info hit_info;
    hit_info.distance = -1.0;
    hit_info.hit = false;
    
    t_vec3 axis = normalize_vec3(cylinder->axis);
    
    t_vec3 oc = sub_vec3(ray->origin, cylinder->center);
    
    double rd_dot_axis = dot_vec3(ray->direction, axis);
    double oc_dot_axis = dot_vec3(oc, axis);
    
    double a = dot_vec3(ray->direction, ray->direction) - 
               pow(rd_dot_axis, 2);
    
    double b = 2 * (dot_vec3(ray->direction, oc) - 
               rd_dot_axis * oc_dot_axis);
    
    double c = dot_vec3(oc, oc) - 
               pow(oc_dot_axis, 2) - 
               pow(cylinder->diameter / 2, 2);
    
    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return hit_info;
    
    double t1 = (-b - sqrt(discriminant)) / (2 * a);
    double t2 = (-b + sqrt(discriminant)) / (2 * a);
    
    double t = t1 > 0.001 ? t1 : t2;
    if (t < 0.001)
        return hit_info;
    
    t_vec3 hit_point = add_vec3(ray->origin, scale_vec3(ray->direction, t));
    
    t_vec3 center_to_hit = sub_vec3(hit_point, cylinder->center);
    double projection = dot_vec3(center_to_hit, axis);
    
    if (fabs(projection) > cylinder->height / 2)
        return hit_info;
    

    hit_info.distance = t;
    hit_info.point = hit_point;

    t_vec3 axis_point = add_vec3(cylinder->center, scale_vec3(axis, projection));
    hit_info.normal = normalize_vec3(sub_vec3(hit_point, axis_point));
    
    hit_info.color = cylinder->color;
    hit_info.hit = true;
    
    return hit_info;
}

t_hit_info intersect_cylinder_cap(t_ray *ray, t_cylinder *cylinder, int cap_side)
{
    t_hit_info hit_info;
    hit_info.distance = -1.0;
    hit_info.hit = false;
    
    t_vec3 axis = normalize_vec3(cylinder->axis);
    
    t_vec3 cap_center = add_vec3(cylinder->center, 
                                scale_vec3(axis, cap_side * (cylinder->height / 2)));
    
    t_vec3 cap_normal = scale_vec3(axis, cap_side);
    
    double denom = dot_vec3(cap_normal, ray->direction);
    if (fabs(denom) < EPSILON)
        return hit_info;
    
    double t = dot_vec3(sub_vec3(cap_center, ray->origin), cap_normal) / denom;
    if (t < 0.001)
        return hit_info;
    
    t_vec3 hit_point = add_vec3(ray->origin, scale_vec3(ray->direction, t));
    
    t_vec3 to_center = sub_vec3(hit_point, cap_center);
    
    t_vec3 radial_component = sub_vec3(to_center, 
                                     scale_vec3(axis, dot_vec3(to_center, axis)));
    
    double radius = cylinder->diameter / 2;
    if (length_vec3(radial_component) > radius)
        return hit_info;
    
    hit_info.distance = t;
    hit_info.point = hit_point;
    hit_info.normal = cap_normal;
    hit_info.color = cylinder->color;
    hit_info.hit = true;
    
    return hit_info;
}

t_hit_info intersect_cylinder(t_ray *ray, t_cylinder *cylinder)
{
    t_hit_info hit_info;
    hit_info.distance = -1.0;
    hit_info.hit = false;
    
    t_hit_info side_hit = intersect_cylinder_side(ray, cylinder);
    
    t_hit_info top_cap_hit = intersect_cylinder_cap(ray, cylinder, 1);
    t_hit_info bottom_cap_hit = intersect_cylinder_cap(ray, cylinder, -1);
    
    if (side_hit.hit && (!top_cap_hit.hit || side_hit.distance < top_cap_hit.distance) 
        && (!bottom_cap_hit.hit || side_hit.distance < bottom_cap_hit.distance))
        hit_info = side_hit;
    else if (top_cap_hit.hit && (!bottom_cap_hit.hit || top_cap_hit.distance < bottom_cap_hit.distance))
        hit_info = top_cap_hit;
    else if (bottom_cap_hit.hit)
        hit_info = bottom_cap_hit;
    
    return hit_info;
}

t_hit_info intersect_plane(t_ray *ray, t_plane *plane)
{
    t_hit_info hit_info;
    double denom, t;
    
    hit_info.distance = -1.0;
    hit_info.hit = false;
    
    denom = dot_vec3(plane->normal, ray->direction);
    
    if (fabs(denom) < EPSILON)
        return (hit_info);
    
    t = dot_vec3(sub_vec3(plane->center, ray->origin), plane->normal) / denom;
    
    if (t < 0.001)
        return (hit_info);
    
    hit_info.distance = t;
    hit_info.point = add_vec3(ray->origin, scale_vec3(ray->direction, hit_info.distance));
    hit_info.normal = plane->normal;
    hit_info.color = plane->color;
    hit_info.hit = true;
    
    return (hit_info);
}

t_color calculate_lighting(t_scene *scene, t_hit_info *hit_info)
{
    t_color color;
    t_vec3 light_dir;
    double intensity;
    bool shadowed;
    

    shadowed = is_in_shadow(scene, hit_info);
    light_dir = normalize_vec3(sub_vec3(scene->light.position, hit_info->point));
    intensity = fmax(0.0, dot_vec3(hit_info->normal, light_dir));
    
    double ambient_strength = 0.1;
    
    if(shadowed)
    {
        intensity = 0.0;
    }
    color.r = hit_info->color.r * (ambient_strength + scene->light.color.r * intensity);
    color.g = hit_info->color.g * (ambient_strength + scene->light.color.g * intensity);
    color.b = hit_info->color.b * (ambient_strength + scene->light.color.b * intensity);
    
    color.r = fmin(1.0, color.r);
    color.g = fmin(1.0, color.g);
    color.b = fmin(1.0, color.b);
    
    return (color);
}

t_hit_info find_closest_intersection(t_container *objects, t_ray *ray)
{
    t_hit_info hit_info, closest_hit;
    t_object *object;
    double closest_distance;
    size_t i;
    

    closest_distance = closest_hit.distance = -1.0;
    closest_hit.hit = false;
    
    for (i = 0; i < objects->size; i++)
    {
        object = get_object(objects, i);
        
        if (object->type == SPHERE)
            hit_info = intersect_sphere(ray, &object->obj.sphere);
        else if(object->type == PLANE)
            hit_info = intersect_plane(ray, &object->obj.plane);
        else if(object->type == CYLINDER)
             hit_info = intersect_cylinder(ray, &object->obj.cylinder);
        else
            continue;
        if (hit_info.hit && hit_info.distance > 0 && 
            (closest_distance < 0 || hit_info.distance < closest_distance))
        {
            closest_distance = hit_info.distance;
            closest_hit = hit_info;
            closest_hit.object_type = object->type;
        }
    }
    
    return (closest_hit);
}

bool is_in_shadow(t_scene *scene, t_hit_info *hit_info)
{
    t_ray shadow_ray;
    t_hit_info shadow_hit;
    double light_distance;
    
    shadow_ray.origin = hit_info->point;
    shadow_ray.direction = normalize_vec3(sub_vec3(scene->light.position, hit_info->point));
    
    shadow_ray.origin = add_vec3(shadow_ray.origin, 
                               scale_vec3(shadow_ray.direction, 0.001));
    
    light_distance = length_vec3(sub_vec3(scene->light.position, hit_info->point));
    
    shadow_hit = find_closest_intersection(scene->objects, &shadow_ray);
    
    return (shadow_hit.hit && shadow_hit.distance > 0 && shadow_hit.distance < light_distance);
}

t_color trace_ray(t_scene *scene, t_ray *ray)
{
    t_hit_info hit_info;
    t_color color;
    
    hit_info = find_closest_intersection(scene->objects, ray);
    
    if (!hit_info.hit || hit_info.distance < 0)
    {
        return (scene->amb_light.color);
    }
    
    color = calculate_lighting(scene, &hit_info);
    return (color);
}

void put_pixel_to_image(t_canvas *canvas, int x, int y, t_color color)
{
    char *dst;
    int int_color;
    
    if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
        return;
    
    int r = (int)(fmin(1.0, fmax(0.0, color.r)) * 255);
    int g = (int)(fmin(1.0, fmax(0.0, color.g)) * 255);
    int b = (int)(fmin(1.0, fmax(0.0, color.b)) * 255);
    
    int_color = (r << 16) | (g << 8) | b;
    
    dst = canvas->addr + (y * canvas->line_length + x * (canvas->bpp / 8));
    *(unsigned int*)dst = int_color;
}

void render_scene(t_program *program)
{
    t_ray ray;
    t_vec3 screen_pos;
    t_color color;
    int x, y;
    
    for (y = 0; y < WIN_HEIGHT; y++)
    {
        for (x = 0; x < WIN_WIDTH; x++)
        {
            screen_pos = screen_to_world(x, y);
            ray = shoot_ray(program->scene, screen_pos);
            color = trace_ray(program->scene, &ray);
            put_pixel_to_image(program->mlx->canvas, x, y, color);
        }
    }
    mlx_put_image_to_window(program->mlx->mlx_ptr, program->mlx->win_ptr, 
                           program->mlx->canvas->img_ptr, 0, 0);
}