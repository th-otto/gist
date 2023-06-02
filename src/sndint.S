/*
 * Separate interrupt timer for library
 */
conterm = 0x484
giselect = 0xffff8800

size_sndstruct = 140

#ifdef __mcoldfire__
	COLDFIRE = 1
#else
	COLDFIRE = 0
#endif

		.text

	.globl timer_irq
	.globl _timer_irq
timer_irq:
_timer_irq:
		.IFNE COLDFIRE
		lea        -7*4(a7),a7
		movem.l    d0-d3/a0-a2,(a7)
		.ELSE
		movem.l    d0-d3/a0-a2,-(a7)
		.ENDC
		lea.l      _div15(pc),a2
		lea.l      _snd+2*size_sndstruct(pc),a0
		movea.w    #giselect,a1
		moveq.l    #2,d2
		move.w     sr,d0
		.IFNE COLDFIRE
		move.l     d0,-(a7)
		ori.l      #0x0500,d0
		andi.l     #0xFDFF,d0
		.ELSE
		move.w     d0,-(a7)
		ori.w      #0x0500,d0
		andi.w     #0xFDFF,d0
		.ENDC
		move.w     d0,sr
		clr.b      conterm.w
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
		.IFNE COLDFIRE
		move.w     8(a0),d1
		addq.l     #1,d1
		move.w     d1,8(a0)
		.ELSE
		addq.w     #1,8(a0)
		.ENDC
		move.l     #0x000F0000,d1
		bra.s      endve
ved:
		cmp.b      #2,d0
		bne.s      ver
		add.l      14(a0),d1
		cmp.l      18(a0),d1
		bgt.s      endve
		.IFNE COLDFIRE
		move.w     8(a0),d1
		addq.l     #1,d1
		move.w     d1,8(a0)
		.ELSE
		addq.w     #1,8(a0)
		.ENDC
		move.l     18(a0),d1
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
		.IFNE COLDFIRE
		move.w     34(a0),d1
		subq.l     #1,d1
		move.w     d1,34(a0)
		.ELSE
		subq.w     #1,34(a0)
		.ENDC
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
		.IFNE COLDFIRE
		move.l     30(a0),d1
		neg.l      d1
		move.l     d1,30(a0)
		.ELSE
		neg.l      30(a0)
		.ENDC
		move.l     d0,d1
enddo_lv:
		move.l     d1,120(a0)
do_vol:
		move.w     8(a0),d0
		.IFNE COLDFIRE
		move.w     26(a0),d1
		or.l       d1,d0
		tst.w      d0
		.ELSE
		or.w       26(a0),d0
		.ENDC
		beq.s      fe
		.IFNE COLDFIRE
		moveq      #0,d0
		move.w     6(a0),d0
		add.l      d0,d0
		move.w     0(a2,d0.l),d0
		.ELSE
		move.w     6(a0),d0
		add.w      d0,d0
		move.w     0(a2,d0.w),d0
		.ENDC
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
		.IFNE COLDFIRE
		move.l     d2,d1
		addq.l     #8,d1
		.ELSE
		move.b     d2,d1
		addq.b     #8,d1
		.ENDC
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
		.IFNE COLDFIRE
		move.w     36(a0),d1
		addq.l     #1,d1
		move.w     d1,36(a0)
		.ELSE
		addq.w     #1,36(a0)
		.ENDC
		move.l     42(a0),d1
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
		.IFNE COLDFIRE
		move.w     36(a0),d1
		addq.l     #1,d1
		move.w     d1,36(a0)
		.ELSE
		addq.w     #1,36(a0)
		.ENDC
		move.l     50(a0),d1
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
		.IFNE COLDFIRE
		move.w     78(a0),d0
		subq.l     #1,d0
		move.w     d0,78(a0)
		.ELSE
		subq.w     #1,78(a0)
		.ENDC
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
		.IFNE COLDFIRE
		move.l     62(a0),d1
		neg.l      d1
		move.l     d1,62(a0)
		.ELSE
		neg.l      62(a0)
		.ENDC
		move.l     d0,d1
enddo_lf:
		move.l     d1,128(a0)
do_fr:
		move.w     36(a0),d0
		.IFNE COLDFIRE
		move.w     58(a0),d1
		or.l       d1,d0
		tst.w      d0
		.ELSE
		or.w       58(a0),d0
		.ENDC
		beq.s      nfe
		move.l     128(a0),d0
		add.l      124(a0),d0
		swap       d0
		muls.w     2(a0),d0
		asl.l      #4,d0
		swap       d0
		bpl.s      do_fr0
		.IFNE COLDFIRE
		addq.l     #1,d0
		.ELSE
		addq.w     #1,d0
		.ENDC
do_fr0:
		.IFNE COLDFIRE
		moveq      #0,d1
		move.w     2(a0),d1
		add.l      d1,d0
		tst.w      d0
		.ELSE
		add.w      2(a0),d0
		.ENDC
		bpl.s      do_fr1
		moveq.l    #0,d0
		bra.s      do_fr2
do_fr1:
		cmp.w      #0x0FFF,d0
		ble.s      do_fr2
		move.w     #0x0FFF,d0
