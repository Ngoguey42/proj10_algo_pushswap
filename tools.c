/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/02 09:50:17 by ngoguey           #+#    #+#             */
/*   Updated: 2015/06/02 13:15:04 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <ps.h>

/*
** 'ps_is_solved'	Checks if a given 't_psl' is solved.
** 		Is first called by 'create_ref' to initialize reference.
** *
** 'ps_dup_l'		duplicates a given 't_psl'.
** *
** 'ps_free_l'		frees a given 't_psl'
** *
** 'ft_exit'		exitsm printing a message to cerr.
*/

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

void		ps_dup_l(const t_psl *lref, t_psl **ldst)
{
	t_psl	*l;

	if (!(l = (t_psl*)malloc(sizeof(t_psl))))
		exit(0);
	if (ft_dbuff_dup(&lref->al, &l->al) ||
		ft_dbuff_dup(&lref->bl, &l->bl) ||
		ft_dstor_dup(&lref->act, &l->act))
		ft_exit("ENOMEM");
	*ldst = l;
	return ;
}

void		ps_free_l(t_psl **l, t_bool free_struct)
{
	free((*l)->al.buf_rear);
	free((*l)->bl.buf_rear);
	free((*l)->act.buf_rear);
	if (free_struct)
		free(*l);
	return ;
}

void		ps_free_setlistlink_content(void *content, size_t size)
{
	(void)size;
	(void)content;
	ft_lstdel(((t_set*)content)->to_b, &ft_lstfreecont);
	free(content);
	return ;
}

void		ft_exit(char *str)
{
	if (str != NULL)
		ft_putendl_fd(str, 2);
	exit(0);
	return ;
}
