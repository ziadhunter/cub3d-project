#include "../cub.h"

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
        free(map);
    }
}


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
void error_exit(t_map *map, char **value, char *str, int fd)
{
    printf("%s", str);
    close(fd);
    free_double_pointer(value);
    free_map(map);
    exit(1);
}

void check_extension(char *file_name, char *ext, int fd)
{
    if (ft_strlen(file_name) < 5 || ft_strncmp(file_name + (ft_strlen(file_name) - 4), ext, 5) != 0)
    {
        if (ft_strncmp(".cub", ext, 5) == 0)
            error_exit(NULL, NULL, "Error\nInvalid file extension: expected .cub\n", fd);
        else
            error_exit(NULL, NULL, "Error\nInvalid file extension: expected .xpm\n", fd);
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
    map->map_width = 0;
    return (map);
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
    {
        return (-1);
    }
	return (result);
}


void add_floor(t_map *map, char **str, int fd)
{
    char **values;
    int i;

    if (map->f)
        error_exit(map, NULL, "Error\nfloor element duplicated\n", fd);
    values = ft_split(str[1], ',');
    if (!values)
        error_exit(map, NULL, "Error\nwrong floor values\n", fd);
    map->f = malloc(sizeof(int) * 3);
    i = 0;
    while (i < 3)
    {
        if (!values[i])
            error_exit(map, values, "Error\nmissing floor values\n", fd);
        map->f[i] = ft_atoi_c(values[i]);// modify atoi based on cube needs 
        if (map->f[i] == -1)
            error_exit(map, values, "Error\nwrong floor value\n", fd);
        i++;
    }
    if ((str[2] && ft_strncmp(str[2],"\n", 2) != 0) || values[3])
        error_exit(map, values, "Error\n extra floor argument\n", fd);
    free_double_pointer(values);
}

void add_ceiling(t_map *map, char **str, int fd)
{
    char **values;
    int i;

    if (map->c)
        error_exit(map, NULL, "Error\nceiling element duplicated\n", fd);
    values = ft_split(str[1], ',');
    if (!values)
        error_exit(map, NULL, "Error\nwrong ceiling value\n", fd);
    map->c = malloc(sizeof(int) * 3);
    i = 0;
    while (i < 3)
    {
        if (!values[i])
            error_exit(map, values, "Error\nmissing ceiling value\n", fd);
        map->c[i] = ft_atoi_c(values[i]);// modify atoi based on cube needs 
        if (map->c[i] == -1)
            error_exit(map, values, "Error\nwrong ceiling value\n", fd);
        i++;
    }
    if ((str[2] && ft_strncmp(str[2],"\n", 2) != 0) || values[3])
        error_exit(map, values, "Error\n extra ceiling argument\n", fd);
    free_double_pointer(values);
}

void add_we(t_map *map, char **str, int fd)
{
    int fdd;
    int lenght;
    char **tmp;

    if (map->we)
        error_exit(map, NULL, "Error\nWE element duplicated\n", fd);
    if (str[1])
    {
        lenght = ft_strlen(str[1]);
        if (str[1][lenght] == '\n')
            str[1][lenght] = '\0';
        tmp = ft_split(str[1], '\n');
        check_extension(tmp[0], ".xpm", fd);
        fdd = open(tmp[0], O_RDONLY);
        free_double_pointer(tmp);
        if (fdd < 0)
            error_exit(map, NULL, "Error\nWE texture file doesn't exist\n", fd);
        close(fdd);
        if (str[2] && ft_strncmp(str[2],"\n", 2) != 0)
            error_exit(map, NULL, "Error\nextra argument of WE\n", fd);
        map->we = ft_strdup(str[1]);
    }
    else
        error_exit(map, NULL, "Error\nmissing WE file texture\n", fd);
}

void add_ea(t_map *map, char **str, int fd)
{
    int fdd;
    int lenght;
    char **tmp;


    if (map->ea)
        error_exit(map, NULL, "Error\nEA element duplicated\n", fd);
    if (str[1])
    {
        lenght = ft_strlen(str[1]);
        if (str[1][lenght] == '\n')
            str[1][lenght] = '\0';
        tmp = ft_split(str[1], '\n');
        check_extension(tmp[0], ".xpm", fd);
        fdd = open(tmp[0], O_RDONLY);
        free_double_pointer(tmp);
        if (fdd < 0)
            error_exit(map, NULL, "Error\nEA texture file doesn't exist\n", fd);
        close(fdd);
        if (str[2] && ft_strncmp(str[2],"\n", 2) != 0)
            error_exit(map, NULL, "Error\nextra argument of EA\n", fd);
        map->ea = ft_strdup(str[1]);
    }
    else
        error_exit(map, NULL, "Error\nmissing EA file texture\n", fd);
}

void add_so(t_map *map, char **str, int fd)
{
    int fdd;
    int lenght;
    char **tmp;

    if (map->so)
        error_exit(map, NULL, "Error\nSO element duplicated\n", fd);
    if (str[1])
    {
        lenght = ft_strlen(str[1]);
        if (str[1][lenght] == '\n')
            str[1][lenght] = '\0';
        tmp = ft_split(str[1], '\n');
        check_extension(tmp[0], ".xpm", fd);
        fdd = open(tmp[0], O_RDONLY);
        free_double_pointer(tmp);
        if (fdd < 0)
            error_exit(map, NULL, "Error\nSO texture file doesn't exist\n", fd);
        close(fdd);
        if (str[2] && ft_strncmp(str[2],"\n", 2) != 0)
            error_exit(map, NULL, "Error\nextra argument of SO\n", fd);
        map->so = ft_strdup(str[1]);
    }
    else
        error_exit(map, NULL, "Error\nmissing SO file texture\n", fd);
}

void add_no(t_map *map, char **str, int fd)
{
    int fdd;
    int lenght;
    char **tmp;

    if (map->no)
        error_exit(map, NULL, "Error\nNO element duplicated\n", fd);
    if (str[1])
    {
        lenght = ft_strlen(str[1]);
        if (str[1][lenght] == '\n')
            str[1][lenght] = '\0';
        tmp = ft_split(str[1], '\n');
        check_extension(tmp[0], ".xpm", fd);
        fdd = open(tmp[0], O_RDONLY);
        free_double_pointer(tmp);
        if (fdd < 0)
            error_exit(map, NULL, "Error\nNO texture file doesn't exist\n", fd);
        close(fdd);
        if (str[2] && ft_strncmp(str[2],"\n", 2) != 0)
            error_exit(map, NULL, "Error\nextra argument of NO\n", fd);
        map->no = ft_strdup(str[1]);
    }
    else
        error_exit(map, NULL, "Error\nmissing NO file texture\n", fd);
}


void which_element(char *line, t_map *map, t_element element[6], int fd)
{
    char **splited_line;
    int i;

    i = 0;
    splited_line = ft_split(line, ' ');
    if (splited_line == NULL || ft_strncmp(splited_line[0], "\n", 1) == 0)
        return;
    while (i < 6)
    {
        if (ft_strncmp(splited_line[0], element[i].type, element[i].length + 1) == 0)
        {
            element[i].handle(map, splited_line, fd);
            free_double_pointer(splited_line);
            return;
        }
        i++;
    }
    free_double_pointer(splited_line);
    error_exit(map, NULL, "Error\nwrong element\n", fd);
}

int all_element_found(t_map *map)
{
    if (map->c && map->f && map->no && map->so && map->ea && map->we)
        return(1);
    return (0);
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
int is_map_element(char c)
{
    if (c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ' || c == 'D')
        return (1);
    return (0); 
}
int check_the_line(t_map *map, char *line, int fd, int i)
{
    int j;

    j = 0;
    if (!line && i == 1)
        error_exit(map, NULL, "Error\nmissing map\n", fd);
    if (line[0] == '\n')
        return (0);
    while (line[j])
    {    
        if (is_map_element(line[j]) || line[j] == '\n')
        {
            j++;
            continue;
        }
        else
        {
            free(line);
            error_exit(map, NULL, "Error\nwrong map element\n", fd);
        }
        j++;
    }
    return (1);   
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

t_map *extract_element(int fd)
{
    t_map *map;
    char *line;
    t_element elements[6];


    initialize_element(&elements);
    map = initialize_map();
    line = get_next_line(fd);
    while (line != NULL)
    {
        if (quick_check(line))
            break;
        which_element(line, map, elements, fd);
        free(line);
        line = get_next_line(fd);
    }
    if (!line || !all_element_found(map))
    {
        free(line);
        error_exit(map, NULL, "Error\nmissing some element(s)!!", fd);
    }
    map->line = line;
    return (map);
}

t_line *new_node_c(char *line, int lenght)
{
    t_line *node;

    node = malloc(sizeof(t_line));
    node->length = lenght;
    node->str = ft_strdup(line);
    node->next = NULL;
    return(node);
}

void add_last(t_line **head, t_line *node)
{
    t_line *tmp;

    if (!node)
        return;
    if (!(*head))
    {
        (*head) = node;
        return;
    }
    tmp = (*head);
    while(tmp->next)
        tmp = tmp->next;
    tmp->next = node;
}

t_line *creat_linked_list(t_map* map, char *line, int fd)
{
    t_line *node;
    t_line *head;

    head = NULL;
    while (line)
    {
        if (check_the_line(map, line, fd, 0))
        {
            node = new_node_c(line, ft_strlen(line));
            if (head == NULL)
                head = node;
            else
                add_last(&head, node);
        }
        else
        {
            free(line);
            error_exit(map, NULL, "Error\n wrong map element\n", fd);
        }
        free(line);
        line = get_next_line(fd);
    }
    return (head);
}

char **convert_to_double_pointer(t_line *head, t_map *map_info, int i, int max_length)
{
    t_line *tmp;
    char *line;
    char **map;
    
    tmp = head;
    while (tmp)
    {
        i++;
        if (max_length < tmp->length)
            max_length = tmp->length;
        tmp = tmp->next;
    }
    map_info->map_width = max_length;
    map_info->map_height = i;
    map = malloc(sizeof(char *) * (i + 1));
    i = 0;
    while (head)
    {
        line = malloc(sizeof(char) * (max_length + 1));
        ft_bzero(line, max_length + 1);
        ft_strlcpy(line, head->str, (size_t)max_length + 1);
        map[i++] = line;
        tmp = head;
        head = head->next;
        free(tmp->str);
        free(tmp);
    }
    map[i] = NULL;
    return (map);
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

int is_space_or_wall(char c)
{
    if (c == ' ' || c == '1' || c == '\n' || c == '\0')
        return (1);
    return (0);
}

int is_space_or_nl(char c)
{
    if (c == ' ' || c == '\n')
        return (1);
    return (0);
}

void check_element_position(t_map *map_info, t_player **player, int i, int j)
{
    char **map;

    map = map_info->map;
    if (i <= 0 || j <= 0 || i >= map_info->map_width || j + 1>= map_info->map_height)
        error_exit(map_info, NULL, "Error\ninvalid map (edge open)\n", -1);
    if (is_space_or_nl(map[j][i - 1]) || is_space_or_nl(map[j - 1][i]) || is_space_or_nl(map[j + 1][i]) || is_space_or_nl(map[j][i + 1]))
        error_exit(map_info, NULL, "Error\ninvalid map (edge open)\n", -1);
    if (map[j][i] == 'N' || map[j][i] == 'S' || map[j][i] == 'W' || map[j][i] == 'E')
    {
        if (!(*player))
            *player = initialize(map[j][i], NULL, NULL);
        else
        {
            free((*player)->old_move);
            free(*player);
            error_exit(map_info, NULL, "Error\ninvalid map(two or more players)", -1);
        }
    }
}

void check_space_position(t_map *map_info, t_player *player, int i, int j)
{
    char **map;
    map = map_info->map;

    if (i <= 0 || j <= 0 || i >= map_info->map_width || j >= map_info->map_height)
        return; 
    if(!is_space_or_wall(map[j + 1][i]) ||
        !is_space_or_wall(map[j - 1][i]) ||
        !is_space_or_wall(map[j][i + 1]) ||
        !is_space_or_wall(map[j][i - 1]))
    {
        if (player)
        {
            free(player->old_move);
            free(player);
        }
        error_exit(map_info, NULL, "Error\ninvalid map", -1);
    }
}

t_player *valid_map(t_map *map_info, char **map, int i, int j)
{
    t_player *player;

    player = NULL;
    while(map[j])
    {
        i = 0;
        while(map[j][i])
        {
            if (map[j][i] == '0' || map[j][i] == 'N' ||
                map[j][i] == 'S' || map[j][i] == 'E' || map[j][i] == 'W')
                check_element_position(map_info, &player,i, j);
            if (map[j][i] == ' ')
                check_space_position(map_info, player, i, j);
            i++;
        }
        j++;
    }
    return (player);
}


t_data *parsing_the_map(t_map *map_info, int fd)
{
    t_line *head;
    t_player *player;
    t_data *data;

    head = creat_linked_list(map_info, map_info->line, fd);
    close(fd);
    map_info->map = convert_to_double_pointer(head, map_info, 0, 0);
    player = valid_map(map_info, map_info->map, 0, 0);
    if (!player)
         error_exit(map_info, NULL, "Error\nmissing a player\n", -1);
    data = malloc(sizeof(t_data));
    data->map = map_info;
    data->player = player;
    return (data);
}

t_data *parsing(char *file_name)
{
    int fd; 
    t_map *map_info;
    t_data * data;

    fd = open(file_name, O_RDONLY);
    if (fd == -1)
        error_exit(NULL, NULL, "Error\ncould not find the file\n", -1);
    check_extension(file_name, ".cub", fd);
    if (fd == -1)
        error_exit(NULL, NULL, "Error\ncould not find the file\n", -1);
    map_info = extract_element(fd);
    data = parsing_the_map(map_info, fd);
    return (data);
}

int main(int argc, char *argv[])
{
    int i;
    int j;
    t_data *data;
    char **map;
    
    i = 0;
    j = 0;
    if (argc == 2)
    {
        data = parsing(argv[1]);
        printf("all good\n");
        map = data->map->map;
        while (map[j])
        {
            printf("%s", map[j]);
            j++;
    }
    }
}