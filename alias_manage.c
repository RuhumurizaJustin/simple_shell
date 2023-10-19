#include "simple_shell.h"

/**
 * print_alias - add, remove or show aliases
 * @data: struct for the program's data
 * @alias: name of the alias to be printed
 * Return: zero if success, or other number if its declared in the arguments
 */
int print_alias(program_data *data, char *alias)
{
	int r, h, alias_length;
	char buffer[250] = {'\0'};

	if (data->alias_list)
	{
		alias_length = str_length(alias);
		for (r = 0; data->alias_list[r]; r++)
		{
			if (!alias || (str_compare(data->alias_list[r], alias, alias_length)
				&&	data->alias_list[r][alias_length] == '='))
			{
				for (h = 0; data->alias_list[r][h]; h++)
				{
					buffer[h] = data->alias_list[r][h];
					if (data->alias_list[r][h] == '=')
						break;
				}
				buffer[h + 1] = '\0';
				buffer_add(buffer, "'");
				buffer_add(buffer, data->alias_list[r] + h + 1);
				buffer_add(buffer, "'\n");
				_print(buffer);
			}
		}
	}

	return (0);
}

/**
 * get_alias - add, remove or show aliases
 * @data: struct for the program's data
 * @name: name of the requested alias.
 * Return: zero if success, or other number if its declared in the arguments
 */
char *get_alias(program_data *data, char *name)
{
	int r, alias_length;

	if (name == NULL || data->alias_list == NULL)
		return (NULL);

	alias_length = str_length(name);

	for (r = 0; data->alias_list[r]; r++)
	{
		if (str_compare(name, data->alias_list[r], alias_length) &&
			data->alias_list[r][alias_length] == '=')
		{
			return (data->alias_list[r] + alias_length + 1);
		}
	}
	return (NULL);

}

/**
 * set_alias - add, or override alias
 * @alias_string: alias to be seted in the form (name='value')
 * @data: struct for the program's data
 * Return: zero if success, or other number if its declared in the arguments
 */
int set_alias(char *alias_string, program_data *data)
{
	int r, h;
	char buffer[250] = {'0'}, *temp = NULL;


	if (alias_string == NULL ||  data->alias_list == NULL)
		return (1);

	for (r = 0; alias_string[r]; r++)
		if (alias_string[r] != '=')
			buffer[r] = alias_string[r];
		else
		{
			temp = get_alias(data, alias_string + r + 1);
			break;
		}


	for (h = 0; data->alias_list[h]; h++)
		if (str_compare(buffer, data->alias_list[h], r) &&
			data->alias_list[h][r] == '=')
		{
			free(data->alias_list[h]);
			break;
		}

	if (temp)
	{
		buffer_add(buffer, "=");
		buffer_add(buffer, temp);
		data->alias_list[h] = str_duplicate(buffer);
	}
	else
		data->alias_list[h] = str_duplicate(alias_string);
	return (0);
}
