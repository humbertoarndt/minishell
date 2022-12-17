/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 22:00:23 by harndt            #+#    #+#             */
/*   Updated: 2022/12/15 02:02:08 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export_no_argvs(t_hash_table *var)
{
	t_hash_item	*hash_tmp;
	size_t		index;

	index = 0;
	while (index < var->size)
	{
		hash_tmp = var->hash_items[index];
		while (hash_tmp)
		{
			ft_printf("declare -x ");
			ft_print_hash_item(hash_tmp);
			hash_tmp = hash_tmp->next;
		}
		index++;
	}
}

void	ft_print_export_error(char *argv)
{
	char	*argv_syntax_error;

	argv_syntax_error = ft_strjoin_free(ft_strdup("`"), argv);
	argv_syntax_error = ft_strjoin_free(argv_syntax_error, ft_strdup("'"));
	print_custom_arg_error2((char *[2]){"export: ", argv_syntax_error}, INVALID_IDENTIFIER);
}

int	is_word(char *str)
{
	size_t	index;

	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (FALSE);
	index = 1;
	while (str[index])
	{
		if (!ft_isalnum(str[index]) && str[index] != '_'
			&& str[index] != EQUAL_CHAR)
			return (FALSE);
		index++;
	}
	return (TRUE);
}

void	print_export_with_args(t_ms *ms, char **argvs)
{
	size_t	index;
	char	*word;
	char	**split_argv;

	index = 1;
	while (argvs[index])
	{
		word = argvs[index];
		if (!is_word(word))
		{
			ft_print_export_error(word);
			ms->invalid_program = SYNTAX_ERR;
			return ;
		}
		split_argv = ft_split_env(word);
		if (!split_argv)
		{
			index++;
			continue ;
		}
		ft_insert_or_update_hash_item(ms->env.var, split_argv[0], split_argv[1]);
		ft_free_split_env(&split_argv);
		index++;
	}
}

t_bool	ms_export(t_ms *ms, t_cmd *cmds, t_bool is_child)
{
	int	count_of_argvs;

	count_of_argvs = ft_lstsize(cmds->argv_list);	
	if (count_of_argvs == 1)
		print_export_no_argvs(ms->env.var);
	else
		print_export_with_args(ms, cmds->argv);
	kill_child(ms, is_child, 1); // TODO Definir valor de exit_code
	return (TRUE);
}
