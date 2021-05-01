#include "../../includes/minishell.h"

static void		find_command(char *cmd, char **cmd_path, char **dir_names)
{
	int				i;
	DIR				*dir;
	struct dirent	*dp;
	struct stat		sb;

	i = -1;
	while (dir_names[++i] != NULL)
	{
		if ((dir = opendir(dir_names[i])) == NULL)
			continue;
		while ((dp = readdir(dir)) != NULL)
		{
			if (stat(dp->d_name, &sb) < 0)
			{
				if (ft_strcmp(cmd, dp->d_name) == EQUAL)
				{
					*cmd_path = ft_strjoin(dir_names[i], "/");
					*cmd_path = ft_strjoin(*cmd_path, dp->d_name);
					return;
				}
			}
		}
		closedir(dir);
	}
}

static char	*search_path(char *cmd_name, t_shell *shell)
{
	char	*env_value;
	char	**dir_names;
	char	*cmd_path;
	int		i;

	cmd_path = NULL;
	env_value = get_shell_var(shell, "PATH");
	dir_names = ft_split(env_value, ':');
	find_command(cmd_name, &cmd_path, dir_names);
	i = 0;
	while (dir_names[i] != NULL)
		free(dir_names[i++]);
	free(dir_names);
	return (cmd_path);
}

void	cmds_execute(char **args, t_shell *shell)
{
	extern char	**environ;
	char		*cmd;
	char		*cmd_path;

	cmd = args[0];
	if (ft_strchr(cmd, '/') != NULL)
		cmd_path = ft_strdup(cmd);
	else 
	{
		cmd_path = search_path(cmd, shell);
		if (cmd_path == NULL)
		{
			free(cmd_path);
			err_notfound(cmd, shell);
		}
	}
	execve(cmd_path, args, environ);
	ft_putendl_fd(strerror(errno), 2);
	shell->exit_status = 126;
	minishell_end(shell);
}

