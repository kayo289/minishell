#include "../includes/minishell.h"

static void	minishell_loop_c(t_shell *shell, char *input)
{
	t_dlist		*line;
	t_list		*tokens;
	char		*s;

	line = NULL;
	while (*input != '\0')
	{
		s = ft_calloc(sizeof(char), 2);
		s[0] = *input;
		ft_dlstadd_back(&line, ft_dlstnew(s));
		input++;
	}
	lexer(line, &tokens);
	parser(tokens, shell);
	ft_dlstclear(&line, free);
	ft_lstclear(&tokens, ip_free);
}

static void	minishell_loop(t_shell *shell)
{
	t_dlist	*line;
	t_list	*tokens;

	while (1)
	{
		prompt("minishell$ ", &line, shell);
		lexer(line, &tokens);
		parser(tokens, shell);
		ft_dlstclear(&line, free);
		ft_lstclear(&tokens, ip_free);
	}
}

void	minishell_end(t_shell *shell)
{
	int	i;

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
	free(shell->pwd);
	while(1)
		;
	exit(shell->exit_status);
}

void	minishell_start(t_shell *shell)
{
	int		old_shlvl;
	char	*shlvl_value;
	char	*new_shlvl;

	new_shell_var(shell);
	set_shell_var(shell, "OLDPWD");
	old_shlvl = ft_atoi(getenv("SHLVL"));
	if (old_shlvl >= 1000)
	{
		ft_putendl_fd("minishell: warning: shell level (1001) \
too high, resetting to 1", 2);
		old_shlvl = 0;
	}
	if (old_shlvl + 1 == 1000)
		shlvl_value = ft_strdup("");
	else
		shlvl_value = ft_itoa(old_shlvl + 1);
	new_shlvl = ft_strjoin("SHLVL=", shlvl_value);
	set_shell_var(shell, new_shlvl);
	free(shlvl_value);
	free(new_shlvl);
}

int	main(int argc, char **argv)
{
	t_shell	shell;

	minishell_start(&shell);
	if (argc > 2 && ft_strncmp("-c", argv[1], 3) == 0)
		minishell_loop_c(&shell, argv[2]);
	else
		minishell_loop(&shell);
	minishell_end(&shell);
	return (0);
}
