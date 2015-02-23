/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_save.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 12:32:08 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/23 14:53:03 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <ps.h>

static size_t	set_len(const t_psl *l, const PS_TYPE *ptr_ref)
{
	size_t			len;
	const PS_TYPE	*ptr;
	PS_TYPE			expected;

 	// qprintf("searching set for %hu\n", *ptr_ref);
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
		if (expected == 0)
			expected = AZS;
			
		// qprintf("looping for %hu  (is %hu ?)\n", *ptr, expected);
		if (*ptr == expected)
		{
			// qprintf("keep\n"); 
			expected--;
			len++;

		}
		
		
		if (ptr == ptr_ref)
			break ;
		ptr++;
	}
	// D(unsigned char, len);
	return (len);
}

static int		tset_sort(const void *a, const void *b)
{
	// D(unsigned char, ((const t_set*)a)->len);
	// D(unsigned char, ((const t_set*)b)->len);
	return (((const t_set*)a)->len >= ((const t_set*)b)->len);
}

#define SOFT_CAP 5
#define HARD_CAP 30

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
	// D(int, tot);
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
	// D(short, AZS);
	while (i < (int)AZS)
	{
/* 		(void)ft_bzero(&set, sizeof(t_set)); */
/* 		set.ptr = AZR; */
/* 		set.first = AZR[i]; */
		if ((s.len = set_len(l, AZR + i)) >= threeshold)
		{
			
			// qprintf("chiffre: %hu  len:%hu\n", (AZR[i]), s.len);
			*s.to_b = NULL;
			s.ptr = AZR + i;
			// qprintf("lol1\n");
			s.first = AZR[i];
			// qprintf("lol2\n");
			if ((int)s.first - (int)s.len + 1 <= 0)
				s.last = (AZS - s.len + s.first + 1);
			else
				s.last = (s.first - s.len + 1);
			// qprintf("lol3\n");
			save_set(alst, &s, &threeshold);
			// qprintf("lol4\n");
			// threeshold = ((const t_set*)ft_lstlast(*alst)->content)->len;
		}
		i++;
	}
	return ;
}
