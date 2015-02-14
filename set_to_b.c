
#include <stdlib.h>
#include <ps.h>

static t_bool	in_set(DBUFF_T nb, DBUFF_T first, DBUFF_T last)
{
	// 9 8 7 6		
	// 3 2 1 9		
	if (first > last)
	{
		if (nb > first || nb < last)
			return (false);
		return (true);
	}
	else
	{
		if (nb > first && nb < last)
			return (false);
		return (true);
	}
}

static int		num_loops(const t_psl *l, DBUFF_T first, DBUFF_T last)
{
	int		i;
	int		ret;
	DBUFF_T	*ptr;

	i = 0;
	ret = 0;
	ptr = l->al.zone_front;
	
	// D(unsigned char, first);
	// D(unsigned char, last);
	while (ptr >= l->al.zone_rear)
	{
		// D(void*, ptr);
		// D(unsigned char, *ptr);
		i++;
		if (!in_set(*ptr, first, last))
			ret = i;
		ptr--;
	}
	return (ret);
}

void			build_alternatives_to_b(const t_psl *lref, t_set *s)
{
	t_psl	*l;
	int		i;
	// return ;
	// ps_print_psl(lref);
	// qprintf("Duping list\n");
	ps_dup_l(lref, &l);
	// ps_print_psl(lref);
	// ps_print_psl(l);
	// qprintf("Duped list\n");
	i = num_loops(l, s->first, s->last);
	// D(int, i);
	while (i--)
	{
		if (!in_set(*l->al.zone_front, s->first, s->last))
			apply_action(l, pb);
		else
			apply_action(l, ra);
	}
	ps_print_psl(l);
	// qprintf("lol\n");
	// D(void*, s->to_b);
	if (ft_lstnewback((t_list**)s->to_b, l, sizeof(t_psl)) == NULL)
		exit(1);
	// qprintf("lol\n");
	free(l);
	return ;
}