#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <limits.h>
#include <signal.h>
#include <termios.h>
#include <termcap.h>
#include <ctype.h>
#include "queue.h"
#include "libft.h"

#define CTRL_SPACE	0
#define CTRLV		22
#define CTRLX		24
#define CTRLY		25
#define CTRLC		3
#define CTRLD		4
#define TAB			9
#define LF			10
#define ESC			27
#define DEL			126
#define BKS			127

#define SUCCESS		1
#define END			0
#define ERROR		-1
#define FAIL		-1
#define INIT		-1
#define OUTOFRANGE	-2
#define BUFFER_SIZE 1024
#define HASH_SIZE	29999

#define TRUE		1
#define FALSE		0

typedef enum u_token		t_token;
typedef enum u_operator		t_operator;
typedef enum u_exec_env		t_exec_env;
typedef struct s_pos		t_pos;
typedef struct s_ip			t_ip;
typedef struct s_data		t_data;
typedef struct s_gmr		t_gmr;
typedef struct s_shell		t_shell;
typedef	struct s_stdfd		t_stdfd;

enum u_token
{
	PIPE,		// |
	REDIRECT,	// >>, >, <
	LEFT_BRACE,	// {
	RIGHT_BRACE,// }
	SEMICOLON,	// ;
	AND,		// &
	ANDAND,		// &&
	OROR,		// ||
	IDENTIFY,	// String
	INPUT_END,	// End Of Input
	ERR,		// ERROR

	TOKEN_NUM	// don't care
};

enum u_operator
{
	ANDAND_OP,
	OROR_OP,
	NEWLINE_OP
};

enum u_exec_env
{
	MAINSHELL,
	SUBSHELL
};

struct s_shell
{
	t_list	*var[HASH_SIZE];
	t_dlist	*hist_lst;
	char	*histfile_path;
	char	*clipboard_path;
	int		exit_status;
	char	*pwd;
};

struct  s_pos
{
	int cursor;
	int max_rg;
	int max_lf;

	bool	is_select;
	int		select;
	t_dlist *selectp;
};

struct	s_ip
{
	t_token		sy;
	char		ch;
	char		*id_string;
};

struct s_data
{
	t_queue		vars;
	t_queue		fds;
	t_list		*words;
};

struct	s_gmr
{
	t_operator	op;
	t_exec_env	exec_env;
	t_list		*datas;
};

struct	s_stdfd
{
	int in;
	int out;
	int err;
};


// minishell
void	minishell_end(t_shell *shell);

// prompt
void	prompt(char *ps, t_dlist **line, t_shell *shell);
void	term_mode(char *p, int arg_cols, int arg_rows);

// prompt_utils
void	insert(t_dlist **lst, char c, t_pos *pos);
void 	backspace(t_pos *pos, t_dlist **cursor);
void	esc(t_pos *pos, t_dlist **cursor, t_shell *shell);
void	init_pos(t_pos *pos, char *ps);
void	delete(t_pos *pos, t_dlist **cursor);

// move
void	move_to_rg(t_pos *pos, t_dlist **cursor);
void	move_to_lf(t_pos *pos, t_dlist **cursor);
void	move_to_word(t_pos *pos, t_dlist **cursor);
void	move_to_home(t_pos *pos, t_dlist **cursor);
void	move_to_end(t_pos *pos, t_dlist **cursor);
void	move_to_up(t_pos *pos, t_dlist **cursor);
void	move_to_down(t_pos *pos, t_dlist **cursor);

// copy_and_paste
void	select_mode(t_pos *pos, t_dlist **cursor);
void	copy(t_pos *pos, t_dlist **cursor, t_shell *shell);
void	paste(t_pos *pos, t_dlist **cursor, t_shell *shell);
void	cut(t_pos *pos, t_dlist **cursor, t_shell *shell);

// history
void	history_next(t_pos *pos, t_dlist **cursor, t_shell *shell);
void	history_prev(t_pos *pos, t_dlist **cursor, t_shell *shell);
void	save_history(t_dlist *line, t_shell *shell);

// lexer
void	lexer(t_dlist *line, t_list **tokens);
void	get_token(t_dlist **line, t_ip *ip, t_list **tokens);
void	save_token(t_ip *ip, t_list **tokens);
char	next_ch(t_dlist **line, t_ip *ip);
void	ip_charjoin(t_ip *ip, char ch);

//	literal
void	literal(t_dlist **line, t_ip *ip, t_list **tokens);
void	quoting(t_dlist **line, t_ip *ip);
void	wildcard(t_ip *ip, t_list **tokens);

//	metachcharacter
void	metacharacter(t_dlist **line, t_ip *ip);

// parser
void	parser(t_list *tokens, t_shell *shell);

// interpreter
void	interpreter(t_list *gmrs, t_shell *shell);
void	exec_pipeline(t_list *datas, int ppfd[], t_shell *shell);
void	exec_simplecmd(t_list *datas, t_shell *shell);
bool	lookup_bltin(char **args);
void	execute_bltin(char **args, t_shell *shell);
void	execute_cmds(char **args, t_shell *shell);
void	assign_variable(t_queue *vars, t_shell *shell);
char	**expand_words(t_list *words, t_shell *shell, bool quote);
char	**expand_word(char *word, t_shell *shell, bool quote);
int		redirect(t_queue *fds, t_shell *shell);
void	here_documents(char *end_word, t_shell *shell);
void	set_signal(void);
void	set_signal_ign(void);
void	set_signal_dfl(void);

// bltin
int		minishell_cd(char **argv, t_shell *shell);
char	*get_absolute_path(char *path, bool *is_absolute_path, t_shell *shell);
char	*path_join(char *path, char *new_path);
char	*three_path_join(char *s1, char *s2, char *s3);
int		minishell_pwd(void);
int		minishell_echo(char **argv);
int		minishell_unset(char **argv, t_shell *shell);
int		minishell_exit(char **argv, t_shell *shell);
int		minishell_export(char **argv, t_shell *shell);
int		minishell_env(char **argv);

// shell_var
char	*get_param_name(char *param);
char	*get_param_value(char *param);
void	set_environ(t_shell *shell, char *name);
void	new_shell_var(t_shell *this);
void	set_shell_var(t_shell *this, char *param);
char	*get_shell_var(t_shell *this, char *name);
int		get_next_line(int fd, char **line);
int		hash(char *name);

// error
void	err_syntax(t_ip *ip, t_shell *shell);
void	err_notfound(char *cmd, t_shell *shell);
void	err_errno(char *s, char *arg);
void	err_cstmmsg(char *s, char *c, char *msg);

// free
void	dp_free(char **str);
void	ip_free(void *content);
void	param_free(void *content);
void	gmr_free(void *content);

#endif
