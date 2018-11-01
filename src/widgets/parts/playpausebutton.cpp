#include "playpausebutton.hpp"

#include "core/globals.hpp"
#include "core/player.hpp"
#include "widgets/parts/iconfactory.hpp"

PlayPauseButton::PlayPauseButton(QWidget *parent)
    : IconButton(parent)
{
    setIcons(IconFactory::make(
        QStrings()
            << ICO_PLAY
            << ICO_PAUSE
    ));
    updateIcon();

    connect(ePlayer, &Player::stateChanged, this, &PlayPauseButton::updateIcon);
}

void PlayPauseButton::setIcon(Icon icon)
{
    m_icon = icon;

    switch (icon)
    {
    case Icon::Play:
        return setIconIndex(0);

    case Icon::Pause:
        return setIconIndex(1);
    }
}

PlayPauseButton::Icon PlayPauseButton::icon() const
{
    return m_icon;
}

void PlayPauseButton::updateIcon()
{
    setIcon(ePlayer->isPlaying() ? Icon::Pause : Icon::Play);
}
