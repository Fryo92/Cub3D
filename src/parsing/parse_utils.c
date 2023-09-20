/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiddane <abiddane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 14:14:05 by mgauvrit          #+#    #+#             */
/*   Updated: 2023/09/19 13:54:40 by abiddane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	opening_extend(t_struct *all, char *str)
{
	char	**tab;
	char	**temp;

	check_nl(str, all);
	tab = ft_split(str, '\n');
	temp = fill_space(tab);
	if (check_map(temp) == -1)
	{
		free(str);
		free_tab(tab);
		free_tab(temp);
		kill_da_shit("Open wall\n", all);
	}
	free_tab(tab);
	free_tab(temp);
}

char	**ft_opening(char *file, t_struct *all)
{
	char	*str;
	char	*buf;
	char	**tab;
	int		fd;

	fd = open(file, O_RDWR);
	if (fd < 0)
		kill_da_shit("File not readable !\n", all);
	str = get_next_line(fd);
	while (1)
	{
		buf = get_next_line(fd);
		if (!buf)
			break ;
		str = ft_strjoin(str, buf);
		free(buf);
	}
	close (fd);
	if (!str)
		kill_da_shit("File is empty !\n", all);
	opening_extend(all, str);
	tab = ft_split(str, '\n');
	free(str);
	return (tab);
}

void	arg_error(int argc, char *argv, t_struct *all)
{
	int	i;

	if (argc != 2)
		kill_da_shit("Invalid args number !", all);
	i = ft_strlen(argv);
	if (argv[i - 3] == 'c'
		&& argv[i - 2] == 'u'
		&& argv[i - 1] == 'b'
		&& argv[i] == '\0')
		return ;
	else
		kill_da_shit("Please check map name.\n", all);
}

int	check_border(char **map)
{
	int		i;
	char	*finder;

	i = -1;
	finder = "1 ";
	while (map[0][++i])
	{
		if (!ft_strchr(finder, map[0][i]))
			return (0);
	}
	i = 1;
	while (i < tablen(map) - 1)
	{
		if (!ft_strchr(finder, map[i][0])
			|| !ft_strchr(finder, map[i][ft_strlen(map[i]) - 1]))
			return (0);
		i++;
	}
	i = -1;
	while (map[tablen(map) - 1][++i])
	{
		if (!ft_strchr(finder, map[tablen(map) - 1][i]))
			return (0);
	}
	return (1);
}

int	check_all_xpm(t_data *data)
{
	if (!check_xpm(data->nimg))
		return (0);
	if (!check_xpm(data->simg))
		return (0);
	if (!check_xpm(data->wimg))
		return (0);
	if (!check_xpm(data->eimg))
		return (0);
	return (1);
}
