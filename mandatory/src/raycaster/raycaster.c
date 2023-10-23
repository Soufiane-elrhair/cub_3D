/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selrhair <selrhair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 19:42:27 by aait-lfd          #+#    #+#             */
/*   Updated: 2023/10/22 19:06:47 by selrhair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/inc.h"

int	ft_get_x(t_point end, int is_vertical, int texture_width)
{
	int		flour;
	float	x;

	if (is_vertical)
	{
		flour = floor(end.y / CELL_SIZE) * CELL_SIZE;
		x = ((end.y - flour) * 100) / 100;
	}
	else
	{
		flour = floor(end.x / CELL_SIZE) * CELL_SIZE;
		x = ((end.x - flour) * 100) / 100;
	}
	x = (x / CELL_SIZE) * texture_width;
	return (x);
}

void	ft_draw(t_data *data, t_directions direction)
{
	while (data->line->i < HIGH)
	{
		if (data->line->i < (HIGH / 2) - (data->line->cub_size / 2))
			data->line->color = data->game_config->ceil_color;
		else if (data->line->i < (HIGH / 2) - (data->line->cub_size / 2)
			+ data->line->cub_size)
		{
			if (data->line->y > data->textures[direction]->height)
				data->line->y = data->textures[direction]->height;
			data->line->color = get_color(data->textures[direction],
					data->line->x, data->line->y);
			data->line->y += data->textures[direction]->height
				/ data->line->wall_size;
			if (data->line->y >= data->textures[direction]->height)
				data->line->y = data->textures[direction]->height;
		}
		else
			data->line->color = data->game_config->floor_color;
		my_mlx_pixel_put(&data->img, data->ray_nb, data->line->i,
			data->line->color);
		data->line->i++;
	}
}

void	ft_draw_line(t_data *data, t_point end, int vertical,
		t_directions direction)
{
	data->line->x = ft_get_x(end, vertical, data->textures[direction]->width);
	data->line->y = 0;
	data->line->i = 0;
	data->line->distance_projection_plane = (WIDTH / 2) / tan(PI / 6);
	data->line->ray_distance = sqrt(pow(end.x
				- data->player_point.x, 2) + pow(end.y
				- data->player_point.y, 2)) * cos(((PI / 6) - ((PI / 3) / WIDTH)
				* data->ray_nb));
	data->line->cub_size = (CELL_SIZE / data->line->ray_distance)
		* data->line->distance_projection_plane;
	data->line->wall_size = data->line->cub_size;
	if (data->line->cub_size > HIGH)
	{
		data->line->y = ((data->line->wall_size / 2 - (HIGH / 2))
				/ data->line->wall_size)
			* data->textures[direction]->height;
		data->line->cub_size = HIGH;
	}
	if (data->line->cub_size <= 0)
		data->line->cub_size = 0;
	ft_draw(data, direction);
}

int	ft_check_wall(t_data *data, int a)
{
	t_point	c;

	if (a)
		c = (t_point){data->a_point.x, data->a_point.y};
	else
		c = (t_point){data->v_point.x, data->v_point.y};
	if (c.x > 0 && c.y > 0 && c.y < data->map_height && c.x < data->map_width
		&& data->map[(int)(c.y / CELL_SIZE)][(int)(c.x / CELL_SIZE)] == '1')
		return (1);
	return (0);
}

int	ft_compare(t_data *data)
{
	double	h;
	double	v;

	if (data->a_point.x == data->map_width
		|| data->a_point.y == data->map_height || data->a_point.x == 0
		|| data->a_point.y == 0)
		return (0);
	else if (data->v_point.x == data->map_width
		|| data->v_point.y == data->map_height || data->v_point.x == 0
		|| data->v_point.y == 0)
		return (1);
	h = sqrt(pow(data->a_point.x - data->player_point.x, 2)
			+ pow(data->a_point.y - data->player_point.y, 2));
	v = sqrt(pow(data->v_point.x - data->player_point.x, 2)
			+ pow(data->v_point.y - data->player_point.y, 2));
	if (h < v && (data->player_angle))
		return (1);
	return (0);
}
