/*********************************************************************************/
/*!
@file           Cfg.h

@brief          Contains all the configuration Information.

@author         L. J. Barman

    Copyright (c)   2008-2020, L. J. Barman and others, all rights reserved

    This file is part of the PianoBooster application

    PianoBooster is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    PianoBooster is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with PianoBooster.  If not, see <http://www.gnu.org/licenses/>.

*/
/*********************************************************************************/

#ifndef __CFG_H__
#define __CFG_H__

#define OPTION_BENCHMARK_TEST     0
#if OPTION_BENCHMARK_TEST
#define BENCHMARK_INIT()        benchMarkInit()
#define BENCHMARK(id,mesg)      benchMark(id,mesg)
#define BENCHMARK_RESULTS()     benchMarkResults()
#else
#define BENCHMARK_INIT()
#define BENCHMARK(id,mesg)
#define BENCHMARK_RESULTS()
#endif

#define LOG_LEVEL_NONE  0
#define LOG_LEVEL_INFO  1
#define LOG_LEVEL_WARN  2
#define LOG_LEVEL_DEBUG 3

class CColor
{
public:
    constexpr CColor()
        : red(0.0f)
        , green(0.0f)
        , blue(0.0f)
    {}

    constexpr CColor(float r, float g, float b)
        : red(r)
        , green(g)
        , blue(b)
    {}

    constexpr CColor(double r, double g, double b)
        : red(static_cast<float>(r))
        , green(static_cast<float>(g))
        , blue(static_cast<float>(b))
    {}

    constexpr bool operator==(CColor color)
    {
        return red == color.red && green == color.green && blue == color.blue;
    }

    float red, green, blue;
};

enum class BuiltInColorTheme {
    Default,
    Light,
};

struct ColorTheme
{
    constexpr ColorTheme() = default;
    ColorTheme &operator=(const ColorTheme &other) = default;
    void load(BuiltInColorTheme builtInColorTheme);

    CColor menuColor          = CColor(0.1, 0.6, 0.6);
    CColor menuSelectedColor  = CColor(0.7, 0.7, 0.1);

    CColor staveColor         = CColor(0.1, 0.7, 0.1);     // green
    CColor staveColorDim      = CColor(0.15, 0.40, 0.15);  // grey
    CColor noteColor          = CColor(0.1, 0.9, 0.1);     // green
    CColor noteColorDim       = CColor(0.25, 0.45, 0.25);  // green
    CColor playedGoodColor    = CColor(0.5, 0.6, 1.0);     // purple
    CColor playedBadColor     = CColor(0.8, 0.3, 0.8);     // orange
    CColor playedStoppedColor = CColor(1.0, 0.8, 0.0);     // bright orange
    CColor backgroundColor    = CColor(0.0, 0.0, 0.0);     // black
    CColor barMarkerColor     = CColor(0.3, 0.25, 0.25);   // grey
    CColor beatMarkerColor    = CColor(0.25, 0.2, 0.2);    // grey
    CColor pianoGoodColor     = playedGoodColor;
    CColor pianoBadColor      = CColor(1.0, 0.0, 0.0);
    CColor noteNameColor      = CColor(1.0, 1.0, 1.0);
    CColor playingZoneBg      = CColor(0.0f, 0.0f, 0.3f);
    CColor playingZoneMiddle  = CColor(0.0f, 0.0f, 0.8f);
    CColor playingZoneBorder  = CColor(0.0f, 0.0f, 0.6f);
    CColor textColor          = CColor(1.0f, 1.0f, 1.0f);
};

/*!
 * @brief   Contains all the configuration Information.
 */
class Cfg
{
public:
    static float staveStartX()         {return 20;}
    static float staveEndX()           {return m_staveEndX;}
    static float playZoneX()           {return scrollStartX() + ( staveEndX() - scrollStartX())* 0.4f;}
    static float clefX()               {return staveStartX() + 20;}
    static float timeSignatureX()       {return clefX() + 25;}
    static float keySignatureX()       {return timeSignatureX() + 25;}
    static float scrollStartX()        {return keySignatureX() + 64;}
    static float pianoX()              {return 25;}

    static float staveThickness()      {return 1;}

    static int playZoneEarly()     {return m_playZoneEarly;}
    static int playZoneLate()      {return m_playZoneLate;}
    static int silenceTimeOut()    {return 8000;} // the time in msec before everything goes quiet
    static int chordNoteGap()      {return 10;} // all notes in a cord must be spaced less than this a gap
    static int chordMaxLength()    {return 20;} // the max time between the start and end of a cord

    static const ColorTheme &colorTheme() { return m_colorTheme; }
    static void loadColorTheme(BuiltInColorTheme builtInColorTheme) { m_colorTheme.load(builtInColorTheme); }

    static void setDefaults() {
    #ifdef _WIN32
         tickRate = 12;
    #else
          tickRate = 4; // was 12
    #endif
    }

    static void setStaveEndX(float x)
    {
         m_staveEndX = x;
    }
    static int getAppX(){return m_appX;}
    static int getAppY(){return m_appY;}
    static int getAppWidth(){return m_appWidth;}
    static int getAppHeight(){return m_appHeight;}
    static void setAppDimentions(int x, int y,int width, int height)
    {
        m_appX = x;
        m_appY = y;
        m_appWidth = width;
        m_appHeight = height;
    }

    static int defaultWrongPatch() {return 7;} // Starts at 1
    static int defaultRightPatch() {return 1;} // Starts at 1

    static int logLevel;
    static bool experimentalTempo;
    static bool experimentalNoteLength;
    static int experimentalSwapInterval;
    static int tickRate;
    static bool useLogFile;
    static bool midiInputDump;
    static int keyboardLightsChan;

private:
    static float m_staveEndX;
    static int m_appX, m_appY, m_appWidth, m_appHeight;
    static const int m_playZoneEarly;
    static const int m_playZoneLate;
    static ColorTheme m_colorTheme;
};

#endif //__CFG_H__
