/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 13:56:03 by gguichar          #+#    #+#             */
/*   Updated: 2019/06/07 12:51:18 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <term.h>
#include <signal.h>
#include "select.h"
#include "items.h"
#include "hotkeys.h"

t_select	*g_select = NULL;

static int	error(char *arg, char *message)
{
	ft_dprintf(STDERR_FILENO, "%s: %s\n", arg, message);
	return (0);
}

static int	init_select(int argc, char **argv, t_select *select)
{
	select->tty_fd = open("/dev/tty", O_WRONLY);
	if (select->tty_fd == -1)
		return (error(argv[0], "unable to open tty"));
	else if (tgetent(NULL, getenv("TERM")) == -1)
		return (error(argv[0], "unable to init termcaps"));
	else if (!setup_term(select))
		return (error(argv[0], "unable to init term"));
	update_winsize(select);
	select->def_items = create_items(argc - 1, argv + 1);
	if (select->def_items == NULL)
	{
		reset_term(select);
		return (error(argv[0], "memory allocation error"));
	}
	return (1);
}

static void	setup_signals(void)
{
	int	sig;

	sig = 1;
	while (sig <= 31)
	{
		signal(sig, handle_common_signal);
		sig++;
	}
	signal(SIGWINCH, handle_resize_signal);
	signal(SIGTSTP, handle_job_signals);
	signal(SIGCONT, handle_job_signals);
}

static void	add_default_hotkeys(t_select *select)
{
	add_hotkey(&select->hotkeys, HOTKEY_ESC, "\033", hotkey_exit_hook);
	add_hotkey(&select->hotkeys, HOTKEY_ENTER, "\012", hotkey_exit_hook);
	add_hotkey(&select->hotkeys, HOTKEY_SPACE, "\040", hotkey_select_hook);
	add_hotkey(&select->hotkeys, HOTKEY_ARROW_LEFT, tgetstr("kl", NULL)
		, hotkey_nav_hook);
	add_hotkey(&select->hotkeys, HOTKEY_ARROW_RIGHT, tgetstr("kr", NULL)
		, hotkey_nav_hook);
	add_hotkey(&select->hotkeys, HOTKEY_BACKSPACE, "\177", hotkey_del_hook);
	add_hotkey(&select->hotkeys, HOTKEY_DELETE, tgetstr("kD", NULL)
		, hotkey_del_hook);
	add_hotkey(&select->hotkeys, HOTKEY_CTRL_A, "\001"
		, hotkey_select_all_hook);
	add_hotkey(&select->hotkeys, HOTKEY_HOME, tgetstr("kh", NULL)
		, hotkey_home_end_hook);
	add_hotkey(&select->hotkeys, HOTKEY_END, tgetstr("@7", NULL)
		, hotkey_home_end_hook);
}

int			main(int argc, char **argv)
{
	t_select	select;

	if (argc < 2)
		return (!error(argv[0], "please specify at least one choice"));
	else if (!isatty(STDIN_FILENO))
		return (!error(argv[0], "standard input is not a tty"));
	ft_memset(&select, 0, sizeof(t_select));
	g_select = &select;
	if (!init_select(argc, argv, &select))
		return (1);
	setup_signals();
	select.cur_items = select.def_items;
	select.cursor_item = select.def_items;
	select.format = get_columns_format(&select);
	add_default_hotkeys(&select);
	select_loop(&select);
	reset_term(&select);
	close(select.tty_fd);
	ft_lstfree(&select.hotkeys);
	free(select.def_items);
	return (0);
}
