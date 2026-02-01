#include   "../../includes/cub3D.h"

static int has_cub_extension(const char *path)
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

char **reader(const char *path)
{
    char **lines;

    if(!path || !has_cub_extension(path))
    {
        err("Error: Invalid file extension. Expected .cub\n");
        return (NULL);
    }
    lines = read_all_lines(path);
    if (!lines)
    {
        err("Error: Could not read file\n");
        return (NULL);
    }
    return lines;
}
