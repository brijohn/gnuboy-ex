/*
 * Copyright (C) 2013  Brian Johnson
 * Author: Brian Johnson <brijohn@gmail.com>
 */



#include <time.h>

#define RTC_RCR1 (*(unsigned char volatile *)0xa413fedc)
#define RTC_RSECCNT (*(unsigned char volatile *)0xa413fec2)
#define RTC_RMINCNT (*(unsigned char volatile *)0xa413fec4)
#define RTC_RHRCNT (*(unsigned char volatile *)0xa413fec6)
#define RTC_RWKCNT (*(unsigned char volatile *)0xa413fec8)
#define RTC_RDAYCNT (*(unsigned char volatile *)0xa413feca)
#define RTC_RMONCNT (*(unsigned char volatile *)0xa413fecc)
#define RTC_RYRCNT (*(unsigned short volatile *)0xa413fece)

static unsigned char bcd2bin(unsigned char bcd)
{
	return (bcd & 0xf) + (bcd >> 4) * 10;
}

static void rtc_gettime(struct tm *t)
{
	do {
		RTC_RCR1 = RTC_RCR1 & 0x6f;
		t->tm_sec =  bcd2bin(RTC_RSECCNT);
		t->tm_min =  bcd2bin(RTC_RMINCNT);
		t->tm_hour = bcd2bin(RTC_RHRCNT);
		t->tm_wday = RTC_RWKCNT;
		t->tm_mday = bcd2bin(RTC_RDAYCNT);
		t->tm_mon = bcd2bin(RTC_RMONCNT);
		t->tm_year = (bcd2bin(RTC_RYRCNT >> 8) * 100) | bcd2bin(RTC_RYRCNT & 0xff);
	} while (RTC_RCR1 & 0x80);
	t->tm_yday = 0;
	t->tm_isdst = -1;
}


/* mktime function taken from linux kernel */

static __inline__ unsigned long
my_mktime (unsigned int year, unsigned int mon,
        unsigned int day, unsigned int hour,
        unsigned int min, unsigned int sec)
{
        if (0 >= (int) (mon -= 2)) {    /* 1..12 -> 11,12,1..10 */
                mon += 12;              /* Puts Feb last since it has leap day */
                year -= 1;
        }

        return (((
                (unsigned long) (year/4 - year/100 + year/400 + 367*mon/12 + day) +
                        year*365 - 719499
            )*24 + hour /* now have hours */
          )*60 + min /* now have minutes */
        )*60 + sec; /* finally seconds */
}


time_t time(time_t *t)
{
	struct tm tm;
	time_t val;
	rtc_gettime(&tm);
	val = my_mktime(tm.tm_year, tm.tm_mon, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	if (t)
		*t = val;
	return val;
}
