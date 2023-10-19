#include "simple_shell.h"

/**
 * free_recurrent_data - frees the fields needed each loop
 * @data: struct of the program's data
 * Return: Nothing
 */
void free_recurrent_data(program_data *data)
{
if (data->tokens)
free_array_of_pointers(data->tokens);
if (data->input_line)
free(data->input_line);
if (data->command_name)
free(data->command_name);

data->input_line = NULL;
data->command_name = NULL;
data->tokens = NULL;
}

/**
 * free_all_data - free all field of the data
 * @data: struct of the program's data
 * Return: Nothing
 */
void free_all_data(program_data *data)
{
if (data->file_descriptor != 0)
{
if (close(data->file_descriptor))
perror(data->program_name);
}
free_recurrent_data(data);
free_array_of_pointers(data->env);
free_array_of_pointers(data->alias_list);
}

/**
 * free_array_of_pointers - frees each pointer of an array
 * @array: array of pointers
 * Return: nothing
 */
void free_array_of_pointers(char **array)
{
int c;

if (array != NULL)
{
for (c = 0; array[c]; c++)
free(array[c]);

free(array);
array = NULL;
}
}
