conterm = 0x484
timer_c = 0x114
vr = 0xfffffa17
giselect = 0xffff8800

		.xref _snd

		.text

timer_irq:
		movem.l    d0-d3/a0-a2,-(a7)
		movea.l    divtable,a2
		movea.l    sndptr,a0
		/* movea.l    #giselect.l,a1 */
		dc.w 0x227c,0xffff,0x8800 /* XXX */
		moveq.l    #2,d2
		move.w     sr,-(a7)
		ori.w      #0x0500,sr
		andi.w     #0xFDFF,sr
		move.b     #0,conterm
vcloop:
		tst.w      (a0)
		beq        endloop
		move.w     8(a0),d0
		move.l     116(a0),d1
		cmp.b      #1,d0
		bne.s      ved
		add.l      10(a0),d1
		cmp.l      #0x000F0000,d1
		blt.s      endve
		move.l     #0x000F0000,d1
		addq.w     #1,8(a0)
		bra.s      endve
ved:
		cmp.b      #2,d0
		bne.s      ver
		add.l      14(a0),d1
		cmp.l      18(a0),d1
		bgt.s      endve
		move.l     18(a0),d1
		addq.w     #1,8(a0)
		bra.s      endve
ver:
		cmp.b      #4,d0
		bne.s      lva
		add.l      22(a0),d1
		tst.l      d1
		bgt.s      endve
		moveq.l    #0,d1
		move.w     d1,8(a0)
		move.w     #1,(a0)
endve:
		move.l     d1,116(a0)
lva:
		move.l     26(a0),d0
		beq.s      do_vol
		tst.w      34(a0)
		beq.s      do_lv
		subq.w     #1,34(a0)
		bra.s      do_vol
do_lv:
		move.l     120(a0),d1
		add.l      30(a0),d1
		cmp.l      d0,d1
		bge.s      do_lv1
		neg.l      d0
		cmp.l      d0,d1
		bgt.s      enddo_lv
do_lv1:
		move.l     d0,d1
		neg.l      30(a0)
enddo_lv:
		move.l     d1,120(a0)
do_vol:
		move.w     8(a0),d0
		or.w       26(a0),d0
		beq.s      fe
		move.w     6(a0),d0
		add.w      d0,d0
		move.w     0(a2,d0.w),d0
		move.l     116(a0),d1
		add.l      120(a0),d1
		bpl.s      do_vol1
		moveq.l    #0,d0
		bra.s      do_vol2
do_vol1:
		asr.l      #8,d1
		muls.w     d1,d0
		swap       d0
		cmp.w      #15,d0
		ble.s      do_vol2
		moveq.l    #15,d0
do_vol2:
		move.b     d2,d1
		addq.b     #8,d1
		move.b     d1,(a1)
		move.b     d0,2(a1)
fe:
		move.w     36(a0),d0
		move.l     124(a0),d1
		cmp.b      #1,d0
		bne.s      fed
		add.l      38(a0),d1
		tst.w      38(a0)
		bmi.s      fea1
		cmp.l      42(a0),d1
		blt.s      endfe
		bra.s      fea2
fea1:
		cmp.l      42(a0),d1
		bgt.s      endfe
fea2:
		move.l     42(a0),d1
		addq.w     #1,36(a0)
		bra.s      endfe
fed:
		cmp.b      #2,d0
		bne.s      fer
		add.l      46(a0),d1
		tst.w      46(a0)
		bmi.s      fed1
		cmp.l      50(a0),d1
		blt.s      endfe
		bra.s      fed2
fed1:
		cmp.l      50(a0),d1
		bgt.s      endfe
fed2:
		move.l     50(a0),d1
		addq.w     #1,36(a0)
		bra.s      endfe
fer:
		cmp.b      #4,d0
		bne.s      lfa
		add.l      54(a0),d1
		tst.w      54(a0)
		bmi.s      fer1
		tst.l      d1
		bmi.s      endfe
		bra.s      fer2
fer1:
		tst.l      d1
		bgt.s      endfe
fer2:
		moveq.l    #0,d1
endfe:
		move.l     d1,124(a0)
lfa:
		move.l     58(a0),d0
		beq.s      do_fr
		tst.w      78(a0)
		beq.s      do_lf
		subq.w     #1,78(a0)
		bra.s      do_fr
do_lf:
		move.l     62(a0),d1
		bmi.s      do_lf2
		add.l      128(a0),d1
		bcc.s      do_lf1
		move.l     66(a0),62(a0)
do_lf1:
		cmp.l      d0,d1
		blt.s      enddo_lf
		bra.s      do_lf4
do_lf2:
		move.l     70(a0),d0
		add.l      128(a0),d1
		bcs.s      do_lf3
		move.l     74(a0),62(a0)
do_lf3:
		cmp.l      d0,d1
		bgt.s      enddo_lf
do_lf4:
		move.l     d0,d1
		neg.l      62(a0)
enddo_lf:
		move.l     d1,128(a0)
do_fr:
		move.w     36(a0),d0
		or.w       58(a0),d0
		beq.s      nfe
		move.l     128(a0),d0
		add.l      124(a0),d0
		swap       d0
		muls.w     2(a0),d0
		asl.l      #4,d0
		swap       d0
		bpl.s      do_fr0
		addq.w     #1,d0
do_fr0:
		add.w      2(a0),d0
		bpl.s      do_fr1
		moveq.l    #0,d0
		bra.s      do_fr2
