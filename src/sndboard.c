/*
 * ----------------------------------------------------------------------------
 *
 * Name: SNDBOARD.C
 * Desc: A Sound Board for all the GIST Effects for GFA 3.0+
 * Auth: Derek J. Evans 2023
 *       Ported to C by Thorsten Otto
 * Note: Max buttons (ie: effects) is 70
 *
 * ----------------------------------------------------------------------------
 */

#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "gistlib.h"

#ifndef FA_RDONLY
# define FA_RDONLY 1
#endif


static _WORD phys_handle;
static _WORD vdi_handle;
static GRECT desk;

static unsigned char old_click;

#define MAX_X 5
#define MAX_Y 14
#define BUTTON_WIDTH 64
#define BUTTON_HEIGHT 14
#define MAX_SOUNDS (MAX_Y * MAX_X)

#define REVERSE_VIDEO 0

int sound_count;
char *sound_data[MAX_SOUNDS];
char sound_name[MAX_SOUNDS][14];


static void init_screen(void)
{
	_WORD workin[11];
	_WORD workout[57];
	_WORD dummy;
	int i;
	
	phys_handle = graf_handle(&dummy, &dummy, &dummy, &dummy);
	for (i = 0; i < 10; i++)
		workin[i] = 1;
	workin[10] = 2;
	vdi_handle = phys_handle;
	v_opnvwk(workin, &vdi_handle, workout);
	vswr_mode(vdi_handle, MD_REPLACE);
	wind_get(0, WF_WORKXYWH, &desk.g_x, &desk.g_y, &desk.g_w, &desk.g_h);
}


static void exit_screen(void)
{
	if (vdi_handle != 0)
	{
		v_clsvwk(vdi_handle);
		vdi_handle = 0;
	}
}



static long stop_click(void)
{
	unsigned char *conterm = (unsigned char *)0x484;
	unsigned char click;
	
	click = *conterm;
	old_click = click;
	click &= ~1;
	*conterm = click;
	return 0;
}


static long restore_click(void)
{
	unsigned char *conterm = (unsigned char *)0x484;
	*conterm = old_click;
	return 0;
}


static void load_sounds(void)
{
	_DTA *olddta;
	_DTA dta;
	int ret;
	char path[80];
	char *name;
	long size;
	int fd;
	char *buf;
	char *p;
	
	sound_count = 0;
	olddta = Fgetdta();
	Fsetdta(&dta);
	strcpy(path, "sounds\\*.snd");
	name = path + sizeof("sounds\\") - 1;
	
	ret = Fsfirst(path, FA_RDONLY);
	while (ret == 0)
	{
		if (sound_count >= MAX_SOUNDS)
			break;
		strcpy(name, dta.dta_name);
		size = dta.dta_size;
		if (size == 112)
		{
			buf = malloc(size);
			if (buf == NULL)
			{
				form_error(-(-39) - 31);
				break;
			}
			sound_data[sound_count] = buf;
			fd = (int)Fopen(path, FO_READ);
			if (fd >= 0)
			{
				Fread(fd, size, buf);
				Fclose(fd);
				p = strchr(name, '.');
				if (p != NULL)
					*p = '\0';
				strcpy(sound_name[sound_count], name);
				sound_count++;
			} else
			{
				free(buf);
			}
		}
		ret = Fsnext();
	}
	
	Fsetdta(olddta);
}


static void cls(void)
{
	_WORD pxy[4];
	
	pxy[0] = 0;
	pxy[1] = 0;
	pxy[2] = desk.g_x + desk.g_w - 1;
	pxy[3] = desk.g_y + desk.g_h - 1;
#if REVERSE_VIDEO
	vsf_color(vdi_handle, G_WHITE);
#else
	vsf_color(vdi_handle, G_BLACK);
#endif
	vs_clip(vdi_handle, 1, pxy);
	vr_recfl(vdi_handle, pxy);
}


static void box(_WORD x1, _WORD y1, _WORD x2, _WORD y2)
{
	_WORD pxy[10];
	
	pxy[0] = x1;
	pxy[1] = y1;
	pxy[2] = x2;
	pxy[3] = y1;
	pxy[4] = x2;
	pxy[5] = y2;
	pxy[6] = x1;
	pxy[7] = y2;
	pxy[8] = x1;
	pxy[9] = y1;
	v_pline(vdi_handle, 5, pxy);
}


