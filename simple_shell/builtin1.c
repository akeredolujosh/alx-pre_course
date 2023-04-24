#include "shell.h"

/**
* _myhistory - displays the history list, one command
* by line, preceded with line numbers, starting at 0.
* @info: Structure containing potential arguments.
* Used to maintain constant function prototype.
* Return: Always 0 This function is used to display the history
* list of commands executed in the shell.
* It takes a structure info as an argument,
* which may contain potential arguments
* for the history command. The function
* displays a numbered list of the previously
* executed commands, starting at 0.
* The function always returns 0, as per the function prototype.
*/
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
* unset_alias - removes an alias from the list of aliases
* @info: parameter struct
* @str: the string alias
* Return: Always 0 on success, 1 on error
* This function is used to remove an alias from the
* list of aliases maintained by the shell.
* It takes a structure info as an argument,
* which contains information about the aliases.
* The str argument is the name of the alias to be removed. The
* function returns 0 on success and 1 on error.
*/
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
* set_alias - adds an alias to the list of aliases
* @info: parameter struct
* @str: the string alias
* Return: Always 0 on success, 1 on error
* This function is used to add an alias to the
* list of aliases maintained by
* the shell. It takes a structure info as an argument,
* which contains information about the aliases.
* The str argument is the alias to be added, in the format
* "alias_name='command'". The function returns 0 on success and 1 on error.
*/
int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
* print_alias - prints an alias string
* @node: the alias node
* Return: Always 0 on success, 1 on error
* This function is used to print the string representation of an alias node.
* It takes an alias node as an argument and prints the alias in the format
* "alias_name='command'". The function returns 0 on success and 1 on error.
*/
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
* _myalias - implements the functionality of the alias command
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: Always 0
* This function is used to implement the
* functionality of the alias command.
* It takes a structure info as an argument,
* which may contain potential arguments
* for the alias command. The function allows
* the user to create, modify, and list
* aliases for commands. The function returns 0 on success.
*/
int _myalias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
