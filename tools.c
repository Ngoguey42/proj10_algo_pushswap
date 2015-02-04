/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/02 09:50:17 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/04 09:48:11 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ps.h>
#include <stdlib.h>
#include <string.h>

t_bool		ps_is_solved(const t_psl *l)
{
	static const DBUFF_T	*al_ref = NULL;
	static  size_t			al_ref_len;

	if (al_ref == NULL)
	{
		al_ref = l->al.zone_rear;
		al_ref_len = l->al.zone_size;
	}
	else if (l->bl.zone_size > 0 ||
			 ft_memcmp(l->al.zone_rear, al_ref, al_ref_len * sizeof(DBUFF_T)))
		return (false);
	return (true);
}

/*
t_bool		is_solved_old(const t_pslist *list)
{
	static PS_TYPE	*solved = NULL;
	static size_t	len = 0;
	// return (false);
	if (solved == NULL)
	{
		solved = list->a;
		len = list->asz * sizeof(PS_TYPE);
		return (true);
	}
	if (list->bsz || ft_memcmp(list->a, solved, len))
		return (false);
	return (true);
}
*/

 /*
t_bool		save_step(t_list *sol[1], const t_action *ac)
{
	if (*ac == none)
		return (true);
	if (ft_lstnewfront((t_list **)sol, ac, sizeof(t_action)) == NULL)
		exit(1);
	return (true);
}
*/

