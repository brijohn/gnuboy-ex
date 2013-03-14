/*
 * Copyright (C) 2013  Brian Johnson
 * Author: Brian Johnson <brijohn@gmail.com>
 */


/* These are wrappers that wrap the EXWord filesystem calls.
   I have implemented just enogh to work with regards to gnuboy.
   As such the are not the most robust implementation for general
   use and don't necessarily comply fully with POSIX.
*/

#include <stdio.h>
#include <stdlib.h>
#include <syscalls/syscalls.h>

typedef struct _file {
	int fd;
	int eof;
	unsigned long pos;
} FILE;

FILE * fopen(const char *path, const char *mode)
{
	int ret;
	FILE * f;
	if (path == NULL)
		return NULL;
	f = malloc(sizeof(FILE));
	if (f) {
		f->eof = f->pos = 0;
		if (mode[0] == 'w') {
			sys_delete(path);
			ret = sys_create(path, 1);
			if (ret >= 0) {
				ret = sys_open(path, FILE_WR);
				f->fd = ret;
				if (ret < 0) {
					sys_delete(path);
					free(f);
					f = NULL;
				}
			} else {
				free(f);
				f = NULL;
			}
		} else if (mode[0] == 'r') {
			ret = sys_open(path, FILE_RD);
			f->fd = ret;
			if (ret < 0) {
				free(f);
				f = NULL;
			}
		}
	}
	return f;
}

int fclose(FILE *fp)
{
	sys_close(fp->fd);
	free(fp);
	return 0;
}

int fseek(FILE *stream, long offset, int whence)
{
	unsigned long pos;
	FILE * f = stream;
	if (whence == SEEK_SET) {
		pos = (unsigned long)offset;
	} else if (whence == SEEK_CUR) {
		pos = f->pos + offset;
	} else if (whence == SEEK_END) {
		pos = sys_get_filesize(f->fd) + offset;
	}
	f->pos = pos;
	return 0;
}

unsigned long fread(void *ptr, unsigned long size, unsigned long nmemb, FILE *stream)
{
	int fd = stream->fd;
	unsigned long bytes = size * nmemb;
	sys_seek(fd, stream->pos, 0);
	int read = sys_read(fd, ptr, bytes);
	if (read < 0)
		read = 0;
	stream->pos += read;
	if (nmemb != (read / size))
		stream->eof = 1;
	return read / size;
}

unsigned long fwrite(const void *ptr, unsigned long size, unsigned long nmemb, FILE *stream)
{
	int fd = stream->fd;
	unsigned long bytes = size * nmemb;
	int written = sys_write(fd, ptr, bytes);
	if (written < 0)
		return 0;
	return written / size;
}

char *fgets(char *s, int size, FILE *stream)
{
	char buffer[512];
	char *p;
	int i;
	int read, bytes;
	int fd = stream->fd;
	if (size <= 0)
		goto error;
	p = s;
	while (size != 0) {
		bytes = (size < 512 ? size : 512);
		read = fread(buffer, 1, bytes, stream);
		if (read == 0 && bytes != 0) {
			stream->eof = 1;
			goto error;
		}
		for (i = 0; i < read; ++i) {
			--size;
			if ((*p++ = buffer[i]) == '\n') {
				fseek(stream, -(read - i - 1), 1);
				if (-(read - i - 1) != 0)
					stream->eof = 0;
				goto eol;
			}
		}
	}
eol:
	if (p > s) {
		*p = 0;
		return s;
	}
error:
	return 0;
}

int feof(FILE *stream)
{
	return stream->eof;
}

int fileno(FILE *stream)
{
	return stream->fd;
}
