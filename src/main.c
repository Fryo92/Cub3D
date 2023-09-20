/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiddane <abiddane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 14:58:46 by mgauvrit          #+#    #+#             */
/*   Updated: 2023/09/18 16:55:00 by abiddane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_associates(t_struct *all)
{
	int	h;
	int	w;

	if (!check_all_xpm(all->data))
	{
		free_img(all->data);
		free(all->mlx->mlx_ptr);
		free(all->mlx->win_ptr);
		kill_da_shit("Texture not xpm\n", all);
	}
	all->mlx->n = mlx_xpm_file_to_image
		(all->mlx->mlx_ptr, all->data->nimg, &w, &h);
	all->mlx->s = mlx_xpm_file_to_image
		(all->mlx->mlx_ptr, all->data->simg, &w, &h);
	all->mlx->e = mlx_xpm_file_to_image
		(all->mlx->mlx_ptr, all->data->eimg, &w, &h);
	all->mlx->w = mlx_xpm_file_to_image
		(all->mlx->mlx_ptr, all->data->wimg, &w, &h);
	free_img(all->data);
	if (!all->mlx->n || !all->mlx->s || !all->mlx->e || !all->mlx->w)
	{
		free(all->mlx->mlx_ptr);
		free(all->mlx->win_ptr);
		kill_da_shit("Failed xpm to image\n", all);
	}
}

int	mlx_initialize(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	if (mlx->mlx_ptr == NULL)
		return (0);
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr,
			SCREENWIDTH, SCREENHEIGHT, "Cub3D");
	if (mlx->win_ptr == NULL)
	{
		free(mlx->win_ptr);
		return (0);
	}
	return (1);
}

int	init_struct_utils(t_struct *all)
{
	all->algo = malloc(sizeof(t_algo));
	if (!all->algo)
	{
		free(all->data);
		free(all->mlx);
		free(all);
		return (0);
	}
	ft_memset(all->algo, 0, sizeof(t_algo));
	all->img = malloc(sizeof(t_img));
	if (!all->img)
	{
		free(all->data);
		free(all->mlx);
		free(all->algo);
		free(all);
		return (0);
	}
	ft_memset(all->img, 0, sizeof(t_img));
	all->data->map = NULL;
	return (1);
}

int	init_struct(t_struct *all)
{
	int	i;

	all->data = malloc(sizeof(t_data));
	if (!all->data)
		return (0);
	ft_memset(all->data, 0, sizeof(t_data));
	all->data->map = NULL;
	all->mlx = malloc(sizeof(t_mlx));
	if (!all->mlx)
	{
		free(all->data);
		return (0);
	}
	ft_memset(all->mlx, 0, sizeof(t_mlx));
	i = init_struct_utils(all);
	return (i);
}

int	main(int argc, char **argv)
{
	t_struct	*all;

	all = malloc(sizeof(t_struct));
	if (!init_struct(all))
		return (-1);
	if (!ft_map_checking(argc, argv[1], all))
	{
		if (!mlx_initialize(all->mlx))
			kill_da_shit("Mlx init failed\n", all);
		ray_init(all->data, all->algo);
		all->img->image = mlx_new_image(all->mlx->mlx_ptr, \
		SCREENWIDTH, SCREENHEIGHT);
		all->img->img_addr = mlx_get_data_addr(all->img->image, \
		&all->img->bp, &all->img->line, &all->img->endian);
		ft_associates(all);
		mlx_hook(all->mlx->win_ptr, 17, 1L << 17, &clean_win_kill, all);
		mlx_hook(all->mlx->win_ptr, 2, 1L << 0, &key_press, all);
		mlx_hook(all->mlx->win_ptr, 3, 1L << 1, &key_release, all);
		mlx_hook(all->mlx->win_ptr, 6, 1L << 6, &mouse_rot, all->data);
		mlx_mouse_hide(all->mlx->mlx_ptr, all->mlx->win_ptr);
		mlx_loop_hook(all->mlx->mlx_ptr, &raycasting, all);
		mlx_loop(all->mlx->mlx_ptr);
		free(all);
	}
	return (1);
}
