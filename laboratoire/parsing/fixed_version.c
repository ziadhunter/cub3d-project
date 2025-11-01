#include "../cub.h"

void free_double_pointer(char **value)
{
    int i;
    
    i = 0;
    if (value)
    {
        while (value[i])
        {
            free(value[i]);
            i++;
        }
        free(value);
    }
}
void free_map(t_map *map)
{
    if (map)
    {
        if (map->c)
            free(map->c);
        if (map->f)
            free(map->f);
        if (map->ea)
            free(map->ea);
        if (map->no)
            free(map->no);    
        if (map->so)
            free(map->so);
        if (map->we)
            free(map->we);
        if (map->map)
            free_double_pointer(map->map);
        free(map);
    }
}
void error_exit(t_map *map, char **value, t_db_pointer *double_pointers,char *str)
{
    printf("%s", str);
    if (value)
        free_double_pointer(value);
    if (double_pointers)
    {
        if (double_pointers->ptr)
            free_double_pointer(double_pointers->ptr);
        if (double_pointers->ptrr)
            free_double_pointer(double_pointers->ptrr);
    }
    free_map(map);
    exit(1);
}
void check_extension(char *file_name, char *ext , t_map *map_info, t_db_pointer *pointers)
{
    int fn = ft_strlen(file_name);
    int ex = ft_strlen(ext);

    if (fn <= ex || ft_strncmp(file_name + fn - ex, ext, ex) != 0)
    {
        if (ft_strncmp(ext, ".cub", ex) == 0)
            error_exit(NULL, NULL, NULL,"Error\nInvalid file extension: expected .cub\n");
        else
            error_exit(map_info, NULL, pointers, "Error\nInvalid file extension: expected .xpm\n");
    }
}



t_map *initialize_map()
{
    t_map *map;

    map = malloc(sizeof(t_map));
    map->c = NULL;
    map->f = NULL;
    map->no = NULL;
    map->so = NULL;
    map->ea = NULL;
    map->we = NULL;
    map->map = NULL;
    map->map_height = 0;
    map->map_length = 0;
    return (map);
}

char ** get_lines_of_file(int fd)
{
    char *line;
    char *lines;
    char **splited_lines; 

    lines = ft_strdup("");
    line = get_next_line(fd);
    while (line)
    {
        lines = ft_strjoin(lines, line);
        line = get_next_line(fd);
    }
    splited_lines = ft_split(lines, '\n');
    free(lines);
    return (splited_lines);
}

int	ft_atoi_c(const char *str)
{
	int	i;
	int	sign;
	int	result;

	sign = 1;
	i = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - 48);
		i++;
	}
    if (str[i] && (str[i] != '\n' || (str[i] == '\n' && i == 0)))
        return (-1);
    result *= sign;
    if (result > 255 || result < 0)
        return (-1);
    return (result);
}

