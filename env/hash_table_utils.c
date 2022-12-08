/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 22:05:14 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/12/07 21:44:25 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_uint	ft_hash(char *key, size_t size)
{
	size_t	key_len;
	size_t	index;
	size_t	hash;

	key_len = ft_strlen(key);
	index = 0;
	hash = 0;
	while (index < key_len)
	{
		hash += key[index];
		hash = (hash * key[index]) % size;
		index++;
	}
	return (hash);
}

t_hash_item	*ft_find_last_item(t_hash_item *hash_head)
{
	t_hash_item	*head_item;

	if (!hash_head)
		return (NULL);
	head_item = hash_head;
	while (head_item->next)
		head_item = head_item->next;
	return (head_item);
}

void	ft_addback_item(t_hash_item **hash_item, t_hash_item *new_hash_item)
{
	t_hash_item	*last_item;

	if (!(*hash_item))
	{
		*hash_item = new_hash_item;
		return ;
	}
	last_item = ft_find_last_item(*hash_item);
	last_item->next = new_hash_item;
	new_hash_item->prev = last_item;
}

size_t	ft_count_items_in_bucket(t_hash_item *hash_head)
{
	size_t	count_items;

	count_items = 0;
	while (hash_head)
	{
		count_items++;
		hash_head = hash_head->next;
	}
	return (count_items);
}

void	ft_add_path(t_ms *ms)
{
	t_hash_item	*path;

	path = ft_search_item_by_key(ms->env.var, PATH);
	ms->env.path = ft_split(path->value, COMMA_CHAR);
}
