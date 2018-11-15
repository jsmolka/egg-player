#ifndef SHORTCUTPROCESSOR_HPP
#define SHORTCUTPROCESSOR_HPP

#include "core/shortcut.hpp"

class ShortcutProcessor : public QObject
{
    Q_OBJECT

public:
    explicit ShortcutProcessor(QObject *parent = nullptr);

public slots:
    static void playPauseAction();
    static void nextAction();
    static void previousAction();
    static void volumeUpAction();
    static void volumeDownAction();

private:
    Shortcut m_playPause;
    Shortcut m_next;
    Shortcut m_previous;
    Shortcut m_volumeUp;
    Shortcut m_volumeDown;
};

#endif // SHORTCUTPROCESSOR_HPP
