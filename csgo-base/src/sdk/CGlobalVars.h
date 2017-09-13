#pragma once
// credits: Alvy Piper@https://github.com/AlvyPiper Copyright 2015
struct CGlobalVars
{
    float realtime;
    int framecount;
    float absoluteframetime;
    float absoluteframestarttimestddev;
    float curtime;
    float frametime;
    int maxclients;
    int tickcount;
    float interval_per_tick;
    float interpolation_amount;
    int simTicksThisFrame;
    int network_protocol;
    char pad00[14];
};
extern CGlobalVars *g_pGlobals;