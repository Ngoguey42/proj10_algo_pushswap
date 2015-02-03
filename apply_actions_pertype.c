/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_actions_pertype.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/02 10:52:15 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/03 10:37:30 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ps.h>
#include <string.h>//debug

/*
** Undefined if called for an impossible action.
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
		l->al.zone_front++;
		l->al.zone_size++;
		*l->al.zone_front = *l->bl.zone_front;
		*l->bl.zone_front = 0;
		l->bl.zone_front = (--l->bl.zone_size) ? l->bl.zone_front - 1 : NULL;
	}
	else if (act == pb)
	{
		if (l->bl.zone_front == l->bl.buf_front)
            ft_dbuff_recenter(&l->bl);
		l->bl.zone_front++;
		l->bl.zone_size++;
		*l->bl.zone_front = *l->al.zone_front;
		*l->al.zone_front = 0;
		l->al.zone_front = (--l->al.zone_size) ? l->al.zone_front - 1 : NULL;
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

/* void		apply_actions_r(t_psl *l, t_action act) */
/* { */
/* 	PS_TYPE	tmp; */

/* 	if (act == ra || act == rr) */
/* 	{ */
/* 		tmp = l->a[l->asz - 1]; */
/* 		(void)ft_memmove(l->a + 1, l->a, */
/* 			sizeof(PS_TYPE) * (l->asz - 1)); */
/* 		l->a[0] = tmp; */
/* 	} */
/* 	if (act == rb || act == rr) */
/* 	{ */
/* 		tmp = l->b[l->bsz - 1]; */
/* 		(void)ft_memmove(l->b + 1, l->b, */
/* 			sizeof(PS_TYPE) * (l->bsz - 1)); */
/* 		l->b[0] = tmp; */
/* 	} */
/* 	return ; */
/* } */

/* void		apply_actions_rr(t_psl *l, t_action act) */
/* { */
/* 	PS_TYPE	tmp; */

/* 	if (act == rra || act == rrr) */
/* 	{ */
/* 		tmp = l->a[0]; */
/* 		(void)ft_memmove(l->a, l->a + 1, */
/* 			sizeof(PS_TYPE) * (l->asz - 1)); */
/* 		l->a[l->asz - 1] = tmp; */
/* 	} */
/* 	if (act == rrb || act == rrr) */
/* 	{ */
/* 		tmp = l->b[0]; */
/* 		(void)ft_memmove(l->b, l->b + 1, */
/* 			sizeof(PS_TYPE) * (l->bsz - 1)); */
/* 		l->b[l->bsz - 1] = tmp; */
/* 	} */
/* 	return ; */
/* } */

/* void		apply_actions_p(t_psl *l, t_action act) */
/* { */
/* 	if (act == pa) */
/* 	{ */
/* 		l->a[l->asz] = l->b[l->bsz - 1]; */
/* 		l->b[l->bsz - 1] = 0; */
/* 		l->asz++; */
/* 		l->bsz--; */
/* 	} */
/* 	else if (act == pb) */
/* 	{ */
/* 		l->b[l->bsz] = l->a[l->asz - 1]; */
/* 		l->a[l->asz - 1] = 0; */
/* 		l->asz--; */
/* 		l->bsz++; */
/* 	} */
/* 	return ; */
/* } */

/* void		apply_actions_s(t_psl *l, t_action act) */
/* { */
/* 	PS_TYPE	tmp; */

/* 	if (act == sa || act == ss) */
/* 	{ */
/* 		tmp = l->a[l->asz - 1]; */
/* 		l->a[l->asz - 1] = l->a[l->asz - 2]; */
/* 		l->a[l->asz - 2] = tmp; */
/* 	} */
/* 	if (act == sb || act == ss) */
/* 	{ */
/* 		tmp = l->b[l->bsz - 1]; */
/* 		l->b[l->bsz - 1] = l->b[l->bsz - 2]; */
/* 		l->b[l->bsz - 2] = tmp; */
/* 	} */
/* 	return ; */
/* } */
