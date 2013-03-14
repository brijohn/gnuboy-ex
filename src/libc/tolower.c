/*
 * Copyright (C) 2013  Brian Johnson
 * Author: Brian Johnson <brijohn@gmail.com>
 */

/*
 *            int tolower(int c);
 */

int tolower(int c)
{
	if (c >= 0x41 && c <= 0x5A) 
            c = c + 0x20;
	return c;
}

