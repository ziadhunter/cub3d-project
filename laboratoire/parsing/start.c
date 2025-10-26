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
    close(1);
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
    if (str[i] && str[i] != '\n')
        return (-1);
    result *= sign;
    if (result > 255 || result < 0)
        {return (-1);}

	return (result * sign);
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
            error_exit(map, values, "Error\nwrong floor values\n", fd);
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
            error_exit(map, values, "Error\nwrong ceiling value\n", fd);
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

    if (map->we)
        error_exit(map, NULL, "Error\nWE element duplicated\n", fd);
    if (str[1])
    {
        lenght = ft_strlen(str[1]);
        if (str[1][lenght] == '\n')
            str[1][lenght] = '\0';
        check_extension(str[1], ".xpm", fd);
        fdd = open(str[1], O_RDONLY);
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

    if (map->ea)
        error_exit(map, NULL, "Error\nEA element duplicated\n", fd);
    if (str[1])
    {
        lenght = ft_strlen(str[1]);
        if (str[1][lenght] == '\n')
            str[1][lenght] = '\0';
        check_extension(str[1], ".xpm", fd);
        fdd = open(str[1], O_RDONLY);
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

    if (map->so)
        error_exit(map, NULL, "Error\nSO element duplicated\n", fd);
    if (str[1])
    {
        lenght = ft_strlen(str[1]);
        if (str[1][lenght] == '\n')
            str[1][lenght] = '\0';
        check_extension(str[1], ".xpm", fd);
        fdd = open(str[1], O_RDONLY);
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

    if (map->no)
        error_exit(map, NULL, "Error\nNO element duplicated\n", fd);
    if (str[1])
    {
        lenght = ft_strlen(str[1]);
        if (str[1][lenght] == '\n')
            str[1][lenght] = '\0';
        check_extension(str[1], ".xpm");
        fdd = open(str[1], O_RDONLY);
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
            element[i].handle(map, splited_line);
            free_double_pointer(splited_line);
            return;
        }
        i++;
    }
    free(splited_line);
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



t_map *extract_element(int fd)
{
    t_map *map;
    char *line;
    t_element elements[6];


    initialize_element(&elements);
    map = initialize_map();
    line = get_next_line(fd);
    while (line != NULL && !all_element_found(map))
    {
        which_element(line, map, elements, fd);
        free(line);
        line = get_next_line(fd);
    }
    if (!line && !all_element_found(map))
        error_exit(map, NULL, "Error\nmissing some element(s)!!", fd);
    return (map);
}

int is_map_element(char c)
{
    if (c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ')
        return (1);
    return (0); 
}

int check_the_line(t_map *map, char *line, int fd)
{
    if (!line)
        error_exit(map, NULL, "Error\nmissing map\n", fd);
    if (line[1] == '\n')
        return (0);
    if (is_map_element(line[1]))
        return (1);
    else
        error_exit(map, NULL, "Error\nwrong map element\n", fd);
        
}

size_t	fstrlen_nl(const char *s)
{
	size_t	i;
    size_t  j;

    if (!s)
        return (0);
	i = 0;
	while (s[i])
    {
        if (s[i] != '\n')
		    j++;
        i++;
    }
	return (i);
}


t_line *new_node(char *line, int lenght)
{
    t_line *node;

    node = malloc(sizeof(t_line));
    node->length = lenght;
    node->str = line;
    return(node);
}

t_line *creat_linked_list(char *line, int fd)
{
    while (line)
    {
        
    }
}


void parsing_map(t_map *map, int fd)
{
    char *line;
    t_line *head;
    line = get_next_line(fd);
    while (line)
    {
        if (check_the_line(map, line, fd))
            break;
        free(line);
        line = get_next_line(fd);
    }
    creat_linked_list(line, fd);
    

}

t_map *parsing(char *file_name)
{
    int fd; 
    t_map *map_info;

    check_extension(file_name, ".cub");
    fd = open(file_name, O_RDONLY);
    if (fd == -1)
        error_exit(NULL, NULL, "Error\ncould not find the file\n", -1);
    map_info = extract_element(fd);
    parse_the_map(map_info, fd);
    close(fd);
    return (map_info);
}

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        parsing(argv[1]);
        printf("all good");
    }
}