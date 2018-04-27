#ifndef SHORTCUT_HPP
#define SHORTCUT_HPP

#include <Windows.h>

#include <QHash>
#include <QStringList>

#include "logger.hpp"
#include "player.hpp"

#include <QDebug>

class Shortcut
{
public:
    static void create();

private:
    struct Keyboard
    {
        Keyboard(DWORD vk = 0, bool shift = false, bool ctrl = false, bool alt = false)
        {
            this->vk = vk;
            this->shift = shift;
            this->ctrl = ctrl;
            this->alt = alt;
        }

        bool operator ==(const Keyboard kb)
        {
            bool result = vk == kb.vk;
            if (shift)
                result = result && shift == kb.shift;
            if (ctrl)
                result = result && ctrl == kb.ctrl;
            if (alt)
                result = result && alt == kb.alt;
            return result;
        }

        DWORD vk;
        bool shift;
        bool ctrl;
        bool alt;
    };

    enum Media {None, PlayPause, Next, Back, VolumeUp, VolumeDown};

    static Keyboard parseShortcut(const QString &shortcut, Media media = None);
    static LRESULT LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);

    static HHOOK hook;
    static const QHash<QString, int> keyMap;

    static Keyboard scPlayPause;
    static Keyboard scNext;
    static Keyboard scBack;
    static Keyboard scVolumeUp;
    static Keyboard scVolumeDown;
};

#endif // SHORTCUT_HPP
