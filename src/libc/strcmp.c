/*
 * Copyright (C) 2002     Manuel Novoa III
 * Copyright (C) 2000-2005 Erik Andersen <andersen@uclibc.org>
 *
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */


int strcmp(register const char *s1, register const char *s2)
{
	int r;

	while (((r = ((int)(*((unsigned char *)s1))) - *((unsigned char *)s2++))
			== 0) && *s1++);

	return r;
}
