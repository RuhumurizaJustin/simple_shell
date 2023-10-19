#include "simple_shell.h"

/**
 * env_get_key - gets the value of an environment variable
 * @key: the environment variable of interest
 * @data: struct of the program's data
 * Return: a pointer to the value of the variable or NULL if it doesn't exist
 */
char *env_get_key(char *key, program_data *data)
{
	int c, key_length = 0;

	if (key == NULL || data->env == NULL)
		return (NULL);

	key_length = str_length(key);

	for (c = 0; data->env[c]; c++)
	{
		if (str_compare(key, data->env[c], key_length) &&
		 data->env[c][key_length] == '=')
		{
			return (data->env[c] + key_length + 1);
		}
	}
	return (NULL);
}

/**
 * env_set_key - overwrite the value of the environment variable
 * or create it if does not exist.
 * @key: name of the variable to set
 * @value: new value
 * @data: struct of the program's data
 * Return: 1 if the parameters are NULL, 2 if there is an erroror 0 if sucess.
 */

int env_set_key(char *key, char *value, program_data *data)
{
	int c, key_length = 0, is_new_key = 1;

	if (key == NULL || value == NULL || data->env == NULL)
		return (1);

	key_length = str_length(key);

	for (c = 0; data->env[c]; c++)
	{
		if (str_compare(key, data->env[c], key_length) &&
		 data->env[c][key_length] == '=')
		{
			is_new_key = 0;
			free(data->env[c]);
			break;
		}
	}
	data->env[c] = str_concat(str_duplicate(key), "=");
	data->env[c] = str_concat(data->env[c], value);

	if (is_new_key)
	{
		data->env[c + 1] = NULL;
	}
	return (0);
}

/**
 * env_remove_key - remove a key from the environment
 * @key: the key to remove
 * @data: the sructure of the program's data
 * Return: 1 if the key was removed, 0 if the key does not exist;
 */
int env_remove_key(char *key, program_data *data)
{
	int c, key_length = 0;

	if (key == NULL || data->env == NULL)
		return (0);

	key_length = str_length(key);

	for (c = 0; data->env[c]; c++)
	{
		if (str_compare(key, data->env[c], key_length) &&
		 data->env[c][key_length] == '=')
		{
			free(data->env[c]);
			c++;
			for (; data->env[c]; c++)
			{
				data->env[c - 1] = data->env[c];
			}
			data->env[c - 1] = NULL;
			return (1);
		}
	}
	return (0);
}


/**
 * print_environ - prints the current environ
 * @data: struct for the program's data
 * Return: nothing
 */
void print_environ(program_data *data)
{
	int j;

	for (j = 0; data->env[j]; j++)
	{
		_print(data->env[j]);
		_print("\n");
	}
}
