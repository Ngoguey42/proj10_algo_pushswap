
#ifndef PS_H
# define PS_H

# include <ft_debug.h>
# include <libft.h>

# define RA 0b00000000001
# define RB 0b00000000010
# define RR 0b00000000100
# define RRA 0b00000001000
# define RRB 0b00000010000
# define RRR 0b00000100000
# define PA 0b00001000000
# define PB 0b00010000000
# define SA 0b00100000000
# define SB 0b01000000000
# define SS 0b10000000000

# define RA_EX (-1 - RB - RRA - RRR)
# define RB_EX (-1 - RA - RRB - RRR)
# define RR_EX (-1 - RRA - RRB - RRR)
# define RRA_EX (-1 - RA - RRB - RR)
# define RRB_EX (-1 - RB - RRA - RR)
# define RRR_EX (-1 - RA - RB - RR)
# define PA_EX (-1 - PB)
# define PB_EX (-1 - PA)
# define S_EX (-1 - SA - SB - SS)

# define A_TOO_SMALL (-1 - SS - SA - PB - RRR - RR - RA - RRA)
# define B_EMPTY     (-1 - SS - SB - PA - RRR - RR - RB - RRB)
# define B_TOO_SMALL (-1 - SS - SB      - RRR - RR - RB - RRB)

#define MAX_BRUTE_LVL 8
#define PS_TYPE unsigned short

typedef struct	s_pslist
{
	PS_TYPE		*a;
	PS_TYPE		asz;
	PS_TYPE		*b;
	PS_TYPE		bsz;
}				t_pslist;

typedef enum	e_action
{
	ra,
	rb,
	rr,
	rra,
	rrb,
	rrr,
	pa,
	pb,
	sa,
	sb,
	ss,
	none
}				t_action;

/*
** Tools
*/
t_bool			save_step(t_list *sol[1], const t_action *ac);
t_bool			is_solved(const t_pslist *list);

/*
** Apply action to list
*/
void			rev_actions(t_pslist *list, t_action ac);
void			apply_actions(t_pslist *list, t_action ac);

void			apply_actions_s(t_pslist *list, t_action ac);
void			apply_actions_p(t_pslist *list, t_action ac);
void			apply_actions_rr(t_pslist *list, t_action ac);
void			apply_actions_r(t_pslist *list, t_action ac);

/*
** Brute solve
*/
t_bool			ps_brute_solve_lvl(t_pslist *list, t_list *sol[1],
					char lvl, t_action ac);
int				ps_brute_solve(t_pslist orig, t_list *solution[1]);

/*
** Debug
*/
const char		*action_name(t_action action);
void			print_list(const t_pslist *list);

#endif