#ifndef VOLUMEBUTTON_HPP
#define VOLUMEBNUTTON_HPP

#include "widgets/iconbutton.hpp"

class VolumeButton : public IconButton
{
    Q_OBJECT

public:
    enum Icon {VolumeFull, VolumeMedium, VolumeLow, VolumeMute};

    explicit VolumeButton(QWidget *parent = nullptr);

    void setIcon(Icon icon);
    Icon icon() const;

private slots:
    void updateIcon(int volume);

private:
    Icon m_icon;
};

#endif // VOLUMEBUTTON_HPP
