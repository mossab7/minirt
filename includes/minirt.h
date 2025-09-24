/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deepseeko <deepseeko@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 19:03:54 by deepseeko         #+#    #+#             */
/*   Updated: 2025/09/20 16:08:15 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include "mlx.h"
# include <X11/keysym.h>
# include <libft.h>
# include <macros.h>
# include <math.h>
# include <pthread.h>
# include <X11/keysym.h>
# include <mlx.h>
# include <stdbool.h>
# include <stdio.h>
#include "ft_string.h"

typedef struct t_vec3
{
	double				x;
	double				y;
	double				z;
}						t_vec3;

typedef struct s_color
{
	double				r;
	double				g;
	double				b;
}						t_color;

/* Pattern constants */
# define CHECKER_SIZE 1.0
# define CHECKER_SCALE 4.0
# define PATTERN_NONE 0
# define PATTERN_CHECKERBOARD 1
# define PATTERN_BUMP_MAP 2
# define PATTERN_TEXTURE 4

/* Bump map constants */
# define BUMP_STRENGTH 0.1
# define BUMP_SCALE 4.0

/* Pattern structure */
typedef struct s_texture
{
	void				*img_ptr;
	char				*addr;
	int					width;
	int					height;
	int					bpp;
	int					line_length;
	int					endian;
}						t_texture;

typedef struct s_pattern
{
	int					type;
	t_color				color1;
	t_color				color2;
	double				scale;
	double				bump_strength;
	t_texture			*texture;
}						t_pattern;

typedef struct s_sphere
{
	t_vec3				center;
	double				diameter;
	t_color				color;
}						t_sphere;

typedef struct s_plane
{
	t_vec3				center;
	t_vec3				normal;
	t_color				color;
}						t_plane;

typedef struct s_hyperboloid
{
	t_vec3				center;
	t_vec3				axis;
	double				diameter;
	double				height;
	t_color				color;
}						t_hyperboloid;

typedef struct s_paraboloid
{
	t_vec3				center;
	t_vec3				axis;
	double				diameter;
	double				height;
	t_color				color;
}						t_paraboloid;

typedef struct s_cylinder
{
	t_vec3				center;
	t_vec3				axis;
	double				diameter;
	double				height;
	t_color				color;
}						t_cylinder;

typedef struct s_cone
{
	t_vec3				center;
	t_vec3				axis;
	double				diameter;
	double				height;
	t_color				color;
}						t_cone;

typedef enum e_object_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	CONE,
	HYPERBOLDOID,
	PARABOLOID
}						t_object_type;

typedef struct s_object
{
	t_object_type		type;
	union
	{
		t_sphere		sphere;
		t_plane			plane;
		t_cylinder		cylinder;
		t_cone			cone;
		t_hyperboloid	hyperboloid;
		t_paraboloid	paraboloid;
	} u_obj;
	t_pattern			pattern;
}						t_object;

typedef struct s_amb_light
{
	double				ratio;
	t_color				color;
}						t_amb_light;

typedef struct s_camera
{
	t_vec3				position;
	t_vec3				direction;
	t_vec3				up;
	t_vec3				right;
	t_vec3				forward;
	double				fov;
	double				width;
	double				height;
}						t_camera;

typedef struct s_light
{
	t_vec3				position;
	t_color				color;
	double				intensity;
}						t_light;

typedef struct s_scene
{
	t_camera			camera;
	t_container			*lights;
	t_amb_light			amb_light;
	t_container			*objects;
}						t_scene;

typedef struct s_hit_info
{
	float				distance;
	bool				hit;
	t_vec3				point;
	t_vec3				normal;
	t_color				color;
	t_object			*object;
	t_object_type		object_type;
}						t_hit_info;

typedef struct s_ray
{
	t_vec3				origin;
	t_vec3				direction;
}						t_ray;

typedef struct s_canvas
{
	void				*img_ptr;
	char				*addr;
	int					bpp;
	int					line_length;
	int					endian;
}						t_canvas;

typedef struct s_mlx
{
	void				*mlx_ptr;
	void				*win_ptr;
	t_canvas			*canvas;
}						t_mlx;

