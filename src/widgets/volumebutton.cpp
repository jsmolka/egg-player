#include "volumebutton.hpp"

#include "core/constants.hpp"
#include "core/iconcreator.hpp"
#include "core/player.hpp"

VolumeButton::VolumeButton(QWidget *parent)
    : IconButton(parent)
{
    setIcons(IconCreator::create(
        QStrings()
            << constants::ico::volume::Full
            << constants::ico::volume::Medium
            << constants::ico::volume::Low
            << constants::ico::volume::Mute
    ));
    updateIcon(egg_player.volume());

    connect(&egg_player, &Player::volumeChanged, this, &VolumeButton::updateIcon);
}

void VolumeButton::setIcon(Icon icon)
{
    m_icon = icon;

    switch (icon)
    {
    case Icon::VolumeFull:
        return setIconIndex(0);

    case Icon::VolumeMedium:
        return setIconIndex(1);

    case Icon::VolumeLow:
        return setIconIndex(2);

    case Icon::VolumeMute:
        return setIconIndex(3);
    }
}

VolumeButton::Icon VolumeButton::icon() const
{
    return m_icon;
}

void VolumeButton::updateIcon(int volume)
{
    if (volume == 0)
        return setIcon(Icon::VolumeMute);
    if (volume <= 33)
        return setIcon(Icon::VolumeLow);
    if (volume <= 66)
        return setIcon(Icon::VolumeMedium);

    setIcon(Icon::VolumeFull);
}
