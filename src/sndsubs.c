#include "gistlib.h"

#ifdef __PUREC__
#include <tos.h>
#endif

#ifdef __GNUC__
#include <osbind.h>
#endif

#ifdef __ALCYON__
#define Supexec(x) xbios(38, x)
#endif

#define VOICES 3

/* defined in install code; supervisor part of install */
long s_install_int PROTO((NOTHING));


/*
 * jumped from the install code in install.S
 */
VOID c_install_int PROTO((NOTHING));


VOID c_install_int(NOTHING)
{
	Supexec(s_install_int);
	init_snds();
}


VOID init_snds PROTO(NOTHING)
{
	int i;
	
	for (i = 0; i < VOICES; i++)
		stop_snd(i);
}


VOID stop_snd(P(short) voice)
PP(short voice;)
{
}
