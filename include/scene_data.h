#ifndef SCENE_DATA
#define SCENE_DATA
#include <stack.h>
#include <string.h>

#define	SEPARATORS " ,"
#define	ITEMS_COUNT 9
typedef void (*t_scene_parser)(t_scene_items *,char *);
typedef void (*t_scene_getter)(t_scene_items *);

typedef struct e_scene_item_ops
{
	t_string		*id;
	t_scene_parser	*parser;
	t_scene_getter	*getter;
}	t_scene_item_ops;

typedef struct e_scene_items
{
	t_string	*id;
	t_stack		*params;
}	t_scene_items;

typedef struct e_scene_items_vector
{
	t_scene_items		**items;
	t_scene_item_ops	ops[ITEMS_COUNT];
	size_t				size;
	size_t				cap;
}	t_scene_items_vector;

#endif //SCENE_DATA
