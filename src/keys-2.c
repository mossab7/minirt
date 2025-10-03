/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys-2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 02:06:02 by zbengued          #+#    #+#             */
/*   Updated: 2025/09/20 03:02:12 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <X11/keysym.h>

int	*get_keys(void)
{
	static int	keys_to_check[] = {
		XK_Up,
		XK_Down,
		XK_Left,
		XK_Right,
		XK_space,
		XK_Shift_L,
		'w',
		'a',
		's',
		'd'
	};

	return (keys_to_check);
}

int	key_press(int keycode, void *param)
{
	t_program	*program;

	program = (t_program *)param;
	if (keycode == XK_Escape)
	{
		if (program->selected_object.hit)
			program->selected_object.hit = false;
		else
			safe_exit(0);
		return (0);
	}
	if (keycode >= 0 && keycode < 70000)
		program->keys[keycode] = true;
	return (0);
}

int	key_release(int keycode, void *param)
{
	t_program	*program;

	program = param;
	if (keycode >= 0 && keycode < 70000)
		program->keys[keycode] = false;
	return (0);
}
