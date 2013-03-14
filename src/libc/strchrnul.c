/*
 * Copyright (C) 2013  Brian Johnson
 * Author: Brian Johnson <brijohn@gmail.com>
 */

/*
 *            char * strchrnul(const char *s1, int i);
 */

#include <string.h>

char * strchrnul(const char *s1, int i)
{
  char *s = strchr(s1, i);

  return s ? s : (char *)s1 + strlen(s1);
}
