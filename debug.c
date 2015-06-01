/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/02 09:46:47 by ngoguey           #+#    #+#             */
/*   Updated: 2015/06/01 18:03:52 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ps.h>

static void	print_dstor_content(const t_dstor *dstor)
{
	int	i;

	i = 0;
	while (i < (int)dstor->buf_size)
	{
		if (i == (int)dstor->zone_size)
			ft_dprintf(2, ":yel:");
		if (i < (int)dstor->zone_size)
		{
			ft_dprintf(2, "%s ", ps_action_name(dstor->buf_rear[i]));
			if (i != 0 && i % 16 == 0)
				ft_putstr_fd("\n       ", 2);
		}
		else
			ft_dprintf(2, "%hhu", dstor->buf_rear[i]);
		i++;
	}
	ft_dprintf(2, ":eof:\n");
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
	ft_dprintf(2, "Push Swap List:\nAl: ");
	ps_print_dbuff_content(&psl->al);
	ft_dprintf(2, "Bl: ");
	ps_print_dbuff_content(&psl->bl);
	ft_dprintf(2, "Ac:%3zu ", psl->act.zone_size);
	print_dstor_content(&psl->act);
	ft_dprintf(2, "\n");	
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
