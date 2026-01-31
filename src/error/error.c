#include "../includes/cub3D.h"

int	err(const char *msg)
{
    if (msg)
    {
        write(STDERR_FILENO, msg, ft_strlen(msg));
    }
    exit(EXIT_FAILURE);
}