#ifndef MINIRT_H
#define MINIRT_H

#include <libft.h>
#include <t_string.h>
#include <t_string_vector.h>
#include <scene_data.h>


typedef enum e_error
{
	OK,
	ERROR,
	CATA_ERROR
}	t_error;

typedef	struct s_program
{
	t_scene_data	*scene_data;
	t_error			error;
}	t_program;

#endif //MINIRT_H
