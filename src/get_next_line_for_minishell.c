#include "../includes/get_next_line.h"

void ft_strmove(char *s, char *t)
{
	int i;

	i = 0;
	while (t[i] != '\0')
	{
		s[i] = t[i];
		i++;
	}
	s[i] = '\0';
}

char *ft_strnjoin(char *s1, char *s2, int s2_len)
{
	int s1_len;
	int i;
	int j;
	char *s3;

	s1_len = ft_strlen(s1);
	if ((s3 = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1))) == NULL)
		return (NULL);
	j = 0;
	i = 0;
	while (i < s1_len)
		s3[j++] = s1[i++];
	i = 0;
	while (i < s2_len)
		s3[j++] = s2[i++];
	s3[j] = '\0';
	return (s3);
}

char *get_char(const char *s, int c)
{
	int i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	return ((char *)&s[i]);
}

static int get_line(int fd, char *buf, char **line)
{
	char *p;
	char *tmp;
	int len;

	p = get_char(buf, '\n');
	tmp = *line;
	*line = ft_strnjoin(*line, buf, p - buf);
	free(tmp);
	if (*line == NULL)
		return (ERROR);
	if (*p == '\n')
	{
		ft_strmove(buf, p + 1);
		return (SUCESS);
	}
	if ((len = read(fd, buf, BUFFER_SIZE)) < 0)
		return (ERROR);
	buf[len] = '\0';
	if (len == 0 && **line == '\0')
		return (END);
	return (get_line(fd, buf, line));
}

int get_next_line(int fd, char **line)
{
	static char buf[1024];

	*line = ft_calloc(sizeof(char *), 1);
	if (*line == NULL || fd < 0 || fd == 1 || fd == 2)
		return (ERROR);
	return (get_line(fd, buf, line));
}
