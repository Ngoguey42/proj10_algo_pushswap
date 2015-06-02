/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_solve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 12:09:36 by ngoguey           #+#    #+#             */
/*   Updated: 2015/06/02 14:12:40 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ps.h>

static void		send_to_a(t_tob *tob)
{
	build_alternatives_to_a(tob);
	return ;
}

static void		send_to_b(const t_psl *l, t_set *s)
{
	t_tob	*way;
	t_list	*lst;

	build_alternatives_to_b(l, s);
	lst = *s->to_b;
	while (lst != NULL)
	{
		way = (t_tob*)lst->content;
		send_to_a(way);
		lst = lst->next;
	}
	ft_lstdel(&lst, &ft_lstfreecont);
	ft_lstdel(way->to_a, &ft_lstfreecont);
	ps_free_l(&way->l, true);
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
		send_to_b(l, s);
		lst = lst->next;
	}
	ft_lstdel(s->to_b, &ft_lstfreecont);
	ft_lstdel(&lst, &ft_lstfreecont);
	ft_lstdel(sets, &ps_free_setlistlink_content);
	return ;
}
