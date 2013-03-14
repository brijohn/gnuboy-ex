
#include <stdio.h>
#include <stdlib.h>
#include <graphics/lcdc.h>
#include <syscalls/syscalls.h>

#include "gnuboy.h"
#include "fb.h"
#include "input.h"
#include "rc.h"

struct fb fb;

static char *skinfile;
static frameskip = 0;
int framecounter = 0;

rcvar_t vid_exports[] =
{
	RCV_INT("frameskip", &frameskip),
	RCV_STRING("skin", &skinfile),
        RCV_END
};


void vid_setpal(int i, int r, int g, int b)
{

}


void vid_settitle(char * title)
{
	char caption[30] = "Gnuboy EX - ";
	strncat(caption, title, 16);
	lcdc_set_vram_address((void*)0xAC200000);
	lcdc_set_window(104, 8, 320, 16);
	set_pen(create_rgb16(0, 0, 0));
	draw_rect(0, 0, 320, 16);
	set_pen(create_rgb16(0xff, 0xff, 0xff));
	render_text(0, 2, caption);
	lcdc_copy_vram();
}

void vid_set_window_size(int scale)
{
	int width, height;
	int x, y;
	width = 160 * scale;
	height = 144 * scale;
	x = (528 - width) / 2;
	y = (320 - height + 16) / 2;
	lcdc_set_vram_address((void*)0xAC202800);
	lcdc_set_window(x, y, width, height);
}

void vid_begin()
{
	vid_set_window_size(rc_getint("scale"));
	if (frameskip >= 0)
                fb.enabled = framecounter==0;
}

void vid_end()
{
	lcdc_copy_vram();
	framecounter++;
	if (framecounter > frameskip)
		framecounter = 0;
}

int load_skin() {
	unsigned short header[2];
	FILE * f = fopen(skinfile, "rb");
	if (!f) return 0;
	fread(header, 2, 2, f);
	if (header[0] != 0x2210 && header[1] != 0x140) {
		fclose(f);
		return 0;
	}
	fread((void *)0xAC200000, 528 * 320 * 2, 1, f);
	fclose(f);
	return 1;
}

#ifndef GNUBOY_NO_SCREENSHOT
static unsigned char bmp_header[] = {
/* Bitmap File Header */
	0x42, 0x4d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x46, 0x00, 0x00, 0x00,
/* Bitmap Header */
	0x28, 0x00, 0x00, 0x00, 0x40, 0x01, 0x00, 0x00,
	0xe0, 0xfe, 0xff, 0xff,	0x01, 0x00, 0x10, 0x00,
	0x03, 0x00, 0x00, 0x00, 0x00, 0xd0, 0x02, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 565 RGBA Masks */
	0x00, 0xf8, 0x00, 0x00, 0xe0, 0x07, 0x00, 0x00,
	0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

void swap32(unsigned char* buf, unsigned long dw)
{
	buf[0] = (dw & 0xff); 
	buf[1] = (dw & 0xff00) >> 8;
	buf[2] = (dw & 0xff0000) >> 16;
	buf[3] = (dw & 0xff000000) >> 24;
}


void hdr_set_wxh(unsigned long width, unsigned height) {
	unsigned char *hdr = bmp_header+14;
	swap32(hdr + 4, width);
	swap32(hdr + 8, -height);
	swap32(hdr + 20, width * height * 2);
}

int take_screenshot(char * filename, unsigned char * bmp)
{
	unsigned short data[512];
	int i, j;
	unsigned long bmp_size = (fb.w * fb.h) * 2;
	FILE * f = fopen(filename, "wb");
	if (!f)
		return 0;
	hdr_set_wxh(fb.w, fb.h);
	if (fwrite(bmp_header, sizeof(bmp_header), 1, f) != 1) {
		fclose(f);
		return 0;
	}
	for (i = 0; i < bmp_size / 1024; ++i) {
		for (j = 0; j < 1024; j+= 2) {
			data[(j / 2)] = (bmp[(i * 1024) + j + 1] << 8) | bmp[(i * 1024) + j];
		}
		if (fwrite(data, 1024, 1, f) != 1) {
			fclose(f);
			return 0;
		}	
	}
	fclose(f);
	return 1;
}

static char *media[2] = {
	"\\\\drv0\\",
	"\\\\crd0\\"
};

char * screenshot_filename(char* name)
{
	static char filename[100];
	char id[10];
	unsigned long drv;
	sys_dict_info(&drv, id);
	sprintf(filename, "%s%s\\_USER\\%s", media[drv], id, name);
	return filename;
}

int  vid_screenshot(char *filename)
{
	unsigned long drv;
	char id[10];
	char * fn = filename;
	if (fn == NULL) {
		fn = screenshot_filename("gnuboy.bmp");
	}
	printf("Saving screenshot %s...\n", fn);
	if (take_screenshot(fn, (void*)0xAC202800) == 0) {
		printf("Screenshot capture failed\n");
	}
}
#endif

void vid_init()
{
	int scale = rc_getint("scale");

	vid_set_window_size(scale);

	fb.pelsize = 2;
	fb.yuv = 0;
	fb.indexed = 0;
	fb.enabled = 1;
	fb.dirty = 0;
	fb.w = 160 * scale;
	fb.h = 144 * scale;
	fb.pitch = fb.w * fb.pelsize;
	fb.ptr = (byte *)0xAC202800;
	fb.cc[0].r = 3;  /* 8-5 (wasted bits on red) */
	fb.cc[0].l = 11; /* this is the offset to the R bits (16-5) */
	fb.cc[1].r = 2;  /* 8-6 (wasted bits on green) */
	fb.cc[1].l = 5;  /* This is the offset to the G bits (16-5-6) */
	fb.cc[2].r = 3;  /* 8-5 (wasted bits on red) */
	fb.cc[2].l = 0;  /* This is the offset to the B bits (16-5-6-5) */

	set_pen(create_rgb16(0, 0, 0));
	draw_rect(0, 0, fb.w, fb.h);
	lcdc_copy_vram();
}

void vid_preinit()
{
	graphics_init(528, 320, (void*)0xAC200000);
	set_pen(create_rgb16(0, 0, 0));
	if (!load_skin())
		draw_rect(0, 0, 528, 320);
	lcdc_copy_vram();
}
