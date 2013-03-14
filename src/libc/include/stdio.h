
#ifndef _STDIO_H
#define _STDIO_H

#include <stdarg.h>
#include "../logger.h"

typedef struct _file FILE;
#define SEEK_SET 0
#define SEEK_END 2
#define SEEK_CUR 1

FILE *fopen(const char *path, const char *mode);
int fclose(FILE *fp);
unsigned long fread(void *ptr, unsigned long size, unsigned long nmemb, FILE *stream);
unsigned long fwrite(const void *ptr, unsigned long size, unsigned long nmemb, FILE *stream);
char *fgets(char *s, int size, FILE *stream);
int fseek(FILE *stream, long offset, int whence);
int fileno(FILE *stream);
int feof(FILE *stream);


#define fflush(x)
#define printf log_write
int sprintf(char *str, const char *format, ...);
int vsprintf(char *str, const char *format, va_list args);

#endif // _STDIO_H
