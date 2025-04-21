#include <zen.h>

void	str_join(t_string	*vec, size_t count, ...)
{
	size_t	i;
	va_list	args;

	va_start(args, count);
	i = 0;
	while (i < count)
	{
		str_append(va_arg(args, char *), vec);
		i++;
	}
	va_end(args);
}

t_string	*vstr_construct(size_t count, ...)
{
	t_string	*vec;
	size_t		i;
	va_list		args;

	va_start(args, count);
	vec = str_construct();
	i = 0;
	while (i < count)
	{
		str_append(va_arg(args, char *), vec);
		i++;
	}
	va_end(args);
	return (vec);
}
