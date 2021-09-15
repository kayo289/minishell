#include "../../includes/minishell.h"

void here_documents(char *end_word, t_shell *shell)
{
	t_dlist *line;
	t_dlist *tmp;
	t_list *word;
	char	**content;
	int		pfd[2];

	pipe(pfd);
	while (1)
	{
		prompt("> ", &line, shell);
		tmp = line;
		word = NULL;
		while(line != NULL)
		{
			ft_lstadd_back(&word, ft_lstnew(line->content));
			line = line->next;
		}
		content = expansion(ft_lstnew(word), shell, false);
		if  (ft_strcmp(*content, end_word) == EQUAL)
		{
			dup2(pfd[0], 0);
			free(content);
			ft_dlstclear(&tmp, free);
			close(pfd[0]);
			close(pfd[1]);
			return;
		}
		ft_putendl_fd(*content, pfd[1]); 
		free(content);
		ft_dlstclear(&tmp, free);
	}
	return;
}

/*
static void expantion(int fd, char *line, t_shell *shell)
{
	char	*name;
	char	*value;
	int		i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '$')
		{
			name = ft_calloc(sizeof(char), 1);
			i++;
			if (line[i] == '{')
			{
				while (line[++i] != '\0')
				{
					if (line[i] != '}')
						break;
					ft_charjoin(&name, line[i]);
				}
			}
			else
			{
				while (line[i] != '\0')
					ft_charjoin(&name, line[i++]);
			}
			value = get_shell_var(shell, name);
			ft_putstr_fd(value, fd);
			free(name);
		}
		else
			ft_putchar_fd(line[i++], fd);
	}
	ft_putendl_fd("", fd);
}

void here_documents(char *word, t_shell *shell)
{
	char	*line;
	int		i;
	int		pfd[2];
	bool	expand;

	expand = true;
	i = 0;
	while (word[i] != '\0')
	{
		printf("%c\n", word[i]);
		if (ft_strchr("\"\'\\", word[i]) != NULL)
			expand = false;
		i++;
	}
	pipe(pfd);
	while (1)
	{
		ft_putstr_fd("> ", 1);
		get_next_line(0, &line);
		if  (ft_strcmp(line, word) == EQUAL)
		{
			free(line);
			dup2(pfd[0], 0);
			close(pfd[0]);
			close(pfd[1]);
			return;
		}
		if (expand)
			expansion(
			expantion(pfd[1], line, shell);
		else
			ft_putendl_fd(line, pfd[1]);
		free(line);
	}
}
*/

