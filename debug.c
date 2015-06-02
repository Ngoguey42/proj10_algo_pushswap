/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/02 09:46:47 by ngoguey           #+#    #+#             */
/*   Updated: 2015/06/02 14:38:56 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ps.h>

static void	print_dstor_content(const t_dstor *dstor)
{
	int	i;

	i = 0;
	while (i < (int)dstor->buf_size)
	{
		if (i < (int)dstor->zone_size)
		{
			if (i != 0)
				ft_putchar(' ');
			ft_putstr(ps_action_name(dstor->buf_rear[i]));
		}
		i++;
	}
	ft_putchar('\n');
	return ;
}

void		ps_print_dstor(const t_dstor *dstor)
{
	ft_dprintf(2, "Dynamic storage:\n");
	ft_dprintf(2, "buff :  rear{%p} size(%u)\n",
		dstor->buf_rear, dstor->buf_size);
	ft_dprintf(2, "zone : front{%p} size(%u)\n",
		dstor->zone_front, dstor->zone_size);
	print_dstor_content(dstor);
	return ;
}

void		ps_print_psl(const t_psl *psl)
{
	print_dstor_content(&psl->act);
	return ;
}

const char	*ps_action_name(t_action action)
{
	static const char	names[][5] = {

	"ra",
	"rb",
	"rr",
	"rra",
	"rrb",
	"rrr",
	"pa",
	"pb",
	"sa",
	"sb",
	"ss",
	"none"};
	return (names[action]);
}