typedef struct s_worker
{
	pthread_t			thread;
	struct s_program	*program;
	int					start_y;
	int					end_y;
	int					start_x;
	int					end_x;
}						t_worker;

typedef struct s_pixel_batch
{
	int					x;
	int					y;
	t_color				color;
}						t_pixel_batch;

typedef struct s_program
{
	t_mlx				*mlx;
	t_scene				*scene;
	t_hit_info			selected_object;
	bool				render_flag;
	pthread_mutex_t		main_mutex;
	pthread_mutex_t		render_mutex;
	pthread_cond_t		render_cond;
	pthread_cond_t		completion_cond;
	int					num_workers;
	t_worker			*workers;
	bool				program_running;
	int					worker_finish_count;
	bool				dirty;
	bool				keys[70000];
}						t_program;

typedef struct s_matrix4d
{
	double				data[4][4];
}						t_matrix4d;

typedef struct t_material
{
	t_color				color;
	double				specular;
	double				diffuse;
	double				shininess;
}						t_material;

typedef void			(*t_parse_function)(char **, t_scene *);
typedef void (*t_parse_fn)(t_scene *s_scene, t_str *line);
typedef struct s_parse_entry
{
	char		*key;
	t_parse_fn	fn;
	size_t		len;
}	t_parse_entry;

void					parse_amb_light(char **data, t_scene *scene);
void					parse_camera(char **data, t_scene *scene);
void					parse_light(char **data, t_scene *scene);
void					parse_sphare(char **data, t_scene *scene);
void					parse_plane(char **data, t_scene *scene);
void					parse_cylinder(char **data, t_scene *scene);
void					parse_cone(char **data, t_scene *scene);
void					parse_hyperboloid(char **data, t_scene *scene);
void					parse_paraboloid(char **data, t_scene *scene);
void					free_object(void *obj_void);
void					parse_obj_data(char **data, t_scene *scene);
int						parse_filename(char *filename);
void					init_obj_parse_func(t_parse_function *parse_func,
							char **obj_name);
t_color					get_color(char *data);
t_vec3					get_vec3(char *data);
void					check_vec_range(t_vec3 vec);
t_scene					*parse_scene(char *filename);
t_object				*get_object(t_container *container, size_t index);
t_light					*get_light(t_container *container, size_t index);
t_vec3					add_vec3(t_vec3 a, t_vec3 b);
t_vec3					sub_vec3(t_vec3 a, t_vec3 b);
t_vec3					mul_vec3(t_vec3 a, t_vec3 b);
t_vec3					div_vec3(t_vec3 a, t_vec3 b);
t_vec3					mul_scalar_vec3(t_vec3 a, double scalar);
t_vec3					div_scalar_vec3(t_vec3 a, double scalar);
double					length_vec3(t_vec3 a);
t_vec3					normalize_vec3(t_vec3 a);
double					dot_vec3(t_vec3 a, t_vec3 b);
double					distance_vec3(t_vec3 a, t_vec3 b);
t_vec3					cross_vec3(t_vec3 a, t_vec3 b);
t_vec3					vec3_negate(t_vec3 vec);
t_vec3					scale_vec3(t_vec3 a, double scalar);
t_color					scale_color(t_color a, double scalar);
/* Matrix creation */
t_matrix4d				matrix4d_identity(void);
t_matrix4d				matrix4d_translation(t_vec3 translation);
t_matrix4d				matrix4d_rotation_x(double angle);
t_matrix4d				matrix4d_rotation_y(double angle);
t_matrix4d				matrix4d_rotation_z(double angle);
t_matrix4d				matrix4d_rotation(t_vec3 rotation);
t_matrix4d				matrix4d_scale(t_vec3 scale);
t_matrix4d				matrix4d_scaling(t_vec3 scale);

/* Matrix operations */
t_matrix4d				matrix4d_mult(t_matrix4d a, t_matrix4d b);
t_matrix4d				matrix4d_transpose(t_matrix4d matrix);
t_matrix4d				matrix4d_inverse(t_matrix4d matrix);
t_vec3					matrix4d_mult_vec3(t_matrix4d matrix, t_vec3 vec);

