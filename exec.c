#include "simple_shell.h"
/**
 * exec - execute a command with its entire path variables.
 * @data: a pointer to the program's data
 * Return: If success returns zero, otherwise, return -1.
 */
int exec(program_data *data)
{
	int retval = 0, status;
	pid_t pidd;

	retval = builtinslist(data);
	if (retval != -1)
		return (retval);

	retval = find_program(data);
	if (retval)
	{
		return (retval);
	}
	else
	{
		pidd = fork();
		if (pidd == -1)
		{
			perror(data->command_name);
			exit(EXIT_FAILURE);
		}
		if (pidd == 0)
		{
			retval = execve(data->tokens[0], data->tokens, data->env);
			if (retval == -1)
				perror(data->command_name), exit(EXIT_FAILURE);
		}
		else
		{
			wait(&status);
			if (WIFEXITED(status))
				errno = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				errno = 128 + WTERMSIG(status);
		}
	}
	return (0);
}
