/*
 * Copyright (C) 2013  Brian Johnson
 * Author: Brian Johnson <brijohn@gmail.com>
 */

/*
 *            int isdigit(int c);
 */

int isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return 1;
	return 0;
}