/* Camera/view matrix */
t_matrix4d				view_matrix(t_vec3 camera_pos, t_vec3 camera_dir);
int						render_scene(t_program *program);
t_program				**get_program(void);
// bonus
t_color					apply_checkerboard_pattern(t_hit_info *hit_info,
							t_pattern *pattern);
t_color					get_pattern_color(t_hit_info *hit_info);
int						parse_pattern(char **data, t_pattern *pattern);
t_vec3					apply_bump_mapping(t_hit_info *hit_info,
							t_pattern *pattern);
double					noise_function(double x, double y);
t_vec3					calculate_bump_normal(t_hit_info *hit_info,
							t_pattern *pattern);
// adf
t_vec3					screen_to_world(int x, int y);
t_ray					shoot_ray(t_scene *scene, t_vec3 screen_pos);
t_hit_info				find_closest_intersection(t_container *objects,
							t_ray *ray);
t_color					trace_ray(t_scene *scene, t_ray *ray);
t_color					calculate_lighting(t_scene *scene,
							t_hit_info *hit_info);
void					put_pixel_to_image(t_canvas *canvas, int x, int y,
							t_color color);

// Cone intersection prototypes
t_hit_info				intersect_cone_side(t_ray *ray, t_cone *cone);
t_hit_info				intersect_cone_base(t_ray *ray, t_cone *cone);
t_hit_info				intersect_cone(t_ray *ray, t_cone *cone);
t_vec3					get_cone_normal(t_cone *cone, t_vec3 point);

void					recalculate_camera_vectors(t_camera *camera);

// parsing
int						parse_filename(char *filename);
void					init_obj_parse_func(t_parse_function *parse_func,
							char **obj_name);
void					parse_obj_data(char **data, t_scene *scene);
t_color					get_color(char *data);
t_vec3					get_vec3(char *vec);
void					parse_amb_light(char **data, t_scene *scene);
void					check_vec_range(t_vec3 vec);
double					dgree_to_rad(double degree);
void					parse_camera(char **data, t_scene *scene);
void					parse_light(char **data, t_scene *scene);
void					parse_sphare(char **data, t_scene *scene);
void					parse_plane(char **data, t_scene *scene);
void					parse_cylinder(char **data, t_scene *scene);
void					parse_cone(char **data, t_scene *scene);
void					parse_hyperboloid(char **data, t_scene *scene);
void					parse_paraboloid(char **data, t_scene *scene);
void					read_to_scene(int fd, t_scene *scene);
t_scene					*init_scene(void);
t_scene					*parse_scene(char *filename);
int						parse_pattern(char **data, t_pattern *pattern);

// matrix_op
t_matrix4d				matrix4d_translation(t_vec3 translation);
t_matrix4d				matrix4d_rotation_x(double angle);
t_matrix4d				matrix4d_rotation_y(double angle);
t_matrix4d				matrix4d_rotation_z(double angle);
t_matrix4d				matrix4d_mult(t_matrix4d a, t_matrix4d b);
t_matrix4d				matrix4d_translation(t_vec3 translation);
t_matrix4d				matrix4d_rotation_x(double angle);
t_matrix4d				matrix4d_rotation_y(double angle);
t_matrix4d				matrix4d_rotation_z(double angle);
t_matrix4d				matrix4d_mult(t_matrix4d a, t_matrix4d b);
double					calculate_determinant3x3(t_matrix4d matrix);
t_matrix4d				inverse_rotation_scale(t_matrix4d matrix, double det);
void					inverse_translation(t_matrix4d *result,
							t_matrix4d original_matrix);
t_matrix4d				matrix4d_inverse(t_matrix4d matrix);
t_matrix4d				matrix4d_rotation(t_vec3 rotation);
t_matrix4d				matrix4d_scale(t_vec3 scale);
t_matrix4d				matrix4d_identity(void);
t_matrix4d				matrix4d_transpose(t_matrix4d matrix);

// texturing

t_color					apply_checkerboard_pattern(t_hit_info *hit_info,
							t_pattern *pattern);
