/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harndt <humberto.arndt@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 18:16:49 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/10/31 21:46:04 by harndt           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

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

t_hash_item	*ft_search_item_by_key(t_hash_table *hash_table, char *key)
{
	t_uint		hash;
	t_hash_item	*head;

	hash = ft_hash(key, hash_table->size);
	head = hash_table->hash_items[hash];
	while (head)
	{
		if (head && head->key != key)
			return (head);
		head = head->next;
	}
	return (NULL);
}

t_hash_item	*ft_create_hash_item(char *key, char *value)
{
	t_hash_item	*hash_item;

	hash_item = (t_hash_item *)malloc(sizeof(t_hash_item));
	hash_item->key = ft_strdup(key);
	hash_item->value = ft_strdup(value);
	hash_item->next = NULL;
	hash_item->prev = NULL;
	return (hash_item);
}

void	ft_initialize_hash_items(t_hash_table *hash_table)
{
	size_t	index;

	index = 0;
	while (index < hash_table->size)
	{
		hash_table->hash_items[index] = NULL;
		index++;
	}
}

t_hash_table	*ft_create_hash_table(size_t size)
{
	t_hash_table	*hash_table;

	hash_table = (t_hash_table *)malloc(sizeof(t_hash_table));
	hash_table->hash_items = (t_hash_item **)malloc(sizeof(t_hash_item *) * size);
	hash_table->size = size;
	hash_table->count = 0;
	ft_initialize_hash_items(hash_table);
	return (hash_table);
}

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

void	ft_clear_hash_item(t_hash_item *hash_item)
{
	ft_free_ptr((void **)&(hash_item->key));
	ft_free_ptr((void **)&(hash_item->value));
	ft_free_ptr((void **)&(hash_item));
}

void	ft_clear_hash_item2(t_hash_item **hash_item)
{
	ft_free_ptr((void **)&((*hash_item)->key));
	ft_free_ptr((void **)&((*hash_item)->value));
	ft_free_ptr((void **)&(*hash_item));
	*hash_item = NULL;
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

int	ft_delete_hash_item_by_key(t_hash_table *hash_table, char *key)
{
	t_hash_item	*found_hash_item;
	t_hash_item	*hash_item_tmp;
	t_uint		hash;

	hash = ft_hash(key, hash_table->size);
	found_hash_item = hash_table->hash_items[hash];
	while (found_hash_item)
	{
		if (found_hash_item 
			&& ft_strncmp(found_hash_item->key, key, ft_strlen(key)) == 0)
			break ;
		found_hash_item = found_hash_item->next;
	}
	if (!found_hash_item)
		return (FALSE);
	if (found_hash_item == hash_table->hash_items[hash])
	{
		ft_clear_hash_item2(&hash_table->hash_items[hash]);
	}
	else
	{
		hash_item_tmp = found_hash_item->prev;
		if (hash_item_tmp)
			hash_item_tmp->next = found_hash_item->next;
		hash_item_tmp = found_hash_item->next;
		if (hash_item_tmp)
			hash_item_tmp->prev = found_hash_item->prev;
		ft_clear_hash_item2(&found_hash_item);
	}
	hash_table->count--;
	return (TRUE);
}

void	ft_clear_hash_items(t_hash_item **hash_head)
{
	t_hash_item	*hash_tmp;

	while (*hash_head)
	{
		if (!(*hash_head)->next)
		{
			ft_clear_hash_item(*hash_head);
			break ;
		}
		hash_tmp = (*hash_head)->next;
		hash_tmp->prev = NULL;
		ft_clear_hash_item(*hash_head);
		(*hash_head) = hash_tmp;
	}
	hash_head = NULL;
}

void	ft_clear_hash_table(t_hash_table *hash_table)
{
	size_t	index;

	index = 0;
	while (index < hash_table->size)
	{
		ft_clear_hash_items(&hash_table->hash_items[index]);
		index++;
	}
	ft_free_ptr((void **)&(hash_table->hash_items));
	ft_free_ptr((void **)&(hash_table));
}

void	ft_print_hash_table(t_hash_table *hash_table)
{
	t_hash_item	*hash_tmp;
	size_t		index;
	size_t		inner_index;

	index = 0;
	while (index < hash_table->size)
	{
		hash_tmp = hash_table->hash_items[index];
		inner_index = 0;
		while (hash_tmp)
		{
			ft_printf("bucket: %d %d- %s=%s\n", index,
				inner_index,hash_tmp->key, hash_tmp->value);
			hash_tmp = hash_tmp->next;
			inner_index++;
		}
		index++;
	}
}

int main(void)
{
	t_hash_table	*hash_table;

	hash_table = ft_create_hash_table(10);
	ft_insert_hash_item(hash_table, "PATH", ":bin:bin/bash");
	ft_insert_hash_item(hash_table, "PATH2", ":bin:bin/bash2");
	ft_insert_hash_item(hash_table, "IHUMJ", ":bin:bin/bash2");
	ft_insert_hash_item(hash_table, "IHULL", ":bin:bin/bash4");
	ft_insert_hash_item(hash_table, "IHULL", ":bin:bin/bash4");
	ft_delete_hash_item_by_key(hash_table, "IHULL");
	ft_print_hash_table(hash_table);
	ft_printf("---------------------\n");
	ft_update_hash_item(hash_table, "IHULL", "IHULLLL");
	ft_print_hash_table(hash_table);
	ft_printf("---------------------\n");
	ft_print_hash_table(hash_table);
	ft_clear_hash_table(hash_table);
	return (0);
}