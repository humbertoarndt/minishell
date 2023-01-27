/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 23:09:44 by harndt            #+#    #+#             */
/*   Updated: 2023/01/20 22:48:14 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_path(t_ms *ms)
{
	t_hash_item	*path;

	path = ft_search_item_by_key(ms->env.var, PATH);
	ms->env.path = ft_split(path->value, COMMA_CHAR);
}

t_bool	ft_contais_path_envp(char **envp)
{
	size_t	index;

	index = 0;
	while (envp[index])
	{
		if (ft_strnstr(envp[index], PATH, ft_strlen(PATH)))
			return (TRUE);
		index++;
	}
	return (FALSE);
}

char	**ft_rebuilt_split_arg(char *word)
{
	char	**split_argv;	

	split_argv = (char **)malloc(sizeof(char *) * 2);
	split_argv[0] = ft_strdup(word);
	split_argv[1] = ft_strdup("");
	return (split_argv);
}

void	ft_print_hash_item_for_export(t_hash_item *hash_item)
{
	char	*value;

	if (!hash_item)
		return ;
	value = hash_item->value;
	if (!*value)
		ft_printf("%s\n", hash_item->key);
	else
		ft_printf("%s=\"%s\"\n", hash_item->key, hash_item->value);
}

void	ft_create_env(t_ms *ms, char *envp[])
{
	size_t	index;
	char	**split_envp;

	index = 0;
	ft_init_env(ms, envp);
	ms->env.var = ft_create_hash_table(HASH_TABLE_SIZE);
	while (ms->env.envp[index])
	{
		split_envp = ft_split_env(ms->env.envp[index]);
		ft_insert_hash_item(ms->env.var, split_envp[0], split_envp[1]);
		ft_free_split_env(&split_envp);
		index++;
	}
	ft_add_path(ms);
}
