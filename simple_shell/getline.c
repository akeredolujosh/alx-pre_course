#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len) /* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		p = buf + i; /* get pointer for return */

		check_chain(info, buf, &j, i, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (r); /* return length of buffer from _getline() */
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: number of bytes read, -1 on failure or EOF
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t buf_pos, buf_len;
	size_t new_len;
	ssize_t bytes_read;
	char *new_ptr, *newline_pos, *cur_pos;

	cur_pos = *ptr;
	if (cur_pos && length)
		new_len = *length;
	else
		new_len = 0;
	/* If we've reached the end of the buffer, read more bytes from stdin */
	if (buf_pos == buf_len)
	{
		buf_pos = buf_len = 0;
		bytes_read = read_buf(info, buf, &buf_len);
		if (bytes_read < 0) /* Read error */
			return (-1);
		else if (bytes_read == 0 && buf_len == 0) /* End of input */
			return (-1);
	}
	/* Search for newline character in buffer */
	newline_pos = memchr(buf + buf_pos, '\n', buf_len - buf_pos);
	if (newline_pos) /* Newline character found */
		new_len += (size_t)(newline_pos - (buf + buf_pos)) + 1;
	else /* No newline character found */
		new_len += buf_len - buf_pos;

	new_ptr = _realloc(cur_pos, *length, new_len + 1);
	if (!new_ptr) /* Memory allocation error */
		return (cur_pos ? free(cur_pos), -1 : -1);
	if (!cur_pos) /* Allocate new buffer */
		new_ptr[0] = '\0';
	/* Copy buffer contents into new_ptr */
	strncat(new_ptr, buf + buf_pos, new_len - (cur_pos ? *length : 0));
	buf_pos += new_len - (cur_pos ? *length : 0);
	if (length)
		*length = new_len;
	*ptr = new_ptr;
	return (new_len);
}
