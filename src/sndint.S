conterm = 0x484
timer_c = 0x114
vr = 0xfffffa17
giselect = 0xffff8800

		.text

/*
 * Supervisor part of installation
 */
	.globl _s_install_int
_s_install_int: .ds.b 0
		movem.l    a0-a1,-(a7)
		lea.l      old_irq(pc),a0
		move.l     timer_c.w,(a0)+
		lea.l      _div15(pc),a1
		move.l     a1,(a0)+  /* -> divtable */
		lea.l      _snd+2*140(pc),a1
		move.l     a1,(a0)+  /* -> sndptr */
		move.b     conterm.w,(a0)
		lea.l      trap9(pc),a0
		move.l     a0,0x000000A4.w
		lea.l      timer_irq(pc),a0
		move.l     a0,timer_c.w
		move.b     #0x40,vr.w /* automatic end-of-interrupt */
		movem.l    (a7)+,a0-a1
		rts

old_irq:
		dc.l 0x4e714e71
divtable:
		dc.l 0x4e714e71
sndptr:
		dc.l 0x4e714e71
old_conterm:
		dc.w 0x4e71

	.globl _s_remove_int
_s_remove_int:
		move.l     old_irq(pc),timer_c.w
		move.b     old_conterm(pc),conterm.w
		move.b     #0x48,vr.w /* software end-of-interrupt */
		rts

/* short gi_rw(short regno, short val, short mask) */
	.globl _gi_rw
_gi_rw:
		move.w     4(a7),d1 /* sound register */
		move.w     6(a7),d0 /* value (-1 for reading) */
		move.w     8(a7),d2 /* mask (only used for regno #7) */
		trap       #9
		rts

trap9:
		move.w     sr,-(a7)
		ori.w      #0x0700,sr
		movea.w    #giselect,a0
		and.b      #15,d1
		move.b     d1,(a0)
		tst.w      d0
		bmi.s      trap9_1
		cmp.b      #7,d1
		bne.s      trap9_2
		move.b     (a0),d1
		and.b      d2,d1
		or.b       d1,d0
trap9_2:
		move.b     d0,2(a0)
trap9_1:
		moveq.l    #0,d0
		move.b     (a0),d0
		move.b     #11,(a0) /* select envelop period low */
		move.w     (a7)+,sr
		rte

timer_irq:
		movem.l    d0-d3/a0-a2,-(a7)


	.data
_div15: .dc.w 0

	.bss
	.globl _snd
_snd: .ds.b 3*140
