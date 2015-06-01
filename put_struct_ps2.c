/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_struct_ps2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/23 14:17:27 by ngoguey           #+#    #+#             */
/*   Updated: 2015/06/01 18:27:28 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ps.h"

static void		check_for_duplicates(int *save_real, int ac, int i, int nb)
{
	while (ac > 1)
	{
		if ((ac - 1) != i && save_real[ac - 1] == nb)
			ft_exit("Error");
		ac--;
	}
}

static int		give_simple_nb(int *save_real, int ac, int i)
{
	int		nb;
	int		j;

	nb = 1;
	j = 0;
	while (j != ac)
		if (save_real[j++] < save_real[i])
			nb++;
	return (nb);
}

void			put_a_b_solved(t_corresp *corresp, int ac)
{
	int		i;

	corresp->corresp = (PS_TYPE*)malloc(sizeof(PS_TYPE) * (ac + 1));
	if (!corresp->corresp)
		ft_exit("Error");
	corresp->corresp[ac] = 0;
	i = 0;
	while (i < ac)
	{
		check_for_duplicates(corresp->ref, ac, i, corresp->ref[i]);
		corresp->corresp[i] = give_simple_nb(corresp->ref, ac, i);
		i++;
	}
}
