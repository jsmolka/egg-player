#include "shortcutprocessor.hpp"

#include "core/config.hpp"
#include "core/player.hpp"

ShortcutProcessor::ShortcutProcessor(QObject *parent)
    : QObject(parent)
    , m_playPause(cfg_shortcut.playPause(), Shortcut::NoRepeat, this)
    , m_next(cfg_shortcut.next(), Shortcut::NoRepeat, this)
    , m_previous(cfg_shortcut.previous(), Shortcut::NoRepeat, this)
    , m_volumeUp(cfg_shortcut.volumeUp(), Shortcut::Repeat, this)
    , m_volumeDown(cfg_shortcut.volumeDown(), Shortcut::Repeat, this)
{
    connect(&m_playPause, &Shortcut::pressed, &ShortcutProcessor::onPlayPausePressed);
    connect(&m_next, &Shortcut::pressed, &ShortcutProcessor::onNextPressed);
    connect(&m_previous, &Shortcut::pressed, &ShortcutProcessor::onPreviousPressed);
    connect(&m_volumeUp, &Shortcut::pressed, &ShortcutProcessor::onVolumeUpPressed);
    connect(&m_volumeDown, &Shortcut::pressed, &ShortcutProcessor::onVolumeDownPressed);
}

void ShortcutProcessor::onPlayPausePressed()
{
    if (egg_player.playlist().isEmpty())
        return;

    if (egg_player.isPlaying())
        egg_player.pause();
    else
        egg_player.play();
}

void ShortcutProcessor::onNextPressed()
{
    if (egg_player.playlist().isEmpty())
        return;

    egg_player.playlist().next();
}

void ShortcutProcessor::onPreviousPressed()
{
    if (egg_player.playlist().isEmpty())
        return;

    if (egg_player.position() <= cfg_player.previousLimit())
        egg_player.playlist().previous();
    else
        egg_player.setPosition(0);
}

void ShortcutProcessor::onVolumeUpPressed()
{
    egg_player.setVolume(egg_player.volume() + 1);
}

void ShortcutProcessor::onVolumeDownPressed()
{
    egg_player.setVolume(egg_player.volume() - 1);
}
