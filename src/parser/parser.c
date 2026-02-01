# include "../../includes/cub3D.h"

int is_line_empty(const char *s)
{
    if (!s)
        return 1;
    while (*s)
    {
        if (*s != ' ' && *s != '\t' && *s != '\r' && *s != '\n')
            return 0;
        s++;
    }
    return 1;
}

int parser(const char *path, t_mlx *game)
{
    char **lines;
    char **raw_map;
    char **grid;
    int i;
    int width;
    int height;

    (void)raw_map;
    (void)grid;
    (void)width;
    (void)height;
    (void)game;
    // (void)i;
    // (void)lines;

    // if (!path || !has_cub_extension(path))
    //     err("Error: Invalid file extension. Expected .cub\n");
    
    lines = reader(path);
    if (!lines) { 
        return (err("Error: Could not read file\n"));
    }
    
    i = 0;
    while (lines[i])
    {
        if (is_line_empty(lines[i]))
        {
            i++;
            continue;
        }
        printf("Line %d: '%s'\n", i + 1, lines[i]);
        i++;
    }

    return 0;
}