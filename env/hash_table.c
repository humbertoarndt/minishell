/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 18:16:49 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/11/10 20:36:23 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

t_hash_item	*ft_search_item_by_key(t_hash_table *hash_table, char *key)
{
	t_uint		hash;
	t_hash_item	*head;

	hash = ft_hash(key, hash_table->size);
	head = hash_table->hash_items[hash];
	while (head)
	{
		if (head && ft_strncmp(head->key, key, ft_strlen(key)) == 0)
			return (head);
		head = head->next;
	}
	return (NULL);
}

void	ft_print_hash_item(t_hash_item *hash_item)
{
	if (!hash_item)
		return ;
	ft_printf("%s=%s\n", hash_item->key, hash_item->value);
}

void	ft_print_hash_table(t_hash_table *hash_table)
{
	t_hash_item	*hash_tmp;
	size_t		index;

	index = 0;
	while (index < hash_table->size)
	{
		hash_tmp = hash_table->hash_items[index];
		while (hash_tmp)
		{
			ft_print_hash_item(hash_tmp);
			hash_tmp = hash_tmp->next;
		}
		index++;
	}
}

void	ft_print_hash_table_as_env(t_hash_table *hash_table)
{
	ft_print_hash_table(hash_table);
	ft_printf("\n");
}