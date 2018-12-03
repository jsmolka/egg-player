#include "shortcut.hpp"

#include <QApplication>
#include <QAbstractEventDispatcher>

#include "core/logger.hpp"

Shortcut::Shortcut(const QString &shortcut, RepeatPolicy repeat, QObject *parent)
    : QObject(parent)
    , m_id(++s_id)
    , m_shortcut(shortcut)
    , m_modifier(0)
    , m_vk(0)
    , m_registered(false)
{
    parseShortcut(shortcut, repeat);

    registerShortcut();

    if (m_registered)
        qApp->eventDispatcher()->installNativeEventFilter(this);
}

Shortcut::~Shortcut()
{
    if (m_registered)
        unregisterShortcut();
}

QString Shortcut::shortcut() const
{
    return m_shortcut;
}

bool Shortcut::isRegistered() const
{
    return m_registered;
}

bool Shortcut::nativeEventFilter(const QByteArray &eventType, void *message, long *result)
{
    Q_UNUSED(eventType);
    Q_UNUSED(result);

    MSG *msg = static_cast<MSG *>(message);
    if (msg->message == WM_HOTKEY
            && static_cast<int>(msg->wParam) == m_id)
        emit activated();

    return false;
}

QStringList Shortcut::createSequence(const QString &shortcut)
{
    return shortcut.toUpper().replace(" ", "").split("+", QString::SkipEmptyParts);
}

UINT Shortcut::parseSequence(const QStringList &sequence, const KeyHash &keys)
{
    UINT vk = 0;
    for (const QString &key : sequence)
    {
        if (keys.contains(key))
            vk |= keys.value(key);
    }
    return vk;
}

void Shortcut::parseShortcut(const QString &shortcut, RepeatPolicy repeat)
{
    const QStringList sequence = createSequence(shortcut);

    m_vk = parseSequence(sequence, s_keys);
    m_modifier = parseSequence(sequence, s_modifiers);

    if (m_vk == 0 || m_modifier == 0)
        egg_log() << "Cannot parse shortcut" << shortcut;

    if (repeat == RepeatPolicy::NoRepeat)
        m_modifier |= MOD_NOREPEAT;
}

void Shortcut::registerShortcut()
{
    m_registered = RegisterHotKey(nullptr, m_id, m_modifier, m_vk);
    if (!m_registered)
        egg_log() << "Cannot register shortcut" << m_shortcut;
}

void Shortcut::unregisterShortcut()
{
    m_registered = UnregisterHotKey(nullptr, m_id);
    if (!m_registered)
        egg_log() << "Cannot unregister shortcut" << m_shortcut;
}

int Shortcut::s_id = 0;

