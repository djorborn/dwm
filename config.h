#include <X11/XF86keysym.h>

/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 1;        /* gap pixel between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const unsigned int minwsz    = 10;       /* Minimal heigt of a client for smfact */
static const char *fonts[]          = { "Hermit:size=12" };
static const char dmenufont[]       = "Hermit:size=12";
static const char col_gray1[]       = "#282a36";
static const char col_gray2[]       = "#bbbbbb";
static const char col_gray3[]       = "#383A46";
static const char col_gray4[]       = "#ff79c6";
static const char col_cyan[]        = "#8be9fd";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray2, col_gray3, col_gray1 },
	[SchemeSel]  = { col_cyan, col_gray1,  col_gray4  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const char *hangouts = "crx_nckgahadagoaajjgafhacjanaoiihapd";
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */

	/* class      instance    title       tags mask     isfloating  ispermanent  monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           0,          -1 },
	{ "Chromium", "crx_nckgahadagoaajjgafhacjanaoiihapd" ,/* Next Line .............  
	...Chromium      */       NULL,       0,            1,           0,          -1 },
	{ "Gcolor3",  NULL,       NULL,       0,            1,           0,          -1 },
	{ "Transmis*",NULL,       NULL,       0,            1,           0,          -1 },
	{ "Tilda",    NULL,       NULL,       0,            1,           1,          -1 }
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const float smfact     = 0.00; /* factor of tiled clients [0.00..0.95] */
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_recent", NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *browsercmd[] = { "chromium", NULL };
static const char *filemanagercmd[] = { "pcmanfm", NULL };
static const char *clipmenucmd[] = { "clipmenu", NULL };
static const char *st[] = { "st", NULL };
/* XF86 commands  */
static const char *xf86_audioplay[] = { "playerctl", "play-pause", NULL };
static const char *xf86_audionext[] = { "playerctl", "next", NULL };
static const char *xf86_audioprev[] = { "playerctl", "previous", NULL };
/* PULSEAUDIO */
static const char *xf86_audioraisevolume[] = { "pactl", "set-sink-volume", "0", "+5%", NULL };
static const char *xf86_audiolowervolume[] = { "pactl", "set-sink-volume", "0", "-5%", NULL };
static const char *xf86_audiomute[] = { "pactl", "set-sink-mute", "0", "toggle", NULL };
/* ALSA */
/* static const char *xf86_audioraisevolume[] = { "amixer", "set", "Master", "5%+", NULL }; */
/* static const char *xf86_audiolowervolume[] = { "amixer", "set", "Master", "5%-", NULL }; */
/* static const char *xf86_audiomute[] = { "amixer", "set", "Master", "toggle", NULL }; */
        /* Brightness */
static const char *xf86_monbrightnessup[] = { "xbacklight", "-inc", "5%", NULL };
static const char *xf86_monbrightnessdown[] = { "xbacklight", "-dec", "5%", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_Left,   focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_Right,  focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_o,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,      setsmfact,      {.f = +0.05} },
 	{ MODKEY|ShiftMask,             XK_l,      setsmfact,      {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_s,      togglesticky,   {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_e,      quit,           {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_r,      quit,           {1} },
													/*    XF86 Bindings Section    */
	{ 0, 						  XF86XK_AudioPlay,        spawn, 				 {.v = xf86_audioplay } },
	{ 0, 						  XF86XK_AudioNext,        spawn, 				 {.v = xf86_audionext } },
	{ 0, 						  XF86XK_AudioPrev,        spawn, 				 {.v = xf86_audioprev } },
	{ 0, 						  XF86XK_AudioRaiseVolume, spawn, 				 {.v = xf86_audioraisevolume } },
	{ 0, 						  XF86XK_AudioLowerVolume, spawn, 				 {.v = xf86_audiolowervolume } },
	{ 0, 						  XF86XK_AudioMute,        spawn, 				 {.v = xf86_audiomute } },
	{ 0,              XF86XK_MonBrightnessUp,  spawn,          {.v = xf86_monbrightnessup } },
	{ 0,              XF86XK_MonBrightnessDown,spawn,          {.v = xf86_monbrightnessdown } },
														/*    Custom Bindings   */
	{ MODKEY|ShiftMask,             XK_w,      spawn,          {.v = browsercmd } },
	{ MODKEY|ShiftMask,             XK_f,      spawn,          {.v = filemanagercmd } },
	{ MODKEY|ShiftMask,             XK_d,      spawn,          {.v = clipmenucmd } },
	{ MODKEY|ShiftMask,             XK_u,      spawn,          {.v = st } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

