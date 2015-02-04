/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_save.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 12:32:08 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/04 13:35:31 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <ps.h>

static size_t	set_len(const t_psl *l, const PS_TYPE *ptr_ref)
{
	size_t			len;
	const PS_TYPE	*ptr;
	PS_TYPE			expected;

/* 	qprintf("searching set for %hu\n", *ptr_ref); */
	ptr = ptr_ref + 1;
	expected = *ptr_ref - 1;
	len = 1;
	while (1)
	{
		if (ptr > AZF)
			ptr = AZR;

/* 		qprintf("rear(%lld) front(%lld) \n", (t_ui64)AZR % 1000, (t_ui64)AZF % 1000); */
/* 		qprintf("(%lld) (%lld) \n", (t_ui64)ptr % 1000, (t_ui64)ptr_ref % 1000); */
/* 		D(short, *ptr); */
		if (*ptr == expected)
		{
/* 			qprintf("keep\n"); */
			len++;
			if (expected == 0)
				expected = AZS;
			else
				expected--;
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



static void		save_set(t_list *alst[1], const t_set *s)
{
	t_list	*lst;
	int		prev;
	int		totshort;
	int		tot;

	if (ft_lstnewsort((t_list**)alst, s, sizeof(t_set), &tset_sort) == NULL)
		exit(1);
	lst = *alst;
	prev = 0;
	totshort = 0;
	tot = 0;
	while (lst != NULL)
	{
		if (((const t_set*)lst->content)->len == prev)
			totshort++;
		else
			totshort = 1;
		tot++;
		prev = ((const t_set*)lst->content)->len;
		lst = lst->next;
	}
	if (tot > 5 && tot - totshort >= 5)
		while (totshort--)
			ft_lstdellast(alst, &ft_lstfreecont);
	return ;
}

void			ps_build_sets(const t_psl *l, t_list *alst[1])
{
	int		i;
	t_set	s;
	size_t	threeshold;

	i = 0;
	threeshold = 3;
	D(short, AZS);
	while (i < (int)AZS)
	{
/* 		(void)ft_bzero(&set, sizeof(t_set)); */
/* 		set.ptr = AZR; */
/* 		set.first = AZR[i]; */
		if ((s.len = set_len(l, AZR + i)) >= threeshold)
		{
			
			qprintf("chiffre: %hu  len:%hu\n", (AZR[i]), s.len);
			s.ptr = AZR + i;
			s.first = AZR[i];
			s.last = s.first + s.len - 1;
			save_set(alst, &s);
			threeshold = ((const t_set*)ft_lstlast(*alst)->content)->len;
		}
		i++;
	}
	return ;
}
