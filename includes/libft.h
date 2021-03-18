/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkikuchi <kkikuchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 23:56:51 by kkikuchi          #+#    #+#             */
/*   Updated: 2021/03/16 09:21:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <string.h>

#define __GNU_SOURCE
# include <unistd.h>


typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

void				*ft_memset(void *buf, int c, size_t n);
void				*ft_memcpy(void *buf1, const void *buf2, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memccpy(void *dest, const void *src, int c, size_t n);
void				*ft_memmove(void *buf1, const void *buf2, size_t n);
void				*ft_memchr(const void *buf, int ch, size_t n);
int					ft_memcmp(const void *buf1, const void *buf2, size_t n);
size_t				ft_strlen(const char *str);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlcat(char *dest, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strnstr(const char *str, const char *to_find, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_substr(char const *s, size_t start, size_t len);
int					ft_atoi(const char *str);
int					ft_isalpha(int n);
int					ft_isdigit(int n);
int					ft_isalnum(int n);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				*ft_calloc(size_t count, size_t size);
char 				**ft_calloc2(size_t nmemb, size_t size);
char 				***ft_calloc3(size_t nmemb, size_t size);
char 				**ft_realloc2(char **old, char *add);
char 				***ft_realloc3(char ***old, char **add);
char				*ft_strdup(const char *src);
char				*ft_substr(char const *s, size_t start, size_t len);
void				ft_charjoin(char **old, char c);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(const char *s, char c);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *str, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
				void (*del)(void *));
int					ft_setenv(char *name, char *value);
char				*ft_getenv(char *name);

#endif
