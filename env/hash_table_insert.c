/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table_insert.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 22:41:34 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/10/31 22:44:46 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_insert_hash_item(t_hash_table *hash_table, char *key, char *value)
{
	t_uint		hash;
	t_hash_item	*hash_item;
	
	hash = ft_hash(key, hash_table->size);
	hash_item = ft_create_hash_item(key, value);
	ft_addback_item(&hash_table->hash_items[hash], hash_item);
	hash_table->count++;
}

int	ft_update_hash_item(t_hash_table *hash_table, char *key, char *value)
{
	t_hash_item	*found_hash_item;

	found_hash_item = ft_search_item_by_key(hash_table, key);
	if (!found_hash_item)
		return (FALSE);
	ft_free_ptr((void **)&(found_hash_item->value));
	found_hash_item->value = ft_strdup(value);
	return (TRUE);
}

void	ft_insert_or_update_hash_item(t_hash_table *hash_table, char *key, char *value)
{
	t_uint		hash;
	t_hash_item	*hash_item;
	int			has_key;
	
	has_key = ft_update_hash_item(hash_table, key, value);
	if (has_key)
		return ;
	hash = ft_hash(key, hash_table->size);
	hash_item = ft_create_hash_item(key, value);
	ft_addback_item(&hash_table->hash_items[hash], hash_item);
	hash_table->count++;
}