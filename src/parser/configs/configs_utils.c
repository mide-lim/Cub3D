#include   "../../../includes/cub3D.h"

/*
** Retorna 1 se a linha tem apenas espaços/tabs (ou é vazia).
** Usamos isso para permitir "linhas vazias" entre configs,
** mas bloquear vazios quando o mapa já começou.
*/
int	is_blank_line(const char *s)
{
	int	i;

	if (!s)
		return (1);
	i = 0;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	return (s[i] == '\0');
}

/*
** Detecta "cara de mapa":
** pula espaços e confere se o primeiro char é 1/0/N/S/E/W.
** A partir da primeira linha assim, consideramos que o resto é mapa.
*/
int	is_map_line(const char *line)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return (line[i] == '1' || line[i] == '0'
		|| line[i] == 'N' || line[i] == 'S'
		|| line[i] == 'E' || line[i] == 'W');
}

/*
** Checa se s começa com o id (ex: "NO", "F"), e que depois vem
** espaço/tabs ou fim de string (pra não aceitar "NORTH" como "NO").
*/
int	starts_with_id(const char *s, const char *id)
{
	int	i;

	if (!s || !id)
		return (0);
	i = 0;
	while (id[i] && s[i] == id[i])
		i++;
	if (id[i] != '\0')
		return (0);
	return (s[i] == ' ' || s[i] == '\t' || s[i] == '\0');
}