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

void 	output_usage_prompt()
{
	std::cout << colors::yellow << "Usage:" << colors::reset << std::endl;
	std::cout << "./a.out" << std::endl;
}

void 	output_error_prompt()
{
	std::cerr << colors::red << "Error" << colors::reset
			  << std::endl;
	std::cerr << "Errno: " << errno << ": ";
	std::cerr << std::strerror(errno) << std::endl;
}

void	error_exit(t_s &s, int err_code)
{
	output_error_prompt();
	if (err_code == -1)
	{
		std::cerr << "s.term_fd = open(\"/dev/tty\", O_RDONLY);" << std::endl;
		std::cerr << "s.term_fd == -1" << std::endl;
	}
	else if (err_code == -2)
		std::cerr << "Specify a terminal type "
					 "with `setenv TERM <yourtype>'." << std::endl;
	else if (err_code == -3)
		std::cerr << "Could not access the termcap data base." << std::endl;
	else if (err_code == -4)
		std::cerr << "Terminal type `%s' is not defined." << std::endl;
	else if (err_code == -5)
		std::cerr << "s.number_of_bytes_actually_read = read(0, s.str, 9999);\n"
					 "s.number_of_bytes_actually_read == 0;" << std::endl;
	else if (err_code == -6)
		std::cerr << "s.number_of_bytes_actually_read = read(0, s.str, 9999);\n"
					 "s.number_of_bytes_actually_read == -1;" << std::endl;
	else
		std::cerr << "Ooops!" << std::endl;
	s.term.c_lflag |= ECHO;
	s.term.c_lflag |= ICANON;
	reset_initial_terminal_attributes(s);
	exit(err_code);
}

void	init_failed(t_s &s, int err_code)
{
	output_error_prompt();
	if (err_code == -1)
		std::cerr << "tcgetattr() returned -1\ninitial terminal "
					 "attributes were not saved." << std::endl;
	else if (err_code == -2)
		std::cerr << "tcgetattr() returned -1\ninitial terminal "
					 "attributes were not saved." << std::endl;
	else if (err_code == -3)
		std::cerr << "tcsetattr() returned -1\nterminal "
					 "attributes were not set" << std::endl;
	s.term.c_lflag |= ECHO;
	s.term.c_lflag |= ICANON;
	reset_initial_terminal_attributes(s);
	exit(-42);
}
