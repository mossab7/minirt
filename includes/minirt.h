#include <libft.h>

typedef float	matrix4d[4][4];

typedef struct t_vec4
{
	float x;
	float y;
	float z;
	float w;
}t_vec4;

typedef struct s_color
{
	float r;
	float g;
	float b;
}t_color;

typedef struct s_sphere
{
	t_vec4 center;
	float diameter;
	t_color color;
}t_sphere;

typedef struct s_plane
{
	t_vec4 point;
	t_vec4 normal;
	t_color color;
}t_plane;

typedef struct s_hyperboloid
{
	t_vec4 center;
	t_vec4 axis;
	float diameter;
	float height;
	t_color color;
}t_hyperboloid;

typedef struct s_paraboloid
{
	t_vec4 center;
	t_vec4 axis;
	float diameter;
	float height;
	t_color color;
}t_paraboloid;

typedef struct s_cylinder
{
	t_vec4 center;
	t_vec4 axis;
	float diameter;
	float height;
	t_color color;
}t_cylinder;

typedef enum e_object_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	HYPERBOLDOID,
	PARABOLOID
}t_object_type;

typedef struct s_object
{
	t_object_type type;
	union
	{
		t_sphere sphere;
		t_plane plane;
		t_cylinder cylinder;
		t_hyperboloid hyperboloid;
		t_paraboloid paraboloid;
	}obj;
}t_object;

typedef struct s_amb_light
{
	t_color color;
	float intensity;
}t_amb_light;

typedef struct s_camera
{
	t_vec4 position;
	t_vec4 direction;
	float fov;
}t_camera;

typedef struct s_light
{
	t_vec4 position;
	t_color color;
	float intensity;
}t_light;

typedef struct s_scene
{
	t_camera camera;
	t_light light;
	t_amb_light amb_light;
	t_object *objects;
}t_scene;
