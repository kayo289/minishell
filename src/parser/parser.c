#include "../../includes/minishell.h"

#define MESSAGE1 "syntax error near unexpected token " 
#define MESSAGE2 ": command not found"

static void sigint(int p_signame)
{
	write(1, "\b\b  \n", 5);
	exit(p_signame + 128);
}

static void set_signal(int p_signame)
{
	if (signal(p_signame, sigint) == SIG_ERR)
	{
		ft_putstr_fd(strerror(errno), 2);
		exit(1);
	}
}

static void go_exec_cmd(char ****args)
{
	pid_t pid;
	int status;

	signal(SIGINT, SIG_IGN);
	set_signal(SIGINT);
	if ((pid = fork()) == 0)
		exec_cmd(0, *args, fetch_path(args));
	else
	{
		waitpid(pid, &status, 0);
		//free(*args);
	}
}

//t_ip *next_token(t_ip **ip, t_list **queue)
void 	next_token(t_ip **ip, t_list **queue)
{
	t_list *head;

	head = *queue;
	*queue = (*queue)->next;
	*ip = (t_ip*)head->content;
	//return (ip);
}

static void command(t_ip **ip, char ****args, t_list **queue)
{
	char **arg;

	arg = (char**)ft_calloc2(sizeof(char*), 1);
	while ((*ip)->sy == IDENTIFY)
	{
		arg = ft_realloc2(arg, (*ip)->id_string);
		next_token(ip, queue);
	}
	*args = ft_realloc3(*args, arg);
	return;
}

void list(t_ip **ip, char ****args, t_list **queue)
{
	if ((*ip)->sy == IDENTIFY)
	{
		command(ip, args, queue);
		while ((*ip)->sy == GT || (*ip)->sy == LT || (*ip)->sy == DGT)
		{
			next_token(ip, queue);
			if ((*ip)->sy == IDENTIFY) 
				next_token(ip, queue);
			else
				error(MESSAGE1, (*ip)->id_string);
		}
		if ((*ip)->sy == PIPE)
		{
			next_token(ip, queue);
			if ((*ip)->sy == IDENTIFY)
				list(ip, args, queue);
			else
				error(MESSAGE1, (*ip)->id_string);
		}
		if ((*ip)->sy == SEMICOLON)
		{
			go_exec_cmd(args);
			next_token(ip, queue);
			if ((*ip)->sy == IDENTIFY)
			{
				*args = ft_calloc3(sizeof(char **), 1);
				list(ip, args, queue);
			}
			else if ((*ip)->sy != INPUT_END)
				error(MESSAGE1, (*ip)->id_string);
		}
		else if ((*ip)->sy == INPUT_END)
			go_exec_cmd(args);
	}
	else if ((*ip)->sy != INPUT_END)
		error(MESSAGE1, (*ip)->id_string);
}

