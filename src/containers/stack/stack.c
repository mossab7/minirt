#include <zen.h>

void	stack_expand(t_stack *stack)
{
	if (stack->size >= stack->cap)
	{
		stack->cap *= VEC_GROWTH_FAC;
		stack->items = ft_realloc(stack->items,
				stack->cap * sizeof(*(stack->items)),
				stack->size * sizeof(*(stack->items)));
	}
}

t_stack	*stack_construct(void)
{
	t_stack	*stack;

	stack = alloc(sizeof(*stack));
	stack->items = alloc(VAC_INIT_CAP * sizeof(*(stack->items)));
	stack->cap = VEC_INIT_CAP;
	stack->size = 0;
	return (stack);
}

void	stack_destroy(t_stack *stack)
{
	if (stack)
	{
		if (stack->items)
			ft_free(stack->items);
		ft_free(stack);
	}
}
