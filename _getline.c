#include "simple_shell.h"

/**
* get_line - read one line from the prompt.
* @data: struct for the program's data
*
* Return: reading counting bytes.
*/

int get_line(program_data *data)
{
	char buff[BUFFER_SIZE] = {'\0'};
	static char *array_commands[10] = {NULL};
	static char array_operators[10] = {'\0'};
	ssize_t bytes_read, r = 0;

	if (!array_commands[0] || (array_operators[0] == '&' && errno != 0) ||
		(array_operators[0] == '|' && errno == 0))
	{
		for (r = 0; array_commands[r]; r++)
		{
			free(array_commands[r]);
			array_commands[r] = NULL;
		}

		bytes_read = read(data->file_descriptor, &buff, BUFFER_SIZE - 1);
		if (bytes_read == 0)
			return (-1);

		r = 0;
		do {
			array_commands[r] = str_duplicate(_strtok(r ? NULL : buff, "\n;"));

			r = check_logic_ops(array_commands, r, array_operators);
		} while (array_commands[r++]);
	}

	data->input_line = array_commands[0];
	for (r = 0; array_commands[r]; r++)
	{
		array_commands[r] = array_commands[r + 1];
		array_operators[r] = array_operators[r + 1];
	}

	return (str_length(data->input_line));
}


/**
* check_logic_ops - checks and split for && and || operators
* @array_commands: array of the commands.
* @r: index in the array_commands to be checked
* @array_operators: array of the logical operators for each previous command
*
* Return: index of the last command in the array_commands.
*/
int check_logic_ops(char *array_commands[], int r, char array_operators[])
{
	char *temp = NULL;
	int h;

	for (h = 0; array_commands[r] != NULL  && array_commands[r][h]; h++)
	{
		if (array_commands[r][h] == '&' && array_commands[r][h + 1] == '&')
		{
			temp = array_commands[r];
			array_commands[r][h] = '\0';
			array_commands[r] = str_duplicate(array_commands[r]);
			array_commands[r + 1] = str_duplicate(temp + h + 2);
			r++;
			array_operators[r] = '&';
			free(temp);
			h = 0;
		}
		if (array_commands[r][h] == '|' && array_commands[r][h + 1] == '|')
		{
			temp = array_commands[r];
			array_commands[r][h] = '\0';
			array_commands[r] = str_duplicate(array_commands[r]);
			array_commands[r + 1] = str_duplicate(temp + h + 2);
			r++;
			array_operators[r] = '|';
			free(temp);
			h = 0;
		}
	}
	return (r);
}
