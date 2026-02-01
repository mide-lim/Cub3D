#include "../../includes/cub3D.h"

static char	*strip_newline(char *s)
{
	char	*p;

	if (!s)
		return (NULL);
	p = s;
	while (*p)
		p++;
	if (p == s)
		return (s);
	p--;
	if (*p == '\n')
	{
		*p = '\0';
		if (p != s && *(p - 1) == '\r')
			*(p - 1) = '\0';
	}
	return (s);
}

static void	free_lines(char **lines)
{
	size_t	i;

	if (!lines)
		return ;
	i = 0;
	while (lines[i])
	{
		free(lines[i]);
		i++;
	}
	free(lines);
}

static char	**grow_lines(char **lines, size_t old_cap, size_t new_cap)
{
	char	**new_lines;

	new_lines = ft_calloc(new_cap, sizeof(char *));
	if (!new_lines)
		return (NULL);
	if (lines)
	{
		ft_memcpy(new_lines, lines, old_cap * sizeof(char *));
		free(lines);
	}
	return (new_lines);
}

static int	push_line(char ***lines, size_t *cap, size_t *len, char *line)
{
	char	**tmp;
	size_t	old_cap;

	if (*cap == 0)
		*cap = 16;
    if (*lines == NULL)
    {
        *lines = ft_calloc(*cap, sizeof(char *));
        if (!*lines)
            return (0);
    }
	if (*len + 1 >= *cap)
	{
		old_cap = *cap;
		*cap *= 2;
		tmp = grow_lines(*lines, old_cap, *cap);
		if (!tmp)
			return (0);
		*lines = tmp;
	}
	(*lines)[*len] = line;
	(*len)++;
	(*lines)[*len] = NULL;
	return (1);
}

char	**read_all_lines(const char *path)
{
	int		fd;
	char	**lines;
	size_t	cap;
	size_t	len;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	lines = NULL;
	cap = 0;
	len = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		line = strip_newline(line);
		if (!push_line(&lines, &cap, &len, line))
			return (close(fd), free(line), free_lines(lines), NULL);
	}
	close(fd);
	if (!lines)
		return (ft_calloc(1, sizeof(char *)));
	return (lines);
}
