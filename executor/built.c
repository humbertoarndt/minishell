
//typedef int (t_bin)(t_command *, t_app *);
typedef int (t_bin)(char *);

t_bin	*get_builtin(char *cmd_path)
{
	static t_bin_def	builtins[7] = {
	{"echo", builtin_echo},
	{"cd", builtin_cd},
	{"pwd", builtin_pwd},
	{"export", builtin_export},
	{"unset", builtin_unset},
	{"env", builtin_env},
	{"exit", builtin_exit},
	};
	int	i;

	i = 0;
	while (i < 7)
	{
		if (ft_streq(cmd_path, builtins[i].name))
			return (builtins[i].builtin);
		i++;
	}
	return (NULL);
}