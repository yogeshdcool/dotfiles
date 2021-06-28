/* See LICENSE file for copyright and license details.
                             _         _                 _
                            | |       | |               | |
 _   _  ___   __ _  ___  ___| |__   __| | ___ ___   ___ | |
| | | |/ _ \ / _` |/ _ \/ __| '_ \ / _` |/ __/ _ \ / _ \| |
| |_| | (_) | (_| |  __/\__ \ | | | (_| | (_| (_) | (_) | |
 \__, |\___/ \__, |\___||___/_| |_|\__,_|\___\___/ \___/|_|
  __/ |       __/ |
 |___/       |___/

*/

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int gap                = 12;       /* gap value I have added it for my ease of use */
static const unsigned int gappih    = gap;      /* horiz inner gap between windows */
static const unsigned int gappiv    = gap;      /* vert inner gap between windows */
static const unsigned int gappoh    = gap;      /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = gap;      /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const Bool viewontag         = False;     /* Switch view on tag switch */
static const char *fonts[]          = { "SauceCodePro Nerd Font:style=Medium:size=12" };

static const char white[]           = "#FFFFFF";
static const char norm_fg[]      	= "#f5e12f";
static const char norm_bg[]      	= "#2F343F";
static const char norm_border[]     = "#2F343F";

static const char sel_fg[]      	= "#f5e12f";
static const char sel_bg[]      	= "#cf7706";
static const char sel_border[]      = "#fa8f05";

static const char *colors[][3]      = {
	/*                    fg       bg         border   */
	[SchemeNorm]    = { norm_fg,  norm_bg,   norm_border },
	[SchemeSel]     = { sel_fg,   sel_bg,    sel_border  },
	[SchemeStatus]  = { norm_fg,  norm_bg,   "#000000"  }, // Statusbar right {text,background,not used but cannot be empty}
	[SchemeTagsSel] = { white,    sel_bg,    "#000000"  }, // Tagbar left selected {text,background,not used but cannot be empty}
    [SchemeTagsNorm]= { norm_fg,  norm_bg,   "#000000"  }, // Tagbar left unselected {text,background,not used but cannot be empty}
    [SchemeInfoSel] = { sel_fg,   norm_bg,   "#000000"  }, // infobar middle  selected {text,background,not used but cannot be empty}
    [SchemeInfoNorm]= { norm_fg,  norm_bg,   "#000000"  }, // infobar middle  unselected {text,background,not used but cannot be empty}
};
typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {"st", "-n", "spterm","-g", "144x41", NULL };
const char *spcmd2[] = {"st", "-n", "spvim", "-g", "144x41", "-e", "nvim", NULL };
const char *spcmd3[] = {"st", "-n", "spcalc","-g", "144x41", "-e", "calc", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"spvim",       spcmd2},
	{"spcalc",      spcmd3},
};
static const XPoint stickyicon[]    = { {0,0}, {4,0}, {4,8}, {2,6}, {0,8}, {0,0} }; /* represents the icon as an array of vertices */
static const XPoint stickyiconbb    = {4,8};	/* defines the bottom right corner of the polygon's bounding box (speeds up scaling) */

