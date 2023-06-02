#include "gistlib.h"

#ifdef __PUREC__
#include <tos.h>
#include <stdarg.h>
#endif

#ifdef __GNUC__
#include <osbind.h>
#include <stdarg.h>
#endif

#ifdef __ALCYON__
#define Supexec(x) xbios(38, x)
#define Giaccess(value, reg) xbios(28, value, reg)
#endif

#define VOICES 3

struct sound {
	/*   0 */ short inuse;
	/*   2 */ short freq;
	/*   4 */ short noise_freq;
	/*   6 */ short volume;
	/*   8 */ short o8;
	/*  10 */ long o10;
	/*  14 */ long o14;
	/*  18 */ long o18;
	          char o22[14];
	/*  36 */ short o36;
	          char o38[20];
	/*  58 */ long o58;
	          char o62[18];
	/*  80 */ short o80;
	          char o82[20];
	/* 102 */ long o102;
	          short o106[3];
	/* 112 */ short pitch;
	/* 114 */ short priority;
	/* 116 */ long o116;
	/* 120 */ long o120;
	/* 124 */ long o124;
	/* 128 */ long o128;
	/* 132 */ long o132;
	/* 136 */ long o136;
	/* 140 */ 
};
extern VOIDPTR old_irq;
extern char old_conterm;

#define timer_c *((VOIDPTR *)0x114)
#define conterm *((char *)0x484)
#define vr *((char *)0xfffffa17L)

extern VOID timer_irq PROTO((NOTHING));
extern struct sound snd[VOICES];

static short const freqs[] = {
/*     C   C#    D   D#    E    F   F#    G   G#    A   A#    B */
	3822,3608,3405,3214,3034,2863,2703,2551,2408,2273,2145,2025,
    1911,1804,1703,1607,1517,1432,1351,1276,1204,1136,1073,1012,
     956, 902, 851, 804, 758, 716, 676, 638, 602, 568, 536, 506,
     478, 451, 426, 402, 379, 358, 338, 319, 301, 284, 268, 253,
     239, 225, 213, 201, 190, 179, 169, 159, 150, 142, 134, 127,
     119, 113, 106, 100,  95,  89,  84,  80,  75,  71,  67,  63,
      60,  56,  53,  50,  47,  45,  42,  40,  38,  36,  34,  32,
      30/* 28,  27,  25,  24,  22,  21,  20,  19,  18,  17,  16 */
};
/*
 * masks for mixer control register
 */
static short const mask[VOICES] = {
	0x00f6, /* channel A: 11110110 */
	0x00ed, /* channel B: 11101101 */
	0x00db  /* channel C: 11011011 */
};


static long s_install_int(NOTHING)
{
	if (old_irq == 0)
	{
		old_irq = timer_c;
		old_conterm = conterm;
		timer_c = timer_irq;
		vr = 0x40;  /* automatic end-of-interrupt */
	}
	return 0;
}


int install_int(NOTHING)
{
	Supexec(s_install_int);
	init_snds();
	return TRUE;
}


static long s_remove_int(NOTHING)
{
	if (old_irq != 0)
	{
		timer_c = old_irq;
		conterm = old_conterm;
		vr = 0x48;  /* software end-of-interrupt */
		old_irq = 0;
	}
	return 0;
}


VOID remove_int(NOTHING)
{
	init_snds();
	Supexec(s_remove_int);
}


VOID init_snds(NOTHING)
{
	int i;
	
	for (i = 0; i < VOICES; i++)
		stop_snd(i);
}


static VOID gi_rw(P(short) regno, P(short) value
#ifdef __ALCYON__
	, mask
#else
	, ...
#endif
)
PP(short regno;)
PP(short value;)
PP(short mask;)
{
	if (regno == 7)
	{
#ifndef __ALCYON__
		va_list args;
		short mask;
		
		va_start(args, value);
		mask = va_arg(args, int);
		va_end(args);
#endif
		value |= Giaccess(0, regno) & mask;
	}
	regno |= 0x80; /* set write mask for Giaccess */
	(VOID) Giaccess(value, regno);
}


short snd_on(P(VOIDPTR) snddata, P(short) voice, P(short) volume, P(short) pitch, P(short) priority)
PP(register VOIDPTR snddata;)
PP(register short voice;)
PP(short volume;)
PP(short pitch;)
PP(short priority;)
{
	register int i;
	register int tonemask;
	register int noisemask;
	register int inuse;
	register struct sound *sndptr;
	register short *data;
	
	if (voice < 0 || voice > VOICES-1)
	{
		for (voice = 0; voice < VOICES && snd[voice].inuse; voice++)
			;
		if (voice == VOICES)
		{
			/*
			 * all voices used. choose the one with the lowest priority
			 */
			voice = snd[0].priority < snd[1].priority ? 0 : 1;
			voice = snd[2].priority > snd[voice].priority ? voice : 2;
		}
	}
	sndptr = &snd[voice];
	if (sndptr->priority > priority)
		return -1;
	stop_snd(voice);
	inuse = *((short *)snddata);
	snddata = (VOIDPTR)((char *)snddata + 2); /* needs a lvalue */
	if (inuse == 0)
		return voice;
	data = &sndptr->freq;
	for (i = 1; i < 56; i++)
	{
		*data++ = *((short *)snddata);
		snddata = (VOIDPTR)((char *)snddata + 2); /* needs a lvalue */
	}
	sndptr->pitch = pitch;
	sndptr->priority = priority;
	sndptr->o116 = sndptr->o120 = sndptr->o132 = sndptr->o136 = sndptr->o124 = sndptr->o128 = 0;
	if (sndptr->freq >= 0)
	{
		tonemask = 0; /* turns note ON */
		if (pitch >= 0)
		{
			while (pitch > 108)
				pitch -= 12;
			while (pitch < 24)
				pitch += 12;
			sndptr->freq = freqs[pitch - 24];
		}
		gi_rw(voice << 1, sndptr->freq & 0xff); /* freq low */
		gi_rw((voice << 1) + 1, sndptr->freq >> 8); /* freq high */
	} else
	{
		tonemask = 1 << voice; /* turns note OFF */
		sndptr->o36 = sndptr->o58 = 0;
	}
	if (sndptr->noise_freq >= 0)
	{
		noisemask = 0; /* turns noise ON */
		gi_rw(6, sndptr->noise_freq);
	} else
	{
		noisemask = 8 << voice; /* turns noise OFF */
		sndptr->o80 = sndptr->o102 = 0;
	}
	gi_rw(7, tonemask | noisemask, mask[voice]);
	if (volume >= 0)
		sndptr->volume = volume;
	if (sndptr->o8 == 0)
	{
		sndptr->o116 = 0xf0000L;
		gi_rw(voice + 8, sndptr->volume);
	}
	sndptr->inuse = inuse;
	return voice;
}


VOID stop_snd(P(short) voice)
PP(short voice;)
{
	if (voice >= 0 && voice <= VOICES-1)
	{
		snd[voice].inuse = snd[voice].priority = 0;
		gi_rw(voice + 8, 0); /* amplitude[voice] = 0 */
	}
}


VOID snd_off(P(short) voice)
PP(short voice;)
{
	if (voice >= 0 && voice <= VOICES-1 && snd[voice].inuse)
	{
		snd[voice].inuse = TRUE;
		snd[voice].pitch = -1;
	}
}


short get_prior(P(short) voice)
PP(short voice;)
{
	return snd[voice].priority;
}
