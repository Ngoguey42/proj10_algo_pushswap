
#include <ps.h>
#define MAX_BRUTE_LVL 8

#define RA_EX	(-1 - RB - RRA - RRR)
#define RB_EX	(-1 - RA - RRB - RRR)
#define RR_EX	(-1 - RRA - RRB - RRR)
#define RRA_EX	(-1 - RA - RRB - RR)
#define RRB_EX	(-1 - RB - RRA - RR)
#define RRR_EX	(-1 - RA - RB - RR)
#define PA_EX	(-1 - PB)
#define PB_EX	(-1 - PA)
#define S_EX	(-1 - SA - SB - SS)

#define A_IS_0_1	(-1 - SS - SA - PB - RRR - RR - RA - RRA)
#define B_IS_0		(-1 - SS - SB - PA - RRR - RR - RB - RRB)
#define B_IS_1		(-1 - SS - SB      - RRR - RR - RB - RRB)


// ra,		0
// rb,		1
// rr,		2
// rra,		3
// rrb,		4
// rrr,		5
// pa,		6
// pb,		7
// sa,		8
// sb,		9
// ss,		10
// none		11
	
/*
** if size <= 2 don"t allow rr rotations
*/

static void			fill_exclusions(PS_TYPE asz, PS_TYPE bsz, t_action pac,
						unsigned short *exclusions)
{
	if (pac == ra)
		*exclusions = RA_EX;
	else if (pac == rb)
		*exclusions = RB_EX;
	else if (pac == rr)
		*exclusions = RR_EX;
	else if (pac == rra)
		*exclusions = RRA_EX;
	else if (pac == rrb)
		*exclusions = RRB_EX;
	else if (pac == rrr)
		*exclusions = RRR_EX;
	else if (pac == pa)
		*exclusions = PA_EX;
	else if (pac == pb)
		*exclusions = PB_EX;
	else if (pac != none)
		*exclusions = S_EX;
	if (asz <= 1)
		*exclusions &= A_IS_0_1;
	if (bsz == 1)
		*exclusions &= B_IS_1;
	else if (bsz == 0)
		*exclusions &= B_IS_0;
	return ;
}

static t_bool		next_lvl(t_pslist *list, t_list *sol[1], char lvl, t_action pac)
{
	t_action		ac;
	unsigned short	exclusions;

	exclusions = -1;
	fill_exclusions(list->asz, list->bsz, pac, &exclusions);
	ac = 0;
	while (ac <= ss)
	{
		// qprintf("while: %3s auth(%hd)\n", action_name(ac), (exclusions & 0x1));
		if ((exclusions & 0x1) && ps_brute_solve_lvl(list, sol, lvl, ac))
			return (true);
		ac++;
		exclusions >>= 1;
	}
	return (false);
}


t_bool				ps_brute_solve_lvl(t_pslist *list, t_list *sol[1], char lvl, t_action ac)
{
	// qprintf("\n==================>entering solve_lvl\n");
	// qprintf("lvl = %hhd  ac = %s \n", lvl, action_name(ac));
	apply_actions(list, ac);
	// print_list(list);
	if (lvl == MAX_BRUTE_LVL)
	{
		if (is_solved(list) == true)
			return (save_step(sol, &ac));
		// qprintf("1leaving solve_lvl<================\n");
		rev_actions(list, ac);
		return (false);
	}
	else if (next_lvl(list, sol, lvl + 1, ac) == true)
		return (save_step(sol, &ac));
	// qprintf("2leaving solve_lvl<================\n");
	rev_actions(list, ac);
	return (false);
}
	
int					ps_brute_solve(t_pslist orig, t_list *solution[1])
{
	ps_brute_solve_lvl(&orig, solution, 0, none);
	print_list(&orig);
	return (1);
}
