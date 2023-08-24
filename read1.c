#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shead.h"

/**
 * read_command_with_args - Read input line and that tokenize
 *
 * Return: Arrays
 */
char **read_command_with_args(void)
{
	char *input_line = NULL;
	size_t input_size = 0;
	ssize_t chars_read;
	char **tokens;
	char *token;
	int token_count = 0;

	/* Read input line with getline */
	chars_read = getline(&input_line, &input_size, stdin);
	if (chars_read == -1)
	{
		free(input_line);
		return (NULL);
	}
	input_line[chars_read - 1] = '\0'; /* Remove newline character */

	/* Tokenize the input_line */
	

	tokens = malloc(sizeof(char *));
	if (tokens == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	token = strtok(input_line, " ");
	while (token != NULL)
	{
		tokens[token_count] = strdup(token);
		if (tokens[token_count] == NULL)
		{
			perror("strdup");
			exit(EXIT_FAILURE);
		}

		token_count++;
		tokens = realloc(tokens, (token_count + 1) * sizeof(char *));
		if (tokens == NULL)
		{
			perror("realloc");
			exit(EXIT_FAILURE);
		}

		token = strtok(NULL, " ");
	}
	tokens[token_count] = NULL; 
	/* Null-terminate the array of tokens */

	free(input_line);

	return (tokens);
}
