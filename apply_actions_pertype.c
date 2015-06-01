/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_actions_pertype.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/02 10:52:15 by ngoguey           #+#    #+#             */
/*   Updated: 2015/06/01 18:23:50 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ps.h>

/*
** Each function apply an action on 'l' according to 'act'.
*/

void		apply_actions_r(t_psl *l, t_action act)
{
	if (act == ra || act == rr)
	{
		if (l->al.zone_rear == l->al.buf_rear)
			ft_dbuff_recenter(&l->al);
		l->al.zone_rear--;
		*l->al.zone_rear = *l->al.zone_front;
		*l->al.zone_front = 0;
		l->al.zone_front--;
	}
	if (act == rb || act == rr)
	{
		if (l->bl.zone_rear == l->bl.buf_rear)
			ft_dbuff_recenter(&l->bl);
		l->bl.zone_rear--;
		*l->bl.zone_rear = *l->bl.zone_front;
		*l->bl.zone_front = 0;
		l->bl.zone_front--;
	}
	return ;
}

void		apply_actions_rr(t_psl *l, t_action act)
{
	if (act == rra || act == rrr)
	{
		if (l->al.zone_front == l->al.buf_front)
			ft_dbuff_recenter(&l->al);
		l->al.zone_front++;
		*l->al.zone_front = *l->al.zone_rear;
		*l->al.zone_rear = 0;
		l->al.zone_rear++;
	}
	if (act == rrb || act == rrr)
	{
		if (l->bl.zone_front == l->bl.buf_front)
			ft_dbuff_recenter(&l->bl);
		l->bl.zone_front++;
		*l->bl.zone_front = *l->bl.zone_rear;
		*l->bl.zone_rear = 0;
		l->bl.zone_rear++;
	}
	return ;
}

void		apply_actions_p(t_psl *l, t_action act)
{
	if (act == pa)
	{
		if (l->al.zone_front == l->al.buf_front)
			ft_dbuff_recenter(&l->al);
		AZF = (AZS == 0) ? l->al.zone_start : AZF + 1;
		AZR = (AZS == 0) ? l->al.zone_start : AZR;
		l->al.zone_size++;
		*l->al.zone_front = *l->bl.zone_front;
		*l->bl.zone_front = 0;
		l->bl.zone_front = (--l->bl.zone_size) ? l->bl.zone_front - 1 : NULL;
		BZR = (BZS == 0) ? NULL : BZR;
	}
	else if (act == pb)
	{
		if (l->bl.zone_front == l->bl.buf_front)
			ft_dbuff_recenter(&l->bl);
		BZF = (BZS == 0) ? l->bl.zone_start : BZF + 1;
		BZR = (BZS == 0) ? l->bl.zone_start : BZR;
		l->bl.zone_size++;
		*l->bl.zone_front = *l->al.zone_front;
		*l->al.zone_front = 0;
		l->al.zone_front = (--l->al.zone_size) ? l->al.zone_front - 1 : NULL;
		AZR = (AZS == 0) ? NULL : AZR;
	}
	return ;
}

void		apply_actions_s(t_psl *l, t_action act)
{
	DBUFF_T	tmp;

	if (act == sa || act == ss)
	{
		tmp = *l->al.zone_front;
		*l->al.zone_front = *(l->al.zone_front - 1);
		*(l->al.zone_front - 1) = tmp;
	}
	if (act == sb || act == ss)
	{
		tmp = *l->bl.zone_front;
		*l->bl.zone_front = *(l->bl.zone_front - 1);
		*(l->bl.zone_front - 1) = tmp;
	}
	return ;
}
