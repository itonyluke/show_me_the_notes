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

#ifndef STRUCTURES_HPP
# define STRUCTURES_HPP

typedef struct	s_s
{
	int											term_fd;
	struct termios								term;
	struct termios								saved_term_attributes;
	char										str[10000];
	int											number_of_bytes_actually_read;
	char										*term_name;
	std::vector<std::string>					files;
	std::vector<std::string>::iterator			it;
	DIR											*dir;
	unsigned int 								note_number;
}				t_s;

#endif //STRUCTURES_HPP
