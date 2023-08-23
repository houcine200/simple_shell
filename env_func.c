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
int _setenv(const char *name, const char *value, int overwrite)
{
	char *new_var;
	int i;

	if (!name || !value)
		return (-1);

	for (i = 0; environ[i]; i++)
	{
		if (_strncmp(environ[i], name, _strlen(name)) == 0)
		{
			if (overwrite)
			{
				new_var = malloc(_strlen(name) + _strlen(value) + 2);
				_strcpy(new_var, name);
				_strcat(new_var, "=");
				_strcat(new_var, value);
				environ[i] = new_var;
				return (0);
			}
			return (0);
		}
	}
	new_var = malloc(_strlen(name) + _strlen(value) + 2);
	_strcpy(new_var, name);
	_strcat(new_var, "=");
	_strcat(new_var, value);
	environ[i] = new_var;
	environ[i + 1] = NULL;
	return (0);
}

int _unsetenv(const char *name)
{
	int i, j = 0;

	if (!name || name[0] == '\0' || strchr(name, '=') != NULL)
		return (-1);

	for (i = 0; environ[i]; i++)
	{
		if (_strncmp(environ[i], name, _strlen(name)) == 0
				&& environ[i][_strlen(name)] == '=')
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
