#include <zen.h>

void	str_expand_anyhow(t_string *vec)
{
	vec->cap *= VEC_GROWTH_FAC;
	vec->cstring = ft_realloc(vec->cstring, vec->cap, vec->size);
}

void	str_expand(t_string *vec)
{
	if (vec->size + 1 >= vec->cap)
		str_expand_anyhow(vec);
}

void	str_push_back(t_string *vec, uintptr_t item)
{
	str_expand(vec);
	vec->cstring[vec->size++] = item;
	vec->cstring[vec->size] = 0;
}

t_string	*str_construct(void)
{
	t_string	*vec;

	vec = alloc(sizeof(*vec));
	vec->cstring = alloc(VEC_INIT_CAP);
	vec->cap = VEC_INIT_CAP;
	vec->size = 0;
	vec->cursor = 0;
	return (vec);
}

void	str_destruct(t_string *vec)
{
	if (vec)
	{
		if (vec->cstring)
			ft_free(vec->cstring);
		vec->cstring = NULL;
		vec->mask = NULL;
		ft_free(vec);
	}
}
