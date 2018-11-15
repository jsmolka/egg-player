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
    connect(&m_playPause, &Shortcut::activated, &ShortcutProcessor::playPauseAction);
    connect(&m_next, &Shortcut::activated, &ShortcutProcessor::nextAction);
    connect(&m_previous, &Shortcut::activated, &ShortcutProcessor::previousAction);
    connect(&m_volumeUp, &Shortcut::activated, &ShortcutProcessor::volumeUpAction);
    connect(&m_volumeDown, &Shortcut::activated, &ShortcutProcessor::volumeDownAction);
}

void ShortcutProcessor::playPauseAction()
{
    if (egg_player.playlist().isEmpty())
        return;

    if (egg_player.isPlaying())
        egg_player.pause();
    else
        egg_player.play();
}

void ShortcutProcessor::nextAction()
{
    if (egg_player.playlist().isEmpty())
        return;

    egg_player.playlist().next();
}

void ShortcutProcessor::previousAction()
{
    if (egg_player.playlist().isEmpty())
        return;

    if (egg_player.position() <= cfg_player.previousLimit())
        egg_player.playlist().previous();
    else
        egg_player.setPosition(0);
}

void ShortcutProcessor::volumeUpAction()
{
    egg_player.setVolume(egg_player.volume() + cfg_shortcut.volumeStep());
}

void ShortcutProcessor::volumeDownAction()
{
    egg_player.setVolume(egg_player.volume() - cfg_shortcut.volumeStep());
}
