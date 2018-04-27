#include "shortcut.hpp"

/*
 * Creates the hook and loads shortcuts.
 */
void Shortcut::create()
{
    if (hook)
        return;

    scPlayPause = parseShortcut(Config::SPlayPause(), PlayPause);
    scNext = parseShortcut(Config::SNext(), Next);
    scBack = parseShortcut(Config::SBack(), Back);
    scVolumeUp = parseShortcut(Config::SVolumeUp(), VolumeUp);
    scVolumeDown = parseShortcut(Config::SVolumeDown()), VolumeDown;

    hook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, GetModuleHandle(NULL), 0);
}

/*
 * Parses the shortcut and returns the equivalent
 * Keyboard structure.
 *
 * :param shortcut: shortcut
 * :param media: type of shortcut
 * :param keyboard: keyboard
 */
Shortcut::Keyboard Shortcut::parseShortcut(const QString &shortcut, Media media)
{
    int vk = 0;
    bool shift = false;
    bool ctrl = false;
    bool alt = false;

    QStringList keys = shortcut.toUpper().split("+");
    if (keys.isEmpty())
        Logger::log("Shortcut: Shortcut is empty");

    for (const QString &key : keys)
    {
        if (!keyMap.contains(key))
        {
            vk = 0;
            break;
        }

        if (key.compare("SHIFT") == 0)
        {
            shift = true;
            continue;
        }
        if (key.compare("CTRL") == 0)
        {
            ctrl = true;
            continue;
        }
        if (key.compare("ALT") == 0)
        {
            alt = true;
            continue;
        }

        if (key.compare("MEDIA") == 0)
        {
            switch (media)
            {
                case PlayPause:
                    vk = VK_MEDIA_PLAY_PAUSE;
                    break;
                case Next:
                    vk = VK_MEDIA_NEXT_TRACK;
                    break;
                case Back:
                    vk = VK_MEDIA_PREV_TRACK;
                    break;
                case VolumeUp:
                    vk = VK_VOLUME_UP;
                    break;
                case VolumeDown:
                    vk = VK_VOLUME_DOWN;
                    break;
            }
        }
        else
        {
            vk = keyMap.value(key);
        }
    }

    if (vk == 0)
        Logger::log("Shortcut: Cannot parse shortcut '%1'", shortcut);

    return Keyboard(vk, shift, ctrl, alt);
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
    if (nCode == HC_ACTION && wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)
    {
        KBDLLHOOKSTRUCT *kbdStruct = reinterpret_cast<KBDLLHOOKSTRUCT *>(lParam);

        DWORD vk = kbdStruct->vkCode;
        bool shift = GetAsyncKeyState(VK_SHIFT) != 0;
        bool ctrl = GetAsyncKeyState(VK_CONTROL) != 0;
        bool alt = GetAsyncKeyState(VK_MENU) != 0;

        Keyboard current(vk, shift, ctrl, alt);

        Player *player = Player::currentInstance();
        if (player)
        {
            if (current == scPlayPause)
                player->isPlaying() ? player->pause() : player->play();
            if (current == scNext)
                player->next();
            if (current == scBack)
                player->back();
            if (current == scVolumeUp)
                player->setVolume(player->volume() + 1);
            if (current == scVolumeDown)
                player->setVolume(player->volume() - 1);
        }
    }
    return CallNextHookEx(hook, nCode, wParam, lParam);
}

/*
 * Pointer to the created hook.
 */
HHOOK Shortcut::hook = nullptr;

/*
 * Map key string to int.
 */
