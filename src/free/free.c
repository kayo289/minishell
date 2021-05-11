#include "../../includes/minishell.h"

void dp_free(char **str)
{
	int i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void ip_free(void *content)
{
	free(((t_ip *)content)->id_string);
	free((t_ip *)content);
}

void data_free(void *content)
{
	t_queue queue;

	queue = ((t_data *)content)->vars; 
	while (!q_empty(&queue))
		deq(&queue);
	queue = ((t_data *)content)->fds; 
	while (!q_empty(&queue))
		deq(&queue);
	free(((t_data *)content)->words);
	free((t_data *)content);
}

void gmr_free(void *content)
{
	ft_lstclear(&((t_gmr *)content)->datas, data_free);
	free(content);
}