do_fr2:
		.IFNE COLDFIRE
		move.l     d2,d1
		add.l      d1,d1
		.ELSE
		move.b     d2,d1
		add.b      d1,d1
		.ENDC
		move.b     d1,(a1)
		move.b     d0,2(a1)
		.IFNE COLDFIRE
		addq.l     #1,d1
		.ELSE
		addq.b     #1,d1
		.ENDC
		move.b     d1,(a1)
		.IFNE COLDFIRE
		asr.l      #8,d0
		.ELSE
		asr.w      #8,d0
		.ENDC
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
		.IFNE COLDFIRE
		move.w     80(a0),d1
		addq.l     #1,d1
		move.w     d1,80(a0)
		.ELSE
		addq.w     #1,80(a0)
		.ENDC
		move.l     86(a0),d1
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
		.IFNE COLDFIRE
		move.w     80(a0),d1
		addq.l     #1,d1
		move.w     d1,80(a0)
		.ELSE
		addq.w     #1,80(a0)
		.ENDC
		move.l     94(a0),d1
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
		.IFNE COLDFIRE
		moveq      #0,d0
		move.w     110(a0),d0
		subq.l     #1,d0
		move.w     d0,110(a0)
		.ELSE
		subq.w     #1,110(a0)
		.ENDC
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
		.IFNE COLDFIRE
		move.l     106(a0),d1
		neg.l      d1
		move.l     d1,106(a0)
		.ELSE
		neg.l      106(a0)
		.ENDC
		move.l     d0,d1
enddo_ln:
		move.l     d1,136(a0)
do_nfr:
		move.w     80(a0),d0
		.IFNE COLDFIRE
		move.w     102(a0),d1
		or.l       d1,d0
		tst.w      d0
		.ELSE
		or.w       102(a0),d0
		.ENDC
		beq.s      dec_dur
		move.l     136(a0),d0
		add.l      132(a0),d0
		swap       d0
		.IFNE COLDFIRE
		moveq      #0,d1
		move.w     4(a0),d1
		add.l      d1,d0
		tst.w      d0
		.ELSE
		add.w      4(a0),d0
		.ENDC
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
		.IFNE COLDFIRE
		move.w     (a0),d0
		subq.l     #1,d0
		move.w     d0,(a0)
		.ELSE
		subq.w     #1,(a0)
		.ENDC
		bne.s      endloop
		clr.w      114(a0)
		tst.w      8(a0)
		bne.s      dec_dur1
		.IFNE COLDFIRE
		move.l     d2,d1
		addq.l     #8,d1
		.ELSE
		move.b     d2,d1
		addq.w     #8,d1
		.ENDC
		move.b     d1,(a1)
		move.b     #0,2(a1)
		bra.s      endloop
dec_dur1:
		.IFNE COLDFIRE
		move.w     (a0),d0
		subq.l     #1,d0
		move.w     d0,(a0)
		.ELSE
		subq.w     #1,(a0)
		.ENDC
		moveq.l    #4,d0
		move.w     d0,8(a0)
		tst.w      36(a0)
		beq.s      dec_dur2
		move.w     d0,36(a0)
		move.w     54(a0),d1
		move.w     124(a0),d3
		.IFNE COLDFIRE
		eor.l      d1,d3
		tst.w      d3
		.ELSE
		eor.w      d1,d3
		.ENDC
		bmi.s      dec_dur2
		.IFNE COLDFIRE
		move.l     54(a0),d1
		neg.l      d1
		move.l     d1,54(a0)
		.ELSE
		neg.l      54(a0)
		.ENDC
dec_dur2:
		tst.w      80(a0)
		beq.s      endloop
		move.w     d0,80(a0)
		move.w     98(a0),d1
		move.w     132(a0),d3
		.IFNE COLDFIRE
		eor.l      d1,d3
		tst.w      d3
		.ELSE
		eor.w      d1,d3
		.ENDC
		bmi.s      endloop
		.IFNE COLDFIRE
		move.l     98(a0),d0
		neg.l      d0
		move.l     d0,98(a0)
		.ELSE
		neg.l      98(a0)
		.ENDC
endloop:
		lea.l      -size_sndstruct(a0),a0
		.IFNE COLDFIRE
		subq.l     #1,d2
		bpl        vcloop
		.ELSE
		dbf        d2,vcloop
		.ENDC

		.IFNE COLDFIRE
		clr.l      d0
		clr.l      d1
		move.w     size_sndstruct(a0),d0
		move.w     size_sndstruct*2(a0),d1
		or.l       d1,d0
		move.w     size_sndstruct*3(a0),d1
		or.l       d1,d0
		bne.s      out
		/* no voices in use anymore, restore conterm */
		move.b     old_conterm(pc),d0
		move.b     d0,conterm.w
		.ELSE
		move.w     size_sndstruct(a0),d0
		or.w       size_sndstruct*2(a0),d0
		or.w       size_sndstruct*3(a0),d0
		bne.s      out
		/* no voices in use anymore, restore conterm */
		move.b     old_conterm(pc),conterm.w
		.ENDC
out:
		.IFNE COLDFIRE
		move.l     (a7)+,d0
		move.w     d0,sr
		movem.l    (a7),d0-d3/a0-a2
		lea        7*4(a7),a7
		.ELSE
		move.w     (a7)+,sr
		movem.l    (a7)+,d0-d3/a0-a2
		.ENDC
		move.l     old_irq(pc),-(a7)
		rts

	.data
_div15:
		dc.w 0
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

	.bss

	.globl snd
	.globl _snd
snd:
_snd: ds.b 3*size_sndstruct

	.globl old_irq
	.globl _old_irq
old_irq:
_old_irq: .ds.l 1

	.globl old_conterm
	.globl _old_conterm
old_conterm:
_old_conterm: .ds.b 1
