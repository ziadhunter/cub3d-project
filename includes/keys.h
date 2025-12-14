#ifndef KEYS_H
#define KEYS_H

typedef struct s_data t_data;

/* Enums */
typedef enum e_keys
{
	UP_BUTTON = 119,
	DOWN_BUTTON = 115,
	LEFT_BUTTON = 97,
	RIGHT_BUTTON = 100,
	LEFT_ARROW = 65361,
	RIGHT_ARROW = 65363,
	ESC = 65307,
	SHIFT_SPEED = 65505,
	SPEED_DOWN = 49,
	SPEED_UP = 50,
	R_SPEED_DOWN = 51,
	R_SPEED_UP = 52,
	MOUSSE_HIDE = 120
} t_keys;

/*KEY HANDLE*/
int		mouse_press(int key, int x, int y, t_data *data);
int		mouse_move(int x, int y, t_data *data);
void	speed_adjustment(int key, t_data *data);
void	mouvement_adjustment(int key, t_data *data);
void	rotation_adjustment(int key, t_data *data);
void	rotation_release(int key, t_data *data);
void	mouvement_release(int key, t_player *player);
int		close_window(t_data *data);
int		mouse_move(int x, int y, t_data *data);
int		key_release(int key, t_data *data);
int		key_press(int key, t_data *data);

#endif