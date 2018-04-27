#ifndef SHORTCUT_HPP
#define SHORTCUT_HPP

#include <Windows.h>

#include <QHash>
#include <QStringList>

#include "logger.hpp"
#include "player.hpp"

class Shortcut
{
public:
    static void create();

private:
    struct Keyboard
    {
        Keyboard()
        {
            vk = 0;
            shift = false;
            ctrl = false;
            alt = false;
        }

        Keyboard(DWORD vk, bool shift, bool ctrl, bool alt)
        {
            this->vk = vk;
            this->shift = shift;
            this->ctrl = ctrl;
            this->alt = alt;
        }

        bool operator ==(const Keyboard kb)
        {
            return vk == kb.vk && shift == kb.shift && ctrl == kb.ctrl && alt == kb.alt;
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
