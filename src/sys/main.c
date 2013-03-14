
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sh4a/cpg.h>
#include "rc.h"
#include "input.h"
#include "lcd.h"

#include "Version"

static char *defaultconfig[] =
{
	"bind esc quit",
	"bind sysrq reset",
	"bind up +up",
	"bind down +down",
	"bind left +left",
	"bind right +right",
	"bind z +a",
	"bind x +b",
	"bind backspace +start",
	"bind slash +select",
	"bind f1 \"set frameskip 0\"",
	"bind f2 \"set frameskip 1\"",
	"bind f3 \"set frameskip 2\"",
	"bind f4 \"set frameskip 3\"",
	"bind f5 \"set frameskip 4\"",
	"bind f8 screenshot",
	"set scale 2",
	"source gnuboy.rc",
	NULL
};

void doevents()
{
	event_t ev;
	int st;

	ev_poll();
	while (ev_getevent(&ev))
	{
		if (ev.type != EV_PRESS && ev.type != EV_RELEASE)
			continue;
		st = (ev.type != EV_RELEASE);
		rc_dokey(ev.code, st);
	}
}

static void copyright()
{
	printf("\ngnuboy " VERSION "\n");
	printf(
"Copyright (C) 2000-2001 Laguna and Gilgamesh\n"
"Portions contributed by other authors; see CREDITS for details.\n"
"\n"
"This program is free software; you can redistribute it and/or modify\n"
"it under the terms of the GNU General Public License as published by\n"
"the Free Software Foundation; either version 2 of the License, or\n"
"(at your option) any later version.\n"
"\n"
"This program is distributed in the hope that it will be useful,\n"
"but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
"GNU General Public License for more details.\n"
"\n"
"You should have received a copy of the GNU General Public License\n"
"along with this program; if not, write to the Free Software\n"
"Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.\n"
"\n");
}


int main(void *ptr)
{
	int i;
	if (*(long *)ptr == 1)
		return -1;

	log_init();
	memmgr_init();
	timer_init();

	copyright();

	init_exports();
	sys_initpath();

	for (i = 0; defaultconfig[i]; i++)
		rc_command(defaultconfig[i]);

	vid_preinit();

	select_rom();

	vid_init();
	pcm_init();
	emu_init();

	emu_reset();
	emu_run();

	loader_unload();
	memmgr_print_stats();

	log_fini();
	timer_fini();

	return -2;
}

