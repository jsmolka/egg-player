#include "playpausebutton.hpp"

#include "constants.hpp"
#include "iconfactory.hpp"
#include "player.hpp"

PlayPauseButton::PlayPauseButton(QWidget *parent)
    : IconButton(parent)
    , m_icon(Play)
{
    setIcons({
        IconFactory::make(ICO_PLAY),
        IconFactory::make(ICO_PAUSE)
    });

    updateIcon();
    connect(ePlayer, &Player::stateChanged, this, &PlayPauseButton::updateIcon);
}

void PlayPauseButton::setIcon(PlayPauseButton::Icon icon)
{
    m_icon = icon;

    switch (icon)
    {
    case Play:
        return setIconIndex(0);
    case Pause:
        return setIconIndex(1);
    }
}

PlayPauseButton::Icon PlayPauseButton::icon() const
{
    return m_icon;
}

void PlayPauseButton::updateIcon()
{
    setIcon(ePlayer->isPlaying() ? Pause : Play);
}
