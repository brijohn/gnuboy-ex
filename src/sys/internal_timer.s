.global _timer, _get_ticks
.extern _keypad_read

_get_ticks:
	mov.l	.L0, r0
	rts
	mov.l	@r0, r0

_timer:
	sts.l   pr,@-r15
	mov.l	.L0, r1
	mov.l	.L0 + 4, r2
	mov.b	@r2, r0
	and	#0xfe, r0
	mov.b	r0, @r2

	mov.w	@(12, r2), r0
	mov.w	.L0 + 8, r3
	and	r3, r0
	mov.w	r0, @(12, r2)

	mov.l	@r1, r0
	add	#1, r0
	mov.l	r0, @r1
	tst	#7, r0
	bf	.L1
	mov.l	.L0 + 12, r1
	jsr	@r1
	nop
.L1:
	mov.l	.L0 + 4, r2
	mov.b	@r2, r0
	or	#1, r0
	mov.b	r0, @r2
	lds.l	@r15+, pr
	rts
	nop
.align 2
.L0:
.long __ms_count
.long 0xa4490004
.word 0xfeff
.word 0
.long _keypad_read

.lcomm __ms_count, 4
