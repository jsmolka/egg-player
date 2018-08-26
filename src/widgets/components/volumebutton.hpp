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

private slots:
    void updateIcon(int volume);

private:
    VolumeButton::Icon m_icon;
};

#endif // VOLUMEBUTTON_HPP
