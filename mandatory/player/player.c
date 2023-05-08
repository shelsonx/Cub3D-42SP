#include "cub3D.h"

void	init_player(t_cubd *cub3d, t_player *player)
{
	player->x = cub3d->game->window.width / 2;
	player->y = cub3d->game->window.height / 2;
	player->width = 1;
	player->height = 1;
	player->turn_direction = 0;
	player->walk_direction = 0;
	player->walk_side_direction = 0;
	player->rotation_angle = (PI / 2);
	player->walk_speed = 15;
	player->turn_speed = 20 * (PI / 180);
}

int	has_wall_at(char **map, double new_x, double new_y, t_cubd *cub3d)
{
	int	x;
	int	y;

	/* if (new_x >= cub3d->game->window.width / 2)
		new_x += cub3d->player->width; */
	/* if (new_y >= cub3d->game->window.height / 2)
		new_y += 1; */
	if (!is_inside_map(cub3d->game->window, new_x, new_y))
		return (TRUE);
	x = (int)floor((new_x / TILE_SIZE));
	y = (int)floor((new_y / TILE_SIZE));
	if (x >= cub3d->map.dimensions.columns - 1
		|| y >= cub3d->map.dimensions.rows - 1)
		return (TRUE);
	return (map[y][x] == WALL_CHAR);
}

int	is_inside_map(t_window window, double new_x, double new_y)
{
	return (new_x >= 0 && new_x <= window.width
		&& new_y >= 0 && new_y <= window.height);
}

void	render_only_player(t_cubd *cub3d, t_player *player)
{
	t_rectangle	player_rect;

	player_rect.x = player->x * MINIMAP_SCALE;
	player_rect.y = player->y * MINIMAP_SCALE;
	player_rect.width = player->width * MINIMAP_SCALE;
	player_rect.height = player->height * MINIMAP_SCALE;
	set_color_rect(&player_rect, RED_PIXEL);
	draw_rect(&cub3d->img_game, &player_rect);
}

void	render_ray_to_play(t_cubd *cub3d, t_player *player, t_line **line)
{	
	*line = draw_ray(cub3d, 
		player->x + cos(player->rotation_angle) * RAY_LENGHT,
		player->y + sin(player->rotation_angle) * RAY_LENGHT,
		WHITE_PIXEL);
}

void	render_player(t_cubd *cub3d, t_player *player)
{
	t_line	*line;

	render_only_player(cub3d, player);
	render_ray_to_play(cub3d, player, &line);
    player->line = line;
}

void	normalize_angle(double *angle)
{
	*angle = remainder(*angle, TWO_PI);
	if (*angle < 0)
		*angle = TWO_PI + *angle;
}

void	move_player(t_cubd *cub3d)

{
	double	move_step;
	double	side_step;
	double	new_player_x;
	double	new_player_y;

	if (cub3d->player->turn_direction)
	{
		cub3d->player->rotation_angle += cub3d->player->turn_direction * cub3d->player->turn_speed;
		normalize_angle(&cub3d->player->rotation_angle);
	}
	if (cub3d->player->walk_direction || cub3d->player->walk_side_direction)
	{

		move_step = cub3d->player->walk_direction * cub3d->player->walk_speed;
		side_step = cub3d->player->walk_side_direction * cub3d->player->walk_speed;
		if (cub3d->player->walk_side_direction && cub3d->player->walk_direction)
		{
			move_step /= 2;
			side_step /= 2;
		}
		new_player_x = cub3d->player->x + (cos(cub3d->player->rotation_angle) * move_step) + (cos(cub3d->player->rotation_angle + PI / 2) * side_step);
		new_player_y = cub3d->player->y + sin(cub3d->player->rotation_angle) * move_step + (sin(cub3d->player->rotation_angle + PI / 2) * side_step);
		if (has_wall_at(cub3d->game->map, new_player_x, new_player_y, cub3d))
			return ;
		cub3d->player->x = new_player_x;
		cub3d->player->y = new_player_y;
	}
}

int	key_down(int key, t_cubd *cub3d)
{
	if (key == KEY_SCAPE)
		game_exit(cub3d);
	else if (key == KEY_W)
		cub3d->player->walk_direction = +1;
	else if (key == KEY_S)
		cub3d->player->walk_direction = -1;
	else if (key == KEY_RIGHT)
		cub3d->player->turn_direction = +1;
	else if (key == KEY_LEFT)
		cub3d->player->turn_direction = -1;
	else if (key == KEY_A)
		cub3d->player->walk_side_direction = -1;
	else if (key == KEY_D)
		cub3d->player->walk_side_direction = +1;
	move_player(cub3d);
	game_render(cub3d);
	return (0);
}

int	key_up(int key, t_cubd *cub3d)
{
	if (key == KEY_W)
		cub3d->player->walk_direction = 0;
	else if (key == KEY_S)
		cub3d->player->walk_direction = 0;
	else if (key == KEY_RIGHT)
		cub3d->player->turn_direction = 0;
	else if (key == KEY_LEFT)
		cub3d->player->turn_direction = 0;
	else if (key == KEY_A)
		cub3d->player->walk_side_direction = 0;
	else if (key == KEY_D)
		cub3d->player->walk_side_direction = 0;
	return (0);
}
