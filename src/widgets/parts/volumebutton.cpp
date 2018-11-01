#include "volumebutton.hpp"

#include "core/globals.hpp"
#include "core/player.hpp"
#include "widgets/parts/iconfactory.hpp"

VolumeButton::VolumeButton(QWidget *parent)
    : IconButton(parent)
{
    setIcons(IconFactory::make(
        QStrings()
            << ICO_VOLUME_FULL
            << ICO_VOLUME_MEDIUM
            << ICO_VOLUME_LOW
            << ICO_VOLUME_MUTE
    ));
    updateIcon(ePlayer->volume());

    connect(ePlayer, &Player::volumeChanged, this, &VolumeButton::updateIcon);
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
