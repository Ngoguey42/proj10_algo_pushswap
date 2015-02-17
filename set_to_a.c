/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_to_a.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/17 09:58:13 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/17 11:36:09 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ps.h>
#include <stdlib.h>
#include <unistd.h>

static DBUFF_T   ra_dist(DBUFF_T last, DBUFF_T *ptr)
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

static void	recenter(t_psl *l, DBUFF_T radist, DBUFF_T rradist)
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

	ps_dup_l(tob->l, &l);
	tot_size = AZS + BZS;
	while (BZS > 0)
	{
		next = *AZF - 1;
		if (next == 0)
			next = tot_size;
		if (*BZF == next)
			apply_action(l, pa);
		else
			apply_action(l, rb);
	}
	tmp = ra_dist(1, AZF);
	recenter(l, tmp, tot_size - tmp);
	ps_print_psl(l);
	return ;
}
