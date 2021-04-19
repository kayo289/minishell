#ifndef SHELL_VAR
#define SHELL_VAR

#define SIZE	29999

struct s_shell;
struct s_param;
typedef struct s_param		t_param;
typedef struct s_shell *	t_shell;

struct s_shell
{
	t_list	*var[SIZE];
	t_dlist	*hist_lst;
	int		exit_status;
};

struct s_param
{
	char *key;
	char *value;
};

// shell_var
t_shell new_shell_var(void);
void set_shell_var(t_shell this, char *param);
char *get_shell_var(t_shell this, char *name);
int hash(char *name);
#endif
