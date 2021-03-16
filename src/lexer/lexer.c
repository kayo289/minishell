#include "../../includes/minishell.h"

char next_ch(char *line, t_ip *ip)
{
	ip->ch = line[ip->index];
	if (line[ip->index] != '\0')
		ip->index++;
	return (ip->ch);
}

static void save_token(t_ip *ip, t_list **queue)
{
	t_list	*lst;
	t_ip	*tmp;

	tmp = malloc(sizeof(t_ip) * 1);
	*tmp = *ip;
	lst = ft_lstnew(tmp);
	ft_lstadd_back(queue, lst);
}

static void get_token(char **line, t_ip *ip, t_list **queue)
{
	ip->id_string = ft_calloc(sizeof(char), 1);
	while (ip->ch == ' ' || ip->ch == '\t')
		next_ch(*line, ip);
	if (ip->ch == '\0')
	{
		ip->sy = INPUT_END;
		return;
	}
	else
	{
		if (ft_strchr("|><;", ip->ch) == NULL)
		{
			while (ft_strchr("|><; \0", ip->ch) == NULL)
			{
				if (ft_strchr("\"\'\\", ip->ch) != NULL)
					quoting(line, ip);
				else
					ft_charjoin(&ip->id_string, ip->ch);
				next_ch(*line, ip);
			}
			ip->sy = IDENTIFY;
		}
		else
			metacharacter(line, ip);
	}
	save_token(ip, queue);
	get_token(line, ip, queue);
}

void parse_line(char *line)
{
	t_ip	ip;
	t_list	*queue;
	char	***args;
	t_ip	*head;

	ip.ch = ' ';
	ip.index = 0;
	queue = NULL;
	get_token(&line, &ip, &queue);
	save_token(&ip, &queue);
	/* To debug */
	/*
	t_list *debug = queue;
	while (debug != NULL)
	{ 
		printf("%s -> ", ((t_ip *)debug->content)->id_string);
		debug = debug->next;
	}
	printf("NULL\n");
	*/

	args = (char ***)ft_calloc3(sizeof(char **), 1);
	next_token(&head, &queue);
	list(&head, &args, &queue);
}
