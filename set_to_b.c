/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_to_b.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/17 09:32:23 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/17 09:32:25 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <ps.h>

static t_bool	in_set(DBUFF_T nb, DBUFF_T first, DBUFF_T last)
{
	// 9 8 7 6		
	// 3 2 1 9		
	if (first > last)
	{
		if (nb > first || nb < last)
			return (false);
		return (true);
	}
	else
	{
		if (nb > first && nb < last)
			return (false);
		return (true);
	}
}

static int		num_loops(const t_psl *l, DBUFF_T first, DBUFF_T last)
{
	int		i;
	int		ret;
	DBUFF_T	*ptr;

	i = 0;
	ret = 0;
	ptr = l->al.zone_front;
	while (ptr >= l->al.zone_rear)
	{
		i++;
		if (!in_set(*ptr, first, last))
			ret = i;
		ptr--;
	}
	return (ret);
}

static size_t	ra_dist(DBUFF_T last, DBUFF_T *ptr)
{
	size_t	dist;

	dist = 0;
	while (*ptr != last)
	{
		dist++;
		ptr--;
	}
	return (dist);
}

static void		recenter(t_psl *l, size_t radist, size_t rradist)
{
	if (radist <= rradist)
		while (radist--)
			apply_action(l, ra);
	else
		while (rradist--)
			apply_action(l, rra);
	return ;
}

void			build_alternatives_to_b(const t_psl *lref, t_set *s)
{
	t_psl	*l;
	int		i;

	ps_dup_l(lref, &l);
	i = num_loops(l, s->first, s->last);
	while (i--)
	{
		if (!in_set(*l->al.zone_front, s->first, s->last))
			apply_action(l, pb);
		else
			apply_action(l, ra);
	}
	i = ra_dist(s->last, l->al.zone_front);
	recenter(l, i, AZS - i);
	ps_print_psl(l);
	if (ft_lstnewback((t_list**)s->to_b, l, sizeof(t_psl)) == NULL)
		exit(1);
	free(l);
	return ;
}
