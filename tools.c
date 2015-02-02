/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/02 09:50:17 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/02 11:56:02 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ps.h>
#include <stdlib.h>

t_bool		is_solved(const t_pslist *list)
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

t_bool		save_step(t_list *sol[1], const t_action *ac)
{
/* 	qprintf("saving %s\n", action_name(*ac)); */
	if (*ac == none)
		return (true);
	if (ft_lstnewfront((t_list **)sol, ac, sizeof(t_action)) == NULL)
		exit(1);
	return (true);
}
