/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/02 10:52:13 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/03 12:12:24 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ps.h>

void		apply_action(t_psl *l, t_action act)
{
	if (act <= rr)
		apply_actions_r(l, act);
	else if (act <= rrr)
		apply_actions_rr(l, act);
	else if (act <= pb)
		apply_actions_p(l, act);
	else if (act != none)
		apply_actions_s(l, act);
	if (l->act.zone_size == l->act.buf_size)
		ft_dstor_realloc(&l->act, l->act.buf_size + 0x20);
	if (l->act.zone_size == 0)
		l->act.zone_front = l->act.buf_rear;
	else
		l->act.zone_front++;
	*l->act.zone_front = (DSTOR_T)act;
	l->act.zone_size++;
	return ;
}

void		rev_action(t_psl *l)
{
	t_action	act;

	act = (t_action)*l->act.zone_front;
	if (act <= rr)
		act += 3;
	else if (act <= rrr)
		act -= 3;
	else if (act == pa)
		act++;
	else if (act == pb)
		act--;
	if (act <= rr)
		apply_actions_r(l, act);
	else if (act <= rrr)
		apply_actions_rr(l, act);
	else if (act <= pb)
		apply_actions_p(l, act);
	else if (act != none)
		apply_actions_s(l, act);
	l->act.zone_size--;
	*l->act.zone_front = 0;
	if (l->act.zone_size == 0)
		l->act.zone_front = NULL;
	else
		l->act.zone_front--;
}
/*
void		apply_actions(t_psl *l, t_action act)
{
	if (act <= rr)
		apply_actions_r(l, act);
	else if (act <= rrr)
		apply_actions_rr(l, act);
	else if (act <= pb)
		apply_actions_p(l, act);
	else if (act != none)
		apply_actions_s(l, act);
}

void		rev_actions(t_psl *l, t_action act)
{
	if (act <= rr)
		act += 3;
	else if (act <= rrr)
		act -= 3;
	else if (act == pa)
		act++;
	else if (act == pb)
		act--;
	if (act <= rr)
		apply_actions_r(l, act);
	else if (act <= rrr)
		apply_actions_rr(l, act);
	else if (act <= pb)
		apply_actions_p(l, act);
	else if (act != none)
		apply_actions_s(l, act);
}
*/
