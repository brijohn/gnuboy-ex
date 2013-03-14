! Entry: arg0: string start address
! Exit:  result: length
!
! Copyright 2002 SuperH Ltd.

	.text
	.align 1
	.global	_strlen
	.type	_strlen, @function
_strlen:
#define STR_INIT r4
#define STR_ORIG STR_INIT
#define STR_COPY STR
#define MASK r1
#define TMP r3
#define RESULT r0
!        r1,r3: clobbered
#define STR RESULT

	mov #3,MASK
	and STR_INIT,MASK
	tst MASK,MASK
	bf.s L_char_loop
	mov STR_INIT, STR_COPY
L_word_loop:
	mov.l @STR+,TMP
	cmp/str MASK,TMP
	bf L_word_loop
	add #-4,STR
L_char_loop:
	mov.b @STR+,TMP
	tst TMP,TMP
	bf L_char_loop
	add #-1,STR
	rts
	sub STR_ORIG,STR
.size _strlen, .-_strlen
