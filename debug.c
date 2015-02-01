
#include <ps.h>

void		print_list(const t_pslist *list)
{
	const PS_TYPE	*a = list->a;
	const PS_TYPE	*b = list->b;

	qprintf("A:(%hu)", list->asz);
	while (*a)
		qprintf("%hu ", *a++);
	qprintf("\n");
	qprintf("B:(%hu)", list->bsz);
	while (*b)
		qprintf("%hu ", *b++);
	qprintf("\n");
	return ;
}

const char	*action_name(t_action action)
{
	static const char	names[][5] = {

	"ra",
	"rb",
	"rr",
	"rra",
	"rrb",
	"rrr",
	"pa",
	"pb",
	"sa",
	"sb",
	"ss",
	"none"};
	return (names[action]);
}