static int draw_button(_WORD x, _WORD y, int select)
{
	_WORD x1, y1, x2, y2;
	_WORD pxy[4];
	int snd;
	
	snd = y * MAX_X + x;
	x1 = x * BUTTON_WIDTH;
	y1 = y * BUTTON_HEIGHT;
	x2 = x1 + BUTTON_WIDTH - 2;
	y2 = y1 + BUTTON_HEIGHT - 2;
	vswr_mode(vdi_handle, MD_REPLACE);
	if (select)
		vsf_color(vdi_handle, G_RED);
	else
		vsf_color(vdi_handle, G_BLUE);
	pxy[0] = x1 + 2;
	pxy[1] = y1 + 2;
	pxy[2] = x2 - 2;
	pxy[3] = y2 - 2;
	vr_recfl(vdi_handle, pxy);
#if REVERSE_VIDEO
	vsl_color(vdi_handle, G_BLACK);
#else
	vsl_color(vdi_handle, G_WHITE);
#endif
	box(x1, y1, x2, y2);
	if (snd < sound_count)
	{
		vswr_mode(vdi_handle, MD_TRANS);
#if REVERSE_VIDEO
		vst_color(vdi_handle, G_WHITE);
#else
		vst_color(vdi_handle, G_BLACK);
#endif
		v_gtext(vdi_handle, x1 + 5, y1 + 9, sound_name[snd]);
#if REVERSE_VIDEO
		vst_color(vdi_handle, G_BLACK);
#else
		vst_color(vdi_handle, G_WHITE);
#endif
		v_gtext(vdi_handle, x1 + 4, y1 + 8, sound_name[snd]);
		return snd;
	}
	return -1;
}


static void sndboard(void)
{
#if REVERSE_VIDEO
	_WORD colors[2][3];

	static _WORD const black[3] = { 0, 0, 0 };
	static _WORD const white[3] = { 1000, 1000, 1000 };
#endif
	_WORD dummy;
	_WORD message[8];
	_WORD mox, moy;
	_WORD button;
	_WORD events;
	_WORD key;
	_WORD x, y;
	_WORD snd;

	load_sounds();
	if (sound_count == 0)
	{
		form_alert(1, "[1][|No sounds found ][ Abort ]");
		return;
	}

	if (!install_int())
		return;

	init_screen();
	v_hide_c(vdi_handle);
	
	/* Turn off key click; this will interfere with sound play */
	Supexec(stop_click);

#if REVERSE_VIDEO
	vq_color(vdi_handle, G_WHITE, 1, colors[0]);
	vq_color(vdi_handle, G_BLACK, 1, colors[1]);
	
	vs_color(vdi_handle, G_WHITE, black);
	vs_color(vdi_handle, G_BLACK, white);
#endif
	vst_height(vdi_handle, 4, &dummy, &dummy, &dummy, &dummy);
	
	cls();

	for (y = 0; y < MAX_Y; y++)
	{
		for (x = 0; x < MAX_X; x++)
			draw_button(x, y, FALSE);
	}
	
	wind_update(BEG_UPDATE);
	wind_update(BEG_MCTRL);
	for (;;)
	{
		v_show_c(vdi_handle, 1);
		events = evnt_multi(MU_KEYBD | MU_BUTTON, 1, 1, 1,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
			message,
#if defined(__AES__) && !defined(__PORTAES_H__) /* old Pure-C library */
			0, 0,
#else
			0, /* gemlib, or newer Pure-C library */
#endif			
			&mox, &moy, &button, &dummy, &key, &dummy);
		v_hide_c(vdi_handle);
		if (events & MU_KEYBD)
		{
			if ((key & 0xff) == 0x1b)
				break;
		}
		if (events & MU_BUTTON)
		{
			x = mox / BUTTON_WIDTH;
			y = moy / BUTTON_HEIGHT;

			snd = draw_button(x, y, TRUE);
			if (snd >= 0)
				snd_on(sound_data[snd], -1, 15, -1, 5);
			
			/* if (button & 1) */
			{
				v_show_c(vdi_handle, 1);
				evnt_button(1, 1, 0, &dummy, &dummy, &dummy, &dummy);
				v_hide_c(vdi_handle);
			}

			draw_button(x, y, FALSE);
		}
	}
	
	remove_int();

#if REVERSE_VIDEO
	vs_color(vdi_handle, G_WHITE, colors[0]);
	vs_color(vdi_handle, G_BLACK, colors[1]);
#endif

	Supexec(restore_click);
	
	wind_update(END_MCTRL);
	wind_update(END_UPDATE);

	v_show_c(vdi_handle, 1);
	exit_screen();
	form_dial(FMD_FINISH, desk.g_x, desk.g_y, desk.g_w, desk.g_h, desk.g_x, desk.g_y, desk.g_w, desk.g_h);
}


int main(void)
{
	int exitcode = 0;

	appl_init();
	graf_mouse(ARROW, NULL);
	
#if defined(__AES__) && !defined(__PORTAES_H__) /* old Pure-C library */
	if (_GemParBlk.global[10] < 4)
#else
	if (aes_global[10] < 4)
#endif
	{
		form_alert(1, "[1][|Color Resolution Required ][ OK ]");
		exitcode = 1;
	} else
	{
		sndboard();
	}

	appl_exit();
	return exitcode;
}
