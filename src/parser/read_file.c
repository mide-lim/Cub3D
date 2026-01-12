# include "../includes/cub3D.h"

#define MAX_LINES 1000

int has_cub_extension(const char *path)
{
    if (!path)
        return 0;
    size_t len = 0;
    while (path[len])
        len++;
    return (len > 4 && path[len - 4] == '.' &&
            path[len - 3] == 'c' &&
            path[len - 2] == 'u' &&
            path[len - 1] == 'b');
}

char **read_all_lines(const char *path)
{
    int fd;
    int i = 0;
    char **lines;

    fd = open(path, O_RDONLY);
    if (fd == -1)
        return NULL;

    lines = malloc(sizeof(char *) * (MAX_LINES + 1));
    if (!lines)
    {
        close(fd);
        return NULL;
    }
    while (1)
    {
        lines[i] = get_next_line(fd);
       if (!lines[i])
           break;
        lines[i] = strip_newline(lines[i]);
        i++;
    }
    lines[i] = NULL;
    close(fd);
    return lines;
}


int parse_cub_file(const char *path, t_mlx *game)
{
    char **lines;
    char **raw_map;
    char **grid;
    int i;
    int width;
    int height;

    if (!path || !has_cub_extension(path))
        // return err("Error: Invalid file extension. Expected .cub\n");
        pritnf("Error: Invalid file extension. Expected .cub\n");
    
    lines = read_all_lines(path);
    if (!lines)
        // return err("Error: Could not read file\n");
        printf("Error: Could not read file\n");
    
    i = 0;
    while (lines[i])
    {
        if (is_line_empty(lines[i]))
        {
            i++;
            continue;
        }
        i++;
    }

    return 0;
}