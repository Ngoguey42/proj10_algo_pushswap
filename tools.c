/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/02 09:50:17 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/04 11:50:20 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ps.h>

t_bool		ps_is_solved(const t_psl *l)
{
	static const DBUFF_T	*al_ref = NULL;
	static size_t			al_ref_len;

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
