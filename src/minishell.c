#include "../includes/minishell.h"

static void minishell_loop_c(t_shell *shell, char *input)
{
	t_dlist *line;
	t_list	*tokens;
	char *s;
	int i;

	line = NULL;
	i = 0;
	while (input[i] != '\0')
	{
		s = ft_calloc(sizeof(char), 2);
		s[0] = input[i];
		ft_dlstadd_back(&line, ft_dlstnew(s));
		i++;
	}
	lexer(line, &tokens, shell);
	parser(tokens, shell);
	ft_dlstclear(&line, free);
	ft_lstclear(&tokens, ip_free);
}

static void minishell_loop(t_shell *shell)
{
	t_dlist *line;
	t_list	*tokens;

	while (1)
	{
		prompt("minishell$ ", &line, shell);
		lexer(line, &tokens, shell);
		parser(tokens, shell);
		ft_dlstclear(&line, free);
		ft_lstclear(&tokens, ip_free);
	}
} 

void minishell_end(t_shell *shell)
{
	int i;

	i = 0;
	while (i < HASH_SIZE)
	{
		ft_lstclear(&shell->var[i], free);
		i++;
	}
	shell->hist_lst = ft_dlsttop(shell->hist_lst);
	ft_dlstclear(&shell->hist_lst, free);
	free(shell->histfile_path);
	free(shell->clipboard_path);
	exit(shell->exit_status);
}

int main(int argc, char **argv)
{
	t_shell shell;
	extern char **environ;
	char **ep;
	char *tmp;
	int shlvl;

	if (environ != NULL)
	{
		ep = environ;
		while (*ep != NULL)
		{
			if (!ft_strncmp(*ep, "SHLVL", 5))
			{
				shlvl = ft_atoi(getenv("SHLVL"));
				tmp = ft_itoa(shlvl + 1);
				*ep = ft_strjoin("SHLVL=", tmp);
				free(tmp);
			}
			ep++;
		}
	}
	new_shell_var(&shell);
	if (argc > 2 && ft_strncmp("-c", argv[1], 3) == 0)
		minishell_loop_c(&shell, argv[2]);
	else
		minishell_loop(&shell);
	minishell_end(&shell);
	return (0);
}
