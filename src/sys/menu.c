#include <graphics/text.h>
#include <sh4a/input/keypad.h>
#include <syscalls/syscalls.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ITEMS_DISPLAYED ((288/24)-1)

const unsigned char iso12x22[] = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 0 */
   0x00, 0x00, 0x06, 0x00, 0x0f, 0x00, 0x0f, 0x00, 
   0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 
   0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x06, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 1 */
   0x00, 0x00, 0x19, 0x80, 0x19, 0x80, 0x19, 0x80, 
   0x19, 0x80, 0x19, 0x80, 0x19, 0x80, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 2 */
   0x00, 0x00, 0x00, 0x00, 0x0c, 0xc0, 0x0c, 0xc0, 
   0x0c, 0xc0, 0x3f, 0xe0, 0x3f, 0xe0, 0x19, 0x80, 
   0x19, 0x80, 0x19, 0x80, 0x19, 0x80, 0x7f, 0xc0, 
   0x7f, 0xc0, 0x33, 0x00, 0x33, 0x00, 0x33, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 3 */
   0x00, 0x00, 0x0a, 0x00, 0x1f, 0x80, 0x6a, 0xc0, 
   0xca, 0x60, 0xca, 0x20, 0xca, 0x00, 0x7a, 0x00, 
   0x3f, 0x80, 0x0b, 0xc0, 0x0a, 0x60, 0x8a, 0x60, 
   0xca, 0x60, 0x6a, 0xc0, 0x3f, 0x00, 0x0a, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 4 */
   0x00, 0x00, 0x00, 0x00, 0x38, 0xc0, 0x4c, 0xc0, 
   0x65, 0x80, 0x39, 0x80, 0x03, 0x00, 0x03, 0x00, 
   0x06, 0x00, 0x06, 0x00, 0x0c, 0x00, 0x0c, 0x00, 
   0x19, 0xc0, 0x1a, 0x60, 0x33, 0x20, 0x31, 0xc0, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 5 */
   0x00, 0x00, 0x0e, 0x00, 0x13, 0x00, 0x21, 0x80, 
   0x31, 0x80, 0x31, 0x00, 0x1a, 0x00, 0x1c, 0x00, 
   0x1e, 0x00, 0x27, 0x00, 0x63, 0x20, 0x61, 0xa0, 
   0x60, 0xc0, 0x70, 0xc0, 0x39, 0x60, 0x1e, 0x20, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 6 */
   0x00, 0x00, 0x0c, 0x00, 0x1e, 0x00, 0x1e, 0x00, 
   0x06, 0x00, 0x06, 0x00, 0x0c, 0x00, 0x18, 0x00, 
   0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 7 */
   0x00, 0x00, 0x01, 0x80, 0x03, 0x00, 0x06, 0x00, 
   0x06, 0x00, 0x0c, 0x00, 0x0c, 0x00, 0x0c, 0x00, 
   0x0c, 0x00, 0x0c, 0x00, 0x0c, 0x00, 0x0c, 0x00, 
   0x06, 0x00, 0x06, 0x00, 0x03, 0x00, 0x01, 0x80, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 8 */
   0x00, 0x00, 0x18, 0x00, 0x0c, 0x00, 0x06, 0x00, 
   0x06, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 
   0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 
   0x06, 0x00, 0x06, 0x00, 0x0c, 0x00, 0x18, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 9 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x0f, 0x00, 0x06, 0x00, 0x66, 0x60, 0x76, 0xe0, 
   0x19, 0x80, 0x00, 0x00, 0x19, 0x80, 0x76, 0xe0, 
   0x66, 0x60, 0x06, 0x00, 0x0f, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 10 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 
   0x06, 0x00, 0x7f, 0xe0, 0x7f, 0xe0, 0x06, 0x00, 
   0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 11 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x0c, 0x00, 0x1e, 0x00, 0x1e, 0x00, 
   0x06, 0x00, 0x06, 0x00, 0x0c, 0x00, 0x18, 0x00, 
   0x10, 0x00, 0x00, 0x00,   /* 12 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x7f, 0xe0, 0x7f, 0xe0, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 13 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x0c, 0x00, 0x1e, 0x00, 0x1e, 0x00, 0x0c, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 14 */
   0x00, 0x00, 0x00, 0x60, 0x00, 0xc0, 0x00, 0xc0, 
   0x01, 0x80, 0x01, 0x80, 0x03, 0x00, 0x03, 0x00, 
   0x06, 0x00, 0x06, 0x00, 0x0c, 0x00, 0x0c, 0x00, 
   0x18, 0x00, 0x18, 0x00, 0x30, 0x00, 0x30, 0x00, 
   0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 15 */
   0x00, 0x00, 0x07, 0x80, 0x1f, 0xc0, 0x20, 0xc0, 
   0x20, 0x60, 0x61, 0x60, 0x62, 0x60, 0x62, 0x60, 
   0x64, 0x60, 0x64, 0x60, 0x68, 0x60, 0x68, 0x60, 
   0x60, 0x40, 0x30, 0x40, 0x3f, 0x80, 0x1e, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 16 */
   0x00, 0x00, 0x02, 0x00, 0x06, 0x00, 0x0e, 0x00, 
   0x1e, 0x00, 0x36, 0x00, 0x46, 0x00, 0x06, 0x00, 
   0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 
   0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x3f, 0xc0, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 17 */
   0x00, 0x00, 0x0f, 0x00, 0x1f, 0x80, 0x21, 0xc0, 
   0x40, 0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0x80, 
   0x01, 0x80, 0x03, 0x00, 0x06, 0x00, 0x0c, 0x00, 
   0x18, 0x00, 0x30, 0x20, 0x7f, 0xe0, 0x7f, 0xc0, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 18 */
   0x00, 0x00, 0x0f, 0x80, 0x1f, 0xc0, 0x20, 0xe0, 
   0x40, 0x60, 0x00, 0x60, 0x00, 0xc0, 0x07, 0x80, 
   0x0f, 0xc0, 0x00, 0xe0, 0x00, 0x60, 0x00, 0x60, 
   0x40, 0x60, 0x60, 0x40, 0x3f, 0x80, 0x1f, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 19 */
   0x00, 0x00, 0x18, 0x00, 0x18, 0x00, 0x18, 0x00, 
   0x19, 0x80, 0x19, 0x80, 0x19, 0x80, 0x11, 0x80, 
   0x31, 0x80, 0x31, 0x80, 0x21, 0x80, 0x7f, 0xe0, 
   0x7f, 0xc0, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 20 */
   0x00, 0x00, 0x0f, 0xe0, 0x0f, 0xe0, 0x10, 0x00, 
   0x10, 0x00, 0x20, 0x00, 0x3f, 0x80, 0x31, 0xc0, 
   0x00, 0xe0, 0x00, 0x60, 0x00, 0x60, 0x00, 0x60, 
   0x40, 0x60, 0x60, 0x60, 0x30, 0xc0, 0x1f, 0x80, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 21 */
   0x00, 0x00, 0x03, 0xc0, 0x0e, 0x00, 0x18, 0x00, 
   0x30, 0x00, 0x30, 0x00, 0x60, 0x00, 0x67, 0x80, 
   0x6f, 0xc0, 0x70, 0xe0, 0x60, 0x60, 0x60, 0x60, 
   0x60, 0x60, 0x70, 0x40, 0x3f, 0x80, 0x1f, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 22 */
   0x00, 0x00, 0x1f, 0xe0, 0x3f, 0xe0, 0x60, 0x60, 
   0x00, 0x40, 0x00, 0x40, 0x00, 0xc0, 0x00, 0x80, 
   0x01, 0x80, 0x01, 0x00, 0x03, 0x00, 0x02, 0x00, 
   0x02, 0x00, 0x06, 0x00, 0x04, 0x00, 0x04, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 23 */
   0x00, 0x00, 0x1f, 0x80, 0x31, 0xc0, 0x60, 0xe0, 
   0x60, 0x60, 0x60, 0x60, 0x30, 0xc0, 0x19, 0x80, 
   0x0f, 0x00, 0x19, 0x80, 0x30, 0xc0, 0x60, 0x60, 
   0x60, 0x60, 0x70, 0x60, 0x38, 0xc0, 0x1f, 0x80, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 24 */
   0x00, 0x00, 0x0f, 0x80, 0x11, 0xc0, 0x20, 0xe0, 
   0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x70, 0xe0, 
   0x3f, 0x60, 0x1e, 0x60, 0x00, 0x60, 0x00, 0xc0, 
   0x00, 0xc0, 0x01, 0x80, 0x07, 0x00, 0x3c, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 25 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x0c, 0x00, 0x1e, 0x00, 0x1e, 0x00, 
   0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 
   0x1e, 0x00, 0x1e, 0x00, 0x0c, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 26 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 
   0x1e, 0x00, 0x1e, 0x00, 0x0c, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x0c, 0x00, 0x1e, 0x00, 0x1e, 0x00, 
   0x06, 0x00, 0x06, 0x00, 0x0c, 0x00, 0x18, 0x00, 
   0x10, 0x00, 0x00, 0x00,   /* 27 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x60, 0x01, 0xc0, 0x03, 0x80, 0x0e, 0x00, 
   0x38, 0x00, 0x70, 0x00, 0x38, 0x00, 0x0e, 0x00, 
   0x03, 0x80, 0x01, 0xc0, 0x00, 0x60, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 28 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xe0, 
   0x7f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xe0, 
   0x7f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 29 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x60, 0x00, 0x38, 0x00, 0x1c, 0x00, 0x07, 0x00, 
   0x01, 0xc0, 0x00, 0xe0, 0x01, 0xc0, 0x07, 0x00, 
   0x1c, 0x00, 0x38, 0x00, 0x60, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 30 */
   0x00, 0x00, 0x0f, 0x00, 0x1b, 0x80, 0x21, 0xc0, 
   0x20, 0xc0, 0x00, 0xc0, 0x00, 0x80, 0x01, 0x00, 
   0x02, 0x00, 0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x06, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 31 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x0f, 0x80, 0x10, 0xc0, 0x20, 0x60, 0x40, 0x20, 
   0x47, 0x20, 0x49, 0x20, 0x49, 0x20, 0x4d, 0x20, 
   0x47, 0xc0, 0x60, 0x00, 0x30, 0x60, 0x1f, 0x80, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 32 */
   0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x06, 0x00, 
   0x0b, 0x00, 0x0b, 0x00, 0x09, 0x00, 0x11, 0x80, 
   0x11, 0x80, 0x10, 0x80, 0x3f, 0xc0, 0x20, 0xc0, 
   0x20, 0x40, 0x40, 0x60, 0x40, 0x60, 0xe0, 0xf0, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 33 */
   0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x61, 0x80, 
   0x60, 0xc0, 0x60, 0xc0, 0x60, 0xc0, 0x60, 0x80, 
   0x7f, 0x80, 0x61, 0xc0, 0x60, 0x60, 0x60, 0x60, 
   0x60, 0x60, 0x60, 0x60, 0x60, 0xc0, 0xff, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 34 */
   0x00, 0x00, 0x00, 0x00, 0x0f, 0xc0, 0x10, 0x60, 
   0x20, 0x20, 0x20, 0x00, 0x60, 0x00, 0x60, 0x00, 
   0x60, 0x00, 0x60, 0x00, 0x60, 0x00, 0x60, 0x00, 
   0x30, 0x00, 0x30, 0x20, 0x18, 0x40, 0x0f, 0x80, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 35 */
   0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x61, 0xc0, 
   0x60, 0xc0, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 
   0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 
   0x60, 0x60, 0x60, 0x40, 0x61, 0x80, 0xfe, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 36 */
   0x00, 0x00, 0x00, 0x00, 0x7f, 0xc0, 0x30, 0xc0, 
   0x30, 0x40, 0x30, 0x00, 0x30, 0x00, 0x30, 0x80, 
   0x3f, 0x80, 0x30, 0x80, 0x30, 0x00, 0x30, 0x00, 
   0x30, 0x00, 0x30, 0x20, 0x30, 0x20, 0x7f, 0xe0, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 37 */
   0x00, 0x00, 0x00, 0x00, 0x7f, 0xc0, 0x30, 0xc0, 
   0x30, 0x40, 0x30, 0x00, 0x30, 0x00, 0x30, 0x80, 
   0x3f, 0x80, 0x30, 0x80, 0x30, 0x00, 0x30, 0x00, 
   0x30, 0x00, 0x30, 0x00, 0x30, 0x00, 0x78, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 38 */
   0x00, 0x00, 0x00, 0x00, 0x0f, 0xc0, 0x10, 0x60, 
   0x20, 0x20, 0x20, 0x00, 0x60, 0x00, 0x60, 0x00, 
   0x60, 0x00, 0x60, 0x00, 0x61, 0xf0, 0x60, 0x60, 
   0x60, 0x60, 0x30, 0x60, 0x1c, 0x60, 0x0f, 0x80, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 39 */
   0x00, 0x00, 0x00, 0x00, 0xf0, 0xf0, 0x60, 0x60, 
   0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 
   0x7f, 0xe0, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 
   0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0xf0, 0xf0, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 40 */
   0x00, 0x00, 0x00, 0x00, 0x1f, 0x80, 0x06, 0x00, 
   0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 
   0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 
   0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x1f, 0x80, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 41 */
   0x00, 0x00, 0x00, 0x00, 0x1f, 0x80, 0x06, 0x00, 
   0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 
   0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 
   0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 
   0x06, 0x00, 0x06, 0x00, 0x04, 0x00, 0x68, 0x00, 
   0x30, 0x00, 0x00, 0x00,   /* 42 */
   0x00, 0x00, 0x00, 0x00, 0xf0, 0xe0, 0x61, 0x80, 
   0x63, 0x00, 0x66, 0x00, 0x6c, 0x00, 0x78, 0x00, 
   0x78, 0x00, 0x7c, 0x00, 0x6e, 0x00, 0x67, 0x00, 
   0x63, 0x80, 0x61, 0xc0, 0x60, 0xe0, 0xf0, 0x70, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 43 */
   0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x30, 0x00, 
   0x30, 0x00, 0x30, 0x00, 0x30, 0x00, 0x30, 0x00, 
   0x30, 0x00, 0x30, 0x00, 0x30, 0x00, 0x30, 0x00, 
   0x30, 0x00, 0x30, 0x20, 0x30, 0x20, 0x7f, 0xe0, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 44 */
   0x00, 0x00, 0x00, 0x00, 0xe0, 0x70, 0x60, 0xe0, 
   0x70, 0xe0, 0x70, 0xe0, 0x70, 0xe0, 0x59, 0x60, 
   0x59, 0x60, 0x59, 0x60, 0x4d, 0x60, 0x4e, 0x60, 
   0x4e, 0x60, 0x44, 0x60, 0x44, 0x60, 0xe4, 0xf0, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 45 */
   0x00, 0x00, 0x00, 0x00, 0xc0, 0x70, 0x60, 0x20, 
   0x70, 0x20, 0x78, 0x20, 0x58, 0x20, 0x4c, 0x20, 
   0x46, 0x20, 0x47, 0x20, 0x43, 0x20, 0x41, 0xa0, 
   0x40, 0xe0, 0x40, 0xe0, 0x40, 0x60, 0xe0, 0x30, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 46 */
   0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x11, 0xc0, 
   0x20, 0xc0, 0x20, 0x60, 0x60, 0x60, 0x60, 0x60, 
   0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 
   0x20, 0x40, 0x30, 0x40, 0x18, 0x80, 0x0f, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 47 */
   0x00, 0x00, 0x00, 0x00, 0x7f, 0x80, 0x30, 0xc0, 
   0x30, 0x60, 0x30, 0x60, 0x30, 0x60, 0x30, 0x40, 
   0x3f, 0x80, 0x30, 0x00, 0x30, 0x00, 0x30, 0x00, 
   0x30, 0x00, 0x30, 0x00, 0x30, 0x00, 0x78, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 48 */
   0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x11, 0xc0, 
   0x20, 0xc0, 0x20, 0x60, 0x60, 0x60, 0x60, 0x60, 
   0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 
   0x30, 0x40, 0x38, 0x80, 0x1f, 0x00, 0x0e, 0x00, 
   0x1f, 0x00, 0x23, 0x90, 0x01, 0xe0, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 49 */
   0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x61, 0x80, 
   0x60, 0xc0, 0x60, 0xc0, 0x60, 0xc0, 0x60, 0x80, 
   0x7f, 0x00, 0x7c, 0x00, 0x6e, 0x00, 0x67, 0x00, 
   0x63, 0x80, 0x61, 0xc0, 0x60, 0xe0, 0xf0, 0x70, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 50 */
   0x00, 0x00, 0x00, 0x00, 0x0f, 0xa0, 0x30, 0xe0, 
   0x60, 0x60, 0x60, 0x20, 0x70, 0x00, 0x3c, 0x00, 
   0x1e, 0x00, 0x07, 0x80, 0x01, 0xc0, 0x00, 0xe0, 
   0x40, 0x60, 0x60, 0x60, 0x70, 0xc0, 0x5f, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 51 */
   0x00, 0x00, 0x00, 0x00, 0x7f, 0xe0, 0x66, 0x60, 
   0x46, 0x20, 0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 
   0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 
   0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x0f, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 52 */
   0x00, 0x00, 0x00, 0x00, 0xf0, 0x70, 0x60, 0x20, 
   0x60, 0x20, 0x60, 0x20, 0x60, 0x20, 0x60, 0x20, 
   0x60, 0x20, 0x60, 0x20, 0x60, 0x20, 0x60, 0x20, 
   0x60, 0x20, 0x70, 0x40, 0x3f, 0xc0, 0x1f, 0x80, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 53 */
   0x00, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0x60, 0x40, 
   0x30, 0x80, 0x30, 0x80, 0x30, 0x80, 0x19, 0x00, 
   0x19, 0x00, 0x19, 0x00, 0x0a, 0x00, 0x0e, 0x00, 
   0x0e, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 54 */
   0x00, 0x00, 0x00, 0x00, 0xf6, 0x70, 0x66, 0x20, 
   0x66, 0x20, 0x66, 0x20, 0x76, 0x20, 0x77, 0x40, 
   0x33, 0x40, 0x37, 0x40, 0x3b, 0xc0, 0x3d, 0x80, 
   0x19, 0x80, 0x19, 0x80, 0x19, 0x80, 0x19, 0x80, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 55 */
   0x00, 0x00, 0x00, 0x00, 0xf0, 0x70, 0x60, 0x20, 
   0x30, 0x40, 0x38, 0x80, 0x18, 0x80, 0x0d, 0x00, 
   0x06, 0x00, 0x06, 0x00, 0x0b, 0x00, 0x11, 0x80, 
   0x11, 0xc0, 0x20, 0xc0, 0x40, 0x60, 0xe0, 0xf0, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 56 */
   0x00, 0x00, 0x00, 0x00, 0xf0, 0x70, 0x60, 0x20, 
   0x30, 0x40, 0x18, 0x80, 0x18, 0x80, 0x0d, 0x00, 
   0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 
   0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x0f, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 57 */
   0x00, 0x00, 0x00, 0x00, 0x3f, 0xe0, 0x30, 0xc0, 
   0x20, 0x80, 0x01, 0x80, 0x01, 0x00, 0x03, 0x00, 
   0x02, 0x00, 0x06, 0x00, 0x04, 0x00, 0x0c, 0x00, 
   0x08, 0x00, 0x18, 0x20, 0x18, 0x60, 0x3f, 0xe0, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 58 */
   0x00, 0x00, 0x0f, 0x80, 0x0f, 0x80, 0x0c, 0x00, 
   0x0c, 0x00, 0x0c, 0x00, 0x0c, 0x00, 0x0c, 0x00, 
   0x0c, 0x00, 0x0c, 0x00, 0x0c, 0x00, 0x0c, 0x00, 
   0x0c, 0x00, 0x0c, 0x00, 0x0f, 0x80, 0x0f, 0x80, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 59 */
   0x00, 0x00, 0x60, 0x00, 0x30, 0x00, 0x30, 0x00, 
   0x18, 0x00, 0x18, 0x00, 0x0c, 0x00, 0x0c, 0x00, 
   0x06, 0x00, 0x06, 0x00, 0x03, 0x00, 0x03, 0x00, 
   0x01, 0x80, 0x01, 0x80, 0x00, 0xc0, 0x00, 0xc0, 
   0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 60 */
   0x00, 0x00, 0x1f, 0x00, 0x1f, 0x00, 0x03, 0x00, 
   0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 
   0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 
   0x03, 0x00, 0x03, 0x00, 0x1f, 0x00, 0x1f, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 61 */
   0x00, 0x00, 0x04, 0x00, 0x0e, 0x00, 0x1b, 0x00, 
   0x31, 0x80, 0x60, 0xc0, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 62 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0xff, 0xf0, 0xff, 0xf0, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 63 */
   0x00, 0x00, 0x01, 0x00, 0x03, 0x00, 0x06, 0x00, 
   0x06, 0x00, 0x07, 0x80, 0x07, 0x80, 0x03, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 64 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x0f, 0x80, 0x10, 0xc0, 
   0x20, 0xc0, 0x00, 0xc0, 0x0f, 0xc0, 0x10, 0xc0, 
   0x30, 0xc0, 0x30, 0xc0, 0x39, 0xc0, 0x1e, 0x60, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 65 */
   0x00, 0x00, 0x20, 0x00, 0x60, 0x00, 0xe0, 0x00, 
   0x60, 0x00, 0x60, 0x00, 0x67, 0x80, 0x6f, 0xc0, 
   0x70, 0xe0, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 
   0x60, 0x60, 0x70, 0x60, 0x78, 0x40, 0x4f, 0x80, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 66 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x0f, 0x80, 0x31, 0xc0, 
   0x20, 0xc0, 0x60, 0x00, 0x60, 0x00, 0x60, 0x00, 
   0x60, 0x00, 0x70, 0x40, 0x39, 0x80, 0x1f, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 67 */
   0x00, 0x00, 0x00, 0x60, 0x00, 0xe0, 0x00, 0x60, 
   0x00, 0x60, 0x00, 0x60, 0x0f, 0x60, 0x31, 0xe0, 
   0x20, 0xe0, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 
   0x60, 0x60, 0x70, 0xe0, 0x39, 0x60, 0x1e, 0x70, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 68 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x0f, 0x80, 0x30, 0xc0, 
   0x60, 0x60, 0x60, 0x60, 0x7f, 0xe0, 0x60, 0x00, 
   0x60, 0x00, 0x70, 0x00, 0x38, 0x60, 0x0f, 0x80, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 69 */
   0x00, 0x00, 0x03, 0x80, 0x04, 0xc0, 0x04, 0x60, 
   0x0c, 0x00, 0x0c, 0x00, 0x0c, 0x00, 0x0c, 0x00, 
   0x3f, 0x80, 0x0c, 0x00, 0x0c, 0x00, 0x0c, 0x00, 
   0x0c, 0x00, 0x0c, 0x00, 0x0c, 0x00, 0x1e, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 70 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x1f, 0x20, 0x31, 0xe0, 
   0x60, 0xc0, 0x60, 0xc0, 0x60, 0xc0, 0x31, 0x80, 
   0x3e, 0x00, 0x60, 0x00, 0x7f, 0x80, 0x3f, 0xc0, 
   0x20, 0x60, 0x40, 0x20, 0x40, 0x20, 0x7f, 0xc0, 
   0x3f, 0x00, 0x00, 0x00,   /* 71 */
   0x00, 0x00, 0x10, 0x00, 0x30, 0x00, 0x70, 0x00, 
   0x30, 0x00, 0x30, 0x00, 0x37, 0x80, 0x39, 0xc0, 
   0x30, 0xc0, 0x30, 0xc0, 0x30, 0xc0, 0x30, 0xc0, 
   0x30, 0xc0, 0x30, 0xc0, 0x30, 0xc0, 0x79, 0xe0, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 72 */
   0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x06, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x06, 0x00, 
   0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 
   0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x1f, 0x80, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 73 */
   0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x01, 0x80, 
   0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x01, 0x80, 
   0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 
   0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 
   0x01, 0x80, 0x21, 0x80, 0x31, 0x80, 0x1b, 0x00, 
   0x0e, 0x00, 0x00, 0x00,   /* 74 */
   0x00, 0x00, 0x60, 0x00, 0xe0, 0x00, 0x60, 0x00, 
   0x60, 0x00, 0x60, 0x00, 0x61, 0xc0, 0x63, 0x00, 
   0x66, 0x00, 0x7c, 0x00, 0x78, 0x00, 0x7c, 0x00, 
   0x6e, 0x00, 0x67, 0x00, 0x63, 0x80, 0xf1, 0xe0, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 75 */
   0x00, 0x00, 0x1e, 0x00, 0x06, 0x00, 0x06, 0x00, 
   0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 
   0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 
   0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x1f, 0x80, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 76 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0xdd, 0xc0, 0x6e, 0xe0, 
   0x66, 0x60, 0x66, 0x60, 0x66, 0x60, 0x66, 0x60, 
   0x66, 0x60, 0x66, 0x60, 0x66, 0x60, 0xef, 0x70, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 77 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x27, 0x80, 0x79, 0xc0, 
   0x30, 0xc0, 0x30, 0xc0, 0x30, 0xc0, 0x30, 0xc0, 
   0x30, 0xc0, 0x30, 0xc0, 0x30, 0xc0, 0x79, 0xe0, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 78 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x0f, 0x80, 0x11, 0xc0, 
   0x20, 0xe0, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 
   0x60, 0x60, 0x70, 0x40, 0x38, 0x80, 0x1f, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 79 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0xcf, 0x80, 0x71, 0xc0, 
   0x60, 0xe0, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 
   0x60, 0x60, 0x60, 0x40, 0x78, 0x80, 0x6f, 0x00, 
   0x60, 0x00, 0x60, 0x00, 0x60, 0x00, 0x60, 0x00, 
   0xf0, 0x00, 0x00, 0x00,   /* 80 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x0f, 0x20, 0x11, 0xe0, 
   0x20, 0xe0, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 
   0x60, 0x60, 0x70, 0x60, 0x38, 0xe0, 0x1f, 0x60, 
   0x00, 0x60, 0x00, 0x60, 0x00, 0x60, 0x00, 0x60, 
   0x00, 0xf0, 0x00, 0x00,   /* 81 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x39, 0xc0, 0x5a, 0x60, 
   0x1c, 0x60, 0x18, 0x00, 0x18, 0x00, 0x18, 0x00, 
   0x18, 0x00, 0x18, 0x00, 0x18, 0x00, 0x3c, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 82 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x0f, 0x40, 0x31, 0xc0, 
   0x30, 0x40, 0x38, 0x00, 0x1e, 0x00, 0x07, 0x80, 
   0x01, 0xc0, 0x20, 0xc0, 0x38, 0xc0, 0x2f, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 83 */
   0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x04, 0x00, 
   0x0c, 0x00, 0x1c, 0x00, 0x7f, 0xc0, 0x0c, 0x00, 
   0x0c, 0x00, 0x0c, 0x00, 0x0c, 0x00, 0x0c, 0x00, 
   0x0c, 0x00, 0x0c, 0x00, 0x0e, 0x40, 0x07, 0x80, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 84 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x79, 0xe0, 0x30, 0xc0, 
   0x30, 0xc0, 0x30, 0xc0, 0x30, 0xc0, 0x30, 0xc0, 
   0x30, 0xc0, 0x30, 0xc0, 0x39, 0xc0, 0x1e, 0x60, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 85 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0xf0, 0x70, 0x60, 0x20, 
   0x30, 0x40, 0x30, 0x40, 0x18, 0x80, 0x18, 0x80, 
   0x0d, 0x00, 0x0d, 0x00, 0x06, 0x00, 0x06, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 86 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0xf6, 0x70, 0x66, 0x20, 
   0x66, 0x20, 0x66, 0x20, 0x37, 0x40, 0x3b, 0x40, 
   0x3b, 0x40, 0x19, 0x80, 0x19, 0x80, 0x19, 0x80, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 87 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0xf8, 0xf0, 0x70, 0x40, 
   0x38, 0x80, 0x1d, 0x00, 0x0e, 0x00, 0x07, 0x00, 
   0x0b, 0x80, 0x11, 0xc0, 0x20, 0xe0, 0xf1, 0xf0, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 88 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0xf0, 0xf0, 0x60, 0x20, 
   0x30, 0x40, 0x30, 0x40, 0x18, 0x80, 0x18, 0x80, 
   0x0d, 0x00, 0x0d, 0x00, 0x06, 0x00, 0x06, 0x00, 
   0x04, 0x00, 0x0c, 0x00, 0x08, 0x00, 0x38, 0x00, 
   0x70, 0x00, 0x00, 0x00,   /* 89 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x7f, 0xe0, 0x60, 0xc0, 
   0x41, 0x80, 0x03, 0x00, 0x06, 0x00, 0x0c, 0x00, 
   0x18, 0x00, 0x30, 0x20, 0x60, 0x60, 0x7f, 0xe0, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 90 */
   0x00, 0x00, 0x03, 0x80, 0x06, 0x00, 0x06, 0x00, 
   0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x0c, 0x00, 
   0x38, 0x00, 0x0c, 0x00, 0x06, 0x00, 0x06, 0x00, 
   0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x03, 0x80, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 91 */
   0x00, 0x00, 0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 
   0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 
   0x06, 0x00, 0x06, 0x00, 0x00, 0x00, 0x06, 0x00, 
   0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 
   0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 92 */
   0x00, 0x00, 0x1c, 0x00, 0x06, 0x00, 0x06, 0x00, 
   0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x03, 0x00, 
   0x01, 0xc0, 0x03, 0x00, 0x06, 0x00, 0x06, 0x00, 
   0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x1c, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 93 */
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x20, 
   0x3e, 0x60, 0x67, 0xc0, 0x43, 0x80, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00,   /* 94 */
};

