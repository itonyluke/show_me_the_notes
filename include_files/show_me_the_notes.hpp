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

#ifndef SHOW_ME_THE_NOTES_HPP
# define SHOW_ME_THE_NOTES_HPP

# include <iostream>
# include <fstream>
# include <vector>
# include <dirent.h>
# include <unistd.h>
# include <termios.h>
# include <fcntl.h>
# include "../include_files/colorize_output.hpp"
# include "../include_files/structures.hpp"
# include "../include_files/term_cap.hpp"

/* # define THE_PATH "./notes/" */
# define THE_PATH "/Users/wanisha/21schoolmain/personal/txt/notes/"

void	init_term(t_s &s);
void	error_exit(t_s &s, int err_code);
void 	output_error_prompt();
void 	output_usage_prompt();
void	reset_initial_terminal_attributes(t_s &s);
void	init_failed(t_s &s, int err_code);
int		output_file(t_s &s);
void	read_input(t_s &s);
int		opendir_and_save_filenames_in_vector(DIR *dir,
												std::vector<std::string> &files);
void	check_opendir_return_value(unsigned int check);

#endif //SHOW_ME_THE_NOTES_HPP
