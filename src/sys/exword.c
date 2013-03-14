#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sh4a/cpg.h>
#include <sh4a/intc.h>
#include <syscalls/syscalls.h>

void timer(void);
interrupt old_timer;

static char *media[2] = {
	"\\\\drv0\\",
	"\\\\crd0\\"
};

void timer_init(void) {
	interrupt t;
	tmu0_stop(0);
	t = set_interrupt(0x400, timer);
	if (old_timer == 0)
		old_timer = t;
	tmu0_set_priority(0, 15);
	tmu0_enable(0);
	tmu0_start(0, 0, 3000);
}

void timer_fini(void) {
	tmu0_stop(0);
	set_interrupt(0x400, old_timer);
}


void delay(uint32_t ms)
{
	uint32_t time = get_ticks();
	while (get_ticks() - time < ms);
}

void *sys_timer()
{
	unsigned long *tv;
	tv = malloc(sizeof *tv);
	*tv = get_ticks() * 1000;
	return (void *) tv;
}

int sys_elapsed(void *prev)
{
	unsigned long now, usecs;
	unsigned long *tv = (unsigned long*)prev;
	now = get_ticks() * 1000;
	usecs = now - *tv;
	*tv = now;
	return (int) usecs;
}

void sys_sleep(int us)
{
	if (us > 0)
		delay(us/1000);
}

void sys_initpath()
{
	char *buf;
	char id[10];
	unsigned long drv;
	sys_dict_info(&drv, id);
	buf = malloc(50);
	sprintf(buf, "%s:%s%s\\_USER\\:%sROMS\\", media[drv], media[drv], id, media[drv]);
	rc_setvar("rcpath", 1, &buf);
	sprintf(buf, "%sROMS\\", media[drv]);
	rc_setvar("savedir", 1, &buf);
	free(buf);
}

