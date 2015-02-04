/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_save.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 12:32:08 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/04 12:45:25 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <ps.h>

static size_t	set_len(const t_psl *l, const PS_TYPE *ptr_ref)
{
	size_t	len;
	PS_TYPE	*ptr;
	PS_TYPE	expected;

	ptr = ptr_ref + 1;
	expected = *ptr;
	len = 1;
	while (ptr != ptr_ref)
	{
		if (ptr > AZF)
			ptr = AZR;
		if (*ptr == expected)
		{
			len++;
			if (expected == AZS)
				expected = 1;
			else
				expected++;
		}
		ptr++;
	}
	return (len);
}

static int		tset_sort(const void *a, const void *b)
{
	return (((const t_set*)a)->len >= ((const t_set*)b)->len);
}

static void		save_set(t_list *alst[1], const t_set *s)
{
	t_list	*lst;
	int		prev;
	int		tot;

	if (ft_lstnewsort((t_list**)alst, s, sizeof(t_set), &tset_sort) == NULL)
		exit(1);
	lst = *alst;
	prev = 0;
	tot = 0;
	while (lst != NULL)
	{
		if (((const t_set*)lst->content)->len == prev)
			tot++;
		else
			tot = 1;
		prev = ((const t_set*)lst->content)->len;
		lst = lst->next;
	}
	return ;
}

void			ps_build_sets(const t_psl *l, t_list *alst[1])
{
	int		i;
	t_set	s;
	size_t	threeshold;

	i = 0;
	threeshold = 0;
	while (i < AZS)
	{
/* 		(void)ft_bzero(&set, sizeof(t_set)); */
/* 		set.ptr = AZR; */
/* 		set.first = AZR[i]; */
		if ((set.len = set_len(l, AZR)) >= threeshold)
		{
			set.ptr = AZR + i;
			set.first = AZR[i];
			set.last = set.first + set.len - 1;
			save_set(alst, &set);
		}
		i++;
	}
	return ;
}
