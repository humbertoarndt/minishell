/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 23:09:44 by bbonaldi          #+#    #+#             */
/*   Updated: 2023/01/16 21:57:53 by bbonaldi         ###   ########.fr       */
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

void	ft_recreate_key_value_pair_env(t_hash_item *hash_item,
			char **env_result_str)
{
	char	*joined_key_equal_symbol;

	joined_key_equal_symbol = ft_strjoin(hash_item->key, EQUAL_STRING);
	(*env_result_str) = ft_strjoin(joined_key_equal_symbol,
			hash_item->value);
	ft_free_ptr((void **)&(joined_key_equal_symbol));
}

char	**ft_rebuild_envp(t_hash_table *env)
{
	char		**env_result;
	size_t		index;
	size_t		index_env;
	t_hash_item	*hash_item;

	env_result = NULL;
	index = 0;
	index_env = 0;
	if (!env || !env->hash_items)
		return (NULL);
	env_result = (char **)malloc(sizeof(char *) * (env->count + 1));
	while (index < env->size)
	{
		hash_item = env->hash_items[index];
		while (hash_item)
		{
			ft_recreate_key_value_pair_env(hash_item, &env_result[index_env]);
			hash_item = hash_item->next;
			index_env++;
		}
		index++;
	}
	env_result[index_env] = NULL;
	return (env_result);
}
