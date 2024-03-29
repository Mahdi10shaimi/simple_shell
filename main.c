#include "shell.h"

/**
 * main - Entry point for the shell program
 *
 * Return: Returns 0 on success, or status of the non_interactive_mode
 */
int main(void)
{
	size_t size_line = 0;
	char *line = NULL;
	int status = 0;

	if (!isatty(0))
	{
		while (getline(&line, &size_line, stdin) != -1)
		{
			inactive_mode(line, &status);
		}
		if (line)
		{
			free(line);
			line = NULL;
		}
		return (status);
	}
	start_shell();
	return (0);
}
/**
 * inactive_mode - Executes shell commands in non_nteractive_mode
 * @token: The string containing commands separated by newline characters
 * @status: integer store the number
 * Return: Returns status.
 */
void inactive_mode(char *token, int *status)
{
	char **single_command;
	char *envp[] = {NULL};

	token[strlen(token) - 1] = '\0';
	single_command = tokenize_string(token, " \t");
	if (single_command[0])
	{
		if (!_strcmp(single_command[0], "exit"))
		{
			if (single_command[1])
			{
				int my_status = _atoi(single_command[1]);

				handle_exit_status(my_status, single_command, &token, status);
			}
			else
			{
				free(token);
				free_array(single_command);
				exit(*status);
			}
		}
		else if (!_strcmp(single_command[0], "env"))
		{
			print_env_var();
			*status = 0;
		}
		else
		_execvep(single_command, envp, status);
	}
	free_array(single_command);
}

/**
 * tokenize_string - Splits a string into tokens
 * @str: The string to tokenize
 * @delimiters: The delimiters to use for tokenization
 *
 * Return: Returns result.
 */
char **tokenize_string(char *str, char *delimiters)
{
	int count = 0;
	char *token;
	char **result = malloc(20 * sizeof(char *));

	if (result == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	token = strtok(str, delimiters);
	while (token != NULL)
	{
		result[count] = _strdup(token);
		count++;
		token = strtok(NULL, delimiters);
	}
	while (count < 20)
	{
		result[count] = NULL;
		count++;
	}

	return (result);
}

