# include <iostream>
# include <fstream>
# include <vector>
# include <dirent.h>
# include <unistd.h>
# include <termios.h>
# include <fcntl.h>
# include "../include_files/colorize_output.hpp"
# include "../include_files/term_cap.hpp"

# define THE_PATH "/Users/wanisha/21schoolmain/personal/txt/notes/"

typedef struct	s_s
{
	/* int											term_fd; */
	struct termios								term;
	struct termios								saved_term_attributes;
	/* char										str[10000]; */
	/* int											number_of_bytes_actually_read; */
	/* char										*term_name; */
	std::vector<std::string>					files;
	std::vector<std::string>::iterator			it;
	DIR											*dir;
	/* unsigned int 								note_number; */
}				t_s;

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

int		main(void)
{
	t_s s;

	s.dir = nullptr;
	check_opendir_return_value(opendir_and_save_filenames_in_vector(s
	.dir, s.files));
	output_file_names_from_vector_1(s.files);

	return (0);
}
