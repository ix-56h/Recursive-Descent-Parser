#include "rdp.h"

void	factor(char *s)
{
	s++;
}

int main(int ac, char **av)
{
	char *input = av[1];
	t_flags	f;

	if (ac < 2)
	{
		printf("Usage: ./rdp \"2*8+(1 - 2)\"\n\t\t\t-debug=1\n\t\t\t-ast=draw\n");
		return (0);
	}
	f = check_param(av + 2);
	if (f.debug_all)
		printf("f.d = %u\nf.a = %u\n", f.debug_all, f.ast_draw);
	factor(input);
	return 0;
}
