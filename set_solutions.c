/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_solutions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 11:51:28 by ngoguey           #+#    #+#             */
/*   Updated: 2015/06/02 14:14:04 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ps.h>

int				ps_total_movements(const t_psl *l)
{
	static int		total_movements = 0;

	if (l != NULL)
		total_movements += l->act.zone_size;
	return (total_movements);
}

t_psl			*ps_solution_storing(t_psl *l)
{
	static t_psl	*saved = NULL;

	if (l == NULL)
		return (saved);
	(void)ps_total_movements(l);
	if (saved == NULL)
		saved = l;
	else if (l->act.zone_size < saved->act.zone_size)
	{
		ps_free_l(&saved, true);
		saved = l;
	}
	else
	{
		ps_free_l(&l, true);
	}
	return (saved);
}

void			ps_printbest_solution(void)
{
	t_psl	*l;

	l = ps_solution_storing(NULL);
	if (l == NULL)
		ft_putstr("Error\n");
	else
	{
		ps_print_psl(l);
		ps_free_l(&l, true);
	}
	return ;
}
