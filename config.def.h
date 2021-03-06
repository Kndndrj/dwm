/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 4;        /* border pixel of windows */
static const unsigned int snap      = 20;       /* snap pixel */
static const unsigned int gappih    = 12;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 12;       /* vert inner gap between windows */
static const unsigned int gappoh    = 12;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 12;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 5;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 30;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const char *fonts[]          = { "FontAwesome:size=12", "monospace:size=12" };
static const char dmenufont[]       = "monospace:size=12";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_green[]       = "#deda60";
static const char *colors[][4]      = {
	/*               fg         bg         border     float-border */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2, col_gray2 },
	[SchemeSel]  = { col_gray1, col_green, col_green, col_gray3 },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                          instance    title	          tags mask    isfloating   monitor */
	/* class                                        instance    title	          tags mask    isfloating   monitor */
	{ "Alacritty",                                  NULL,       "File Manager",     0,           1,           -1 },
	{ "Alacritty",                                  NULL,       "Popup",            0,           1,           -1 },
	{ "com-st-microxplorer-maingui-STM32CubeMX",    NULL,       NULL,               0,           1,           -1 },
	{ "discord",                                    NULL,       NULL,               1 << 8,      0,           -1 },
	{ "Microsoft Teams - Preview",                  NULL,       NULL,               1 << 7,      0,           -1 },
	{ "Slack",                                      NULL,       NULL,               1 << 7,      0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.60; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int attachdirection = 2;    /* 0 default, 1 above, 2 aside, 3 below, 4 bottom, 5 top */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "\uf0c8\uf0c9",   tile },   /* first entry is default */
	{ "\uf0c8\uf149",   dwindle },	
	{ "\uf0c8\uf0c9",   tile },
	{ "\uf0c8\uf149",   dwindle },  /* first entry is default */
	{ " \uf06c ",       NULL },    /* no layout function means floating behavior */
	{ "\uf24d",         monocle },
	{ "\uf00a",         grid },
	{ "[@]",            spiral },
	{ "H[]",            deck },
	{ "TTT",            bstack },
	{ "===",            bstackhoriz },
	{ "###",            nrowgrid },
	{ "---",            horizgrid },
	{ ":::",            gaplessgrid },
	{ "|M|",            centeredmaster },
	{ ">M>",            centeredfloatingmaster },
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
static const char *dmenucmd[] = { "rofi", "-show", "drun", "-show-icons", "-display-drun", "Run", NULL };
static const char *windowcmd[] = { "rofi", "-show", "window", "-show-icons", "-display-window", "Windows", NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char scratchpadname[] = "Scratchpad";
static const char *scratchpadcmd[] = { "alacritty", "-t", scratchpadname };

static Key keys[] = {
	/* modifier                     key          function        argument */
	{ MODKEY,                       XK_d,        spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Tab,      spawn,          {.v = windowcmd } },
	{ MODKEY,	                XK_Return,   spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_w,        togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY,                       XK_o,        togglebar,      {0} },
	{ MODKEY,                       XK_j,        focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,        focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,        incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_p,        incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,        setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,        setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return,   zoom,           {0} },
	{ MODKEY,    			XK_scaron,   incrgaps,       {.i = +4 } },
	{ MODKEY, 		        XK_dstroke,  incrgaps,       {.i = -4 } },
//	{ MODKEY|Mod1Mask,              XK_i,        incrigaps,      {.i = +1 } },
//	{ MODKEY|Mod1Mask|ShiftMask,    XK_i,        incrigaps,      {.i = -1 } },
//	{ MODKEY|Mod1Mask,              XK_o,        incrogaps,      {.i = +1 } },
//	{ MODKEY|Mod1Mask|ShiftMask,    XK_o,        incrogaps,      {.i = -1 } },
//	{ MODKEY|Mod1Mask,              XK_6,        incrihgaps,     {.i = +1 } },
//	{ MODKEY|Mod1Mask|ShiftMask,    XK_6,        incrihgaps,     {.i = -1 } },
//	{ MODKEY|Mod1Mask,              XK_7,        incrivgaps,     {.i = +1 } },
//	{ MODKEY|Mod1Mask|ShiftMask,    XK_7,        incrivgaps,     {.i = -1 } },
//	{ MODKEY|Mod1Mask,              XK_8,        incrohgaps,     {.i = +1 } },
//	{ MODKEY|Mod1Mask|ShiftMask,    XK_8,        incrohgaps,     {.i = -1 } },
//	{ MODKEY|Mod1Mask,              XK_9,        incrovgaps,     {.i = +1 } },
//	{ MODKEY|Mod1Mask|ShiftMask,    XK_9,        incrovgaps,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_scaron,   togglegaps,     {0} },
	{ MODKEY|ShiftMask,	        XK_dstroke,  defaultgaps,    {0} },
	{ MODKEY|ShiftMask,             XK_q,        killclient,     {0} },
	{ MODKEY,                       XK_r,        setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_t,        setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_z,        setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_u,        setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_space,    togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_space,    setlayout,      {0} },
	{ MODKEY,                       XK_0,        view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,        tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,    focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,   focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,    tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,   tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                        0)
	TAGKEYS(                        XK_2,                        1)
	TAGKEYS(                        XK_3,                        2)
	TAGKEYS(                        XK_4,                        3)
	TAGKEYS(                        XK_5,                        4)
	TAGKEYS(                        XK_6,                        5)
	TAGKEYS(                        XK_7,                        6)
	TAGKEYS(                        XK_8,                        7)
	TAGKEYS(                        XK_9,                        8)
	{ MODKEY|ShiftMask,             XK_e,        quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

