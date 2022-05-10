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

bool no_signal_received = true;

void get_input_and_output_the_notes(t_s &s)
{
	std::memset(s.str, '\0', 1000);
	s.it = s.files.begin();
	system("clear");
	if (output_file(s) == 1)
		error_exit(s,-7);
	while (no_signal_received)
	{
		read_input(s);
		if (std::strcmp(s.str, UP_ARROW) == 0)
		{
			if (s.it != s.files.begin())
				--s.it;
			system("clear");
			if (output_file(s))
				continue;
		}
		else if (std::strcmp(s.str, DOWN_ARROW) == 0)
		{
			if (s.it != s.files.end())
				++s.it;
			system("clear");
			if (output_file(s))
				continue;
		}
	}
}

int	opendir_and_save_filenames_in_vector(DIR *dir, std::vector<std::string> &files)
{
	struct dirent *diread = nullptr;
	dir = opendir(THE_PATH);
	if (dir != nullptr)
	{
		while ((diread = readdir(dir)) != nullptr)
		{
			if (std::strncmp(diread->d_name, ".", 1) == 0 || std::strncmp
																 (diread->d_name, ".. ", 2) == 0)
				continue;
			files.push_back(diread->d_name);
		}
		closedir(dir);
	}
	else
	{
		output_error_prompt();
		return (1);
	}
	return (0);
}

void	check_opendir_return_value(unsigned int check)
{
	if (check != 0)
	{
		output_error_prompt();
		std::cerr << "check = opendir_and_save_the_filenames_in_vector(dir, "
					 "files)" << std::endl;
		std::cerr << "check = " << check << std::endl;
		exit(EXIT_FAILURE);
	}
}

void	ft_sig_handle(int sig)
{
	if (sig == SIGINT)
	{
		(void)sig;
		std::cout << colors::yellow << "received SIGINT : interrupt the "
									   "program "
									   "and terminate "
									   "process"	<< colors::reset << std::endl;
		no_signal_received = false;
		exit(EXIT_SUCCESS);
	}
}

int		main(int argc, char **argv)
{
	if (argc == 1)
	{
		t_s		s;
		(void) argv;
		signal(SIGINT, ft_sig_handle);

		s.dir = nullptr;
		check_opendir_return_value(opendir_and_save_filenames_in_vector(s
		.dir, s.files));
		init_term(s);
		get_input_and_output_the_notes(s);
	}
	else
		output_usage_prompt();
	return (0);
}
