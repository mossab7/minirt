#include <minirt.h>

int	parse_filename(char *filename)
{

}

t_scene *parse_scene(char *filename)
{
	t_scene	*scene;
	int		fd;

	if (parse_filename(filename) == -1)
	{
		ft_putstr_fd("Error: Invalid file name\n", 2);
		return (NULL);
	}
	scene = (t_scene *)alloc(sizeof(t_scene));
	fd = ft_open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_free(scene);
		return (NULL);
	}
	read_to_scene(fd, scene);
	ft_close(fd);
	return (scene);
}
