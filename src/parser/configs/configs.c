#include   "../../../includes/cub3D.h"

/*
** Valida que as 6 configs existem.
** Essa checagem acontece após consumirmos o bloco de configs.
*/
static int	all_configs_present(t_cfg *cfg)
{
	if (!cfg->has_no || !cfg->has_so || !cfg->has_we || !cfg->has_ea)
		return (0);
	if (!cfg->has_floor || !cfg->has_ceiling)
		return (0);
	return (1);
}

/*
** Enquanto estamos em "modo mapa", toda linha deve ser "cara de mapa".
** Linha vazia ou linha com texto aleatório após map_start é erro.
*/
static int	validate_map_continuation(char **lines, int start)
{
	int	i;

	i = start;
	while (lines[i])
	{
		if (is_blank_line(lines[i]))
			return (0);
		if (!is_map_line(lines[i]))
			return (0);
		i++;
	}
	return (1);
}

/*
** Varre lines do início:
** - ignora vazias nas configs
** - parseia NO/SO/WE/EA/F/C
** - ao encontrar 1ª linha "cara de mapa", marca map_start e para configs
** - proíbe configs após mapa e vazios dentro do mapa
*/
int	configs(char **lines, t_cfg *cfg, int *map_start)
{
	int	i;

	i = 0;
	*map_start = -1;
	while (lines[i])
	{
		if (is_blank_line(lines[i]))
		{
			i++;
			continue ;
		}
		if (is_map_line(lines[i]))
		{
			*map_start = i;
			break ;
		}
		if (!elements(lines[i], cfg))
			return (0);
		i++;
	}
	if (*map_start == -1 || !all_configs_present(cfg))
		return (0);
	return (validate_map_continuation(lines, *map_start));
}
