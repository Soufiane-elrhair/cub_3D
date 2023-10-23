/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast_help.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selrhair <selrhair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 18:56:45 by selrhair          #+#    #+#             */
/*   Updated: 2023/10/22 19:49:34 by selrhair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/inc.h"

void	ft_open_close_door(t_data *data)
{
	int	x;
	int	y;
	int	i;
	int	j;

	x = data->player_point.x;
	y = data->player_point.y;
	i = x;
	j = y;
	x += round(cos(data->player_angle) * CELL_SIZE / 2);
	y -= round(sin(data->player_angle) * CELL_SIZE / 2);
	if (data->map[y / CELL_SIZE][x / CELL_SIZE] == '2')
		data->map[y / CELL_SIZE][x / CELL_SIZE] = '3';
	else if (data->map[y / CELL_SIZE][x / CELL_SIZE] == '3')
		data->map[y / CELL_SIZE][x / CELL_SIZE] = '2';
	if (data->map[j / CELL_SIZE][i / CELL_SIZE] == '2')
		data->map[y / CELL_SIZE][x / CELL_SIZE] = '3';
	ft_rotate(data);
}

int	ft_mouse_move(int x, int y, t_data *data)
{
	(void)y;
	if (x >= WIDTH)
		x = WIDTH / 2;
	if (x <= 0)
		x = WIDTH / 2;
	if (x > data->last_mouse_x)
	{
		data->player_angle -= 0.05;
		if (data->player_angle >= -6.260000 && data->player_angle <= -6.240000)
			data->player_angle = 0;
		ft_rotate(data);
	}
	if (x < data->last_mouse_x)
	{
		data->player_angle += 0.05;
		if (data->player_angle >= 6.260000 && data->player_angle <= 6.240000)
			data->player_angle = 0;
		ft_rotate(data);
	}
	data->last_mouse_x = x;
	return (0);
}

int	ft_quit(t_data *vars)
{
	int	i;

	i = 0;
	while (vars->map[i])
	{
		free(vars->map[i]);
		i++;
	}
	free(vars->map);
	exit(0);
}

t_directions	check_door(t_data *data, t_directions direction, t_point end)
{
	if (end.x > 0 && end.y > 0 && end.y < data->map_height
		&& end.x < data->map_width
		&& data->map[(int)end.y / CELL_SIZE][(int)end.x / CELL_SIZE] == '2')
			direction = DOOR;
	return (direction);
}
