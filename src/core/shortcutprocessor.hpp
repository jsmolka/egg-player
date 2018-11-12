#ifndef SHORTCUTPROCESSOR_HPP
#define SHORTCUTPROCESSOR_HPP

#include "core/shortcut.hpp"

class ShortcutProcessor : public QObject
{
    Q_OBJECT

public:
    explicit ShortcutProcessor(QObject *parent = nullptr);

public slots:
    static void onPlayPausePressed();
    static void onNextPressed();
    static void onPreviousPressed();
    static void onVolumeUpPressed();
    static void onVolumeDownPressed();

private:
    Shortcut m_playPause;
    Shortcut m_next;
    Shortcut m_previous;
    Shortcut m_volumeUp;
    Shortcut m_volumeDown;
};

#endif // SHORTCUTPROCESSOR_HPP
