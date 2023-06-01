/*
 * ----------------------------------------------------------------------------
 *
 * GIST Library for C
 *
 * ----------------------------------------------------------------------------
 *
 */

#ifndef __GNUC__
# ifndef __PUREC__
#   ifndef __TURBOC__
#     ifndef LATTICE
#       define __ALCYON__ 1
#     endif
#   endif
# endif
#endif

#ifdef __PUREC__
#include <tos.h>
#include <aes.h>
#include <vdi.h>
#define _DTA DTA
#define dta_name d_fname
#define dta_size d_length
# ifndef _WORD
#   define _WORD int
# endif
#endif

#ifdef __GNUC__
#include <osbind.h>
#include <gem.h>
#define cdecl
# ifndef _WORD
#   define _WORD short
# endif
#endif


#ifdef __ALCYON__
#define VOID int					/* Void function return	   */
#define VOIDPTR char *
#define NOTHING                     /* no parameters */
#define PROTO(p) ()
#define P(t)
#define PP(v) v
#define volatile
#define const
#define signed
#define __MSHORT__ 1
#define __SHORT_EXTERNAL_NAMES
#define cdecl
#else
#define NOTHING void                /* no parameters */
#define PROTO(p) p
#define P(t) t
#define PP(v)
#endif

#ifdef __TURBOC__
#define __MSHORT__ 1
#endif

#ifdef __PUREC__
#ifndef __AHCC__
#define __MSHORT__ 1
#endif
#endif

#ifndef VOID
#define VOID	void					/* Void function return	   */
#endif

#ifndef VOIDPTR
#define VOIDPTR	void *
#endif

#ifndef NULL
#define	NULL	((VOIDPTR)0)			/*	Null pointer value	    */
#endif

#ifndef FALSE
#  define FALSE 0
#  define TRUE 1
#endif

#ifndef G_WHITE
#  define G_WHITE WHITE
#  define G_RED   RED
#  define G_BLUE  BLUE
#  define G_BLACK BLACK
#endif



/*
 * install_int will install the interrupt routine. The vector for
 * the 200 Hz system timer interrupt routine is set to point to the
 * sound interrupt routine. This routine MUST be called after appl_init
 * and before any of the below routines are called.
 */
int install_int PROTO((NOTHING));


/*
 * remove_int will remove the interrupt routine. The 200 Hz system timer
 * interrupt routine vector is returned to its normal location. This
 * routine MUST be called prior to appl_exit. None of the below routines
 * should be called after this routine.
 */
VOID remove_int PROTO((NOTHING));


/*
 * init_snds will completely stop sound on all channels.
 */
VOID init_snds PROTO((NOTHING));


/*
 * get_prior will return the priority of the requested voice. This
 * routine is useful if you have a case where a snd_off might turn off
 * the wrong sound. You can call get_prior and issue the snd_off only
 * if the priority matches the original.
 *
 * get_prior(voice)
 *
 * voice = the voice whose priority is requested (0, 1 or 2)
 *
 * NOTE: type WORD is always returned
 */
short get_prior PROTO((short voice));


/*
 * snd_on will play a sound that was created using GIST and stored as a
 * GFA source code (DATA) on a channel of the GI chip.
 *
 * snd_on(sndptr,voice,volume,pitch,priority)
 *
 * sndptr   = the pointer to the array of parameters known as
 *             sound data
 *
 * voice    = the voice number corresponding to the GI channel number
 *             0, 1, or 2. A -1 tells the sound driver to use any
 *             available channel.
 *
 * volume   = volume of the sound (0-15) or -1 to use volume
 *             stored with sound data.
 *
 * pitch    = the pitch of the sound. When playing sound effects,
 *             (pitch = -1) the sound will play using the frequency value
 *             in the sound data; the duration is determined by the
 *             duration value in the sound data. A snd_off will
 *             automatically be issued when the duration has elapsed.
 *             When playing musical tones, pitch (24-108) corresponds
 *             to the semitone number.
 *                 60 = middle C on a piano keyboard or 262 Hz;
 *                 72 = one octave above;
 *                 This is the same as MIDI pitch numbers.
 *             The sound will remain on until a snd_off is issued.
 *             In other words, if pitch = -1, it is considered a sound effect.
 *             If pitch is specified, it is considered a musical note.
 *
 * priority = priority of the sound (0-32767) where the higher the value,
 *             the higher the priority. Equal values take precedence over
 *             each other.  When a snd_off is issued, the priority is reduced
 *             to zero during the release phase of any sound. Thus, priority
 *             should normally set set to at least 1.
 *
 * The voice number used will be returned. If no voice was available, -1
 * is returned (NOTE: type WORD is always returned
 */
short snd_on PROTO((VOIDPTR sndptr, short voice, short volume, short pitch, short priority));


/*
 * snd_off will cause the sound to move into its release phase and reduce
 * the priority to zero.
 *
 * snd_off(voice)
 *
 * voice  = the voice which is to be moved into its release
 *          phase (0, 1, or 2). Any other value has no effect.
 */
VOID snd_off PROTO((short voice));


/*
 * stop_snd will cause the sound to completely stop. No matter what phase
 * the sound is in (attack, decay, sustain, or release), the sound will
 * end. Unlike snd_off, there is no release.
 *
 * stop_snd(voice)
 *
 * voice = the voice which is to be stopped (0, 1 or 2).
 *         Any other value has no effect.
 */
VOID stop_snd PROTO((short voice));
