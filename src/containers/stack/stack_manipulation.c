#include <minirt.h>

void	stack_push_back(t_stack *stack, float item)
{
	stack_expand(stack);
	stack->items[stack->size++] = item;
}

int	*stack_pop(t_stack *stack)
{
	if (stack && stack->size)
		return (&stack->items[--stack->size]);
	return (NULL);
}

int	*stack_peek(t_stack *stack)
{
	if (stack && stack->size)
		return (&stack->items[-1 + stack->size]);
	return (NULL);
}
