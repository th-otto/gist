/*
 * Standalone sound driver.
 *
 * original version as found on the G.I.S.T disk (2248 bytes)
 */
conterm = 0x484
timer_c = 0x114
vr = 0xfffffa17
giselect = 0xffff8800

		.text
start:

/* void install_int(void) */
		.globl install_int
install_int:
		lea.l      relocflag(pc),a0
		tst.w      (a0)
		bne.s      already_relocated
		move.w     #1,(a0)
		lea.l      start(pc),a0
		move.l     a0,d0      /* start addr is value for relocations */
		movea.l    a0,a1
		suba.w     #28,a1     /* to start of GEMDOS header */
		adda.l     2(a1),a0   /* add size of text segment */
		adda.l     6(a1),a0   /* add size of data segment */
		move.l     a0,-(a7)   /* save for later use (will become start of bss) */
		move.l     10(a1),-(a7) /* save size of bss segment */
		adda.l     14(a1),a0  /* skip symbol table, if any */
		movea.l    (a0),a1    /* a0 now points to relocations; get first offset */
		tst.l      (a0)+
		beq.s      donerelocs /* if zero nothing to relocate */
		adda.l     d0,a1
		clr.w      d1
applyreloc:
		add.l      d0,(a1)    /* apply relocation */
relocloop:
		move.b     (a0)+,d1   /* get next offset */
		beq.s      donerelocs /* we are done if zero */
		adda.w     d1,a1      /* calc next address */
		cmp.w      #1,d1      /* was it 1? */
		bne.s      applyreloc
		adda.w     #253,a1    /* skip another 253 bytes */
		bra.s      relocloop

relocflag: dc.w 0

donerelocs:
		move.l     (a7)+,d0   /* get back size of bss */
		movea.l    (a7)+,a0   /* bet back start of bss */
		bra.s      clrloop1
clrloop:
		clr.b      (a0)+
clrloop1:
		dbf        d0,clrloop
already_relocated:
		jmp        c_install_int

c_install_int:
		link       a6,#-4
		move.l     #s_install_int,(a7)
		move.w     #38,-(a7)
		jsr        xbios
		addq.l     #2,a7
		bsr.s      init_snds
		unlk       a6
		rts

/* void remove_int(void) */
		.globl remove_int
remove_int:
		link       a6,#-4
		bsr.s      init_snds
		move.l     #s_remove_int,(a7)
		move.w     #38,-(a7)
		jsr        xbios
		addq.l     #2,a7
		unlk       a6
		rts

/* void init_snds(void) */
		.globl init_snds
init_snds:
		link       a6,#-6
		clr.w      -2(a6)
		bra.s      init_snds_1
init_snds_2:
		move.w     -2(a6),(a7)
		bsr        stop_snd
		addq.w     #1,-2(a6)
init_snds_1:
		cmpi.w     #3,-2(a6)
		blt.s      init_snds_2
		unlk       a6
		rts

/* short cdecl snd_on(void *sndptr, short voice, short volume, short pitch, short priority) */
		.globl snd_on
snd_on:
		link       a6,#0
		movem.l    d2-d7/a3-a5,-(a7)
		movea.l    8(a6),a5
		move.w     12(a6),d7
		tst.w      d7
		blt.s      L10000
		cmp.w      #2,d7
		ble.s      L7
L10000:
		clr.w      d7
		bra.s      L5
L6:
		addq.w     #1,d7
L5:
		cmp.w      #3,d7
		bge.s      L10001
		move.w     d7,d0
		muls.w     #140,d0
		movea.l    d0,a0
		movea.l    #_snd,a1
		tst.w      0(a0,a1.l)
		bne.s      L6
L10001:
		cmp.w      #3,d7
		bne.s      L7
		move.w     _snd+114,d0
		cmp.w      _snd+254,d0
		bge.s      L10002
		clr.w      d0
		bra.s      L10004
L10002:
		moveq.l    #1,d0
L10004:
		move.w     d0,d7
		move.w     d7,d0
		muls.w     #140,d0
		movea.l    d0,a0
		movea.l    #_snd,a1
		move.w     114(a0,a1.l),d0
		cmp.w      _snd+394,d0
		bge.s      L10005
		move.w     d7,d0
		bra.s      L10007