const QHash<QString, int> Shortcut::keyMap =
{
    {"MEDIA"    , 0x0000},  // Placeholder for media keys
    {"CANCEL"   , 0x0001},
    {"BACK"     , 0x0008},
    {"TAB"      , 0x0009},
    {"CLEAR"    , 0x000C},
    {"ENTER"    , 0x000D},
    {"SHIFT"    , 0x0010},
    {"CTRL"     , 0x0011},
    {"ALT"      , 0x0012},
    {"PAUSE"    , 0x0013},
    {"CAPS"     , 0x0014},
    {"ESC"      , 0x001B},
    {"SPACE"    , 0x0020},
    {"PAGEUP"   , 0x0021},
    {"PAGEDOWN" , 0x0022},
    {"END"      , 0x0023},
    {"HOME"     , 0x0024},
    {"LEFT"     , 0x0025},
    {"UP"       , 0x0026},
    {"RIGHT"    , 0x0027},
    {"DOWN"     , 0x0028},
    {"SELECT"   , 0x0029},
    {"PRINT"    , 0x002A},
    {"EXECUTE"  , 0x002B},
    {"SNAPSHOT" , 0x002C},
    {"INSERT"   , 0x002D},
    {"DELETE"   , 0x002E},
    {"HELP"     , 0x002F},
    {"0"        , 0x0030},
    {"1"        , 0x0031},
    {"2"        , 0x0032},
    {"3"        , 0x0033},
    {"4"        , 0x0034},
    {"5"        , 0x0035},
    {"6"        , 0x0036},
    {"7"        , 0x0037},
    {"8"        , 0x0038},
    {"9"        , 0x0039},
    {"A"        , 0x0041},
    {"B"        , 0x0042},
    {"C"        , 0x0043},
    {"D"        , 0x0044},
    {"E"        , 0x0045},
    {"F"        , 0x0046},
    {"G"        , 0x0047},
    {"H"        , 0x0048},
    {"I"        , 0x0049},
    {"J"        , 0x004A},
    {"K"        , 0x004B},
    {"L"        , 0x004C},
    {"M"        , 0x004D},
    {"N"        , 0x004E},
    {"O"        , 0x004F},
    {"P"        , 0x0050},
    {"Q"        , 0x0051},
    {"R"        , 0x0052},
    {"S"        , 0x0053},
    {"T"        , 0x0054},
    {"U"        , 0x0055},
    {"V"        , 0x0056},
    {"W"        , 0x0057},
    {"X"        , 0x0058},
    {"Y"        , 0x0059},
    {"Z"        , 0x005A},
    {"NUM0"     , 0x0060},
    {"NUM1"     , 0x0061},
    {"NUM2"     , 0x0062},
    {"NUM3"     , 0x0063},
    {"NUM4"     , 0x0064},
    {"NUM5"     , 0x0065},
    {"NUM6"     , 0x0066},
    {"NUM7"     , 0x0067},
    {"NUM8"     , 0x0068},
    {"NUM9"     , 0x0069},
    {"MUL"      , 0x006A},
    {"ADD"      , 0x006B},
    {"SEP"      , 0x006C},
    {"SUB"      , 0x006D},
    {"DEC"      , 0x006E},
    {"DIV"      , 0x006F},
    {"F1"       , 0x0070},
    {"F2"       , 0x0071},
    {"F3"       , 0x0072},
    {"F4"       , 0x0073},
    {"F5"       , 0x0074},
    {"F6"       , 0x0075},
    {"F7"       , 0x0076},
    {"F8"       , 0x0077},
    {"F9"       , 0x0078},
    {"F10"      , 0x0079},
    {"F11"      , 0x007A},
    {"F12"      , 0x007B},
    {"F13"      , 0x007C},
    {"F14"      , 0x007D},
    {"F15"      , 0x007E},
    {"F16"      , 0x007F},
    {"F17"      , 0x0080},
    {"F18"      , 0x0081},
    {"F19"      , 0x0082},
    {"F20"      , 0x0083},
    {"F21"      , 0x0084},
    {"F22"      , 0x0085},
    {"F23"      , 0x0086},
    {"F24"      , 0x0087},
    {"NUMLOCK"  , 0x0090},
    {"SCROLL"   , 0x0091}
};

/*
 * Keyboard shortcuts.
 */
Shortcut::Keyboard Shortcut::scPlayPause;
Shortcut::Keyboard Shortcut::scNext;
Shortcut::Keyboard Shortcut::scBack;
Shortcut::Keyboard Shortcut::scVolumeUp;
Shortcut::Keyboard Shortcut::scVolumeDown;