struct font iso_dot_font = {
	12,
	22,
	0,
	iso12x22,
};

static char *media[2] = {
	"\\\\drv0\\",
	"\\\\crd0\\"
};

typedef struct {
  char **array;
  unsigned int used;
  unsigned int size;
} menu;

char * roms_filename(char* name)
{
	static char filename[100];
	char id[10];
	unsigned long drv;
	sys_dict_info(&drv, id);
	sprintf(filename, "%sROMS\\%s", media[drv], name);
	return filename;
}

void menu_init(menu *m, unsigned int size)
{
	m->array = malloc(size * sizeof(char *));
	m->used = 0;
	m->size = size;
}

void insert_menuitem(menu *m, char *item)
{
	if (m->used == m->size) {
		m->size *= 2;
		m->array = realloc(m->array, m->size * sizeof(char *));
	}
	m->array[m->used++] = strdup(item);
}

void menu_free(menu *m)
{
	int i;
	for (i = 0; i < m->used; ++i) {
		free(m->array[i]);
	}
	free(m->array);
	m->array = NULL;
	m->used = m->size = 0;
}

void print_menu(int start, int current, menu *m)
{
	int i;

	set_pen(create_rgb16(0xff, 0xff, 0xff));
	draw_rect(0, 0, 320, 288);
	set_pen(create_rgb16(0, 0, 0));
	draw_line(0, 0, 319, 0);
	draw_line(0, 0, 0, 287);
	draw_line(0, 287, 319, 287);
	draw_line(319, 0, 319, 287);
	draw_line(0,25,319,25);
	render_text((320-(strlen("SELECT ROM")*12))/2, 2, "SELECT ROM");
	for (i = 0; i < ITEMS_DISPLAYED && i < m->used; ++i) {
		render_text(14, ((i + 1) * 24) + 1 , m->array[start + i]);
		if ((start + i) == current) {
			invert_rect(1, ((i + 1) * 24), 318, 24);
		}
	}
	lcdc_copy_vram();
}

