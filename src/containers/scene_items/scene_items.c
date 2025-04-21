#include <minirt.h>

void	sdatav_expand(t_scene_items_vector *scene_items)
{
	if (scene_items->size >= scene_items->cap)
	{
		scene_items->items = ft_realloc(scene_items->items,
			scene_items->cap * sizeof(*scene_items->items),
			scene_items->size * sizeof(*scene_items->items));
	}
}

void	sitemsv_push_back(t_scene_items_vector *scene_items, t_scene_items *item)
{
	if (!item)
		return ;
	sitemsv_expand(scene_items);
	scene_items->items[scene_items->size++] = item;
	scene_items->items[scene_items->size] = NULL;
}
void	sitemsv_destruct(t_scene_items_vector *scene_items)
{
	size_t	index;

	index = 0;
	while (index < scene_items->size)
	{
		ft_free(scene_items->items[index]->id);
		stack_destroy(scene_items->items[index]->params);
		ft_free(scene_items->items[index]);
		index++;
	}
	ft_free(scene_items->items);
	ft_free(scene_items);
}

void	init_scene_item_ops(t_scene_item_ops *ops)
{
	ops[0].id = ft_strdup("A");
	ops[0].parser = parse_ambient;
	ops[0].getter = get_ambient;
	ops[1].id = ft_strdup("C");
	ops[1].parser = parse_camera;
	ops[1].getter = get_camera;
	ops[2].id = ft_strdup("L");
	ops[2].parser = parse_light;
	ops[2].getter = get_light;
	ops[3].id = ft_strdup("sp");
	ops[3].parser = parse_sphere;
	ops[3].getter = get_sphere;
	ops[4].id = ft_strdup("pl");
	ops[4].parser = parse_plane;
	ops[4].getter = get_plane;
	ops[5].id = ft_strdup("cy");
	ops[5].parser = parse_cylinder;
	ops[5].getter = get_cylinder;
}

t_scene_items_vector	*sitemsv_construct(void)
{
	t_scene_items_vector	*scene_items;

	scene_items = alloc(sizeof(*scene_items));
	scene_items->items = alloc(VEC_INIT_CAP * sizeof(*scene_items->items));
	init_scene_item_ops(scene_items->ops);
	scene_items->cap = VEC_INIT_CAP;
	scene_items->size = 0;
	return (scene_items);
}
