
#include "libft.h"

int		ft_cmpi_e(const void *a, const void *b)
{
	return (*(int*)a == *(int*)b);
}

int		ft_cmpi_l(const void *a, const void *b)
{
	return (*(int*)a < *(int*)b);
}

int		ft_cmpi_le(const void *a, const void *b)
{
	return (*(int*)a <= *(int*)b);
}

int		ft_cmpi_g(const void *a, const void *b)
{
	return (*(int*)a > *(int*)b);
}

int		ft_cmpi_ge(const void *a, const void *b)
{
	return (*(int*)a >= *(int*)b);
}
