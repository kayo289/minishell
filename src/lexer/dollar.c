#include "../../includes/minishell.h"

void dollar(line, ip, tokens)
	t_dlist **line; t_ip *ip; t_queue *tokens;
{
	char *val;
	char *str;

	if ((val = expand_parameter(line)) == NULL)
	{
		ip->sy = INPUT_END;
		return;
	}
	str = ft_strtrim(val, " \t\n");
	if (ft_strchr(" \t\n", val[0]) != NULL) {
		if (ft_strcmp(ip->id_string, "") != 0)
		{
			ip->sy = IDENTIFY;
			save_token(ip, tokens);
		}
	}
	ip->id_string = ft_strjoin(ip->id_string, str);
	if (ft_strchr(" \t\n", val[ft_strlen(val) - 1]) != NULL)
	{
		if (ft_strcmp(ip->id_string, "") != 0)
		{
			ip->sy = IDENTIFY;
			save_token(ip, tokens);
		}
	}
}
