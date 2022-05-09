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

void	output_file_names_from_vector(std::vector<std::string>& files)
{
	std::vector<std::string>::iterator it = files.begin();
	while (it != files.end())
	{
		if (it[0] != "." && it[0] != "..")
			std::cout << *it << std::endl;
		++it;
	}
}

int output_file(t_s &s)
{
	char			buffer[PATH_MAX];
	std::string		str = THE_PATH + *s.it;

	std::memset(buffer, '\0', PATH_MAX);
	std::strcpy(buffer, str.c_str());

	if (std::strcmp(buffer, THE_PATH) == 0)
	{
		std::cout << "you've reached the end of the directory" <<
				  std::endl;
		return (1);
	}
	FILE *file = std::fopen(buffer, "r");
	if (file)
	{
		std::cout << *s.it << std::endl;
		int c = 0;
		while ((c = std::fgetc(file)) != EOF)
			std::putchar(c);
		std::fclose(file);
	}
	else
	{
		output_error_prompt();
		std::cerr << "file.open(" << *s.it << ") failed" << std::endl;
		error_exit(s, -7);
	}
	return (0);
}

void	read_input(t_s &s)
{
	s.number_of_bytes_actually_read = read(0, s.str, 9999);
	if (s.number_of_bytes_actually_read == 0)
		error_exit(s, -5);
	else if (s.number_of_bytes_actually_read == -1)
		error_exit(s, -6);
}

