/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_actions_pertype.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/02 10:52:15 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/02 15:10:20 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ps.h>
#include <string.h>

void		apply_actions_r(t_pslist *list, t_action ac)
{
	PS_TYPE	tmp;

	if (ac == ra || ac == rr)
	{
		tmp = list->a[list->asz - 1];
		(void)ft_memmove(list->a + 1, list->a,
			sizeof(PS_TYPE) * (list->asz - 1));
		list->a[0] = tmp;
	}
	if (ac == rb || ac == rr)
	{
		tmp = list->b[list->bsz - 1];
		(void)ft_memmove(list->b + 1, list->b,
			sizeof(PS_TYPE) * (list->bsz - 1));
		list->b[0] = tmp;
	}
	return ;
}

void		apply_actions_rr(t_pslist *list, t_action ac)
{
	PS_TYPE	tmp;

	if (ac == rra || ac == rrr)
	{
		tmp = list->a[0];
		(void)ft_memmove(list->a, list->a + 1,
			sizeof(PS_TYPE) * (list->asz - 1));
		list->a[list->asz - 1] = tmp;
	}
	if (ac == rrb || ac == rrr)
	{
		tmp = list->b[0];
		(void)ft_memmove(list->b, list->b + 1,
			sizeof(PS_TYPE) * (list->bsz - 1));
		list->b[list->bsz - 1] = tmp;
	}
	return ;
}

void		apply_actions_p(t_pslist *list, t_action ac)
{
	if (ac == pa)
	{
		list->a[list->asz] = list->b[list->bsz - 1];
		list->b[list->bsz - 1] = 0;
		list->asz++;
		list->bsz--;
	}
	else if (ac == pb)
	{
		list->b[list->bsz] = list->a[list->asz - 1];
		list->a[list->asz - 1] = 0;
		list->asz--;
		list->bsz++;
	}
	return ;
}

void		apply_actions_s(t_pslist *list, t_action ac)
{
	PS_TYPE	tmp;

	if (ac == sa || ac == ss)
	{
		tmp = list->a[list->asz - 1];
		list->a[list->asz - 1] = list->a[list->asz - 2];
		list->a[list->asz - 2] = tmp;
	}
	if (ac == sb || ac == ss)
	{
		tmp = list->b[list->bsz - 1];
		list->b[list->bsz - 1] = list->b[list->bsz - 2];
		list->b[list->bsz - 2] = tmp;
	}
	return ;
}
