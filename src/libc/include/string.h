
#ifndef _STRING_H
#define _STRING_H

#define NULL 0

void *memset(void *s, int c, unsigned long n);
int memcmp(const void *s1, const void *s2, unsigned long n);
void *memcpy(void *dest, const void *src, unsigned long n);

char *strdup(const char *s1);
unsigned long strlen(const char *s);
int strcmp(const char *s1, const char *s2);
char *strcpy(char *dest, const char *src);
char *strncpy(char *dest, const char *src, unsigned long n);
char *strcat(char *dest, const char *src);
char *strncat(char * s1, const char * s2, unsigned long n);
char *strchr(const char *s, int c);
char *strrchr(const char *s, int c);
char *strchrnul(const char *s, int c);
char *strpbrk(const char *s1, const char *s2);

#endif // _STRING_H
