/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/02 09:46:47 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/03 11:16:46 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ps.h>

void		ps_print_dstor(const t_dstor *dstor)
{
	int	i;

	ft_dprintf(2, "Dynamic storage:\n");
	ft_dprintf(2, "buff :  rear{%p} size(%u)\n",
		dstor->buf_rear, dstor->buf_size);
	ft_dprintf(2, "zone : front{%p} size(%u)\n",
		dstor->zone_front, dstor->zone_size);
	i = 0;
	while (i < (int)dstor->buf_size)
	{
		if (i == (int)dstor->zone_size)
			ft_dprintf(2, ":yel:");
		if (i < (int)dstor->zone_size)
			ft_dprintf(2, "%s ", ps_action_name(dstor->buf_rear[i]));
		else
			ft_dprintf(2, "%hhu", dstor->buf_rear[i]);
		i++;
	}
	ft_dprintf(2, ":eof:\n");
	return ;
}

void		ps_print_dbuff(const t_dbuff *dbuff)
{
	int	i;

	ft_dprintf(2, "Dynamic buffer:\n");
	ft_dprintf(2, "buff : rear{%16p} front{%16p} size(%u)\n",
		dbuff->buf_rear, dbuff->buf_front, dbuff->buf_size);
	ft_dprintf(2, "zone : rear{%16p} front{%16p} size(%u)\n",
		dbuff->zone_rear, dbuff->zone_front, dbuff->zone_size);
	if (dbuff->zone_size != 0)
		ft_dprintf(2, "delta: rear{%16u} front{%16u} size(%u)\n",
			dbuff->zone_rear - dbuff->buf_rear,
			dbuff->buf_front - dbuff->zone_front,
			dbuff->buf_size - dbuff->zone_size);
	i = 0;
	ft_dprintf(2, ":yel:");
	while (i < (int)dbuff->buf_size)
	{
		if (i == (int)(dbuff->zone_rear - dbuff->buf_rear))
			ft_dprintf(2, ":eoc:");
		if (i == (int)(dbuff->zone_front - dbuff->buf_rear))
			ft_dprintf(2, ":yel:");
		ft_dprintf(2, "%hu", dbuff->buf_rear[i]);
		i++;
	}
	ft_dprintf(2, ":eof:\n");
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
