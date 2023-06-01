/*
 * ----------------------------------------------------------------------------
 *
 * GIST Library for C
 *
 * Version for using the drivercode
 * either from external program, or from embedded data.
 * 
 * ----------------------------------------------------------------------------
 *
 */
#include <stddef.h>
#include <stdio.h>
#include "gistlib.h"

/* define to 1 to use the embedded version */
#define EMBEDDED  0
/* define to 1 to use the new version */
#define NEWDRIVER 1

#if EMBEDDED
#if NEWDRIVER
#include "gistdrvn.h"
#else
#include "gistdrvr.h"
#endif
#endif

typedef void (cdecl *INSTALL_INT_PTR)(void);
typedef void (cdecl *REMOVE_INT_PTR)(void);
typedef void (cdecl *INIT_SNDS_PTR)(void);
/*
 * Compilers with 32bit default ints cannot call these directly
 */
#ifdef __MSHORT__
typedef short (cdecl *SND_ON_PTR)(void *sndptr, short voice, short volume, short pitch, short priority);
typedef void (cdecl *STOP_SND_PTR)(short voice);
typedef void (cdecl *SND_OFF_PTR)(short voice);
typedef short (cdecl *GET_PRIOR_PTR)(short voice);
#else
struct SND_ON_parm {
	void *sndptr;
	short voice;
	short volume;
	short pitch;
	short priority;
};
typedef short (cdecl *SND_ON_PTR)(struct SND_ON_parm parm);
struct STOP_SND_parm {
	short voice;
	short pad;
};
typedef void (cdecl *STOP_SND_PTR)(struct STOP_SND_parm parm);
struct SND_OFF_parm {
	short voice;
	short pad;
};
typedef void (cdecl *SND_OFF_PTR)(struct SND_OFF_parm parm);
struct GET_PRIOR_parm {
	short voice;
	short pad;
};
typedef short (cdecl *GET_PRIOR_PTR)(struct GET_PRIOR_parm parm);
#endif

static INSTALL_INT_PTR install_int_ptr;
static REMOVE_INT_PTR remove_int_ptr;
static INIT_SNDS_PTR init_snds_ptr;
static SND_ON_PTR snd_on_ptr;
static STOP_SND_PTR stop_snd_ptr;
static SND_OFF_PTR snd_off_ptr;
static GET_PRIOR_PTR get_prior_ptr;


#define MSDOS_ERR(e) (-(e) - 31)

int install_int(void)
{
	
	if (install_int_ptr == 0)
	{
#if !EMBEDDED
		char *buf;
		int fd;
		long size;

#if NEWDRIVER
		fd = (int)Fopen("gistdrvn.prg", FO_READ);
#else
		fd = (int)Fopen("gistdrvr.prg", FO_READ);
#endif
		if (fd < 0)
		{
			form_error(MSDOS_ERR(-33)); /* ENOENT */
			return FALSE;
		}
		size = Fseek(0, fd, SEEK_END);
		Fseek(0, fd, SEEK_SET);
		buf = (char *)Malloc(size + 752); /* that makes 3000 bytes for original version */
		if (buf == NULL)
		{
			Fclose(fd);
			form_error(MSDOS_ERR(-39)); /* ENOMEM */
			return FALSE;
		}
		Fread(fd, size, buf);
		Fclose(fd);
#else
		const char *buf = driverdata;
#endif
		if (*((const unsigned short *)(buf)) != 0x601a)
		{
#if !EMBEDDED
			Mfree(buf);
#endif
			form_error(MSDOS_ERR(-66)); /* EPLFMT */
			return FALSE;
		}
		install_int_ptr = (INSTALL_INT_PTR) (buf);
		if (*((const unsigned long *)(buf + 2)) == 1962 && /* textlen */
			*((const unsigned long *)(buf + 6)) == 208  && /* datalen */
			*((const unsigned long *)(buf + 10)) == 424 && /* bsslen */
			*((const unsigned short *)(buf + 28)) == 0x41fa)
		{
			/* we got the original driver; use fixed offsets */
			remove_int_ptr = (REMOVE_INT_PTR) (buf + 148);
			init_snds_ptr = (INIT_SNDS_PTR) (buf + 176);
			snd_on_ptr = (SND_ON_PTR) (buf + 210);
			stop_snd_ptr = (STOP_SND_PTR) (buf + 704);
			snd_off_ptr = (SND_OFF_PTR) (buf + 782);
			get_prior_ptr = (GET_PRIOR_PTR) (buf + 868);
		} else
		{
			buf += 28; /* skip GEMDOS header */
			/*
			 * new version has the offsets embedded
			 */
			remove_int_ptr = (REMOVE_INT_PTR) (buf + *((const short *)(buf + 2)));
			init_snds_ptr = (INIT_SNDS_PTR) (buf + *((const short *)(buf + 4)));
			snd_on_ptr = (SND_ON_PTR) (buf + *((const short *)(buf + 6)));
			stop_snd_ptr = (STOP_SND_PTR) (buf + *((const short *)(buf + 8)));
			snd_off_ptr = (SND_OFF_PTR) (buf + *((const short *)(buf + 10)));
			get_prior_ptr = (GET_PRIOR_PTR) (buf + *((const short *)(buf + 12)));
		}
		
		install_int_ptr();
	}
	return TRUE;
}


void remove_int(void)
{
	if (install_int_ptr)
	{
		remove_int_ptr();
#if !EMBEDDED
		Mfree(install_int_ptr);
#endif
		install_int_ptr = 0;
	}
}


void init_snds(void)
{
	if (install_int_ptr)
		init_snds_ptr();
}


short get_prior(short voice)
{
	if (install_int_ptr)
	{
#ifdef __MSHORT__
		return get_prior_ptr(voice);
#else
		struct GET_PRIOR_parm parm;
		parm.voice = voice;
		return get_prior_ptr(parm);
#endif
	}
	return -1;
}


short snd_on(void *sndptr, short voice, short volume, short pitch, short priority)
{
	if (install_int_ptr)
	{
#ifdef __MSHORT__
		return snd_on_ptr(sndptr, voice, volume, pitch, priority);
#else
		struct SND_ON_parm parm;
		parm.sndptr = sndptr;
		parm.voice = voice;
		parm.volume = volume;
		parm.pitch = pitch;
		parm.priority = priority;
		return snd_on_ptr(parm);
#endif
	}
	return -1;
}


void snd_off(short voice)
{
	if (install_int_ptr)
	{
#ifdef __MSHORT__
		snd_off_ptr(voice);
#else
		struct SND_OFF_parm parm;
		parm.voice = voice;
		snd_off_ptr(parm);
#endif
	}
}


void stop_snd(short voice)
{
	if (install_int_ptr)
	{
#ifdef __MSHORT__
		stop_snd_ptr(voice);
#else
		struct STOP_SND_parm parm;
		parm.voice = voice;
		stop_snd_ptr(parm);
#endif
	}
}
