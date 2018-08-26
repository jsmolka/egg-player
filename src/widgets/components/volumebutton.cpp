#include "volumebutton.hpp"

#include "config.hpp"
#include "constants.hpp"
#include "iconfactory.hpp"
#include "player.hpp"

VolumeButton::VolumeButton(QWidget *parent)
    : IconButton(parent)
    , m_icon(VolumeFull)
{
    setIcons({
        IconFactory::make(ICO_VOLUME_FULL),
        IconFactory::make(ICO_VOLUME_MEDIUM),
        IconFactory::make(ICO_VOLUME_LOW),
        IconFactory::make(ICO_VOLUME_MUTE)
    });

    updateIcon(ePlayer->volume());
    connect(ePlayer, &Player::volumeChanged, this, &VolumeButton::updateIcon);
}

void VolumeButton::setIcon(VolumeButton::Icon icon)
{
    m_icon = icon;

    switch (icon)
    {
    case VolumeFull:
        return setIconIndex(0);
    case VolumeMedium:
        return setIconIndex(1);
    case VolumeLow:
        return setIconIndex(2);
    case VolumeMute:
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
        return setIcon(VolumeMute);
    if (volume <= 33)
        return setIcon(VolumeLow);
    if (volume <= 66)
        return setIcon(VolumeMedium);
    setIcon(VolumeFull);
}
