/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 23:09:44 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/11/01 22:14:30 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_split_env(char *envp)
{
	int		index;
	char	**split_env;
	index = ft_strchr_pos(envp, EQUAL_CHAR);
	if (index == -1)
		return (NULL);
	split_env = (char **)malloc(sizeof(char *) * 2);
	split_env[0] = ft_substr(envp, 0, index);
	split_env[1] = ft_substr(envp, index + 1, ft_strlen(envp) - index);
	return (split_env);
}

void	ft_free_split_env(char ***split_envp)
{
	size_t	index;

	index = 0;
	while (index < 2)
		ft_free_ptr((void **)&((*split_envp)[index++]));
	ft_free_ptr((void **)(*split_envp));
	ft_free_ptr((void **)&(*split_envp));
}

void	ft_add_path(t_ms *ms)
{
	t_hash_item *path;
	
	path = ft_search_item_by_key(ms->env.var, PATH);
	ms->env.path = ft_split(path->value, COMMA_CHAR);
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