int show_menu(menu *m)
{
	int start = 0, current = 0, x = 0;
	int refresh = 1;
	lcdc_set_vram_address((void*)0xAC202800);
	lcdc_set_window(104, 24, 320, 288);
	set_font(&iso_dot_font);
	while(!get_key_pressed(KEY_ENTER)) {
		if (refresh) {
			print_menu(start, current, m);
			refresh = 0;
		}
		if (get_key_pressed(KEY_DOWN)) {
			if (current < m->used - 1) {
				++current; 
				++x;
				if (x >= ITEMS_DISPLAYED) { 
					x = ITEMS_DISPLAYED; 
					if (start < (m->used - ITEMS_DISPLAYED)) ++start; 
				}
				refresh = 1;
			}
		}
		if (get_key_pressed(KEY_UP)) {
			if (current > 0) {
				--current;
				--x;
				if (x <= 0) {
					x = 0; 
					if (start > 0) --start; 
				}
				refresh = 1; 
			}
		}
	}
	set_font(NULL);
	draw_rect(0, 0, 320, 288);
	lcdc_copy_vram();
	return current;
}

void select_rom()
{
	int item;
	menu m;
	char *p, *cmd;
	char line[20];
	FILE * f, *f2;
	menu_init(&m, 2);
	char *fname = roms_filename("roms.lst");
	f = fopen(fname, "r");
	if (!f) die("No roms.lst file found.\n");
	for (;;)
	{
		if (feof(f)) break;
		fgets(line, sizeof(line), f);
		if ((p = strpbrk(line, "#\r\n")))
			*p = 0;
		if (*line != '\0') {
			if ((f2 = fopen(roms_filename(line), "r"))) {
				fclose(f2);
				insert_menuitem(&m, line);
			}
		}
	}
	fclose(f);
	if (m.used == 0) die("No roms found\n");
	item = show_menu(&m);
	fname = roms_filename(m.array[item]);
	loader_init(fname);
	menu_free(&m);
}