L10005:
		moveq.l    #2,d0
L10007:
		move.w     d0,d7
L7:
		move.w     d7,d0
		muls.w     #140,d0
		movea.l    d0,a4
		adda.l     #_snd,a4
		move.w     114(a4),d0
		cmp.w      18(a6),d0
		ble.s      L8
		moveq.l    #-1,d0
		bra        L1
L8:
		move.w     d7,(a7)
		bsr        stop_snd
		move.w     (a5)+,d3
		bne.s      L9
		move.w     d7,d0
		bra        L1
L9:
		move.w     d7,d0
		muls.w     #140,d0
		movea.l    d0,a3
		adda.l     #_snd,a3
		addq.l     #2,a3
		moveq.l    #1,d6
		bra.s      L12
L13:
		move.w     (a5)+,(a3)+
		addq.w     #1,d6
L12:
		cmp.w      #56,d6
		blt.s      L13
		move.w     16(a6),112(a4)
		move.w     18(a6),114(a4)
		clr.l      d0
		move.l     d0,128(a4)
		move.l     d0,124(a4)
		move.l     d0,136(a4)
		move.l     d0,132(a4)
		move.l     d0,120(a4)
		move.l     d0,116(a4)
		tst.w      2(a4)
		blt.s      L14
		clr.w      d5
		tst.w      16(a6)
		blt.s      L15
		bra.s      L18
L17:
		subi.w     #12,16(a6)
L18:
		cmpi.w     #108,16(a6)
		bgt.s      L17
		bra.s      L21
L20:
		addi.w     #12,16(a6)
L21:
		cmpi.w     #24,16(a6)
		blt.s      L20
		movea.w    16(a6),a0
		adda.w     #-24,a0
		adda.l     a0,a0
		adda.l     #_freqs,a0
		move.w     (a0),2(a4)
L15:
		move.w     2(a4),(a7)
		andi.w     #255,(a7)
		move.w     d7,d0
		asl.w      #1,d0
		move.w     d0,-(a7)
		jsr        gi_rw
		addq.l     #2,a7
		move.w     2(a4),d0
		asr.w      #8,d0
		move.w     d0,(a7)
		move.w     d7,d0
		asl.w      #1,d0
		move.w     d0,-(a7)
		addq.w     #1,(a7)
		jsr        gi_rw
		addq.l     #2,a7
		bra.s      L22
L14:
		moveq.l    #1,d5
		move.w     d7,d0
		asl.w      d0,d5
		clr.l      d0
		move.l     d0,58(a4)
		move.w     d0,36(a4)
L22:
		tst.w      4(a4)
		blt.s      L23
		clr.w      d4
		move.w     4(a4),(a7)
		move.w     #6,-(a7)
		jsr        gi_rw
		addq.l     #2,a7
		bra.s      L24
L23:
		moveq.l    #8,d4
		move.w     d7,d0
		asl.w      d0,d4
		clr.l      d0
		move.l     d0,102(a4)
		move.w     d0,80(a4)
L24:
		movea.w    d7,a0
		adda.l     a0,a0
		movea.l    #_mask,a1
		move.w     0(a0,a1.l),(a7)
		move.w     d5,-(a7)
		move.w     d4,d0
		or.w       d0,(a7)
		move.w     #7,-(a7)
		jsr        gi_rw
		addq.l     #4,a7
		tst.w      14(a6)
		blt.s      L25
		move.w     14(a6),6(a4)
L25:
		tst.w      8(a4)
		bne.s      L26
		move.l     #0x000F0000,116(a4)
		move.w     6(a4),(a7)
		move.w     d7,-(a7)
		addq.w     #8,(a7)
		jsr        gi_rw
		addq.l     #2,a7
L26:
		move.w     d3,(a4)
		move.w     d7,d0
L1:
		tst.l      (a7)+
		movem.l    (a7)+,d3-d7/a3-a5
		unlk       a6
		rts

/* void cdecl stop_snd(short voice) */
		.globl stop_snd
