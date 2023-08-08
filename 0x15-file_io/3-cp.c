#include "main.h"
#include <stdio.h>
#include <stdlib.h>

char *create_bOF(char *file);
void close_file(int file_Descriptor);

/**
 * create_buffer - Allocates 1024 bytes for a buffer.
 * @file: The name of the file buffer is storing chars for.
 *
 * Return: A pointer to the newly-allocated buffer.
 */
char *create_bOF(char *file)
{
	char *bOF;

	bOF = malloc(sizeof(char) * 1024);

	if (bOF == NULL)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't write to %s\n", file);
		exit(99);
	}

	return (bOF);
}

/**
 * close_file - Closes file descriptors.
 * @file_Descriptor: The file descriptor to be closed.
 */
void close_file(int file_Descriptor)
{
	int c;

	c = close(file_Descriptor);

	if (c == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", file_Descriptor);
		exit(100);
	}
}

/**
 * main - Copies the contents of a file to another file.
 * @argc: The number of arguments supplied to the program.
 * @argv: An array of pointers to the arguments.
 *
 * Return: 0 on success.
 *
 * Description: If the argument count is incorrect - exit code 97.
 * If file_from does not exist or cannot be read - exit code 98.
 * If file_to cannot be created or written to - exit code 99.
 * If file_to or file_from cannot be closed - exit code 100.
 */
int main(int argc, char *argv[])
{
	int from, to, r, W;
	char *bOF;

	if (argc != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit(97);
	}

	bOF = create_bOF(argv[2]);
	from = open(argv[1], O_RDONLY);
	r = read(from, bOF, 1024);
	to = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0664);

	do {
		if (from == -1 || r == -1)
		{
			dprintf(STDERR_FILENO,
				"Error: Can't read from file %s\n", argv[1]);
			free(bOF);
			exit(98);
		}

		W = write(to, bOF, r);
		if (to == -1 || W == -1)
		{
			dprintf(STDERR_FILENO,
				"Error: Can't write to %s\n", argv[2]);
			free(bOF);
			exit(99);
		}

		r = read(from, bOF, 1024);
		to = open(argv[2], O_WRONLY | O_APPEND);

	} while (r > 0);

	free(bOF);
	close_file(from);
	close_file(to);

	return (0);
}


