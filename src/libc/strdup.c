/*
 * Copyright (C) 2002     Manuel Novoa III
 * Copyright (C) 2000-2005 Erik Andersen <andersen@uclibc.org>
 *
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */

#include <stdlib.h>

char *strdup(register const char *s1)
{
	register char *s;
	register unsigned long l = (strlen(s1) + 1) * sizeof(char);

	if ((s = malloc(l)) != NULL) {
		memcpy(s, s1, l);
	}

	return s;
}
