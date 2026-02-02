#include   "../../../includes/cub3D.h"

/*
** Pula espaços/tabs e retorna ponteiro para o começo do "valor"
** (path da textura ou string da cor).
*/
static const char	*skip_id_and_spaces(const char *line, int n)
{
	int	i;

	i = n;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return (line + i);
}

/*
** Seta uma textura garantindo que não repete e que existe valor.
** Copiamos a string para ownership do cfg.
*/
static int	set_tex(char **dst, int *flag, const char *value)
{
	if (*flag)
		return (0);
	if (!value || *value == '\0')
		return (0);
	*dst = ft_strdup(value);
	if (!*dst)
		return (0);
	*flag = 1;
	return (1);
}

/*
** Marca F/C como presente e guarda a string para parsear depois.
** Se você já tiver parse RGB pronto, aqui pode chamar diretamente.
** (Pra manter simples agora, só garantimos "existe" e "não repete".)
*/
static int	set_color_present(int *flag, const char *value)
{
	if (*flag)
		return (0);
	if (!value || *value == '\0')
		return (0);
	*flag = 1;
	return (1);
}

/*
** Identifica qual elemento é a linha e preenche cfg.
** Se não for nenhum ID válido, é erro (linha inválida no bloco de configs).
*/
int	elements(const char *line, t_cfg *cfg)
{
	const char	*v;

	if (starts_with_id(line, "NO"))
		return (set_tex(&cfg->no, &cfg->has_no, skip_id_and_spaces(line, 2)));
	if (starts_with_id(line, "SO"))
		return (set_tex(&cfg->so, &cfg->has_so, skip_id_and_spaces(line, 2)));
	if (starts_with_id(line, "WE"))
		return (set_tex(&cfg->we, &cfg->has_we, skip_id_and_spaces(line, 2)));
	if (starts_with_id(line, "EA"))
		return (set_tex(&cfg->ea, &cfg->has_ea, skip_id_and_spaces(line, 2)));
	if (starts_with_id(line, "F"))
	{
		v = skip_id_and_spaces(line, 1);
		return (set_color_present(&cfg->has_floor, v));
	}
	if (starts_with_id(line, "C"))
	{
		v = skip_id_and_spaces(line, 1);
		return (set_color_present(&cfg->has_ceiling, v));
	}
	return (0);
}
