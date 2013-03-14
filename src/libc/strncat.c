/*
 * Copyright (C) 2002     Manuel Novoa III
 * Copyright (C) 2000-2005 Erik Andersen <andersen@uclibc.org>
 *
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */


char *strncat(char * __restrict s1, register const char * __restrict s2,
				unsigned long n)
{
	register char *s = s1;

	while (*s++);
	--s;
	while (n && ((*s = *s2++) != 0)) {
		--n;
		++s;
	}
	*s = 0;

	return s1;
}

