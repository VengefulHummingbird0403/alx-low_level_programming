#include "main.h"
#include <stdlib.h>

/**
 * read_textfile- Read text file print to STDOUT.
 * @filename: text file being read
 * @letters: number of letters to be read
 * Return: w; actual number of bytes read and printed
 *        0; filename is NULL.
 */
ssize_t read_textfile(const char *filename, size_t letters)
{
	char *bOF;
	ssize_t file_Descriptor;
	ssize_t W;
	ssize_t t;

	file_Descriptor = open(filename, O_RDONLY);
	if (file_Descriptor == -1)
		return (0);
	bOF = malloc(sizeof(char) * letters);
	t = read(file_Descriptor, bOF, letters);
	W = write(STDOUT_FILENO, bOF, t);

	free(bOF);
	close(file_Descriptor);
	return (W);
}