stop_snd:
		link       a6,#-4
		tst.w      8(a6)
		blt.s      L27
		cmpi.w     #2,8(a6)
		bgt.s      L27
		move.w     8(a6),d0
		muls.w     #140,d0
		add.l      #_snd,d0
		movea.l    d0,a0
		moveq.l    #0,d0
		move.w     d0,114(a0)
		move.w     8(a6),d1
		muls.w     #140,d1
		add.l      #_snd,d1
		movea.l    d1,a1
		move.w     d0,(a1)
		clr.w      (a7)
		move.w     8(a6),-(a7)
		addq.w     #8,(a7)
		jsr        gi_rw
		addq.l     #2,a7
L27:
		unlk       a6
		rts

/* void cdecl snd_off(short voice) */
		.globl snd_off
snd_off:
		link       a6,#-4
		tst.w      8(a6)
		blt.s      L29
		cmpi.w     #2,8(a6)
		bgt.s      L29
		move.w     8(a6),d0
		muls.w     #140,d0
		movea.l    d0,a0
		movea.l    #_snd,a1
		tst.w      0(a0,a1.l)
		beq.s      L29
		move.w     8(a6),d0
		muls.w     #140,d0
		add.l      #_snd,d0
		movea.l    d0,a0
		move.w     #1,(a0)
		move.w     8(a6),d0
		muls.w     #140,d0
		add.l      #_snd,d0
		movea.l    d0,a0
		move.w     #-1,112(a0)
L29:
		unlk       a6
		rts

/* short get_prior(short voice) */
		.globl get_prior
get_prior:
		link       a6,#-4
		move.w     8(a6),d0
		muls.w     #140,d0
		movea.l    d0,a0
		movea.l    #_snd,a1
		move.w     114(a0,a1.l),d0
		unlk       a6
		rts

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
		move.b     #0,conterm.l
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
		move.b     old_conterm,conterm.l
out:
		move.w     (a7)+,sr
		movem.l    (a7)+,d0-d3/a0-a2
		move.l     old_irq,-(a7)
		rts

s_install_int:
		movem.l    a0-a1,-(a7)
		lea.l      old_irq,a0
		move.l     timer_c.l,(a0)+
		lea.l      _div15,a1
		move.l     a1,(a0)+  /* -> divtable */
		lea.l      _snd+2*140,a1
		move.l     a1,(a0)+  /* -> sndptr */
		move.b     conterm.l,(a0)
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

s_remove_int:
		move.l     old_irq,timer_c.l
		move.b     old_conterm,conterm.l
		move.b     #0x48,vr.l /* software end-of-interrupt */
		rts

/* short gi_rw(short regno, short val, short mask) */
gi_rw:
		move.w     4(a7),d1 /* sound register */
		move.w     6(a7),d0 /* value (-1 for reading) */
		move.w     8(a7),d2 /* mask (only used for regno #7) */
		trap       #9
		rts

trap9:
		move.w     sr,-(a7)
		ori.w      #0x0700,sr
		/* movea.l    #giselect.l,a0 */
		dc.w 0x207c,0xffff,0x8800 /* XXX */
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

xbios:
		move.l     (a7)+,retpc
		trap       #14
		move.l     retpc,-(a7)
		rts

bios:
		move.l     (a7)+,retpc
		trap       #13
		move.l     retpc,-(a7)
		rts

gemdos:
		move.l     (a7)+,retpc
		trap       #1
		move.l     retpc,-(a7)
		rts

	.data
_freqs:
          /*      C   C#    D   D#    E    F   F#    G   G#    A   A#    B */
          dc.w 3822,3608,3405,3214,3034,2863,2703,2551,2408,2273,2145,2025
          dc.w 1911,1804,1703,1607,1517,1432,1351,1276,1204,1136,1073,1012
          dc.w  956, 902, 851, 804, 758, 716, 676, 638, 602, 568, 536, 506
          dc.w  478, 451, 426, 402, 379, 358, 338, 319, 301, 284, 268, 253
          dc.w  239, 225, 213, 201, 190, 179, 169, 159, 150, 142, 134, 127
          dc.w  119, 113, 106, 100,  95,  89,  84,  80,  75,  71,  67,  63
          dc.w   60,  56,  53,  50,  47,  45,  42,  40,  38,  36,  34,  32
          dc.w   30/* 28,  27,  25,  24,  22,  21,  20,  19,  18,  17,  16 */

_mask:
		dc.w 0x00f6
		dc.w 0x00ed
		dc.w 0x00db

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
retpc: ds.l 1
_snd: ds.b 3*140
