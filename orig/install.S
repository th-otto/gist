		.xref _c_install_int
		
		.text
start: .ds.b 0

/* void install_int(void) */
		.globl _install_int
_install_int:
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
		jmp        _c_install_int
