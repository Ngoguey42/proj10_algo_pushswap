/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_to_a.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/17 09:58:13 by ngoguey           #+#    #+#             */
/*   Updated: 2015/06/02 12:56:33 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ps.h>
#include <stdlib.h>
#include <unistd.h>
#define NEXT(val, max) (val == 1 ? max : val - 1)

static DBUFF_T   r_dist(DBUFF_T last, DBUFF_T *ptr)
{
	DBUFF_T  dist;

	dist = 0;
	while (*ptr != last)
	{
		dist++;
		ptr--;
	}
	return (dist);
}

static int	recenter_b(t_psl *l, t_action action, DBUFF_T tot, DBUFF_T nnext)
{
	int		next_moved;
	
	next_moved = 0;
	while (tot--)
	{
		if (*BZF == nnext)
		{
			apply_action(l, pa);
			next_moved = 1;
			if (action == rrb)
				apply_action(l, rrb);
		}
		else
			apply_action(l, action);
	}
	return (next_moved);
}

static void	recenter_a(t_psl *l, DBUFF_T radist, DBUFF_T rradist)
{
	if (radist <= rradist)
		while (radist--)
			apply_action(l, ra);
	else
		while (rradist--)
			apply_action(l, rra);
	return ;
}

void		build_alternatives_to_a(t_tob *tob)
{
	t_psl	*l;
	PS_TYPE	next;
	PS_TYPE	tot_size;
	PS_TYPE	tmp;
	int		next_moved;

	ps_dup_l(tob->l, &l);
	tot_size = AZS + BZS;
	while (BZS > 0)
	{
		
		next = NEXT(*AZF, tot_size);
		tmp = r_dist(next, BZF);
		if (tmp <= BZS - tmp)
			next_moved = recenter_b(l, rb, tmp, NEXT(next, tot_size));
		else
			next_moved = recenter_b(l, rrb, BZS - tmp, NEXT(next, tot_size));
		apply_action(l, pa);
		if (next_moved)
			apply_action(l, sa);
	}
	tmp = r_dist(1, AZF);
	recenter_a(l, tmp, tot_size - tmp);
	ps_solution_storing(l);
/* 	ps_free_l(&l, false); //added */
	return ;
}
