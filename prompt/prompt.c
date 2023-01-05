/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harndt <harndt@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 21:56:49 by bbonaldi          #+#    #+#             */
/*   Updated: 2023/01/04 22:01:46 by harndt           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_key_for_prompt(t_hash_table *env, char *key)
{
	t_hash_item	*hash_item;

	hash_item = ft_search_item_by_key(env, key);
	if (!hash_item)
		return ("unknown");
	return (hash_item->value);
}

char	*ft_get_hostname()
{
	int		fd;
	char	*hostname;
	char	*hostname_no_nl;
	size_t	index;

	index = 0;
	fd = open("/etc/hostname", O_RDONLY, DEFAULT_PERMISSION);
	if (fd < 0)
		return ("unknown");
	hostname = ft_get_next_line(fd);
	while (hostname[index] && hostname[index] != NEWLINE)
		index++;
	hostname_no_nl = ft_substr(hostname, 0, index);
	ft_free_ptr((void **)&hostname);
	ft_close_fd(fd);
	return (hostname_no_nl);
}

char	*ft_get_cwd(t_hash_table *env)
{
	char	*cwd;
	char	*cwd_tmp;
	char	*home;
	//usar pwd function
	cwd = getcwd(NULL, 0);
	if (!cwd)
		cwd = ft_get_key_for_prompt(env, PWD_KEY);
	if (!cwd)
		return (ft_strdup("unknown"));
	home = ft_get_key_for_prompt(env, "HOME");
	if (home)
	{
		cwd_tmp = ft_replace_str(cwd, home, "~");
		ft_free_ptr((void **)&cwd);
		cwd = cwd_tmp;

	}
	return (cwd);
}

void	ft_create_prompt_str(t_ms *ms, t_hash_table *env)
{
	char	*user;
	char	*cwd;
	char	*hostname;
	size_t	len;

	user = ft_get_key_for_prompt(env, USER_KEY);
	hostname = ft_get_hostname();
	cwd = ft_get_cwd(env);
	len = ft_strlen(user) + ft_strlen(hostname) + ft_strlen(cwd)
		+ ft_strlen(AT) + ft_strlen(COMMA) + ft_strlen(PROMPT_START)
		+ ft_strlen(GREEN) + ft_strlen(RESET) + ft_strlen(BLUE)
		+ ft_strlen(RESET) + 1;
	ms->prompt_str = (char *)malloc(sizeof(char) * len);
	ft_strlcpy(ms->prompt_str, GREEN, len);
	ft_strlcat(ms->prompt_str, user, len);
	ft_strlcat(ms->prompt_str, AT, len);
	ft_strlcat(ms->prompt_str, hostname, len);
	ft_strlcat(ms->prompt_str, RESET, len);
	ft_strlcat(ms->prompt_str, COMMA, len);
	ft_strlcat(ms->prompt_str, BLUE, len);
	ft_strlcat(ms->prompt_str, cwd, len);
	ft_strlcat(ms->prompt_str, RESET, len);
	ft_strlcat(ms->prompt_str, PROMPT_START, len);
	ft_free_ptr((void **)&hostname);
	ft_free_ptr((void **)&cwd);
}


int	ft_prompt(t_ms *ms)
{
	ms->exit_code = SUCCESS_CODE;
	while (TRUE)
	{
		ft_init_ms(ms);
		set_signals();
		ft_create_prompt_str(ms, ms->env.var);
		ms->buffer = readline(ms->prompt_str);
		if (ms->buffer == NULL)
		{
			ft_free_all_ms(ms, TRUE);
			ft_printf("exit\n");
			exit(0);
		}
		ms->buffer_start = ms->buffer;
		add_history(ms->buffer);
		ft_tokenizer(ms);
		if (!ms->invalid_program)
		{
				//ft_print_tokens_list(ms->tokens);
			ms->executor = ft_parser(ms);
			//ft_print_tree_recursive(ms->executor, "root", 0, TRUE);
			ms->exit_code = ft_execute(ms);
			//printf("%s\n", ms->buffer_start);
			ft_free_ms(ms);
		}
		
	}
	return (ms->exit_code);
}

// char    *ft_get_cwd(t_hash_table *env)
// {
//     char    *cwd;
//     char    *cwd_tmp;
//     char    *home;
//     //usar pwd function
//     cwd = getcwd(NULL, 0);
//     if (!cwd)
//         cwd = ft_get_key_for_prompt(env, PWD_KEY);
//     if (!cwd)
//         return (ft_strdup("unknown"));
//     home = ft_get_key_for_prompt(env, "HOME");
//     if (home)
//     {
//         cwd_tmp = ft_replace_str(cwd, home, "~");
//         ft_free_ptr((void **)&cwd);
//         cwd = cwd_tmp;

//     }
//     return (cwd);
// }