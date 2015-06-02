/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_save.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 12:32:08 by ngoguey           #+#    #+#             */
/*   Updated: 2015/06/02 14:13:20 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <ps.h>

static size_t	set_len(const t_psl *l, const PS_TYPE *ptr_ref)
{
	size_t			len;
	const PS_TYPE	*ptr;
	PS_TYPE			expected;

	ptr = ptr_ref + 1;
	expected = *ptr_ref - 1;
	len = 1;
	while (1)
	{
		if (ptr > AZF)
			ptr = AZR;
		if (expected == 0)
			expected = AZS;
		if (*ptr == expected)
		{
			expected--;
			len++;
		}
		if (ptr == ptr_ref)
			break ;
		ptr++;
	}
	return (len);
}

static int		tset_sort(const void *a, const void *b)
{
	return (((const t_set*)a)->len >= ((const t_set*)b)->len);
}

static void		trim_list(t_list *alst[1],
							int tot, int totshortest, size_t *threeshold)
{
	t_list	*tmp;

	if (tot > 5 && tot - totshortest >= SOFT_CAP)
		while (totshortest--)
		{
			tot--;
			tmp = ft_lstpulllast(alst);
			*threeshold = ((const t_set*)tmp->content)->len + 1;
			ft_lstdelone(&tmp, &ft_lstfreecont);
		}
	while (tot-- > HARD_CAP)
	{
		tmp = ft_lstpulllast(alst);
		*threeshold = ((const t_set*)tmp->content)->len + 1;
		ft_lstdelone(&tmp, &ft_lstfreecont);
	}
	return ;
}

static void		save_set(t_list *alst[1], const t_set *s, size_t *threeshold)
{
	t_list	*lst;
	int		prev;
	int		totshortest;
	int		tot;

	if (ft_lstnewsort((t_list**)alst, s, sizeof(t_set), &tset_sort) == NULL)
		exit(1);
	lst = *alst;
	prev = 0;
	totshortest = 0;
	tot = 0;
	while (lst != NULL)
	{
		if (((const t_set*)lst->content)->len == prev)
			totshortest++;
		else
			totshortest = 1;
		tot++;
		prev = ((const t_set*)lst->content)->len;
		lst = lst->next;
	}
	trim_list(alst, tot, totshortest, threeshold);
	return ;
}

void			ps_build_sets(const t_psl *l, t_list *alst[1])
{
	int		i;
	t_set	s;
	size_t	threeshold;

	i = 0;
	threeshold = 2;
	while (i < (int)AZS)
	{
		if ((s.len = set_len(l, AZR + i)) >= threeshold)
		{
			*s.to_b = NULL;
			s.ptr = AZR + i;
			s.first = AZR[i];
			if ((int)s.first - (int)s.len + 1 <= 0)
				s.last = (AZS - s.len + s.first + 1);
			else
				s.last = (s.first - s.len + 1);
			save_set(alst, &s, &threeshold);
		}
		i++;
	}
	return ;
}
