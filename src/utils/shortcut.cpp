#include "shortcut.hpp"

/*
 * Constructor.
 *
 * :param parent: parent, default nullptr
 */
Shortcut::Shortcut(QObject *parent) :
    QObject(parent)
{

}

/*
 * Constructor.
 *
 * :param shortcut: shortcut
 * :param repeat: repeat signal while pressed
 * :param parent: parent, default nullptr
 */
Shortcut::Shortcut(const QString &shortcut, bool repeat, QObject *parent) :
    QObject(parent),
    m_shortcut(shortcut)
{
    m_count++;

    m_id = m_count;
    m_registered = registerShortcut(shortcut, repeat);

    if (m_registered)
        qApp->eventDispatcher()->installNativeEventFilter(this);
    else
        Logger::log("Shortcut: Cannot register shortcut '%1'", {shortcut});

}

/*
 * Destructor.
 */
Shortcut::~Shortcut()
{
    if (m_registered)
        unregisterShortcut();
}

/*
 * Getter for id property.
 *
 * :return: id
 */
int Shortcut::id() const
{
    return m_id;
}

/*
 * Getter for registered property.
 *
 * :return: registered
 */
bool Shortcut::isRegistered() const
{
    return m_registered;
}

/*
 * Getter for shortcut property.
 *
 * :return: shortcut
 */
QString Shortcut::shortcut() const
{
    return m_shortcut;
}

/*
 * Event filter.
 *
 * :param eventType: eventType
 * :param message: message
 * :param result: result
 * :emit pressed: pressed
 * :return: false
 */
bool Shortcut::nativeEventFilter(const QByteArray &eventType, void *message, long *result)
{
    Q_UNUSED(eventType);
    Q_UNUSED(result);

    MSG* msg = static_cast<MSG *>(message);
    if (msg->message == WM_HOTKEY && msg->wParam == m_id)
        emit pressed();

    return false;
}

/*
 * Parses a shortcut.
 *
 * :param shortcut: shortcut
 * :return: combination
 */
Shortcut::Combination Shortcut::parseShortcut(const QString &shortcut)
{
    UINT vk = 0;
    UINT modifier = 0;

    QStringList keys = shortcut.toUpper().replace(" ", "").split("+");
    for (const QString &key : keys)
    {
        if (!m_map.contains(key))
        {
            vk = 0;
            break;
        }
        if (key.compare("SHIFT") == 0)
        {
            modifier |= MOD_SHIFT;
            continue;
        }
        if (key.compare("CTRL") == 0)
        {
            modifier |= MOD_CONTROL;
            continue;
        }
        if (key.compare("ALT") == 0)
        {
            modifier |= MOD_ALT;
            continue;
        }

        vk = m_map.value(key);
    }
    return Combination(vk, modifier);
}

/*
 * Registers a shortcut.
 *
 * :param repeat: repeat signal while pressed
 * :param combination: combination
 * :return: success
 */
bool Shortcut::registerShortcut(const QString &shortcut, bool repeat)
{
    Combination combination = parseShortcut(shortcut);

    if (!combination.isValid())
        return false;

    if (!repeat)
        combination.modifier |= MOD_NOREPEAT;

    return (bool) RegisterHotKey(NULL, m_id, combination.modifier, combination.vk);
}

/*
 * Unregisters shortcut.
 *
 * :return: success
 */
bool Shortcut::unregisterShortcut()
{
    return (bool) UnregisterHotKey(NULL, m_id);
}

/*
 * Counts the number of instances and is the
 * identifier for each shortcut.
 */
int Shortcut::m_count = 0;

/*
 * Map key string to int.
 */
const QHash<QString, int> Shortcut::m_map =
{
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