/* tagging */
static const char *tags[] = { "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX" };
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     iscentered   isfloating   monitor */
	{ NULL,       NULL,       "Pictures/screenshots", 0,0,           1,           -1 },
 	{ NULL,       NULL,       "Event Tester", 0,        1,           1,           -1 }, /* xev */
 	{ NULL,       NULL,       "Picture-in-picture",   0,0,           1,           -1 },
 	{ "Dragon-drag-and-drop", NULL,       NULL,         0,           1,            1,-1 }, /* xev */
	{ NULL,		  "spterm",	  NULL,		  SPTAG(0),     0,           1,			  -1 },
	{ NULL,	  	  "spvim",	  NULL,		  SPTAG(1),		0,           1,			  -1 },
	{ NULL,	      "spcalc",	  NULL,	      SPTAG(2),		0,           1,			  -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
#include <X11/XF86keysym.h>

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "[M]",      monocle },
	{ "H[]",      deck },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ "[\\]",     dwindle },
	{ ":::",      gaplessgrid },
	{ "HHH",      grid },
	{ "[@]",      spiral },
	{ "><>",      NULL },    /* no layout function means floating behavior */
    { NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define Shell(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define Term(cmd) { .v = (const char*[]){ Terminal, "-e", cmd, NULL } }

static const char Terminal[]          = "alacritty";
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_Return, spawn,          Shell(Terminal) },
    { MODKEY,             			XK_space,  spawn,          Shell("rofi -modi drun,file-browser,window,run -show drun -show-icons -sidebar-mode")},
	{ MODKEY,                       XK_w,      spawn,          Shell("brave") },
	{ MODKEY,		                XK_x,      spawn,          Shell("thunar") },
	{ MODKEY,       		        XK_z,      spawn,          Shell("gvim") },
 	{ MODKEY,                       XK_s,      spawn,          Shell("vscodium") },
	{ MODKEY|ControlMask,         	XK_Return, spawn,          Term("nvim") },
	{ MODKEY|Mod1Mask,   	    	XK_Return, spawn,          Term("ranger") },
	{ MODKEY,                       XK_a,      spawn,          Term("mocp") },
	{ MODKEY,                       XK_e,      spawn,          Term("gotop") },
	{ MODKEY|ControlMask,           XK_l,      spawn,          Shell("betterlockscreen -l dimblur") },
	{ MODKEY,		                XK_F1,     spawn,          Shell("~/.bin/powermenu.sh") },
	{ MODKEY,		                XK_F2,     spawn,          Shell("~/.bin/network.sh") },
	{ 0,		                    XK_Print,  spawn,          Shell("~/.bin/screenshot.sh") },
	{ MODKEY|ShiftMask,             XK_c,      spawn,          Shell("systemctl poweroff") },
	{ MODKEY|ShiftMask,             XK_v,      spawn,          Shell("systemctl reboot") },
	{ MODKEY|ShiftMask,             XK_x,      spawn,          Shell("killall xinit") },
	{ MODKEY|ShiftMask,             XK_b,      spawn,          Shell("systemctl suspend") },
	{ 0,                            XF86XK_MonBrightnessUp,    spawn,     Shell("light -A 1") },
	{ 0,                            XF86XK_MonBrightnessDown,  spawn,     Shell("light -U 1") },
	{ Mod1Mask,                     XK_F2,     spawn,          Shell("light -S 0") },
	{ Mod1Mask,                     XK_F3,     spawn,          Shell("light -S 6") },
	{ 0,                            XF86XK_AudioRaiseVolume,   spawn,     Shell("amixer -c 0 -q set Master 2dB+") },
	{ 0,                            XF86XK_AudioLowerVolume,   spawn,     Shell("amixer -c 0 -q set Master 2dB-") },
	{ 0,                            XF86XK_AudioMute,      	   spawn,     Shell("amixer set Master toggle") },
	{ 0,                            XF86XK_AudioPlay,      	   spawn,     Shell("mocp -G") },
	{ 0,                            XF86XK_AudioPrev,      	   spawn,     Shell("mocp -r") },
	{ 0,                            XF86XK_AudioNext,      	   spawn,     Shell("mocp -f") },
	{ 0,                            XF86XK_RFKill,      	   spawn,     Shell("~/.bin/wifi-toggle") },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY|ShiftMask,           	XK_j,      pushdown,       {0} },
	{ MODKEY|ShiftMask,           	XK_k,      pushup,         {0} },
	{ MODKEY|ShiftMask,           	XK_h,      pushdownmaster, {0} },
	{ MODKEY|ShiftMask,           	XK_l,      pushupmaster,   {0} },
	{ MODKEY|ShiftMask,    			XK_minus,  togglegaps,     {0} },
	{ MODKEY|ShiftMask,             XK_equal,  defaultgaps,    {0} },
	{ MODKEY,              			XK_equal,  incrgaps,       {.i = +1 } },
	{ MODKEY,              			XK_minus,  incrgaps,       {.i = -1 } },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,		                XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_d,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_c,      setlayout,      {.v = &layouts[5]} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[13]} },
	{ MODKEY|ShiftMask,             XK_space,  setlayout,      {13} },
	{ MODKEY,						XK_comma,  cyclelayout,    {.i = -1 } },
	{ MODKEY,           			XK_period, cyclelayout,    {.i = +1 } },
	{ MODKEY|ControlMask,           XK_f,  	   togglefloating, {0} },
	{ MODKEY,             			XK_f,      togglefullscr,  {0} },
	{ MODKEY|ShiftMask,             XK_s,      togglesticky,   {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },

	{ MODKEY|ShiftMask,             XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ControlMask,           XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,            			XK_grave,  togglescratch,  {.ui = 0 } },
	{ MODKEY|ShiftMask,            	XK_a,	   togglescratch,  {.ui = 1 } },
	{ MODKEY|ShiftMask,            	XK_w,      togglescratch,  {.ui = 2 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          Shell(Terminal) },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

