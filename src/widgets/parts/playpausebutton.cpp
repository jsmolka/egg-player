#include "playpausebutton.hpp"

#include "core/player.hpp"
#include "widgets/parts/iconfactory.hpp"

PlayPauseButton::PlayPauseButton(QWidget *parent)
    : IconButton(parent)
{
    setIcons(IconFactory::make(
        QStrings()
            << constants::ico::play
            << constants::ico::pause
    ));

    updateIcon();

    connect(&egg_player, &Player::stateChanged, this, &PlayPauseButton::updateIcon);
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
    setIcon(egg_player.isPlaying() ? Icon::Pause : Icon::Play);
}
