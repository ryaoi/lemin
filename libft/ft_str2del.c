
#include "libft.h"

void		ft_str2del(char ***tab)
{
	int		i;

	i = 0;
	while ((*tab)[i] != 0)
	{
		free((*tab)[i]);
		i++;
	}
	free(*tab);
}
