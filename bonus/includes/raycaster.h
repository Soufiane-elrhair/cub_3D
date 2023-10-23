/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selrhair <selrhair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 20:01:51 by aait-lfd          #+#    #+#             */
/*   Updated: 2023/10/22 19:49:53 by selrhair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H

typedef struct s_line
{
	unsigned int		color;
	int					i;
	int					distance_projection_plane;
	double				ray_distance;
	int					cub_size;
	double				x;
	double				wall_size;
	double				y;
}	t_line;

typedef struct s_data
{
	t_line	*line;
	char	**map;
	int		map_width;
	int		map_height;
	char	player_char;
	double	player_angle;
	t_point	player_point;
	t_point	a_point;
	t_point	v_point;
	double	last_mouse_x;
	int		door;
	int		ray_nb;
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	*textures[5];
	t_game	*game_config;
	t_img	img;
}			t_data;

typedef enum directions
{
	NORTH = 0,
	SOUTH = 1,
	WEST = 2,
	EAST = 3,
	DOOR = 4,
}			t_directions;

void			ft_rotate(t_data *data);
void			ft_window(t_data *data);
double			ft_find_player(t_data *data);
int				ft_key_press(int keycode, t_data *data);
void			ft_up(t_data *data);
void			ft_down(t_data *data);
int				ft_check_wall(t_data *data, int a);
int				ft_quit(t_data *vars);
unsigned int	get_color(t_img *img, int x, int y);
void			ft_work_(t_data *data);
void			ft_open_close_door(t_data *data);
int				ft_mouse_move(int x, int y, t_data *data);
t_directions	check_door(t_data *data, t_directions direction, t_point end);
#endif