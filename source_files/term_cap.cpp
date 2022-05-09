//Copyright 2022 Anton Pavlyukevich.

//This file is part of a show_me_the_notes.
//
//show_me_the_notes is free software: you can redistribute it
// and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
//show_me_the_notes is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with show_me_the_notes.  If not, see <https://www.gnu.org/licenses/>.

//
// Created by pavlyukevich.anton@gmail.com on 09.05.22
//

// built and tested on Darwin Kernel Version 18.7.0: Tue Jun 22 19:37:08 PDT 2021; root:xnu-4903.278.70~1/RELEASE_X86_64 x86_64

#include "../include_files/show_me_the_notes.hpp"

void	get_and_save_initial_terminal_attributes(t_s &s)
{
	int	err_check;

	err_check = tcgetattr(s.term_fd, &(s.saved_term_attributes));
	if (err_check == -1)
		init_failed(s, -1);
}

void	get_and_save_terminal_attributes(t_s &s)
{
	int	err_check;

	err_check = tcgetattr(s.term_fd, &(s.term));
	if (err_check == -1)
		init_failed(s, -2);
}

void 	set_terminal_attributes(t_s &s)
{
	int	err_check;

	err_check = tcsetattr(s.term_fd, TCSANOW, &(s.term));
	if (err_check == -1)
		init_failed(s, -3);
}

void	reset_initial_terminal_attributes(t_s &s)
{
	int	err_check;

	err_check = tcsetattr(s.term_fd, TCSANOW, &(s.saved_term_attributes));
	if (err_check == -1)
		std::cerr << "tcsetattr() returned -1\ninitial terminal attributes were not reset" << std::endl;
}

void	init_term(t_s &s)
{
	s.term_fd = open("/dev/tty", O_RDONLY);
	if (s.term_fd == -1)
		error_exit(s, -1);
	get_and_save_initial_terminal_attributes(s);
	get_and_save_terminal_attributes(s);
	s.term.c_lflag &= ~ECHO;
	s.term.c_lflag &= ~ICANON;
	set_terminal_attributes(s);
}
