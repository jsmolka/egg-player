#include "shortcut.hpp"

/*
 * Creates the hook.
 */
void Shortcut::create()
{
    if (hook)
        return;

    loadShortcuts();

    hook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, GetModuleHandle(NULL), 0);
}

/*
 * Loads shortcuts from config.
 */
void Shortcut::loadShortcuts()
{

}

/*
 * Function which gets called on every keypress
 *
 * :param nCode: information about wParam and lParam
 * :param wParam: identifier of keyboard message
 * :param lParam: pointer to KBDLLHOOKSTRUCT
 * :return: exit code
 */
LRESULT CALLBACK Shortcut::LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    KBDLLHOOKSTRUCT *kbdStruct = reinterpret_cast<KBDLLHOOKSTRUCT *>(lParam);
    //bool alt = GetAsyncKeyState(VK_RMENU);//kbdStruct->flags & LLKHF_ALTDOWN;

    if (nCode == HC_ACTION && wParam == WM_KEYDOWN)
    {
        DWORD key = kbdStruct->vkCode;
        bool shift = GetAsyncKeyState(VK_SHIFT) != 0;
        bool ctrl = GetAsyncKeyState(VK_CONTROL) != 0;
        bool alt = GetAsyncKeyState(VK_MENU) != 0;
        Keyboard current(key, shift, ctrl, alt);
        qDebug() << current.key << current.shift << current.ctrl << current.alt << altgr;


    }
    return CallNextHookEx(hook, nCode, wParam, lParam);
}

bool Shortcut::isShiftDown()
{
    return GetAsyncKeyState(VK_SHIFT) != 0;
}

bool Shortcut::isCtrlDown()
{
    return GetAsyncKeyState(VK_CONTROL) != 0;
}

bool Shortcut::isAltDown(KBDLLHOOKSTRUCT *kbdStruct)
{
    return false;
}

/*
 * Pointer to the created hook.
 */
HHOOK Shortcut::hook = nullptr;
