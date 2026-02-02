#ifndef PARSER_H
# define PARSER_H
# include "cub3D.h"

typedef struct s_cfg
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		floor_color;
	int		ceiling_color;
	int		has_no;
	int     has_so;
	int     has_we;
	int     has_ea;
	int     has_floor;
	int     has_ceiling;
}	t_cfg;

char	**reader(const char *path);
/* Configs */
int		configs(char **lines, t_cfg *cfg, int *map_start);
/* Configs utils */
int		is_blank_line(const char *s);
int		is_map_line(const char *line);
int		starts_with_id(const char *s, const char *id);
/* Configs elements */
int		elements(const char *line, t_cfg *cfg);

#endif