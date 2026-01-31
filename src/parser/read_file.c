# include "../../includes/cub3D.h"

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

/* Remove trailing newline (and optional '\r' antes do '\n') de uma string
   Retorna o mesmo ponteiro passado (ou NULL se input for NULL). */
char *strip_newline(char *s)
{
    char *p;
    if (!s)
        return NULL;
    /* ir até o fim */
    p = s;
    while (*p)
        p++;
    if (p == s)
        return s;
    /* p aponta para o '\0', retrocede e remove '\n' e '\r' se presentes */
    p--;
    if (*p == '\n')
    {
        *p = '\0';
        if (p != s && *(p - 1) == '\r')
            *(p - 1) = '\0';
    }
    return s;
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

    (void)raw_map;
    (void)grid;
    (void)width;
    (void)height;
    (void)game;
    // (void)i;
    // (void)lines;

    if (!path || !has_cub_extension(path))
        err("Error: Invalid file extension. Expected .cub\n");
    
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
        printf("Line %d: '%s'\n", i + 1, lines[i]);
        i++;
    }

    return 0;
}