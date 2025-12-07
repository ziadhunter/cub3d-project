#ifndef PARSING_H
#define PARSING_H

typedef struct s_data t_data;
typedef struct s_player t_player;
typedef struct s_coordinates t_cord;

typedef struct s_line
{
	char			*str;
	int				length;
	struct s_line	*next;
}					t_line;

typedef struct s_map_data
{
	char			**map;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	int				*f;
	int				*c;
	int				columns;
	int				rows;
	int				map_start;
	int				map_width;
	int				map_height;
}					t_map_data;

typedef struct s_element
{
	char			*type;
	int				length;
	void			(*handle)(t_map_data *map, char **str, char **lines, int i);
}					t_element;

typedef struct s_db_po
{
	char			**ptr;
	char			**ptrr;
}					t_db_pointer;

/* PARSING FUNCTIONS */
void				add_ceiling(t_map_data *map, char **str, char **lines, int i);
void				add_we(t_map_data *map, char **str, char **lines, int i);
void				add_ea(t_map_data *map, char **str, char **lines, int i);
void				add_so(t_map_data *map, char **str, char **lines, int i);
void				add_no(t_map_data *map, char **str, char **lines, int i);
void				add_floor(t_map_data *map, char **str, char **lines, int i);
void				which_element(char **line, int index, t_map_data *map,
						t_element element[6]);
int					all_element_found(t_map_data *map);
int					quick_check(char *line);
t_map_data				*extract_element(char **lines);
void				free_double_pointer(char **value);
void				free_map(t_map_data *map);
void				free_data(t_data *data);
void				error_exit(t_map_data *map, char **value,
						t_db_pointer *double_pointers, char *str);
int					is_space_or_wall(char c);
int					is_space_or_nl(char c);
t_map_data				*initialize_map(void);
t_player			*initialize_player(char c, int x, int y);
void				initialize_element(t_element (*element)[6]);
void				find_empty_line(t_map_data *map_info, char **lines, char *line,
						int fd);
void				check_empty_line(t_map_data *map_info, char **lines,
						char *file_name);
char				**set_new_lines(int len, int characters, char **lines);
char				**rebuild_map_with_same_size(t_map_data *map, char **lines,
						int start);
t_data				*parsing_the_map(t_map_data *map_info, char **lines,
						char *file_name);
void				check_extension(char *file_name, char *ext, t_map_data *map_info,
						t_db_pointer *pointers);
char				**get_lines_of_file(int fd);
int					ft_atoi_c(const char *str);
int					is_map_element(char c);
void				invalid_position(t_map_data *map_info, t_player *player,
						char **lines, t_cord cor);
void				check_element_position(t_map_data *map_info, t_player **player,
						char **lines, t_cord cor);
void				check_space_position(t_map_data *map_info, t_player *player,
						char **lines, t_cord cor);
t_player			*valid_map(t_map_data *map_info, char **map, int i, int j);
t_data				*parsing(char *file_name);

#endif