do_fr1:
		cmp.w      #0x0FFF,d0
		ble.s      do_fr2
		move.w     #0x0FFF,d0
do_fr2:
		move.b     d2,d1
		add.b      d1,d1
		move.b     d1,(a1)
		move.b     d0,2(a1)
		addq.b     #1,d1
		move.b     d1,(a1)
		asr.w      #8,d0
		move.b     d0,2(a1)
nfe:
		move.w     80(a0),d0
		move.l     132(a0),d1
		cmp.b      #1,d0
		bne.s      nfed
		add.l      82(a0),d1
		tst.w      82(a0)
		bmi.s      nfea1
		cmp.l      86(a0),d1
		blt.s      endnfe
		bra.s      nfea2
nfea1:
		cmp.l      86(a0),d1
		bgt.s      endnfe
nfea2:
		move.l     86(a0),d1
		addq.w     #1,80(a0)
		bra.s      endnfe
nfed:
		cmp.b      #2,d0
		bne.s      nfer
		add.l      90(a0),d1
		tst.w      90(a0)
		bmi.s      nfed1
		cmp.l      94(a0),d1
		blt.s      endnfe
		bra.s      nfed2
nfed1:
		cmp.l      94(a0),d1
		bgt.s      endnfe
nfed2:
		move.l     94(a0),d1
		addq.w     #1,80(a0)
		bra.s      endnfe
nfer:
		cmp.b      #4,d0
		bne.s      lnfa
		add.l      98(a0),d1
		tst.w      98(a0)
		bmi.s      nfer1
		tst.l      d1
		bmi.s      endnfe
		bra.s      nfer2
nfer1:
		tst.l      d1
		bgt.s      endnfe
nfer2:
		moveq.l    #0,d1
endnfe:
		move.l     d1,132(a0)
lnfa:
		move.l     102(a0),d0
		beq.s      do_nfr
		tst.w      110(a0)
		beq.s      do_lnf
		subq.w     #1,110(a0)
		bra.s      do_nfr
do_lnf:
		move.l     136(a0),d1
		add.l      106(a0),d1
		cmp.l      d0,d1
		bge.s      do_lnf1
		neg.l      d0
		cmp.l      d0,d1
		bgt.s      enddo_ln
do_lnf1:
		move.l     d0,d1
		neg.l      106(a0)
enddo_ln:
		move.l     d1,136(a0)
do_nfr:
		move.w     80(a0),d0
		or.w       102(a0),d0
		beq.s      dec_dur
		move.l     136(a0),d0
		add.l      132(a0),d0
		swap       d0
		add.w      4(a0),d0
		bpl.s      do_nfr1
		moveq.l    #0,d0
		bra.s      do_nfr2
do_nfr1:
		cmp.b      #31,d0
		ble.s      do_nfr2
		moveq.l    #31,d0
do_nfr2:
		move.b     #6,(a1)
		move.b     d0,2(a1)
dec_dur:
		tst.w      112(a0)
		bpl.s      endloop
		subq.w     #1,(a0)
		bne.s      endloop
		clr.w      114(a0)
		tst.w      8(a0)
		bne.s      dec_dur1
		move.b     d2,d1
		addq.w     #8,d1
		move.b     d1,(a1)
		move.b     #0,2(a1)
		bra.s      endloop
dec_dur1:
		subq.w     #1,(a0)
		moveq.l    #4,d0
		move.w     d0,8(a0)
		tst.w      36(a0)
		beq.s      dec_dur2
		move.w     d0,36(a0)
		move.w     54(a0),d1
		move.w     124(a0),d3
		eor.w      d1,d3
		bmi.s      dec_dur2
		neg.l      54(a0)
dec_dur2:
		tst.w      80(a0)
		beq.s      endloop
		move.w     d0,80(a0)
		move.w     98(a0),d1
		move.w     132(a0),d3
		eor.w      d1,d3
		bmi.s      endloop
		neg.l      98(a0)
endloop:
		lea.l      -140(a0),a0
		dbf        d2,vcloop
		move.w     140(a0),d0
		or.w       280(a0),d0
		or.w       420(a0),d0
		bne.s      out
		move.b     old_conterm,conterm
out:
		move.w     (a7)+,sr
		movem.l    (a7)+,d0-d3/a0-a2
		move.l     old_irq,-(a7)
		rts

/*
 * Supervisor part of installation
 */
	.globl _s_install_int
_s_install_int:
		movem.l    a0-a1,-(a7)
		lea.l      old_irq,a0
		move.l     timer_c.l,(a0)+
		lea.l      _div15,a1
		move.l     a1,(a0)+  /* -> divtable */
		lea.l      _snd+2*140,a1
		move.l     a1,(a0)+  /* -> sndptr */
		move.b     conterm,(a0)
		lea.l      trap9,a0
		move.l     a0,0x000000A4.l
		lea.l      timer_irq,a0
		move.l     a0,timer_c.l
		move.b     #0x40,vr.l /* automatic end-of-interrupt */
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
		move.l     old_irq,timer_c
		move.b     old_conterm,conterm
		move.b     #0x48,vr.l /* software end-of-interrupt */
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
		movea.l    #giselect,a0
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

	.data

_div15: dc.w 0
		dc.w 18
		dc.w 35
		dc.w 52
		dc.w 69
		dc.w 86
		dc.w 103
		dc.w 120
		dc.w 137
		dc.w 154
		dc.w 171
		dc.w 188
		dc.w 205
		dc.w 222
		dc.w 239
		dc.w 256
