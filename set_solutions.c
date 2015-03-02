
#include <ps.h>

int				ps_total_movements(const t_psl *l)
{
	static int		total_movements = 0;

	qprintf("%u\n", total_movements);
	if (l != NULL)
		total_movements += l->act.zone_size;
	return (total_movements);
}

t_psl			*ps_solution_storing(t_psl *l)
{
	static t_psl	*saved = NULL;

	if (l == NULL)
		return (saved);
	ps_total_movements(l);
	if (saved)
		qprintf("prev: %u", saved->act.zone_size);
	qprintf("new: %u\n", l->act.zone_size);
	if (saved == NULL)
		saved = l;
	else if (l->act.zone_size < saved->act.zone_size)
	{
		ps_free_l(&saved, true);
		saved = l;
	}
	else
	{
		ps_free_l(&l, true);
	}
	return (saved);
}

void			ps_printbest_solution(void)
{
	t_psl*	l;

	l = ps_solution_storing(NULL);
	if (l == NULL)
		ft_putstr("Error\n");
	else
	{
		ps_print_psl(l);
		ps_free_l(&l, true);
	}
	return ;
}
