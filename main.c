
#include <ps.h>
#include <stdlib.h>

int			main(void)
{
	t_list	*solutions[1];
	t_pslist	orig;

	PS_TYPE	*solved;
	
	solved = malloc(sizeof(PS_TYPE) * 8);
	solved[0] = 1;
	solved[1] = 2;
	solved[2] = 3;
	solved[3] = 4;
	solved[4] = 5;
	solved[5] = 6;
	// solved[6] = 7;
	// solved[7] = 8;
	(void)is_solved(&(t_pslist){solved, 6, NULL, 0});
	
	orig.a = ft_memalloc(sizeof(PS_TYPE) * 7);
	orig.b = ft_memalloc(sizeof(PS_TYPE) * 7);
	orig.bsz = 2;
	orig.asz = 4;
	orig.a[0] = 4;
	orig.a[1] = 3;
	orig.a[2] = 2;
	orig.a[3] = 1;
	
	orig.b[0] = 6;
	orig.b[1] = 5;
	ps_brute_solve(orig, solutions);
	return (0);
}
