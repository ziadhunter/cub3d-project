#include "cub.h"

t_direction *facing_direction(double ray_angle)
{
	t_direction *dir;

	dir = malloc(sizeof(t_direction));
	if (!dir)
		return (NULL);
	dir->x = (ray_angle > 0 && ray_angle < PI) ? 0 : 1;
	dir->y = (ray_angle < 0.5 * PI || ray_angle > 1.5 * PI) ? 1 : 0;
	return (dir);
}

int is_wall2(t_data *data, double x, double y)
{
	t_cell *cell;
	double rx = x / TILE_SIZE;
	double ry = y / TILE_SIZE;

	// data->player->is_looking_at_door = false;
	if (!(x >= 0 && x < MAP_WIDTH * TILE_SIZE
		&& y >= 0 && y < MAP_HEIGHT * TILE_SIZE))
		return (NONE);
	cell = &(data->map.map[(int)ry][(int)rx]);
	if (cell->cell_type == DOOR && (((t_door *)(cell->options))->is_valid == true)
		&& ((t_door *)(cell->options))->door_state == CLOSED)
		return (DOOR);
	return (NONE);
}

int wall(t_data *data, double x, double y)
{
	t_cell *cell;
	double rx = x / TILE_SIZE;
	double ry = y / TILE_SIZE;

	cell = &(data->map.map[(int)ry][(int)rx]);
	if (cell->cell_type == WALL)
		return (WALL);
	else if (cell->cell_type == DOOR)
	{
		if (((t_door *)(cell->options))->is_valid == false)
			return (WALL);
		if ((((t_door *)(cell->options))->is_valid == true)
			&& ((t_door *)(cell->options))->door_state == CLOSED)
		return (DOOR);
	}

	return (0);
}

t_direction *find_horizontal_intersiction(
	t_data *data, double ray_angle, int facing_up, int facing_right)
{
	double x_step;
	double y_step;
	double x_intr;
	double y_intr;
	int vert, hors;
	t_cell_type cell_type;
	t_direction *dir;

	dir = malloc(sizeof(t_direction));
	if (!dir)
		return (NULL);
	if (fabs(tan(ray_angle)) < 1e-6)
	{
		free(dir);
		return (NULL);
	}
	y_intr = floor(data->player->y / TILE_SIZE) * TILE_SIZE;
	if (!facing_up)
		y_intr += TILE_SIZE;
	x_intr = ((y_intr - data->player->y) / tan(ray_angle))
		+ data->player->x;
	y_step = TILE_SIZE;
	if (facing_up)
		y_step *= -1;
	x_step = TILE_SIZE / tan(ray_angle);
	if ((x_step > 0 && !facing_right) || (x_step < 0 && facing_right))
		x_step *= -1;
	if (facing_up)
		y_intr--;

	if (facing_right) hors = 1;
	else hors = -1;

	if (facing_up) vert = -1;
	else vert = 1;
	while (x_intr >= 0 && x_intr < MAP_WIDTH * TILE_SIZE
		&& y_intr >= 0 && y_intr < MAP_HEIGHT * TILE_SIZE)
	{
		cell_type = wall(data, x_intr, y_intr);
        if (cell_type == DOOR)
            cell_type = is_wall2(
                data,
                x_intr + (x_step / 2),
                y_intr + (TILE_SIZE / 2) * vert);
		if (cell_type != NONE)
		{
			dir->x = x_intr;
			dir->y = y_intr;
			if (cell_type == DOOR)
			{
				dir->x += (x_step / 2);
				dir->y += (TILE_SIZE / 2) * vert;
			}
			return dir;
		}
		x_intr += x_step;
		y_intr += y_step;
	}
	return NULL;
}

