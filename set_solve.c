/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_solve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 12:09:36 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/04 14:03:56 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ps.h>

void			ps_set_solve(t_psl *l)
{
	t_list	*sets[1];
	t_list	*lst;
	t_set	*s;

	ps_build_sets(l, sets);
	lst = *sets;
	while (lst)
	{
		s = (t_set*)lst->content;
		(void)s;
		lst = lst->next;
	}
	ft_lstdel(sets, &ft_lstfreecont);
	return ;	
}
