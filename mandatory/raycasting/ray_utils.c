#include "cub3D.h"

t_line	*draw_ray(t_cubd *cub3d, double end_x, double end_y, int color)
{
	t_line	*line;

	line = malloc(sizeof(t_line));
	if (!line)
		return (NULL);
	line->begin_x = MINIMAP_SCALE * cub3d->player->x;
	line->begin_y = MINIMAP_SCALE * cub3d->player->y;
	line->end_x = MINIMAP_SCALE * end_x;
	line->end_y = MINIMAP_SCALE * end_y;
	line->color = color;
	draw_line(cub3d, line);
	return (line);
}
