#include <zen.h>

void	str_append(char *src, t_string *vec)
{
	size_t	index;

	if (!src)
		return ;
	index = 0;
	while (src[index])
	{
		str_push_back(vec, src[index]);
		mask_push_back(vec->mask, 0);
		index++;
	}
}

void	str_overwrite(char *src, t_string *vec)
{
	if (!src)
		return ;
	vec->size = 0;
	vec->cstring[vec->size] = 0;
	if (!*src)
		return ;
	str_append(src, vec);
}

int	str_search_using_cursor(t_string *vec, const char *text)
{
	char	*cursor;

	cursor = ft_strnstr(((const char *) vec->cstring + vec->cursor),
			text, vec->size);
	if (cursor)
		return ((int)(cursor - vec->cstring));
	return (-1);
}

int	str_search(t_string *vec, const char *text, int offset)
{
	char	*cursor;

	cursor = ft_strnstr(((const char *) vec->cstring + offset),
			text, vec->size);
	if (cursor)
		return ((int)(cursor - vec->cstring));
	return (-1);
}

void	str_print(t_string *str)
{
	size_t	i;

	ft_printf("Mask size: %u\n", str->mask->size);
	ft_printf("str  size: %u\n", str->size);
	ft_printf("[%u]# %s\n", str->size, str->cstring);
	ft_printf("     ");
	i = 0;
	while (i < str->mask->size)
		ft_printf("%u", str->mask->items[i++]);
	ft_printf("\n");
}
