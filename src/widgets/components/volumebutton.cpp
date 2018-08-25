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

    setVolume(cfgPlayer.volume());
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

void VolumeButton::setVolume(int volume)
{
    volume = qBound(0, volume, 100);
    ePlayer->setVolume(volume);

    if (volume == 0)
        return setIcon(VolumeMute);
    if (volume < 34)
        return setIcon(VolumeLow);
    if (volume < 67)
        return setIcon(VolumeMedium);
    setIcon(VolumeFull);
}
