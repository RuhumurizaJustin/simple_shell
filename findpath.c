#include "simple_shell.h"

int check_file(char *full_path);

/**
 * find_program - find a program in path
 * @data: a pointer to the program's data
 * Return: 0 if success, errcode otherwise
 */

int find_program(program_data *data)
{
int r = 0, ret_code = 0;
char **directories;

if (!data->command_name)
return (2);

if (data->command_name[0] == '/' || data->command_name[0] == '.')
return (check_file(data->command_name));

free(data->tokens[0]);
data->tokens[0] = str_concat(str_duplicate("/"), data->command_name);
if (!data->tokens[0])
return (2);

directories = tokenize_path(data);

if (!directories || !directories[0])
{
errno = 127;
return (127);
}
for (r = 0; directories[r]; r++)
{
directories[r] = str_concat(directories[r], data->tokens[0]);
ret_code = check_file(directories[r]);
if (ret_code == 0 || ret_code == 126)
{
errno = 0;
free(data->tokens[0]);
data->tokens[0] = str_duplicate(directories[r]);
free_array_of_pointers(directories);
return (ret_code);
}
}
free(data->tokens[0]);
data->tokens[0] = NULL;
free_array_of_pointers(directories);
return (ret_code);
}

/**
 * tokenize_path - tokenize the path in directories
 * @data: a pointer to the program's data
 * Return: array of path directories
 */

char **tokenize_path(program_data *data)
{
int r = 0;
int counter_directories = 2;
char **tokens = NULL;
char *PATH;

PATH = env_get_key("PATH", data);
if ((PATH == NULL) || PATH[0] == '\0')
{
return (NULL);
}

PATH = str_duplicate(PATH);

for (r = 0; PATH[r]; r++)
{
if (PATH[r] == ':')
counter_directories++;
}

tokens = malloc(sizeof(char *) * counter_directories);

r = 0;
tokens[r] = str_duplicate(_strtok(PATH, ":"));
while (tokens[r++])
{
tokens[r] = str_duplicate(_strtok(NULL, ":"));
}

free(PATH);
PATH = NULL;
return (tokens);

}

/**
 * check_file - checks if exists a file, if it is not a dairectory and
 * if it has excecution permisions for permisions.
 * @full_path: pointer to the full file name
 * Return: 0 on success, or error code if it exists.
 */

int check_file(char *full_path)
{
struct stat sb;

if (stat(full_path, &sb) != -1)
{
if (S_ISDIR(sb.st_mode) ||  access(full_path, X_OK))
{
errno = 126;
return (126);
}
return (0);
}

errno = 127;
return (127);
}