int						*get_perm(void);
const int				*get_p(void);
void					init_permutation_table(void);
double					fade(double t);
double					lerp(double t, double a, double b);
double					noise_function(double x, double y);
t_vec3					calculate_bump_normal(t_hit_info *hit_info,
							t_pattern *pattern);
t_color					apply_texture(t_hit_info *hit_info, t_pattern *pattern);
t_vec3					apply_bump_mapping(t_hit_info *hit_info,
							t_pattern *pattern);
t_color					get_pattern_color(t_hit_info *hit_info);

t_texture				*load_texture(char *filename);
t_color					get_pixel_color(t_texture *texture, int x, int y);
void					free_texture(void *texture_void);

t_program				**get_program(void);
void					free_all_textures(t_scene *scene);
t_object				*get_object(t_container *container, size_t index);
t_light					*get_light(t_container *container, size_t index);
void					register_allocation(void *ptr,
							void (*free_func)(void *));
void					trans_keys(int key, t_vec3 *trans, t_program *program,
							bool *changed);
void					rot_keys(int key, t_vec3 *rot, bool *has_changed);
void					transforme_camera(t_program *program, t_vec3 rotation,
							t_vec3 trans);
void					apply_transformation(t_program *program, t_vec3 trans,
							t_vec3 rot);
int						key_hook(int keycode, void *param);
int						mouse_hook(int button, int x, int y, void *param);

t_hit_info				intersect_cylinder_side(t_ray *ray,
							t_cylinder *cylinder);
t_vec3					cross_product(t_vec3 a, t_vec3 b);
t_vec3					screen_to_world(int x, int y);
t_ray					shoot_ray(t_scene *scene, t_vec3 screen_pos);
t_hit_info				intersect_sphere(t_ray *ray, t_sphere *sphere);
t_program				**get_program(void);
void					free_all_textures(t_scene *scene);
t_object				*get_object(t_container *container, size_t index);
t_light					*get_light(t_container *container, size_t index);
t_hit_info				compute_cylinder_hit(t_ray *ray, t_cylinder *cylinder,
							t_vec3 axis, double *val);
void					register_allocation(void *ptr,
							void (*free_func)(void *));
t_hit_info				intersect_cylinder_side(t_ray *ray,
							t_cylinder *cylinder);
t_hit_info				intersect_cylinder_cap(t_ray *ray, t_cylinder *cylinder,
							int cap_side);
t_hit_info				intersect_cone_side(t_ray *ray, t_cone *cone);
t_hit_info				intersect_cone_base(t_ray *ray, t_cone *cone);
t_hit_info				intersect_cone(t_ray *ray, t_cone *cone);
t_hit_info				intersect_cylinder(t_ray *ray, t_cylinder *cylinder);
t_hit_info				intersect_plane(t_ray *ray, t_plane *plane);
t_vec3					get_cone_normal(t_cone *cone, t_vec3 point);
t_pattern				*get_object_pattern(t_hit_info *hit_info);
t_vec3					compute_light_dir(t_hit_info *hit_info, t_light *light);
bool					is_in_shadow(t_scene *scene, t_hit_info *hit_info,
							t_light *light);
t_vec3					compute_light_dir(t_hit_info *hit_info, t_light *light);
t_hit_info				find_closest_intersection(t_container *objects,
							t_ray *ray);
bool					is_in_shadow(t_scene *scene, t_hit_info *hit_info,
							t_light *light);
void					set_up_workers(t_program *program);
void					worker_render_scene(t_worker *worker);
void					*worker_loop(void *arg);
int						loop_hook(void *param);
long					get_num_cores_unix(void);
void					set_single_worker_bounds(t_worker *worker);
void					set_grid_division_bounds(t_worker *workers,
							int num_threads);
void					calculate_worker_bounds(t_program *program);
int						safe_exit(int status);
t_canvas				*init_canvas(void *mlx_ptr, int width, int height);
t_mlx					*_init_mlx(void);

int						key_press(int keycode, void *param);
int						key_release(int keycode, void *param);
int						*get_keys(void);

#endif // MINIRT_H
