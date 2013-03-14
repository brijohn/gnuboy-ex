/*
 * Copyright (C) 2002     Manuel Novoa III
 * Copyright (C) 2000-2005 Erik Andersen <andersen@uclibc.org>
 *
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */

int strcasecmp(register const char *s1, register const char *s2)
{
	int r = 0;

	while ( ((s1 == s2) ||
			 !(r = ((int)( tolower(*((unsigned char *)s1))))
			   - tolower(*((unsigned char *)s2))))
			&& (++s2, *s1++));

	return r;
}
