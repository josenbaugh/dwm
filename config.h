/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 6;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { 
    "Hack Nerd Font:size=8.5",
    "Noto Color Emoji:pixelsize=10:antialias=true:autohint=true"
};
static const char dmenufont[]          = "Hack Nerd Font:size=8.5";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
    /*               fg         bg         border   */
    [SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
    [SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "dev", "dev2", "www", "sys", "misc", "chat", "db", "mail", "misc" };

static const Rule rules[] = {
    /* xprop(1):
     *  WM_CLASS(STRING) = instance, class
     *  WM_NAME(STRING) = title
     */
    /* class            instance  title                 tags mask  isfloating  isterminal  noswallow  monitor */
    { "Gimp",           NULL,     NULL,                 0,         1,          0,           0,        -1 },
    { NULL,             NULL,    "StatusCalendar",      0,         1,          0,          -1,        -1 },
    { NULL,             NULL,    "galculator",          0,         1,          0,          -1,        -1 },
    { NULL,             NULL,    "zoom",                0,         1,          0,          -1,        -1 }, //zoom popups
    { "1Password",      NULL,     NULL,                 0,         1,          0,          -1,        -1 },
    { "firefox",          NULL,     NULL,                 1 << 2,    0,          0,          -1,        -1 },
    { "Slack",          NULL,     NULL,                 1 << 5,    0,          0,          -1,        -1 },
    { "DBeaver",        NULL,     NULL,                 1 << 6,    0,          0,          -1,        -1 },
    { NULL,             NULL,     "mail",               1 << 7,    0,          0,          -1,        -1 },
    { "Thunderbird",    NULL,     NULL,                 1 << 7,    0,          0,          -1,        -1 },
    { NULL,             NULL,     "rss",                1 << 8,    0,          0,          -1,        -1 },
    { "st-256color",    NULL,     NULL,                 0,         0,          1,           0,        -1 },
    { NULL,             NULL,     "Event Tester",       0,         0,          0,           1,        -1 }, /* xev */
    { NULL,             NULL,     "OpenSSH Authentication Passphrase Request",            0,         0,          0,           1,        -1 },

};


/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

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
static const char *dmenucmd[] = { "dmenu_run", "-c", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };

static const char *dwmblocksconfigcmd[] = { "st", "nvim", "code/dwmblocks/config.h", NULL };


#include "selfrestart.c"
#include <X11/XF86keysym.h>

static Key keys[] = {
    /* modifier                     key        function        argument */
    { MODKEY|ShiftMask,             XK_Return, spawn,          {.v = dmenucmd } },
    { MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
    { MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
    { Mod1Mask,                     XK_Return, zoom,           {0} },
    { MODKEY,                       XK_grave,  togglescratch,  {.v = scratchpadcmd } }, //open scratchpad
    { MODKEY|ShiftMask,             XK_t,      spawn,          SHCMD("todo") },
    { MODKEY|ShiftMask,             XK_w,      spawn,          SHCMD("worktodo") },
    { MODKEY|ShiftMask,             XK_p,      spawn,          SHCMD("scrotclip -c") },
    { MODKEY,                       XK_p,      spawn,          SHCMD("scrotclip /home/josh/pictures") },
    { MODKEY|ShiftMask,             XK_m,      spawn,          SHCMD("manmenu") },
    { MODKEY|ShiftMask,             XK_e,      spawn,          SHCMD("dmenuunicode") },
    { MODKEY,                       XK_u,      spawn,          SHCMD("dmmount") },
    { MODKEY|ShiftMask,             XK_u,      spawn,          SHCMD("dmumount") },
    { MODKEY|ControlMask,           XK_u,      spawn,          SHCMD("dmumount -l") },
    { MODKEY|ShiftMask,             XK_c,      spawn,          SHCMD("calendar") },
    { MODKEY,                       XK_x,      spawn,          SHCMD("xkill") },
    { MODKEY,                       XK_b,      spawn,          SHCMD("firefox") },
    { MODKEY,                       XK_m,      spawn,          SHCMD("st -t mail -e neomutt") },
    { MODKEY,                       XK_r,      spawn,          SHCMD("st -t rss -e newsboat") },
    { MODKEY,                       XK_s,      spawn,          SHCMD("mailsync") },

    /* Multimedia */
    { 0,                            XF86XK_AudioLowerVolume , spawn, SHCMD("amixer -q set Master 2%- unmute; kill -44 $(pidof dwmblocks)") },
    { 0,                            XF86XK_AudioRaiseVolume , spawn, SHCMD("amixer -q set Master 2%+ unmute; kill -44 $(pidof dwmblocks)") },
    { 0,                            XF86XK_AudioMute        , spawn, SHCMD("amixer -q set Master toggle; kill -44 $(pidof dwmblocks)") },
    { 0,                            XF86XK_MonBrightnessUp  , spawn, SHCMD("xbacklight -inc 2.5; kill -45 $(pidof dwmblocks)") },
    { 0,                            XF86XK_MonBrightnessDown, spawn, SHCMD("xbacklight -dec 2.5; kill -45 $(pidof dwmblocks)") },
    { 0,                            XF86XK_Mail             , spawn, SHCMD("xbacklight -inc 2.5; kill -45 $(pidof dwmblocks)") }, //brightness up for velocifire
    { 0,                            XF86XK_Tools            , spawn, SHCMD("xbacklight -dec 2.5; kill -45 $(pidof dwmblocks)") }, //brightness up for velocifire

    /* Window manipulation */
    { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } }, //send window to tag
    { MODKEY,                       XK_c,      killclient,     {0} }, //kill window

    /* Stack manipulation */
    { MODKEY,                       XK_j,      focusstack,     {.i = +1 } }, //move up through window stack
    { MODKEY,                       XK_k,      focusstack,     {.i = -1 } }, //move down through window stack
    { MODKEY,                       XK_space,  focusstack,     {.i = -1 } }, //move down through window stack
    { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} }, //resize horizontally
    { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} }, //resize horizontally
    { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
    { MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
    { MODKEY|ShiftMask,             XK_j,      rotatestack,    {.i = +1 } },
    { MODKEY|ShiftMask,             XK_k,      rotatestack,    {.i = -1 } },

    /* Layout manipulation */
    { MODKEY|ShiftMask,             XK_space,  setlayout,      {0} },
    { MODKEY|ControlMask,           XK_space,  togglefloating, {0} }, //toggle floating for selected window
    { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
    { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
    { MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[2]} },

    /* Monitor manipulation */
    { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
    { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

    /* dwm controls */
    { MODKEY,                       XK_q,      spawn,          SHCMD("light-locker-command -l") }, //lock screen
    { MODKEY|ShiftMask,             XK_q,      quit,           {0} }, //quit out of dwm
    { MODKEY|ShiftMask,             XK_r,      quit,           {1} }, //restart dwm

    /* Tag Keys */
    { MODKEY,                       XK_Tab,    view,           {0} }, //back and forth between tags
    { MODKEY,                       XK_0,      view,           {.ui = ~0 } }, //view all tags
    TAGKEYS(                        XK_1,                      0)
    TAGKEYS(                        XK_2,                      1)
    TAGKEYS(                        XK_3,                      2)
    TAGKEYS(                        XK_4,                      3)
    TAGKEYS(                        XK_5,                      4)
    TAGKEYS(                        XK_6,                      5)
    TAGKEYS(                        XK_7,                      6)
    TAGKEYS(                        XK_8,                      7)
    TAGKEYS(                        XK_9,                      8)
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
    { ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} },
    { ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} },
    { ClkStatusText,        ShiftMask,      Button1,        sigdwmblocks,   {.i = 6} },
    { ClkStatusText,        ShiftMask,      Button3,        spawn,          SHCMD("st -d ~/code/dwmblocks nvim ~/code/dwmblocks/config.h") },
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

