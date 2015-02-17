/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_solve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 12:09:36 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/17 10:06:39 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ps.h>

static void		send_to_a(t_tob *tob)
{
	build_alternatives_to_a(tob); //only one alternative, so far
	return ;
}

static void		send_to_b(const t_psl *l, t_set *s)
{
	t_tob	*way;
	t_list	*lst;

	build_alternatives_to_b(l, s); //only one alternative, so far
	lst = *s->to_b;
	while (lst != NULL)
	{
		way = (t_tob*)lst->content;
		send_to_a(way);
		lst = lst->next;
	}
	return ;
}

void			ps_set_solve(t_psl *l)
{
	t_list	*sets[1];
	t_list	*lst;
	t_set	*s;

	*sets = NULL;
	ps_build_sets(l, sets);
	lst = *sets;
	while (lst)
	{
		s = (t_set*)lst->content;
		(void)s;
		qprintf("\033[41mset:%2hu %2hu (%2hu)\n\033[0m", s->first, s->last, s->len);
		send_to_b(l, s);
		lst = lst->next;
	}
	ft_lstdel(sets, &ft_lstfreecont);
	return ;	
}
