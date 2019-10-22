#include "rdp.h"

t_flags	check_param(char **av)
{
	t_flags f;
	f.debug_all = 0;
	f.ast_draw = 0;
	while (*av)
	{
		if (strcmp(*av, "-debug=all") == 0)
			f.debug_all = 1;
		else if (strcmp(*av, "-ast=draw") == 0)
			f.ast_draw = 1;
		av++;
	}
	return (f);
}
