#ifndef SHORTCUT_HPP
#define SHORTCUT_HPP

#include <Windows.h>

#include "logger.hpp"
#include "player.hpp"

class Shortcut
{
public:
    static void create();

private:
    struct Keyboard
    {
        Keyboard(DWORD key, bool shift, bool ctrl, bool alt)
        {
            this->key = key;
            this->shift = shift;
            this->ctrl = ctrl;
            this->alt = alt;
        }

        bool operator ==(const Keyboard kb)
        {
            return key == kb.key && shift == kb.shift && ctrl == kb.ctrl && alt == kb.alt;
        }

        DWORD key;
        bool shift;
        bool ctrl;
        bool alt;
    };

    static void loadShortcuts();
    static LRESULT LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);

    static bool isShiftDown();
    static bool isCtrlDown();
    static bool isAltDown(KBDLLHOOKSTRUCT *kbdStruct);

    static HHOOK hook;
};

#endif // SHORTCUT_HPP
