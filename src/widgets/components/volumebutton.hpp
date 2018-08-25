#ifndef VOLUMEBUTTON_HPP
#define VOLUMEBUTTON_HPP

#include "iconbutton.hpp"

class VolumeButton : public IconButton
{
public:
    explicit VolumeButton(QWidget *parent = nullptr);

    enum Icon {VolumeFull, VolumeMedium, VolumeLow, VolumeMute};

    void setIcon(VolumeButton::Icon icon);
    VolumeButton::Icon icon() const;

    void setVolume(int volume);

private:
    Icon m_icon;
};

#endif // VOLUMEBUTTON_HPP