int is_map_element(char c)
{
    if (c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ' || c == 'D')
        return (1);
    return (0); 
}



void add_floor(t_map *map, char **str, char **lines)
{
    char **values;
    int i;

    if (map->f)
        error_exit(map, lines, &(t_db_pointer){str, NULL}, "Error\nfloor element duplicated\n");
    values = ft_split(str[1], ',');
    if (!values)
        error_exit(map, lines, &(t_db_pointer){str, NULL}, "Error\nthere is no floor values\n");
    map->f = malloc(sizeof(int) * 3);
    i = 0;
    while (i < 3)
    {
        if (!values[i])
            error_exit(map, values, &(t_db_pointer){lines, str}, "Error\nmissing floor values\n");
        map->f[i] = ft_atoi_c(values[i]);// modify atoi based on cube needs 
        if (map->f[i] == -1)
            error_exit(map, values, &(t_db_pointer){lines, str}, "Error\nwrong floor value\n");
        i++;
    }
    if (str[2] || values[3])
        error_exit(map, values, &(t_db_pointer){lines, str}, "Error\n extra floor argument\n");
    free_double_pointer(values);
}


void add_ceiling(t_map *map, char **str, char **lines)
{
    char **values;
    int i;

    if (map->c)
        error_exit(map, lines, &(t_db_pointer){str, NULL},"Error\nceiling element duplicated\n");
    values = ft_split(str[1], ',');
    if (!values)
        error_exit(map, lines, &(t_db_pointer){str, NULL}, "Error\nthere is no ceiling value\n");
    map->c = malloc(sizeof(int) * 3);
    i = 0;
    while (i < 3)
    {
        if (!values[i])
            error_exit(map, values, &(t_db_pointer){lines, str}, "Error\nmissing ceiling value\n");
        map->c[i] = ft_atoi_c(values[i]);
        if (map->c[i] == -1)
            error_exit(map, values, &(t_db_pointer){lines, str}, "Error\nwrong ceiling value\n");
        i++;
    }
    if (str[2] || values[3])
        error_exit(map, values, &(t_db_pointer){lines, str}, "Error\n extra ceiling argument\n");
    free_double_pointer(values);
}

void add_we(t_map *map, char **str, char **lines)
{
    int fdd;

    if (map->we)
        error_exit(map, lines, &(t_db_pointer){str, NULL},"Error\nWE element duplicated\n");
    if (str[1])
    {
        check_extension(str[1], ".xpm", map, &(t_db_pointer){str, lines});
        fdd = open(str[1], O_RDONLY);
        if (fdd < 0)
            error_exit(map, lines, &(t_db_pointer){str, NULL}, "Error\nWE texture file doesn't exist\n");
        close(fdd);
        if (str[2])
            error_exit(map, lines, &(t_db_pointer){str, NULL}, "Error\nextra argument of WE\n");
        map->we = ft_strdup(str[1]);
    }
    else
        error_exit(map, lines, &(t_db_pointer){str, NULL}, "Error\nmissing WE file texture\n");
}

void add_ea(t_map *map, char **str, char **lines)
{
    int fdd;

    if (map->ea)
        error_exit(map, lines, &(t_db_pointer){str, NULL}, "Error\nEA element duplicated\n");
    if (str[1])
    {
        check_extension(str[1], ".xpm", map, &(t_db_pointer){str, lines});
        fdd = open(str[1], O_RDONLY);
        if (fdd < 0)
            error_exit(map, lines, &(t_db_pointer){str, NULL}, "Error\nEA texture file doesn't exist\n");
        close(fdd);
        if (str[2])
            error_exit(map, lines, &(t_db_pointer){str, NULL}, "Error\nextra argument of EA\n");
        map->ea = ft_strdup(str[1]);
    }
    else
        error_exit(map, lines, &(t_db_pointer){str, NULL}, "Error\nmissing EA file texture\n");
}

void add_so(t_map *map, char **str, char **lines)
{
    int fdd;

    if (map->so)
        error_exit(map, lines, &(t_db_pointer){str, NULL}, "Error\nSO element duplicated\n");
    if (str[1])
    {
        check_extension(str[1], ".xpm", map, &(t_db_pointer){str, lines});
        fdd = open(str[1], O_RDONLY);
        if (fdd < 0)
            error_exit(map, lines, &(t_db_pointer){str, NULL}, "Error\nSO texture file doesn't exist\n");
        close(fdd);
        if (str[2])
            error_exit(map, lines, &(t_db_pointer){str, NULL}, "Error\nextra argument of SO\n");
        map->so = ft_strdup(str[1]);
    }
    else
        error_exit(map, lines, &(t_db_pointer){str, NULL}, "Error\nmissing SO file texture\n");
}

void add_no(t_map *map, char **str, char **lines)
{
    int fdd;

    if (map->no)
        error_exit(map, lines, &(t_db_pointer){str, NULL}, "Error\nNO element duplicated\n");
    if (str[1])
    {
        check_extension(str[1], ".xpm", map, &(t_db_pointer){str, lines});
        fdd = open(str[1], O_RDONLY);
        if (fdd < 0)
            error_exit(map, lines, &(t_db_pointer){str, NULL}, "Error\nNO texture file doesn't exist\n");
        close(fdd);
        if (str[2])
            error_exit(map, lines, &(t_db_pointer){str, NULL}, "Error\nextra argument of NO\n");
        map->no = ft_strdup(str[1]);
    }
    else
        error_exit(map, lines, &(t_db_pointer){str, NULL}, "Error\nmissing NO file texture\n");
}

t_player *initialize(char c, t_player *player, t_oldmove *old)
{
    old = malloc(sizeof(t_oldmove));
    old->back = 0;
    old->forw = 0;
    old->left = 0;
    old->right = 0;
    old->turn_left = 0;
    old->turn_right = 0;
    player = malloc(sizeof(t_player));
    player->old_move = old;
    player->x = 7 * 64;
    player->y = 5 * 64;
    player->radius = 9;
    player->back_forw = 0;
    player->left_right = 0;
    player->rotation_angle = 0;
    if (c == 'S')
        player->rotation_angle = PI / 2;
    if (c == 'N')
        player->rotation_angle = 3 * (PI / 2);
    if (c == 'W')
        player->rotation_angle = PI;
    player->walking_speed = 2;
    player->rotation_speed = (PI / 180) / 2 ;
    return(player);
}

void initialize_element(t_element (*element)[6])
{
    (*element)[0].type = "F";
    (*element)[0].length = 1;
    (*element)[0].handle = add_floor;
    (*element)[1].type = "C";
    (*element)[1].length = 1;
    (*element)[1].handle = add_ceiling;
    (*element)[2].type = "NO";
    (*element)[2].length = 2;
    (*element)[2].handle = add_no;
    (*element)[3].type = "SO";
    (*element)[3].length = 2;
    (*element)[4].type = "EA";
    (*element)[4].length = 2;
    (*element)[5].type = "WE";
    (*element)[5].length = 2;
    (*element)[3].handle = add_so;
    (*element)[4].handle = add_ea;
    (*element)[5].handle = add_we;
}

void which_element(char **line, int index, t_map *map, t_element element[6])
{
    char **splited_line;
    int i;

    i = 0;
    splited_line = ft_split(line[index], ' ');
    if (splited_line == NULL)
        return;
    while (i < 6)
    {
        if (ft_strncmp(splited_line[0], element[i].type, element[i].length + 1) == 0)
        {
            element[i].handle(map, splited_line, line);
            free_double_pointer(splited_line);
            return;
        }
        i++;
    }
    free_double_pointer(splited_line);
    free_double_pointer(line);
    error_exit(map, NULL, NULL, "Error\nwrong element\n");
}


int all_element_found(t_map *map)
{
    if (map->c && map->f && map->no && map->so && map->ea && map->we)
        return(1);
    return (0);
}

int quick_check(char *line)
{
    int i;

    i = 0;
    while(line[i])
    {
        if (is_map_element(line[i]) || (line[i] == '\n' && i != 0))
        {
            i++;
            continue;
        }
        return (0);
    }
    return(1);
}

t_map *extract_element(char **lines)
{
    t_map *map;
    int i;
    t_element elements[6];

    i = 0;
    initialize_element(&elements);
    map = initialize_map();

    while (lines[i])
    {
        if (quick_check(lines[i]))
            break;
        which_element(lines, i, map, elements);
        i++;
    }
    if (!all_element_found(map))
    {
        free_double_pointer(lines);
        error_exit(map, NULL, NULL, "Error\nmissing some element(s)!!");
    }
    map->map_start = i;
    return (map);
}

int is_space_or_wall(char c)
{
    if (c == ' ' || c == '1' || c == '\0')
        return (1);
    return (0);
}

int is_space_or_nl(char c)
{
    if (c == ' ' || c == '\0')
        return (1);
    return (0);
}

void invalid_position(t_map *map_info, t_player *player, char **lines, t_cord cor)
{
    int i;
    int j;

    i = cor.x;
    j = cor.y;
    if (i <= 0 || j <= 0 || i + 1 >= map_info->map_length || j + 1>= map_info->map_height)
    {
        if (player)
        {
            free(player->old_move);
            free(player);
        }
        error_exit(map_info, lines, NULL, "Error\ninvalid map (edge open)1\n");
    }
    if (is_space_or_nl(lines[j][i - 1]) || is_space_or_nl(lines[j - 1][i]) || is_space_or_nl(lines[j + 1][i]) || is_space_or_nl(lines[j][i + 1]))
    {
        if (player)
        {
            free(player->old_move);
            free(player);
        }
        error_exit(map_info, lines, NULL, "Error\ninvalid map (edge open)\n");
    }
}

void check_element_position(t_map *map_info, t_player **player, char **lines, t_cord cor)
{
    int i;
    int j;

    i = cor.x;
    j = cor.y;
    invalid_position(map_info, *player, lines, cor);
    if (lines[j][i] == 'N' || lines[j][i] == 'S' || lines[j][i] == 'W' || lines[j][i] == 'E')
    {
        if (!(*player))
            *player = initialize(lines[j][i], NULL, NULL);
        else
        {
            free((*player)->old_move);
            free(*player);
            error_exit(map_info, lines, NULL, "Error\ninvalid map(two or more players)");
        }
    }
}

void check_space_position(t_map *map_info, t_player *player, char **lines, t_cord cor)
{
    int i;
    int j;

    i = cor.x;
    j = cor.y;
    if (i <= 0 || j <= 0 || i >= map_info->map_length|| j + 1>= map_info->map_height)
        return;
    if(!is_space_or_wall(lines[j + 1][i]) ||
        !is_space_or_wall(lines[j - 1][i]) ||
        !is_space_or_wall(lines[j][i + 1]) ||
        !is_space_or_wall(lines[j][i - 1]))
    {
        if (player != NULL)
        {
            free(player->old_move);
            free(player);
        }
        error_exit(map_info, lines, NULL, "Error\ninvalid map");
    }
}

t_player *valid_map(t_map *map_info, char **map, int i, int j)
{
    t_player *player;

    player = NULL;
    j = 0;
    while(map[j])
    {
        i = 0;
        while(map[j][i])
        {
            if (map[j][i] == '0' || map[j][i] == 'N' ||
                map[j][i] == 'S' || map[j][i] == 'E' || map[j][i] == 'W')
                check_element_position(map_info, &player, map, (t_cord){i, j});
            if (map[j][i] == ' ')
                check_space_position(map_info, player, map, (t_cord){i, j});
            i++;
        }
        j++;
    }
    map_info->map = map;
    return (player);
}

void check_empty_line(t_map *map_info, char **lines, char *file_name)
{
    int fd;
    char *line;
    int i;

    i = map_info->map_start;
    fd = open(file_name, O_RDONLY);
    line = get_next_line(fd);
    while(ft_strncmp(lines[0], line, ft_strlen(lines[0])) != 0)
    {
        free(line);
        line = get_next_line(fd);
    }
    while (line)
    {
        if (line[0] == '\n')
        {
            while (line)
            {
                if (line[0] != '\n')
                {
                    close(fd);
                    free(line);
                    error_exit(map_info, lines, NULL, "Error\nempty line inside map\n");
                }
                free(line);
                line = get_next_line(fd);
            }
            return;
        }
        free(line);
        line = get_next_line(fd);
    }
}

char **set_new_lines(int len, int characters, char **lines)
{
    char **new_lines;
    int i;

    i = 0;
    if (len <= 0)
    {
        free_double_pointer(lines);
        return (NULL);
    }
    new_lines = malloc(sizeof(char *) * (len + 1));
    while(i < len)
    {
        new_lines[i] = malloc(sizeof(char) * (characters + 1));
        ft_memset(new_lines[i], ' ', characters);
        new_lines[i][characters] = '\0';
        i++;
    }
    new_lines[i] = NULL;
    return(new_lines); 
}

char **rebuild_map_with_same_size(t_map *map,char **lines, int start)
{
    int i;
    int max_lenght;
    int current_lenght;
    char **new_lines;

    i = start;
    max_lenght = 0;
    while(lines[i])
    {
        current_lenght = ft_strlen(lines[i]);
        if (max_lenght < current_lenght)
            max_lenght = current_lenght;
        i++;
    }
    map->map_height = i - start;
    map->map_length = max_lenght;
    new_lines = set_new_lines(i - start, max_lenght, lines);
    if (!new_lines)
        return (NULL);
    i = -1;
    while (new_lines[++i])
        ft_strlcpy(new_lines[i], lines[start + i], max_lenght + 1);
    free_double_pointer(lines);
    return (new_lines);
}

t_data *parsing_the_map(t_map *map_info, char **lines, char *file_name)
{
    t_player *player;
    t_data *data;

    lines = rebuild_map_with_same_size(map_info, lines, map_info->map_start);
    if (!lines)
        error_exit(map_info, NULL, NULL, "Error\nmap missing\n");
    check_empty_line(map_info, lines, file_name);
    player = valid_map(map_info, lines, 0, 0);
    if (!player)
         error_exit(map_info, lines, NULL, "Error\nmissing a player\n");
    data = malloc(sizeof(t_data));
    data->map_info = map_info;
    data->player = player;
    return (data);
}

t_data *parsing(char *file_name)
{
    int fd; 
    t_map *map_info;
    t_data * data;
    char **lines;

    check_extension(file_name, ".cub", NULL, NULL);
    fd = open(file_name, O_RDONLY);
    if (fd == -1)
        error_exit(NULL, NULL, NULL, "Error\ncould not find the file\n");
    lines = get_lines_of_file(fd);
    close(fd);
    map_info = extract_element(lines);
    data = parsing_the_map(map_info, lines, file_name);
    return (data);
}

void free_data(t_data *data)
{
    free_map(data->map_info);
    free(data->player->old_move);
    free(data->player);
    free(data);
}

int main(int argc, char *argv[])
{
    int i;
    int j;
    t_data *data;
    t_map *map;
    
    i = 0;
    j = 0;
    if (argc == 2)
    {
        data = parsing(argv[1]);
        printf("all good\n");
        map = data->map_info;
        printf("floor :%d, %d, %d\n", map->f[0], map->f[1], map->f[2]);
        printf("ceiling :%d, %d, %d\n", map->c[0], map->c[1], map->c[2]);
        printf("north wall :%s\n", map->no);
        printf("south wall :%s\n", map->so);
        printf("east wall :%s\n", map->ea);
        printf("west wall :%s\n", map->we);
        while (map->map[j])
        {
            printf("%s\n", map->map[j]);
            j++;
        }
        free_data(data);
    }
    // free_data(data);
}