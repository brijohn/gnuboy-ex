/*
 * Copyright (C) 2013  Brian Johnson
 * Author: Brian Johnson <brijohn@gmail.com>
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <syscalls/syscalls.h>
#include "logger.h"

int log_fd = -1;

static char *media[2] = {
	"\\\\drv0\\",
	"\\\\crd0\\"
};

char * log_filename(char* name)
{
	static char filename[100];
	char id[10];
	unsigned long drv;
	sys_dict_info(&drv, id);
	sprintf(filename, "%s%s\\%s", media[drv], id, name);
	return filename;
}

void log_init(void)
{
	int fd;
	char *log_file = log_filename("_USER\\gnuboy.log");
	sys_delete(log_file);
	if (sys_create(log_file, 1) < 0)
		return;
	fd = sys_open(log_file, FILE_WR);
	if (fd >= 0)
		log_fd = fd;
}

void log_fini(void)
{
	if (log_fd >= 0) {
		sys_close(log_fd);
		log_fd = -1;
	}
}

void log_write(const char *format, ...)
{
	char msg[1024];
        va_list args;       
        va_start( args, format );
	int n = vsprintf(msg, format, args);
	if (log_fd >= 0)
		sys_write(log_fd, msg, strlen(msg));
}

void die(char *format, ...)
{
	char msg[512];
	va_list args;
	va_start(args, format);
	vsprintf(msg, format, args);
	if (log_fd >= 0)
		sys_write(log_fd, msg, strlen(msg));
	exit(-2);
}
