/*
 * Copyright (C) 2002     Manuel Novoa III
 * Copyright (C) 2000-2005 Erik Andersen <andersen@uclibc.org>
 *
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */


int memcmp(const void *s1, const void *s2, unsigned long n)
{
	register const unsigned char *r1 = (const unsigned char *) s1;
	register const unsigned char *r2 = (const unsigned char *) s2;

	int r = 0;

	while (n-- && ((r = ((int)(*r1++)) - *r2++) == 0));

	return r;
}

