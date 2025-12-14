#ifndef RENDRING_H
#define RENDRING_H

#include <cub3d.h>

/*knife*/
int     pick_pixel(t_img *data, int x, int y);
void	pput_pixel(t_img *data, int x, int y, int color);
void	put_image_to_window(t_img *dst, t_img *src, int x_src);
void	render_knife_hit(t_data *data);
void	render_knife_move(t_data *data);
void	render_knife(t_data *data); 


/*PROJACTION*/
void	render_wall(t_data *data, int x, int y, int wall_hight);
void	projaction(t_data *data);

/*MINI MAP*/
void	base_of_mini_map(t_data *data);
void	mini_map(t_data *data, int x, int y, int color);
void	render_player_mini_map(t_data *data);
void	render_mini_map_rays(t_data *data, t_cord cord, double z, double w);
void	render_rays_mini_map(t_data *data, int i);
void	render_mini_map(t_data *data);

/* FUNCTIONS */
void	free_rays(t_ray **rays);
void	free_all_data_and_exit(t_data *data, char *str);
int		is_wall(t_data *data, double *x, double *y);
void	put_pixel(t_img *data, int x, int y, int color);
void	update_palyer_state(t_data *data, t_player *player);
int		the_animation(t_data *data);
void	initialize_rays(t_data *data);
void	initialization(t_data *data);

#endif