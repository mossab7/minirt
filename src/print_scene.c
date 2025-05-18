#include <minirt.h>

char *get_type(t_object_type type)
{
    if (type == SPHERE)
        return ("SPHERE");
    else if (type == PLANE)
        return ("PLANE");
    else if (type == CYLINDER)
        return ("CYLINDER");
    else if (type == HYPERBOLDOID)
        return ("HYPERBOLDOID");
    else if (type == PARABOLOID)
        return ("PARABOLOID");
    return ("UNKNOWN");
}

void print_sphere(t_object *obj)
{
    t_sphere *sphere = &obj->obj.sphere;
    printf("Sphere: Center: (%f, %f, %f), Diameter: %f\n",
           sphere->center.x, sphere->center.y, sphere->center.z, sphere->diameter);
    printf ("Color: (%f, %f, %f)\n", sphere->color.r, sphere->color.g, sphere->color.b);
}

void print_plane(t_object *obj)
{
    t_plane *plane = &obj->obj.plane;
    printf("Plane: Center: (%f, %f, %f), Normal: (%f, %f, %f)\n",
           plane->center.x, plane->center.y, plane->center.z,
           plane->normal.x, plane->normal.y, plane->normal.z);
    printf ("Color: (%f, %f, %f)\n", plane->color.r, plane->color.g, plane->color.b);
}
void print_cylinder(t_object *obj)
{
    t_cylinder *cylinder = &obj->obj.cylinder;
    printf("Cylinder: Center: (%f, %f, %f), Axis: (%f, %f, %f), Diameter: %f, Height: %f\n",
           cylinder->center.x, cylinder->center.y, cylinder->center.z,
           cylinder->axis.x, cylinder->axis.y, cylinder->axis.z,
           cylinder->diameter, cylinder->height);
    printf ("Color: (%f, %f, %f)\n", cylinder->color.r, cylinder->color.g, cylinder->color.b);
}
void print_hyperboloid(t_object *obj)
{
    t_hyperboloid *hyperboloid = &obj->obj.hyperboloid;
    printf("Hyperboloid: Center: (%f, %f, %f), Axis: (%f, %f, %f), Diameter: %f, Height: %f\n",
           hyperboloid->center.x, hyperboloid->center.y, hyperboloid->center.z,
           hyperboloid->axis.x, hyperboloid->axis.y, hyperboloid->axis.z,
           hyperboloid->diameter, hyperboloid->height);
    printf ("Color: (%f, %f, %f)\n", hyperboloid->color.r, hyperboloid->color.g, hyperboloid->color.b);
}
void print_paraboloid(t_object *obj)
{
    t_paraboloid *paraboloid = &obj->obj.paraboloid;
    printf("Paraboloid: Center: (%f, %f, %f), Axis: (%f, %f, %f), Diameter: %f\n",
           paraboloid->center.x, paraboloid->center.y, paraboloid->center.z,
           paraboloid->axis.x, paraboloid->axis.y, paraboloid->axis.z,
           paraboloid->diameter);
    printf ("Color: (%f, %f, %f)\n", paraboloid->color.r, paraboloid->color.g, paraboloid->color.b);
}
void print_object(t_object *obj)
{
    if (obj->type == SPHERE)
        print_sphere(obj);
    else if (obj->type == PLANE)
        print_plane(obj);
    else if (obj->type == CYLINDER)
        print_cylinder(obj);
    else if (obj->type == HYPERBOLDOID)
        print_hyperboloid(obj);
    else if (obj->type == PARABOLOID)
        print_paraboloid(obj);
}

void print_scene(t_scene *scene)
{
    for(size_t i = 0; i < scene->objects->size; i++)
    {
        t_object *obj = get_object(scene->objects, i);
        if (obj)
        {
            printf("Object %zu: Type: %s\n", i, get_type(obj->type));
            print_object(obj);
            printf("\n");
        }
    }
}