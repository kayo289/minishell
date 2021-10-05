#include "../../includes/minishell.h"

char *path_join(char *path, char *new_path)
{
	char *result_path;
	char *tmp;

	if (ft_strlen(path) == 0 || path[ft_strlen(path) - 1] != '/')
	{
		tmp = ft_strjoin(path, "/");
		result_path = ft_strjoin(tmp, new_path);
		free(tmp);
	}else
		result_path = ft_strjoin(path, new_path);
	return (result_path);
}

char *three_path_join(char *s1, char *s2, char *s3)
{
	char *str;
	char *str2;

	str = path_join(s1, s2);
	str2 = path_join(str, s3);
	free(str);
	return (str2);
}

static char *get_parent(char *path)
{
	char *result;

	result = ft_substr(path, 0, ft_strrchr(path, '/') - path);
	if (result && ft_strlen(result) == 0)
		result = ft_strdup("/");
	return (result);
}

static char *normalize(char *path)
{
	char **str;
	int i;
	char *result;
	struct stat buf;
	char *tmp;

	i = 0;
	str = ft_split(path, '/');
	result = ft_strdup("/");
	while (str[i])
	{
		if (ft_strncmp(str[i], "..", 2) == 0)
			result = get_parent(result);
		else if (str[i][0] != '.')
		{
			tmp = result;
			result = path_join(tmp, str[i]);
			free(tmp);
		}
		if (stat(result, &buf) != 0)
		{
			free(result);
			dp_free(str);
			return (NULL);
		}
		i++;

	}
	if (path[0] == '/' && path[1] == '/' && path[2] != '/')
		result = path_join("/", result);
	dp_free(str);
	return (result);
}

char *get_absolute_path(char *path, bool *is_absolute_path, t_shell *shell)
{
	char *new_path;
	char *norm_path;

	if(path[0] == '/')
		new_path = ft_strdup(path);
	else
		new_path = path_join(shell->pwd, path);
	norm_path = normalize(new_path);
	if (norm_path != NULL)
	{
		*is_absolute_path = true;
		free(new_path);
		return (norm_path);
	}
	*is_absolute_path = false;
	free(norm_path);
	return (new_path);
}
