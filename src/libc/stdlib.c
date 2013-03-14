/*
 * Copyright (C) 2013  Brian Johnson
 * Author: Brian Johnson <brijohn@gmail.com>
 */


static unsigned int lastrandom = 0x12345678;
	
void srand(unsigned int seed)
{
	lastrandom = seed;
}

int rand(void)
{
	lastrandom = 0x41C64E6D*lastrandom + 0x3039;
	return lastrandom >> 16;
}

int atoi(const char *s)
{
	int a = 0;
	if (*s == '0')
	{
		s++;
		if (*s == 'x' || *s == 'X')
		{
			s++;
			while (*s)
			{
				if (isdigit(*s))
					a = (a<<4) + *s - '0';
				else if (strchr("ABCDEF", *s))
					a = (a<<4) + *s - 'A' + 10;
				else if (strchr("abcdef", *s))
					a = (a<<4) + *s - 'a' + 10;
				else return a;
				s++;
			}
			return a;
		}
		while (*s)
		{
			if (strchr("01234567", *s))
				a = (a<<3) + *s - '0';
			else return a;
			s++;
		}
		return a;
	}
	if (*s == '-')
	{
		s++;
		for (;;)
		{
			if (isdigit(*s))
				a = (a*10) + *s - '0';
			else return -a;
			s++;
		}
	}
	while (*s)
	{
		if (isdigit(*s))
			a = (a*10) + *s - '0';
		else return a;
		s++;
	}
	return a;
}
