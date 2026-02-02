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

/*
** cfg_is_complete()
** Lógica: o parser só pode aceitar mapa depois que os 6 elementos existirem.
** Isso impede mapa começar antes e impede "faltou textura" silencioso.
*/
static int	cfg_is_complete(t_cfg *c)
{
	return (c->has_no && c->has_so && c->has_we && c->has_ea && c->has_floor && c->has_ceiling);
}

/*
** count_map_end()
** Lógica: descobre até onde vai o mapa (até acabar o arquivo).
** Também valida: não pode ter linha vazia dentro do mapa.
*/
static int	count_map_end(char **lines, int start)
{
	int	i;

	i = start;
	while (lines[i])
	{
		if (is_line_empty(lines[i]))
			return (-1);
		if (!is_map_line(lines[i]))
			return (-1);
		i++;
	}
	return (i);
}

/*
** parse_header()
** Lógica: percorre do início:
** - ignora vazias
** - tenta parse_element_line()
** - se achar uma linha "cara de mapa" antes de completar configs -> erro
** Retorna o índice onde o mapa começa.
*/

int parser(const char *path, t_mlx *game)
{
    t_cfg	cfg;
    char    **lines;
    char    **raw_map;
    char    **grid;
    int     i;
    int     width;
    int     height;
    int		map_start;

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
    map_start = parse_header(lines, &game->config);
	if (map_start < 0)
		return (free_lines(lines), err("Error: invalid header/configs\n"), 1);
	if (!build_map(lines, map_start, game))
		return (free_lines(lines), err("Error: invalid map\n"), 1);
	free_lines(lines);

    return 0;
}