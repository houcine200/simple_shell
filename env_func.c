#include "header.h"

/**
 * execute_env - Execute the "env" built-in command
 */

void execute_env(void)
{
	int i;
	char **env = environ;

	for (i = 0; env[i] != NULL; i++)
	{
		_puts(env[i]);

	}
}

/**
 * execute_setenv - Execute the "setenv" built-in command
 * @args: Array of arguments containing variable name and value
 */

void execute_setenv(char **args)
{
	if (args[1] == NULL || args[2] == NULL)
	{
		write(STDERR_FILENO, "Usage: setenv VARIABLE VALUE\n",
				_strlen("Usage: setenv VARIABLE VALUE\n"));
		return;
	}
	if (setenv(args[1], args[2], 1) != 0)
	{
		perror("setenv");
	}
}

/**
 * execute_unsetenv - Execute the "unsetenv" built-in command
 * @args: Array of arguments containing variable name to unset
 */

void execute_unsetenv(char **args)
{
	if (args[1] == NULL)
	{
		write(STDERR_FILENO, "Usage: unsetenv VARIABLE\n",
				_strlen("Usage: unsetenv VARIABLE\n"));
		return;
	}

	if (unsetenv(args[1]) != 0)
	{
		perror("unsetenv");
	}
}

/**
 * _setenv - Set a new environment variable or modify an existing one
 * @var_name: The name of the variable to set
 * @var_value: The value to set for the variable
 * @flag_overwrite: Flag to determine
 * if overwriting an existing variable is allowed
 * Return: 0 on success, -1 on failure
 */
int _setenv(const char *var_name, const char *var_value, int flag_overwrite)
{
	char *new_var;
	int i;

	if (!var_name || !var_value)
		return (-1);

	for (i = 0; environ[i]; i++)
	{
		if (_strncmp(environ[i], var_name, _strlen(var_name)) == 0)
		{
			if (flag_overwrite)
			{
				new_var = malloc(_strlen(var_name) + _strlen(var_value) + 2);
				_strcpy(new_var, var_name);
				_strcat(new_var, "=");
				_strcat(new_var, var_value);
				environ[i] = new_var;
				return (0);
			}
			return (0);
		}
	}
	new_var = malloc(_strlen(var_name) + _strlen(var_value) + 2);
	_strcpy(new_var, var_name);
	_strcat(new_var, "=");
	_strcat(new_var, var_value);
	environ[i] = new_var;
	environ[i + 1] = NULL;
	return (0);
}

/**
 * _unsetenv - Remove an environment variable
 * @var_name: The name of the variable to remove
 * Return: 0 on success, -1 on failure
 */

int _unsetenv(const char *var_name)
{
	int i, j = 0;

	if (var_name == NULL || var_name[0] == '\0' || strchr(var_name, '=') != NULL)
		return (-1);

	for (i = 0; environ[i] != NULL; i++)
	{
		if (_strncmp(environ[i], var_name, _strlen(var_name)) == 0
				&& environ[i][_strlen(var_name)] == '=')
		{
			free(environ[i]);

			for (j = i; environ[j] != NULL; j++)
			{
				environ[j] = environ[j + 1];
			}

			return (0);
		}
	}

	return (0);
}