const Shortcut::KeyHash Shortcut::s_keys =
{
    {"CANCEL"   , VK_CANCEL   },
    {"BACK"     , VK_BACK     },
    {"TAB"      , VK_TAB      },
    {"CLEAR"    , VK_CLEAR    },
    {"ENTER"    , VK_RETURN   },
    {"PAUSE"    , VK_PAUSE    },
    {"CAPS"     , VK_CAPITAL  },
    {"ESCAPE"   , VK_ESCAPE   },
    {"ESC"      , VK_ESCAPE   },
    {"SPACE"    , VK_SPACE    },
    {"PAGEUP"   , VK_PRIOR    },
    {"PAGEDOWN" , VK_NEXT     },
    {"END"      , VK_END      },
    {"HOME"     , VK_HOME     },
    {"LEFT"     , VK_LEFT     },
    {"UP"       , VK_UP       },
    {"RIGHT"    , VK_RIGHT    },
    {"DOWN"     , VK_DOWN     },
    {"SELECT"   , VK_SELECT   },
    {"PRINT"    , VK_PRINT    },
    {"EXECUTE"  , VK_EXECUTE  },
    {"SNAPSHOT" , VK_SNAPSHOT },
    {"INSERT"   , VK_INSERT   },
    {"DELETE"   , VK_DELETE   },
    {"HELP"     , VK_HELP     },
    {"0"        , 0x0030      },
    {"1"        , 0x0031      },
    {"2"        , 0x0032      },
    {"3"        , 0x0033      },
    {"4"        , 0x0034      },
    {"5"        , 0x0035      },
    {"6"        , 0x0036      },
    {"7"        , 0x0037      },
    {"8"        , 0x0038      },
    {"9"        , 0x0039      },
    {"A"        , 0x0041      },
    {"B"        , 0x0042      },
    {"C"        , 0x0043      },
    {"D"        , 0x0044      },
    {"E"        , 0x0045      },
    {"F"        , 0x0046      },
    {"G"        , 0x0047      },
    {"H"        , 0x0048      },
    {"I"        , 0x0049      },
    {"J"        , 0x004A      },
    {"K"        , 0x004B      },
    {"L"        , 0x004C      },
    {"M"        , 0x004D      },
    {"N"        , 0x004E      },
    {"O"        , 0x004F      },
    {"P"        , 0x0050      },
    {"Q"        , 0x0051      },
    {"R"        , 0x0052      },
    {"S"        , 0x0053      },
    {"T"        , 0x0054      },
    {"U"        , 0x0055      },
    {"V"        , 0x0056      },
    {"W"        , 0x0057      },
    {"X"        , 0x0058      },
    {"Y"        , 0x0059      },
    {"Z"        , 0x005A      },
    {"NUMPAD0"  , VK_NUMPAD0  },
    {"NUMPAD1"  , VK_NUMPAD1  },
    {"NUMPAD2"  , VK_NUMPAD2  },
    {"NUMPAD3"  , VK_NUMPAD3  },
    {"NUMPAD4"  , VK_NUMPAD4  },
    {"NUMPAD5"  , VK_NUMPAD5  },
    {"NUMPAD6"  , VK_NUMPAD6  },
    {"NUMPAD7"  , VK_NUMPAD7  },
    {"NUMPAD8"  , VK_NUMPAD8  },
    {"NUMPAD9"  , VK_NUMPAD9  },
    {"MULTIPLY" , VK_MULTIPLY },
    {"ADD"      , VK_ADD      },
    {"SEPARATOR", VK_SEPARATOR},
    {"SUBTRACT" , VK_SUBTRACT },
    {"DECIMAL"  , VK_DECIMAL  },
    {"DIVIDE"   , VK_DIVIDE   },
    {"F1"       , VK_F1       },
    {"F2"       , VK_F2       },
    {"F3"       , VK_F3       },
    {"F4"       , VK_F4       },
    {"F5"       , VK_F5       },
    {"F6"       , VK_F6       },
    {"F7"       , VK_F7       },
    {"F8"       , VK_F8       },
    {"F9"       , VK_F9       },
    {"F10"      , VK_F10      },
    {"F11"      , VK_F11      },
    {"F12"      , VK_F12      },
    {"F13"      , VK_F13      },
    {"F14"      , VK_F14      },
    {"F15"      , VK_F15      },
    {"F16"      , VK_F16      },
    {"F17"      , VK_F17      },
    {"F18"      , VK_F18      },
    {"F19"      , VK_F19      },
    {"F20"      , VK_F20      },
    {"F21"      , VK_F21      },
    {"F22"      , VK_F22      },
    {"F23"      , VK_F23      },
    {"F24"      , VK_F24      },
    {"NUMLOCK"  , VK_NUMLOCK  },
    {"SCROLL"   , VK_SCROLL   }
};

const Shortcut::KeyHash Shortcut::s_modifiers =
{
    {"CONTROL", MOD_CONTROL},
    {"CTRL"   , MOD_CONTROL},
    {"SHIFT"  , MOD_SHIFT  },
    {"ALT"    , MOD_ALT    }
};
