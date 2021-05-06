#include "../../../includes/minishell.h"

static int strcmp_ignorecase(const char* s1, const char* s2)
{
	while (ft_tolower(*s1) == ft_tolower(*s2))
	{
		if (*s1 == '\0')
			return 0;
		++s1;
		++s2;
	}
	return (ft_tolower(*s1) - ft_tolower(*s2));
}

static void sort(char **tab)
{
	char *tmp;
	int i;
	int j;
	int n;

	n = 0;
	while (tab[n] != NULL)
		n++;
	i = -1;
	while (++i < n - 1)
	{
		j = n;
		while (--j > i)
		{
			if (strcmp_ignorecase(tab[j], tab[j - 1]) < 0)
			{
				tmp = tab[j - 1];
				tab[j - 1] = tab[j];
				tab[j] = tmp;
			}
		}
	}
}

bool match( char * s1 , char * s2 )
{

	if(s1[0] == '\0' && s2[0] == '\0')
		return true;

	if(s1[0] == '*')
	{
		if(s2[0] == '\0')
			return (match(&s1[1], &s2[0]));
		else
		{
			if(match(&s1[1], &s2[0]) == true)
				return true;
			else
				return match(&s1[0], &s2[1]);
		}
	}
	if(s1[0] == s2[0])
		return match(&s1[1] , &s2[1]);
	return (false);
}

static char **ft_dstrjoin(char **src, char **dest)
{
	char **result;
	int i;
	int j;

	result = ft_calloc2(sizeof(char), 1);
	if (src != NULL)
	{
		i = 0;
		while (src[i] != NULL)
		{
			result = ft_realloc2(result, ft_strdup(src[i]));
			i++;
		}
		free(src);
	}
	if (dest != NULL)
	{	
		j = 0;
		while (dest[j] != NULL)
		{
			result = ft_realloc2(result, ft_strdup(dest[j]));
			j++;
		}
		free(dest);
	}
	return (result);
}

static char **recursive(char *dty, char **str)
{
	DIR				*dir;
	struct dirent	*dp;
	struct stat		st;
	char			**store;
	char			*s;
	char			*tmp;
	
	store = ft_calloc2(sizeof(char *), 1);
	if ((dir = opendir(dty)) == NULL)
	{
		ft_putendl_fd(strerror(errno), 2);
		return (NULL);
	}
	while ((dp = readdir(dir)) != NULL)
	{
		if (dp->d_name[0] == '.')
			continue;
		if (match(*str, dp->d_name))
		{
			if (*(str + 1) == NULL)
				store = ft_realloc2(store, ft_strdup(dp->d_name));
			else
			{
				if (stat(dp->d_name, &st) != 0)
					continue;
				if ((st.st_mode & S_IFMT) == S_IFDIR)
					store = ft_dstrjoin(store, recursive(dp->d_name, str+1));
				else
				{
					tmp = ft_strjoin(dty, "/");
					s = ft_strjoin(tmp, dp->d_name);
					free(tmp);
					store = ft_realloc2(store, s);
				}
			}
		}
	}
	closedir(dir);
	return (store);
}


void wildcard(t_ip *ip, t_list **tokens)
{
	char 	**store;
	char 	**str;
	int		i;

	str = ft_split(ip->id_string, '/');
	store = recursive(".", str);
	if (store == NULL)
		return;
	sort(store);
	i = -1;
	while (store[++i] != NULL)
	{
		ip->sy = IDENTIFY;
		ip->id_string = store[i];
		if (store[i + 1] != NULL)
			save_token(ip, tokens);
	}
	free(store);
}
