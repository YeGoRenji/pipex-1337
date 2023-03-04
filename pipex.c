#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void	handle_error(int argc, char **argv)
{
	(void)argv;
	if (argc != 5)
	{
		write(1, "Invalid Format ! \nUse: ./pipex file1 cmd1 cmd2 file2\n", 53);
		exit(-1);
	}
	printf("Exists ? : %d\n", access(argv[1], F_OK));
	printf("Read ? : %d\n", access(argv[1], R_OK));
}

int main(int argc, char **argv)
{
	(void)argv;
	handle_error(argc, argv);
}
