#include <stdio.h>
#include "input.h"
#include "rc.h"
#include <sh4a/input/keypad.h>

rcvar_t joy_exports[] =
{
	RCV_END
};

/* {scancode, localcode, last state (1 = pressed, 0 = not pressed)}*/
int keymap[][3] = {
	{ KEY_POWER, K_ESC, 0 },
	{ KEY_DOWN, K_DOWN, 0},
	{ KEY_UP, K_UP, 0},
	{ KEY_RIGHT, K_RIGHT, 0},
	{ KEY_LEFT, K_LEFT, 0},
	{ KEY_SHIFT, K_SHIFT, 0},
	{ KEY_BACKSPACE, K_BS, 0},
	{ KEY_SYMBOL, K_SLASH, 0},
	{ KEY_PAGE_UP, K_PRIOR, 0},
	{ KEY_PAGE_DOWN, K_NEXT, 0},
	{ KEY_ENTER, K_ENTER, 0},
	{ KEY_BACK, K_DEL, 0},
	{ KEY_HISTORY, K_SYSRQ, 0},
	{ KEY_ZOOM, K_PAUSE, 0},
	{ KEY_JUMP, K_SCROLL, 0},
	{ KEY_AUDIO, K_NUMLOCK, 0},
	{ KEY_CHAR_A, 'a', 0},
	{ KEY_CHAR_B, 'b', 0},
	{ KEY_CHAR_C, 'c', 0},
	{ KEY_CHAR_D, 'd', 0},
	{ KEY_CHAR_E, 'e', 0},
	{ KEY_CHAR_F, 'f', 0},
	{ KEY_CHAR_G, 'g', 0},
	{ KEY_CHAR_H, 'h', 0},
	{ KEY_CHAR_I, 'i', 0},
	{ KEY_CHAR_J, 'j', 0},
	{ KEY_CHAR_K, 'k', 0},
	{ KEY_CHAR_L, 'l', 0},
	{ KEY_CHAR_M, 'm', 0},
	{ KEY_CHAR_N, 'n', 0},
	{ KEY_CHAR_O, 'o', 0},
	{ KEY_CHAR_P, 'p', 0},
	{ KEY_CHAR_Q, 'q', 0},
	{ KEY_CHAR_R, 'r', 0},
	{ KEY_CHAR_S, 's', 0},
	{ KEY_CHAR_T, 't', 0},
	{ KEY_CHAR_U, 'u', 0},
	{ KEY_CHAR_V, 'v', 0},
	{ KEY_CHAR_W, 'w', 0},
	{ KEY_CHAR_X, 'x', 0},
	{ KEY_CHAR_Y, 'y', 0},
	{ KEY_CHAR_Z, 'z', 0},
	{ KEY_FUNC_1, K_F1, 0},
	{ KEY_FUNC_2, K_F2, 0},
	{ KEY_FUNC_3, K_F3, 0},
	{ KEY_FUNC_4, K_F4, 0},
	{ KEY_FUNC_5, K_F5, 0},
	{ KEY_FUNC_6, K_F6, 0},
	{ KEY_FUNC_7, K_F7, 0},
	{ KEY_FUNC_8, K_F8, 0},
	{ 0, 0, 0 }
};

void ev_poll() {
	event_t ev;
	int i, state;
	for (i = 0; keymap[i][0]; ++i) {
		state = !!get_key_state(keymap[i][0]);
		if (state != keymap[i][2]) {
			keymap[i][2] = state;
			ev.code = keymap[i][1];
			ev.type = (state ? EV_PRESS : EV_RELEASE);
			ev_postevent(&ev);
		}
	}
	
}
