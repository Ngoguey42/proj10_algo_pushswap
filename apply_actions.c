/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/02 10:52:13 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/02 13:43:03 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ps.h>

void		apply_actions(t_pslist *list, t_action ac)
{
	if (ac <= rr)
		apply_actions_r(list, ac);
	else if (ac <= rrr)
		apply_actions_rr(list, ac);
	else if (ac <= pb)
		apply_actions_p(list, ac);
	else if (ac != none)
		apply_actions_s(list, ac);
}

void		rev_actions(t_pslist *list, t_action ac)
{
	if (ac <= rr)
		ac += 3;
	else if (ac <= rrr)
		ac -= 3;
	else if (ac == pa)
		ac++;
	else if (ac == pb)
		ac--;
	if (ac <= rr)
		apply_actions_r(list, ac);
	else if (ac <= rrr)
		apply_actions_rr(list, ac);
	else if (ac <= pb)
		apply_actions_p(list, ac);
	else if (ac != none)
		apply_actions_s(list, ac);
}