t_direction *find_vertical_intersiction(
	t_data *data, double ray_angle, int facing_up, int facing_right)
{
	double x_step;
	double y_step;
	double x_intr;
	double y_intr;
	int hors, vert;
	t_cell_type cell_type;
	t_direction *dir;

	if (fabs(cos(ray_angle)) < VERTICAL_RAY_THRESHOLD)
		return (NULL);
	dir = malloc(sizeof(t_direction));
	if (!dir)
		return (NULL);
	x_intr = floor(data->player->x / TILE_SIZE) * TILE_SIZE;
	if (facing_right)
		x_intr += TILE_SIZE;
	y_intr = data->player->y + (x_intr - data->player->x) * tan(ray_angle);
	x_step = TILE_SIZE;
	if (!facing_right)
		x_step *= -1;
	y_step = TILE_SIZE * tan(ray_angle);
	if ((y_step > 0 && facing_up) || (y_step < 0 && !facing_up))
		y_step *= -1;
	if (!facing_right)
		x_intr--;

	if (facing_right) hors = 1;
	else hors = -1;

	if (facing_up) vert = -1;
	else vert = 1;
	int sign_y = (tan(ray_angle) > 0 ? +1 : -1);

	while (x_intr >= 0 && x_intr < MAP_WIDTH * TILE_SIZE
		&& y_intr >= 0 && y_intr < MAP_HEIGHT * TILE_SIZE)
	{
		cell_type = wall(data, x_intr, y_intr);
        if (cell_type == DOOR)
            cell_type = is_wall2(
                data,
                x_intr + ((TILE_SIZE / 2) * hors),
                y_intr + ((y_step / 2)));
		if (cell_type != NONE)
		{
			dir->y = y_intr;
			dir->x = x_intr;
			if (cell_type == DOOR)
			{
				dir->y += (y_step / 2);
				dir->x += (TILE_SIZE / 2) * hors;
			}
			return dir;
		}
		x_intr += x_step;
		y_intr += y_step;
	}
	return NULL;
}

void insert_end_ray(t_ray *ray, t_direction *dir, int intersection)
{
	ray->end_x = dir->x;
	ray->end_y = dir->y;
	ray->intersection = intersection;
}

void short_ray(t_data * data, t_ray *ray, t_direction *horizontal_inters, t_direction *vertical_inters)
{
	double dist_h;
	double dist_v;

	if (horizontal_inters && vertical_inters)
	{
		dist_h = hypot(horizontal_inters->x - data->player->x,
				horizontal_inters->y - data->player->y);
		dist_v = hypot(vertical_inters->x - data->player->x,
				vertical_inters->y - data->player->y);
		if (dist_h < dist_v)
			insert_end_ray(ray, horizontal_inters, HORIZONTAL);
		else
			insert_end_ray(ray, vertical_inters, VERTICAL);
	}
	else if (horizontal_inters)
		insert_end_ray(ray, horizontal_inters, HORIZONTAL);
	else if (vertical_inters)
		insert_end_ray(ray, vertical_inters, VERTICAL);
}

// void render_rays(t_data *data, double x, double y, double z, double w)
// {
//     double xi;
//     double yi;
//     int step;

//     if (fabs(z - x) > fabs(w - y))
//         step = fabs(z - x);
//     else
//         step = fabs(w - y);
//     xi = (z - x) / step;
//     yi = (w - y) / step;
//     for (int i = 0; i < step; i++)
//     {
//         put_pixel(&data->new_image, x, y, BLUE);
//         put_pixel(&data->new_image, x + 1, y, BLUE);
//         put_pixel(&data->new_image, x, y + 1, BLUE);
//         put_pixel(&data->new_image, x, y - 1, BLUE);
//         put_pixel(&data->new_image, x -1, y, BLUE);       
//         x += xi;
//         y += yi;
//     }
// }
void define_ray_position(t_data *data, double ray_angle, t_ray *ray)
{
	t_direction *dir;
	t_direction *horizontal_inters;
	t_direction *vertical_inters;
	int short_inter;

	dir = facing_direction(ray_angle);
	horizontal_inters = find_horizontal_intersiction(data, ray_angle, dir->x, dir->y);
	vertical_inters = find_vertical_intersiction(data, ray_angle, dir->x, dir->y);
	short_ray(data, ray, horizontal_inters, vertical_inters);
	ray->ray_direction.x = dir->x;
	ray->ray_direction.y = dir->y;
	free(dir);
	free(horizontal_inters);
	free(vertical_inters);
}


t_ray **creat_ray_casting(t_data *data)
{
	double ray_angle;
	int column;
	t_ray **rays;

	rays = malloc(sizeof(t_ray *) * NUM_COLUMNS);
	if (!rays)
		return NULL;
	for (int i = 0; i < NUM_COLUMNS; i++)
	{
		rays[i] = malloc(sizeof(t_ray));
		if (!rays[i])
			return NULL; 
	}
	column = 0;
	ray_angle = data->player->rotation_angle - (FOV / 2);
	while (column < NUM_COLUMNS)
	{
		if (ray_angle > (2 * PI) || ray_angle < 0)
			ray_angle = normalize_angle(ray_angle);
		rays[column]->ray_angle = ray_angle;
		rays[column]->start_x = data->player->x;
		rays[column]->start_y = data->player->y;
		define_ray_position(data, ray_angle, rays[column]);

		ray_angle += FOV / NUM_COLUMNS;
		column++;
	}
	return(rays);
}